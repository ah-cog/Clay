/*
 * TCP_Receiver.c
 *
 *  Created on: Mar 2, 2016
 *      Author: thebh_000
 */
/*
 * States:
 *      Disable -- No receiving occurs.
 *          -Go to configure when enable received
 *      Configure -- set up serial port, interrupts, etc
 *          -Go to Idle upon completion
 *      Idle
 *          -Watch for received data.
 *          -Go to Disable if disabled.
 *      Rx_Blocked
 *          -Something else has exclusive access to the rx buffer. Wait for it to finish.
 *          -Exit to Idle when exclusive access has been relinquished
 *          -Exit to Disable if disabled
 *      Data_Received
 *          -Put data into rx buffer and return to Idle.
 * */

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "TCP_Connection_Manager.h"
#include "TCP_Receiver.h"

#include "../include/AddressSerialization.h"
#include "Clay_Config.h"

#include "UART.h"

#include "Message_Queue.h"

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable, Configure, ListenForConnect, TCP_STATE_MAX
} TCP_Receiver_States;

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static TCP_Receiver_States State;

static int ret;

static struct sockaddr_in lastSourceAddress;
static struct sockaddr_in server_addr;

static int32 listenfd;
static int32 len;
static int32 client_sock;
static uint16 httpd_server_port = 1002;

static volatile int32 Task_Count;

////Local Prototypes///////////////////////////////////////////////
static bool ConnectListener();
static bool Listen();
bool TCP_Open_Connection(int32 * newSocket);
static int32 Receive(int32 rx_socket, uint8 * rx_buf, int32 max_length,
		uint8 * fail_count);
static void ReceiveTask(void * pvParameters);
static bool Enqueue(uint8 * buffer, struct sockaddr_in * sourceAddress);

////Local implementations /////////////////////////////////////////
bool ICACHE_RODATA_ATTR TCP_Receiver_Init()
{
	bool rval = false;
	State = Disable;

	SocketListInitialize();
	Initialize_Message_Queue(&incomingMessageQueue);

	xTaskCreate(TCP_Receiver_State_Step, "tcprx1", 512, NULL, 2, NULL);

	return rval;
}

void ICACHE_RODATA_ATTR TCP_Receiver_State_Step()
{
	for (;;)
	{
		switch (State)
		{
		case Disable:
		{
			if (wifi_station_get_connect_status() == STATION_GOT_IP)
			{
				State = Configure;
			}
			break;
		}

		case Configure:
		{
			if (ConnectListener())
			{
				State = ListenForConnect;
				Task_Count = 0;
			}

			break;
		}

		case ListenForConnect:
		{
			Listen();
			break;
		}

		case TCP_STATE_MAX:
		default:
		{
			State = ListenForConnect;
			break;
		}
		}
	}
}

////Local implementations /////////////////////////////////////////

//create and bind listener socket.
bool ICACHE_RODATA_ATTR ConnectListener()
{
	bool rval = false;

	/* Construct local address structure */
	memset(&server_addr, 0, sizeof(server_addr)); /* Zero out structure */
	server_addr.sin_family = AF_INET; /* Internet address family */
	server_addr.sin_addr.s_addr = INADDR_ANY; /* Any incoming interface */
	server_addr.sin_len = sizeof(server_addr);
	server_addr.sin_port = htons(httpd_server_port); /* Local port */
	/* Create socket for incoming connections */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd == -1)
	{
		vTaskDelay(1000 / portTICK_RATE_MS);
		rval = false;
	}
	else
	{
		rval = true;
	}

	if (rval)
	{
		/* Bind to the local port */
		ret = bind(listenfd, (struct sockaddr * )&server_addr,
				sizeof(server_addr));
		if (ret != 0)
		{
			vTaskDelay(1000 / portTICK_RATE_MS);
			rval = false;
			close(listenfd);
		}
		else
		{
			int millis = 100;
			setsockopt(listenfd, SOL_SOCKET, SO_RCVTIMEO, &millis,
					sizeof(millis));

			rval = true;
		}
	}
