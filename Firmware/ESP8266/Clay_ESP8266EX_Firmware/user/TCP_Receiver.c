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
static TCP_Receiver_States state;

static int ret;

static struct sockaddr_in last_source_address;
static struct sockaddr_in server_addr;

static int32 listenfd;
static int32 len;
static int32 client_sock;
static uint16 httpd_server_port = 1002;

static volatile int32 task_count;

////Local Prototypes///////////////////////////////////////////////
static bool ConnectListener();
static bool Listen();
bool TCP_Start_Task(int32 * new_socket);
static int32 Receive(int32 rx_socket, uint8 * rx_buf, int32 max_length,
		uint8 * fail_count);
static void ReceiveTask(void * pvParameters);
static bool ICACHE_RODATA_ATTR Enqueue(uint8 * buffer, char * source_address,
		char * dest_address);

////Local implementations /////////////////////////////////////////
bool ICACHE_RODATA_ATTR TCP_Receiver_Init()
{
	bool rval = false;
	state = Disable;

	SocketListInitialize();
	Initialize_Message_Queue(&incoming_message_queue);

	xTaskCreate(TCP_Receiver_State_Step, "tcprx1", 512, NULL, 2, NULL);

	return rval;
}

void ICACHE_RODATA_ATTR TCP_Receiver_State_Step()
{
	for (;;)
	{
		switch (state)
		{
		case Disable:
		{
			if (wifi_station_get_connect_status() == STATION_GOT_IP)
			{
				state = Configure;
			}
			break;
		}

		case Configure:
		{
			if (ConnectListener())
			{
				state = ListenForConnect;
				task_count = 0;
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
			state = ListenForConnect;
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
	if ((client_sock = accept(listenfd, (struct sockaddr * )&last_source_address,
			(socklen_t * )&len)) < 0)
	{
		rval = false;
		lwip_close(client_sock);
	}
	else if (task_count <= TCP_MAX_CONNECTIONS)
	{
		//Set receive timeout.
		int millis = TCP_RECEIVE_CONNECTION_TIMEOUT_ms;
		setsockopt(client_sock, SOL_SOCKET, SO_RCVTIMEO, &millis,
				sizeof(millis));

		//NOTE: we may need to make a copy of client_sock to make sure it doesn't get corrupted.
		if (TCP_Start_Task(&client_sock))
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

bool ICACHE_RODATA_ATTR TCP_Start_Task(int32 * new_socket)
{
//	taskENTER_CRITICAL();
//	printf("create task for sock:%d\r\n", *newSocket);
//	taskEXIT_CRITICAL();

	bool rval = (SocketListAdd(*new_socket) != -1);

	int taskCount = uxTaskGetNumberOfTasks();

	int fail_count = 0;
	xTaskHandle handle;
	xTaskHandle idle_handle;

	if (rval)
	{
//		taskENTER_CRITICAL();
//		printf("create task for sock:%d\r\n", *newSocket);
//		taskEXIT_CRITICAL();

		rval = false;
		while (!rval && fail_count < 10)
		{
//			taskENTER_CRITICAL();
//			printf("\r\ntask count reported:%d\r\n", taskCount);
//			taskEXIT_CRITICAL();

			//spawn new task to receive.
			long create_return = xTaskCreate(ReceiveTask, "socket_rx", 512,
					new_socket, 2, &handle);

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

			++task_count;
		}
	}
//	else
//	{
//		taskENTER_CRITICAL();
//		printf("couldn't add socket to list.\r\n");
//		taskEXIT_CRITICAL();
//	}

//	taskENTER_CRITICAL();
//	printf("task create return\r\n");
//	taskEXIT_CRITICAL();

	return rval;
}

static void ICACHE_RODATA_ATTR ReceiveTask(void * pvParameters)
{
	int32 rx_socket = *((int32*) pvParameters);
	struct sockaddr_in source_address;
	struct sockaddr_in local_address;
	int32 addressSize = sizeof(source_address);

//	taskENTER_CRITICAL();
//	printf("\r\n\r\n\r\nsock:%d pvParameters:%d\r\n\r\n\r\n", rx_socket,
//			*((int32*) pvParameters));
//	taskEXIT_CRITICAL();

	getpeername(rx_socket, (struct sockaddr* )&source_address, &addressSize);
	getsockname(rx_socket, (struct sockaddr* )&local_address, &addressSize);

	uint8 * data = zalloc(CLAY_MESSAGE_LENGTH_MAX_BYTES);
	uint8 * temp;
	uint8 * unprocessed_data = NULL;
	uint8 * processed_message;
	uint8 fail_count = 0;

	uint8 addr_string[50];

	taskENTER_CRITICAL();
	uint8 * source_addr_string_buf = zalloc(CLAY_ADDR_STRING_BUF_LENGTH);
	uint8 * dest_addr_string_buf = zalloc(CLAY_ADDR_STRING_BUF_LENGTH);
	taskEXIT_CRITICAL();

	taskENTER_CRITICAL();
	Serialize_Address(source_address.sin_addr.s_addr,
			ntohs(source_address.sin_port), source_addr_string_buf,
			CLAY_ADDR_STRING_BUF_LENGTH);
	Serialize_Address(local_address.sin_addr.s_addr, TCP_RECEIVE_PORT,
			dest_addr_string_buf,
			CLAY_ADDR_STRING_BUF_LENGTH);
	taskEXIT_CRITICAL();

//	taskENTER_CRITICAL();
//	Serialize_Address(sourceAddress.sin_addr.s_addr, sourceAddress.sin_port,
//			addr_string, 50, MESSAGE_TYPE_TCP);
//	printf("\r\nsock:%d\r\naddr:[%s]\r\n\r\n", rx_socket, addr_string);
//	taskEXIT_CRITICAL();

	bool found_message = false;

	int32 length = 0;
	int32 unprocessed_length = 0;
	int32 unprocessed_buffer_size = 0;

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

			taskENTER_CRITICAL();
			printf("rx'd %d\r\n", received_length);
			taskEXIT_CRITICAL();

			//copy data into unprocessed_data
			if (unprocessed_data == NULL)
			{
				taskENTER_CRITICAL();
				printf("alloc:%d,free:%d\r\n",
						unprocessed_length + received_length,
						system_get_free_heap_size());
				unprocessed_data = zalloc(received_length + 1);
				memcpy(unprocessed_data, data, received_length);
				taskEXIT_CRITICAL();

				unprocessed_length = received_length + 1;
				unprocessed_buffer_size = unprocessed_length;
				unprocessed_data[unprocessed_length] = '\0';
				processed_message_index = 0;

//				taskENTER_CRITICAL();
//				printf("alloc'd %d unproc bytes\r\n", unprocessed_length);
//				taskEXIT_CRITICAL();

			}
			else
			{
				taskENTER_CRITICAL();
				printf("alloc:%d,free:%d\r\n",
						unprocessed_length + received_length,
						system_get_free_heap_size());
				//already have space in the unprocessed buffer for a null
				temp = zalloc(unprocessed_length + received_length);
				memcpy(temp, unprocessed_data, unprocessed_length);
				memcpy(temp + unprocessed_length - 1, data, received_length); //-1 to clobber null

//				printf("before free unproc:%d\r\n",
//						system_get_free_heap_size());

				free(unprocessed_data);
				taskEXIT_CRITICAL();

//				taskENTER_CRITICAL();
//				printf("free unproc:%d\r\n", system_get_free_heap_size());
//				taskEXIT_CRITICAL();

				unprocessed_data = temp;
				temp = NULL;

				//don't need to add one for the null here.
				unprocessed_length += received_length;
				unprocessed_buffer_size = unprocessed_length;
				unprocessed_data[unprocessed_length] = '\0';
				processed_message_index = 0;

//				taskENTER_CRITICAL();
//				printf("unprocessed now %d\r\n", unprocessed_length);
//				taskEXIT_CRITICAL();
			}

			received_length = 0;

			//
			//
			//
			//
			//IMPORTANT:
			//MULTIPLE CALLS TO STRTOK: To avoid having strtok reset unexpectedly, either
			//							-This loop must be in a
			//							 critical section to avoid resetting
			//							 the internal state machine.
			//						    -Subsequent calls to strtok are made
			//  						 with with processed_message_index into
			//						     unprocessed_data
			//
			//
			//
			//

			//check for end of message
			taskENTER_CRITICAL();
			processed_message = strtok(unprocessed_data, message_delimiter);
			taskEXIT_CRITICAL();

			while (processed_message != NULL)
			{
//				taskENTER_CRITICAL();
//				printf("sock %d found message [%s] at %d\r\n", rx_socket,
//						processed_message, processed_message_index);
//				printf("free heap:%d\r\n", system_get_free_heap_size());
//				taskEXIT_CRITICAL();

				portENTER_CRITICAL();
				UART_WaitTxFifoEmpty(UART0);
				portEXIT_CRITICAL();

				taskENTER_CRITICAL();
				processed_message_length = strlen(processed_message) + 2; //+1 for null, +1 for newline
				taskEXIT_CRITICAL();

				//-1 to account for the null beoming a null and newline in processed_message
				unprocessed_length -= processed_message_length - 1;
				processed_message_index += processed_message_length - 1;

				taskENTER_CRITICAL();
				temp = zalloc(processed_message_length);
				sprintf(temp, "%s%s", processed_message, message_delimiter);
				taskEXIT_CRITICAL();

				//enqueue if we received message end.
				Enqueue(temp, source_addr_string_buf, dest_addr_string_buf);

				taskENTER_CRITICAL();
				free(temp);
				taskEXIT_CRITICAL();

				taskENTER_CRITICAL();
				processed_message = strtok(
						unprocessed_data + processed_message_index,
						message_delimiter);
				taskEXIT_CRITICAL();

//				taskYIELD();

				found_message = true;
			}

//			taskENTER_CRITICAL();
//			printf(
//					"\r\nsock:%d parsed unproc. size: a%d,s%d leftover: %d processed index %d\r\n",
//					rx_socket, unprocessed_length + processed_message_index,
//					unprocessed_buffer_size, unprocessed_length,
//					processed_message_index);
//			printf("leftover unproc: [%s]\r\n\r\n",
//					unprocessed_data + processed_message_index);
//			taskEXIT_CRITICAL();
//

			if (found_message)
			{
				if (unprocessed_length > 1
						&& unprocessed_length
								< (2 * CLAY_MESSAGE_LENGTH_MAX_BYTES)
						&& unprocessed_data[0] != '\0') //if == 1, then it's just a null and we don't need it.
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
//
//					taskENTER_CRITICAL();
//					printf("free heap:%d\r\n", system_get_free_heap_size());
//					taskEXIT_CRITICAL();
				}
				else
				{
					taskENTER_CRITICAL();
					free(unprocessed_data);
					taskEXIT_CRITICAL();

//					taskENTER_CRITICAL();
//					printf("freed unproc:%d\r\n", system_get_free_heap_size());
//					taskEXIT_CRITICAL();

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
	free(source_addr_string_buf);
	free(dest_addr_string_buf);
	taskEXIT_CRITICAL();

	SocketListRemove(rx_socket);
	lwip_close(rx_socket);

	--task_count;

	taskENTER_CRITICAL();
	printf("\r\n\r\n\r\nkillin\r\n\r\n\r\n", rx_socket);
	taskEXIT_CRITICAL();

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
//
//	portENTER_CRITICAL();
//	UART_WaitTxFifoEmpty(UART0);
//	portEXIT_CRITICAL();

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
		rval = lwip_recv(rx_socket, rx_buf, max_length, 0);

//		taskENTER_CRITICAL();
//		printf("rx:%d\r\n", rval);
//		taskEXIT_CRITICAL();
	}

//	taskENTER_CRITICAL();
//	printf("rx exit:%d\r\n\r\n", rval);
//	taskEXIT_CRITICAL();

	return rval;
}

static bool ICACHE_RODATA_ATTR Enqueue(uint8 * buffer, char * source_address,
		char * dest_address)
{
	bool rval = false;
	Message tempMessage;

	taskENTER_CRITICAL();
	Initialize_Message(&tempMessage, message_type_strings[MESSAGE_TYPE_TCP],
			source_address, dest_address, buffer);
	Queue_Message(&incoming_message_queue, &tempMessage);
	taskEXIT_CRITICAL();

	rval = true;

	return rval;
}
