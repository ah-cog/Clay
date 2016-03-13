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
static void Disconnect();
static bool Listen();
bool TCP_Open_Connection(int newSocket);
static int32 Receive(int32 rxSocket, uint8_t * rxbuf, int32 maxRxCount);
static void ReceiveTask(void * pvParameters);
static int32 Get_Index_Of_Message_End(uint8 * buffer, int32 count);
static bool Enqueue(uint8 * buffer, int32 count,
		struct sockaddr_in * sourceAddress);

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

	if (rval)
	{
		++Task_Count;

		//spawn new task to receive.
		xTaskCreate(ReceiveTask, "socket_rx", 512, ((void* )&newSocket), 2,
				NULL);
	}

	return rval;
}

static void ICACHE_RODATA_ATTR ReceiveTask(void * pvParameters)
{
	int32 rxSocket = *((int32*) pvParameters);
	struct sockaddr_in sourceAddress;
	int32 addressSize = sizeof(sourceAddress);
	getpeername(rxSocket, (struct sockaddr* )&sourceAddress, &addressSize);

	uint8 * data = zalloc(TCP_RECEIVE_TASK_BUFFER_SIZE);
	int32 length = 0;
	int receivedValue = 0;
	int indexOfMessageEnd;

	if (data != NULL)
	{
		//listen until socket is closed.
		while (rxSocket > 0)
		{
			receivedValue = Receive(rxSocket, data + length,
			TCP_RECEIVE_TASK_BUFFER_SIZE - length);

			if (receivedValue
					> 0&& length + receivedValue <= TCP_RECEIVE_TASK_BUFFER_SIZE)
			{
				length += receivedValue;
				receivedValue = 0;

				//check for end of message
				indexOfMessageEnd = Get_Index_Of_Message_End(data, length);

				if (indexOfMessageEnd > 0)
				{
					//TODO: parse multiple messages here, in case we got more than one newline

					//enqueue if we received message end.
					Enqueue(data, length, &sourceAddress);

					length = 0;
					taskENTER_CRITICAL();
					memset(data, 0, TCP_RECEIVE_TASK_BUFFER_SIZE);
					taskEXIT_CRITICAL();
				}
				else if (length >= TCP_RECEIVE_TASK_BUFFER_SIZE)
				{

					//overflow. drop this message.
					length = 0;
				}
			}
			else if (receivedValue < 0)
			{
				break;
			}

			taskYIELD();
		}
	}

	SocketListRemove(rxSocket);
	lwip_close(rxSocket);
	free((void*) data);

	--Task_Count;

	vTaskDelete(NULL);
}

//reads data from the socket
static int32 ICACHE_RODATA_ATTR Receive(int32 rxSocket, uint8_t * rxbuf,
		int32 maxRxCount)
{
	int32 rval = lwip_recv(rxSocket, (void*) rxbuf, maxRxCount, MSG_PEEK);

	if (rval < 0)
	{
		int32 error = 0;
		uint32 optionLength = sizeof(error);
		int getReturn = lwip_getsockopt(rxSocket, SOL_SOCKET, SO_ERROR, &error,
				&optionLength);

		rval = (error == ECONNRESET ? -1 : 0);
	}
	else if (rval <= maxRxCount && rval > 0)
	{
		rval = lwip_recv(rxSocket, rxbuf, maxRxCount, 0);
		rxbuf[rval] = '\0';
	}

	return rval;
}

static int32 ICACHE_RODATA_ATTR Get_Index_Of_Message_End(uint8 * buffer,
		int32 count)
{
	int32 rval = false;
	uint8 * bangIdx = strchr(buffer, '\n');

	if (bangIdx != NULL)
	{
		rval = (bangIdx - buffer);
	}

	return rval;
}

static bool ICACHE_RODATA_ATTR Enqueue(uint8 * buffer, int32 count,
		struct sockaddr_in * sourceAddress)
{
	bool rval = false;
	Message tempMessage;
	uint8 * addrStringBuf = zalloc(CLAY_ADDR_STRING_BUF_LENGTH);

	taskENTER_CRITICAL();
	Serialize_Address(sourceAddress, addrStringBuf, CLAY_ADDR_STRING_BUF_LENGTH,
			MESSAGE_TYPE_TCP);
	taskEXIT_CRITICAL();

	taskENTER_CRITICAL();
	Initialize_Message(&tempMessage, addrStringBuf, addrStringBuf, buffer);
	Queue_Message(&incomingMessageQueue, &tempMessage);
	taskEXIT_CRITICAL();

	rval = true;

	free(addrStringBuf);

	return rval;
}