//Establish TCP server interception:
	if (rval)
	{
		/* Listen to the local connection */
		ret = listen(listenfd, TCP_MAX_CONNECTIONS);
		if (ret != 0)
		{
			close(listenfd);
			vTaskDelay(1000 / portTICK_RATE_MS);
			rval = false;
		}
		else
		{
			rval = true;
		}
	}

	return rval;
}

//listens for connections and accepts them
static bool ICACHE_RODATA_ATTR Listen()
{
	bool rval = false;

	//spawn new tasks as receivers.
	//		Each task allocates its own buffer.
	//		each task receives until connection closes or timeout expires
	//			 then enqueues messages into incoming queue

	len = sizeof(struct sockaddr_in);
	/*block here waiting remote connect request*/
	if ((client_sock = accept(listenfd, (struct sockaddr * )&lastSourceAddress,
			(socklen_t * )&len)) < 0)
	{
		rval = false;
		lwip_close(client_sock);
	}
	else if (Task_Count <= TCP_MAX_CONNECTIONS)
	{
		//timeout alive time in ms / 10. We should call this about 10 times before timing out.
		int millis = TCP_RECEIVE_CONNECTION_TIMEOUT_ms;
		setsockopt(client_sock, SOL_SOCKET, SO_RCVTIMEO, &millis,
				sizeof(millis));

		//NOTE: we may need to make a copy of client_sock to make sure it doesn't get corrupted.
		if (TCP_Open_Connection(&client_sock))
		{
//			taskENTER_CRITICAL();
//			printf("opened sock:%d\r\n\r\n", client_sock);
//			taskEXIT_CRITICAL();

			rval = true;
		}
		else
		{
//			taskENTER_CRITICAL();
//			printf("couldn't open sock:%d\r\n\r\n", client_sock);
//			taskEXIT_CRITICAL();

			rval = false;
		}
	}

	if (!rval)
	{
		lwip_close(client_sock);
	}

//Wait until TCP client is connected with the server, then start receiving data packets when TCP
//communication is established:

	return rval;
}

bool ICACHE_RODATA_ATTR TCP_Open_Connection(int32 * newSocket)
{
	bool rval = (SocketListAdd(*newSocket) != -1);

	int taskCount = uxTaskGetNumberOfTasks();

	int fail_count = 0;
	xTaskHandle handle;
	xTaskHandle idle_handle;

	if (rval)
	{
//		taskENTER_CRITICAL();
//		printf("create task for sock:%d", *newSocket);
//		taskEXIT_CRITICAL();

		rval = false;
		while (!rval && fail_count < 10)
		{
//			taskENTER_CRITICAL();
//			printf("\r\ntask count reported:%d\r\n", taskCount);
//			taskEXIT_CRITICAL();

			//spawn new task to receive.
			long create_return = xTaskCreate(ReceiveTask, "socket_rx", 512,
					newSocket, 2, &handle);

			if (handle == NULL || create_return < 0)
			{
				++fail_count;

//				taskENTER_CRITICAL();
//				printf("handle is null\r\n");
//				taskEXIT_CRITICAL();

//				taskENTER_CRITICAL();
//				printf("task create failed:%d\r\n", create_return);
//				taskEXIT_CRITICAL();

//				taskENTER_CRITICAL();
//				printf("fail count:%d\r\n", fail_count);
//				taskEXIT_CRITICAL();

//				taskENTER_CRITICAL();
//				printf("raise idle priority.\r\n");
//				taskEXIT_CRITICAL();

				idle_handle = xTaskGetIdleTaskHandle();

				vTaskPrioritySet(idle_handle, 2);
				vTaskDelay(100 / portTICK_RATE_MS);
				vTaskPrioritySet(idle_handle, 0);
			}
			else
			{
//				taskENTER_CRITICAL();
//				printf("handle:%d, return:%d \r\n", handle, create_return);
//				taskEXIT_CRITICAL();
				rval = true;
			}
		}

		if (rval)
		{
//			taskENTER_CRITICAL();
//			printf("created task for sock:%d", *newSocket);
//			taskEXIT_CRITICAL();

			++Task_Count;
		}
	}
//	else
//	{
//		taskENTER_CRITICAL();
//		printf("couldn't add socket to list.\r\n");
//		taskEXIT_CRITICAL();
//	}

	taskENTER_CRITICAL();
	printf("task create return\r\n");
	taskEXIT_CRITICAL();

	return rval;
}

