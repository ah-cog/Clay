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
bool TCP_Open_Connection(int newSocket);
static int32 Receive(int32 rxSocket, uint8_t * rxbuf, int32 max_length);
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
			int millis = TCP_RECEIVE_CONNECTION_TIMEOUT_ms;
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

		if (TCP_Open_Connection(client_sock))
		{
			rval = true;
		}
		else
		{
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

bool ICACHE_RODATA_ATTR TCP_Open_Connection(int newSocket)
{
	bool rval = (SocketListAdd(newSocket) != -1);

	int taskCount = uxTaskGetNumberOfTasks();

	int fail_count = 0;
	xTaskHandle handle;
	xTaskHandle idle_handle;

	if (rval)
	{
		rval = false;
		while (!rval && fail_count < 10)
		{
//			taskENTER_CRITICAL();
//			printf("task count reported:%d", taskCount);
//			taskEXIT_CRITICAL();

			//spawn new task to receive.
			long create_return = xTaskCreate(ReceiveTask, "socket_rx", 512,
					((void* )&newSocket), 2, &handle);

			if (handle == NULL || create_return < 0)
			{
//				taskENTER_CRITICAL();
//				printf("handle is null\r\n");
//				taskEXIT_CRITICAL();
				++fail_count;

//				taskENTER_CRITICAL();
//				printf("task create failed:%d\r\n", create_return);
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

//		taskENTER_CRITICAL();
//		printf("fail count:%d\r\n", fail_count);
//		taskEXIT_CRITICAL();

		if (rval)
		{
			++Task_Count;
		}
	}

	return rval;
}

static void ICACHE_RODATA_ATTR ReceiveTask(void * pvParameters)
{
	int32 rxSocket = *((int32*) pvParameters);
	struct sockaddr_in sourceAddress;
	int32 addressSize = sizeof(sourceAddress);
	getpeername(rxSocket, (struct sockaddr* )&sourceAddress, &addressSize);

	uint8 * data = zalloc(CLAY_MESSAGE_LENGTH_MAX_BYTES);
	uint8 * temp;
	uint8 * unprocessed_data = NULL;
	uint8 * processed_message;

	bool found_message = false;

	int32 length = 0;
	int32 unprocessed_length = 0;

	int32 processed_message_length = 0;
	int32 processed_message_index = 0;

	int received_length = 0;
	int indexOfMessageEnd;

	//listen until socket is closed.
	while (rxSocket > 0)
	{
		received_length = Receive(rxSocket, data,
		CLAY_MESSAGE_LENGTH_MAX_BYTES);

		if (received_length > 0)
		{
			//copy data into unprocessed_data
			if (unprocessed_data == NULL)
			{
				taskENTER_CRITICAL();
				unprocessed_data = zalloc(received_length + 1);
				memcpy(unprocessed_data, data, received_length);

				taskEXIT_CRITICAL();

				unprocessed_length = received_length;
				unprocessed_data[unprocessed_length] = '\0';
				processed_message_index = 0;
			}
			else
			{
				taskENTER_CRITICAL();
				temp = zalloc(unprocessed_length + received_length + 1);
				memcpy(temp, unprocessed_data, unprocessed_length);
				memcpy(temp + unprocessed_length - 1, data, received_length);

				free(unprocessed_data);
				taskEXIT_CRITICAL();

				unprocessed_data = temp;
				temp = NULL;

				unprocessed_length += received_length;
				unprocessed_data[unprocessed_length] = '\0';
				processed_message_index = 0;
			}

			received_length = 0;

			//check for end of message
			processed_message = strtok(unprocessed_data, "\n");

			while (processed_message != NULL)
			{
				taskENTER_CRITICAL();
				processed_message_length = strlen(processed_message) + 1;
				taskEXIT_CRITICAL();

				unprocessed_length -= processed_message_length; //+1 for newline, which is now null and not counted.
				processed_message_index += processed_message_length;

				taskENTER_CRITICAL();
				temp = zalloc(processed_message_length + 1);
				sprintf(temp, "%s\n", processed_message);
				taskEXIT_CRITICAL();

				//enqueue if we received message end.
				Enqueue(temp, &sourceAddress);

				taskENTER_CRITICAL();
				free(temp);
				taskEXIT_CRITICAL();

				processed_message = strtok(NULL, "\n");

				found_message = true;

				taskYIELD();
			}

			if (found_message)
			{
				if (unprocessed_length > 0)
				{
					taskENTER_CRITICAL();
					temp = zalloc(unprocessed_length);
					memcpy(temp, unprocessed_data + processed_message_index,
							unprocessed_length);

					free(unprocessed_data);
					taskEXIT_CRITICAL();

					unprocessed_data = temp;

					unprocessed_data[unprocessed_length] = '\0';
				}
				else
				{
					taskENTER_CRITICAL();
					free(unprocessed_data);
					taskEXIT_CRITICAL();
					unprocessed_data = NULL;
				}

				processed_message_index = 0;
			}

		}
		else if (received_length < 0)
		{
			break;
		}

		taskYIELD();
	}

	taskENTER_CRITICAL();
	free(unprocessed_data);
	free(data);
	taskEXIT_CRITICAL();

	SocketListRemove(rxSocket);
	lwip_close(rxSocket);

	--Task_Count;

	vTaskDelete(NULL);
}

//reads data from the socket, allocates memory for it in rxbuf, and returns the count.
//			if return = -1, the connection has been reset by the remote
static int32 ICACHE_RODATA_ATTR Receive(int32 rxSocket, uint8_t *rxbuf,
		int32 max_length)
{
	int32 rval = lwip_recv(rxSocket, (void*) rxbuf, (size_t) max_length,
	MSG_PEEK);

	if (rval < 0)
	{
		int32 error = 0;
		uint32 optionLength = sizeof(error);
		int getReturn = lwip_getsockopt(rxSocket, SOL_SOCKET, SO_ERROR, &error,
				&optionLength);

		rval = (error == ECONNRESET ? -1 : 0);

		if (rval == -1)
		{
		}
	}
	else if (rval > 0 && rval < max_length)
	{
		rval = lwip_recv(rxSocket, rxbuf, max_length, 0);
	}

	return rval;
}

static bool ICACHE_RODATA_ATTR Enqueue(uint8 * buffer,
		struct sockaddr_in * sourceAddress)
{
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

	return rval;
}