static void ICACHE_RODATA_ATTR ReceiveTask(void * pvParameters)
{
	//ERROR DETECTED: why is this 100?
	int32 rx_socket = *((int32*) pvParameters);
	struct sockaddr_in sourceAddress;
	int32 addressSize = sizeof(sourceAddress);

//	printf("\r\nsock:%d pvParameters:%d\r\n", rx_socket,
//			*((int32*) pvParameters));
	getpeername(rx_socket, (struct sockaddr* )&sourceAddress, &addressSize);

	uint8 * data = zalloc(CLAY_MESSAGE_LENGTH_MAX_BYTES);
	uint8 * temp;
	uint8 * unprocessed_data = NULL;
	uint8 * processed_message;
	uint8 fail_count = 0;

	uint8 addr_string[50];

	taskENTER_CRITICAL();
	Serialize_Address(sourceAddress.sin_addr.s_addr, sourceAddress.sin_port,
			addr_string, 50, MESSAGE_TYPE_TCP);
	printf("\r\nsock:%d\r\naddr:[%s]\r\n\r\n", rx_socket, addr_string);
	taskEXIT_CRITICAL();

	bool found_message = false;

	int32 length = 0;
	int32 unprocessed_length = 0;

	int32 processed_message_length = 0;
	int32 processed_message_index = 0;

	int received_length = 0;
	int indexOfMessageEnd;

	//listen until socket is closed.
	while (rx_socket > 0)
	{
		received_length = Receive(rx_socket, data,
		CLAY_MESSAGE_LENGTH_MAX_BYTES, &fail_count);

		if (received_length > 0)
		{
			fail_count = 0;

//			taskENTER_CRITICAL();
//			printf("rx'd\r\n");
//			taskEXIT_CRITICAL();
//			UART_WaitTxFifoEmpty(UART0);

			//copy data into unprocessed_data
			if (unprocessed_data == NULL)
			{
				taskENTER_CRITICAL();
				unprocessed_data = zalloc(received_length + 1);
				memcpy(unprocessed_data, data, received_length);
				taskEXIT_CRITICAL();

				unprocessed_length = received_length + 1;
				unprocessed_data[unprocessed_length] = '\0';
				processed_message_index = 0;

//				taskENTER_CRITICAL();
//				printf("alloc'd %d unproc bytes\r\n", unprocessed_length);
//				taskEXIT_CRITICAL();

				UART_WaitTxFifoEmpty(UART0);
			}
			else
			{
				taskENTER_CRITICAL();
				//already have space in the unprocessed buffer for a null
				temp = zalloc(unprocessed_length + received_length);
				memcpy(temp, unprocessed_data, unprocessed_length);
				memcpy(temp + unprocessed_length - 1, data, received_length); //-1 to clobber null

//				printf("before free unproc:%d\r\n",
//						system_get_free_heap_size());
//				UART_WaitTxFifoEmpty(UART0);

				free(unprocessed_data);
				taskEXIT_CRITICAL();

//				taskENTER_CRITICAL();
//				printf("free unproc:%d\r\n", system_get_free_heap_size());
//				taskEXIT_CRITICAL();
//				UART_WaitTxFifoEmpty(UART0);

				unprocessed_data = temp;
				temp = NULL;

				//don't need to add one for the null here.
				unprocessed_length += received_length;
				unprocessed_data[unprocessed_length] = '\0';
				processed_message_index = 0;

//				taskENTER_CRITICAL();
//				printf("unprocessed now %d\r\n", unprocessed_length);
//				taskEXIT_CRITICAL();
//				UART_WaitTxFifoEmpty(UART0);
			}

			received_length = 0;

			//
			//
			//
			//
			//IMPORTANT:
			//MULTIPLE CALLS TO STRTOK: This means this loop must be in a
			//							critical section to avoid resetting
			//							the internal state machine.
			//						    We could also make subsequent calls to strtok
			//  						by using the processed_message_index
			//
			//
			//
			//

			//check for end of message
			taskENTER_CRITICAL();
			processed_message = strtok(unprocessed_data, "\n");

			while (processed_message != NULL)
			{
//				printf("sock %d found message [%s] at %d\r\n", rx_socket,
//						processed_message, processed_message_index);
//				printf("free heap:%d\r\n", system_get_free_heap_size());

				UART_WaitTxFifoEmpty(UART0);

				processed_message_length = strlen(processed_message) + 2; //+1 for null, +1 for newline

				unprocessed_length -= processed_message_length; //+1 for newline, which is now null and not counted.
				processed_message_index += processed_message_length;

				temp = zalloc(processed_message_length);
				sprintf(temp, "%s\n", processed_message);

				//enqueue if we received message end.
				Enqueue(temp, &sourceAddress);  //TODO: add destination address.

				free(temp);

				processed_message = strtok(NULL, "\n");

				found_message = true;

				UART_WaitTxFifoEmpty(UART0);
			}
			taskEXIT_CRITICAL();

//			taskENTER_CRITICAL();
//			printf(
//					"\r\nsock:%d found all messages in unproc. unproc size: %d leftover: %d processed index %d\r\n",
//					rx_socket, unprocessed_length + processed_message_index,
//					unprocessed_length, processed_message_index);
//			printf("leftover unproc: [%s]\r\n\r\n",
//					unprocessed_data + processed_message_index);
//			taskEXIT_CRITICAL();
//			UART_WaitTxFifoEmpty(UART0);

			if (found_message)
			{
				if (unprocessed_length > 1 && unprocessed_length) //if == 1, then it's just a null and we don't need it.
				{
					taskENTER_CRITICAL();
					temp = zalloc(unprocessed_length);
					memcpy(temp, unprocessed_data + processed_message_index,
							unprocessed_length);

					free(unprocessed_data);
					taskEXIT_CRITICAL();

					unprocessed_data = temp;

					unprocessed_data[unprocessed_length] = '\0';

//					taskENTER_CRITICAL();
//					printf("unproc'd data left:%d\r\n", unprocessed_length);
//					taskEXIT_CRITICAL();
//					UART_WaitTxFifoEmpty(UART0);

//					taskENTER_CRITICAL();
//					printf("free heap:%d\r\n", system_get_free_heap_size());
//					taskEXIT_CRITICAL();
//					UART_WaitTxFifoEmpty(UART0);
				}
				else
				{
					taskENTER_CRITICAL();
					free(unprocessed_data);
					taskEXIT_CRITICAL();

//					taskENTER_CRITICAL();
//					printf("freed unproc:%d\r\n", system_get_free_heap_size());
//					taskEXIT_CRITICAL();

					UART_WaitTxFifoEmpty(UART0);

					unprocessed_data = NULL;
				}

				processed_message_index = 0;
			}

		}
		else if (received_length < 0)
		{
			break;
		}

//		taskENTER_CRITICAL();
//		printf("received_length:%d\r\n\r\n\r\n", received_length);
//		taskEXIT_CRITICAL();

		taskYIELD();
	}

//	taskENTER_CRITICAL();
//	printf("kill task for socket:%d\r\n", rx_socket);
//	taskEXIT_CRITICAL();

	taskENTER_CRITICAL();
	free(unprocessed_data);
	free(data);
	taskEXIT_CRITICAL();

	SocketListRemove(rx_socket);
	lwip_close(rx_socket);

	--Task_Count;

//	taskENTER_CRITICAL();
//	printf("killin\r\n\r\n\r\n", rx_socket);
//	taskEXIT_CRITICAL();

	vTaskDelete(NULL);
}

//reads data from the socket, allocates memory for it in rxbuf, and returns the count.
//			if return = -1, the connection has been reset by the remote
static int32 ICACHE_RODATA_ATTR Receive(int32 rx_socket, uint8 *rx_buf,
		int32 max_length, uint8 * fail_count)
{
//	taskENTER_CRITICAL();
//	printf("rx enter\r\n");
//	taskEXIT_CRITICAL();

	int32 rval = lwip_recv(rx_socket, (void*) rx_buf, (size_t) max_length,
	MSG_PEEK);

//	taskENTER_CRITICAL();
//	printf("rx rval:%d\r\n", rval);
//	taskEXIT_CRITICAL();

	if (rval < 0)
	{
		int32 error = 0;
		uint32 optionLength = sizeof(error);
		int getReturn = lwip_getsockopt(rx_socket, SOL_SOCKET, SO_ERROR, &error,
				&optionLength);

		switch (error)
		{
		case ECONNRESET:
		{
//			taskENTER_CRITICAL();
//			printf("conn reset\r\n");
//			taskEXIT_CRITICAL();
			rval = -1;
			break;
		}
		case EAGAIN:
		{
//			taskENTER_CRITICAL();
//			printf("timeout\r\n");
//			taskEXIT_CRITICAL();

			rval = 0;

			break;
		}
		default:
		{
			++(*fail_count);

			if ((*fail_count) > 20)
			{
//				taskENTER_CRITICAL();
//				printf("unknown error limit exceeded:%d\r\n", error);
//				taskEXIT_CRITICAL();

				rval = -1;
			}
			else
			{
				rval = 0;
			}

			break;
		}
		}
	}
	else if (rval > 0 && rval < max_length)
	{
//		taskENTER_CRITICAL();
//		printf("rx:%d\r\n", rval);
//		taskEXIT_CRITICAL();

		rval = lwip_recv(rx_socket, rx_buf, max_length, 0);
	}

//	taskENTER_CRITICAL();
//	printf("rx exit:%d\r\n\r\n", rval);
//	taskEXIT_CRITICAL();

	return rval;
}

static bool ICACHE_RODATA_ATTR Enqueue(uint8 * buffer,
		struct sockaddr_in * sourceAddress)
{
//	taskENTER_CRITICAL();
//	printf("nq\r\n");
//	taskEXIT_CRITICAL();

	UART_WaitTxFifoEmpty(UART0);

	bool rval = false;
	Message tempMessage;
	uint8 * addrStringBuf = zalloc(CLAY_ADDR_STRING_BUF_LENGTH);

	taskENTER_CRITICAL();
	Serialize_Address(sourceAddress->sin_addr.s_addr, TCP_RECEIVE_PORT,
			addrStringBuf,
			CLAY_ADDR_STRING_BUF_LENGTH, MESSAGE_TYPE_TCP);
	taskEXIT_CRITICAL();

	taskENTER_CRITICAL();
	Initialize_Message(&tempMessage, addrStringBuf, addrStringBuf, buffer);
	Queue_Message(&incomingMessageQueue, &tempMessage);
	taskEXIT_CRITICAL();

	rval = true;

	free(addrStringBuf);

//	taskENTER_CRITICAL();
//	printf("nq'd\r\n");
//	taskEXIT_CRITICAL();

	UART_WaitTxFifoEmpty(UART0);

	return rval;
}
