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

#include "TCP_Receiver.h"
#include "Clay_Config.h"

#include "Clay_Message.h"
#include "Message_Queue.h"

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable, Configure, ListenForConnect, UDP_STATE_MAX
} TCP_Receiver_States;

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static TCP_Receiver_States State;

static int ret;

static struct sockaddr_in lastSourceAddress;
static struct sockaddr_in server_addr;

//static char sinZeroStr[50];
//static int sinZeroSize;
//static int i;

//TODO: move to clay_config.
#define CONNECTION_ALIVE_TIME_us 200 * 1000   //200 msec
#define SERVER_PORT 1002
#define CLIENT_MAX_CONN    10
#define SERVER_IP "192.168.1.11"
#define RECEIVE_TASK_BUFFER_SIZE 512
#define CLAY_ADDR_STRING_BUF_LENGTH 70
//#define SERVER_PORT 1001

static int32 listenfd;
static int32 len;
static int32 client_sock;
static uint16 httpd_server_port = 1002;

static uint32 Rx_Start_Time;
static uint32 Rx_Start_Time_temp;
static int temp_rx_counter;

static int32 Task_Count;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static void Disconnect();
static bool Listen();
static int32 Receive(int32 rxSocket, uint8_t * rxbuf, int32 maxRxCount);
static void ReceiveTask(void * pvParameters);
static int32 Get_Index_Of_Message_End(uint8 * buffer, int32 count);
static bool Enqueue(uint8 * buffer, int32 count,
		struct sockaddr_in * sourceAddress);

////Local implementations /////////////////////////////////////////
bool TCP_Receiver_Init()
{
	bool rval = false;
	State = Disable;

	Initialize_Message_Queue(&incomingMessageQueue);

	xTaskCreate(TCP_Receiver_State_Step, "tcprx1", 1024, NULL, 2, NULL);

	return rval;
}

void TCP_Receiver_State_Step()
{
	//Working demo:
//	while (!Connect())
//		;
//	for (;;)
//	{
//
//		if (Receive())
//		{
//			taskENTER_CRITICAL();
//			TCP_Rx_Buffer[TCP_Rx_Count] = '\0';
//			printf("%d:[%s]\r\n", system_get_time(), TCP_Rx_Buffer);
//			taskEXIT_CRITICAL();
//		}
//		taskYIELD();
//	}
	//end working demo

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
			if (Connect())
			{
//				taskENTER_CRITICAL();
//				printf("rx connected\r\n");
//				taskEXIT_CRITICAL();

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

		case UDP_STATE_MAX:
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
bool Connect()
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
//		printf("ESP8266 TCP server task > socket error\r\n");
		vTaskDelay(1000 / portTICK_RATE_MS);
		rval = false;
	}
	else
	{
		rval = true;
//		printf("ESP8266 TCP server task > create socket: %d\r\n", listenfd);
	}

	if (rval)
	{
		/* Bind to the local port */
		ret = bind(listenfd, (struct sockaddr * )&server_addr,
				sizeof(server_addr));
		if (ret != 0)
		{
//			printf("ESP8266 TCP server task > bind fail\r\n");
			vTaskDelay(1000 / portTICK_RATE_MS);
			rval = false;
			close(listenfd);
		}
		else
		{
			rval = true;
//			printf("ESP8266 TCP server task > port:%d\r\n",
//					ntohs(server_addr.sin_port));
		}
	}
//Establish TCP server interception:
	if (rval)
	{
		/* Listen to the local connection */
		ret = listen(listenfd, CLIENT_MAX_CONN);
		if (ret != 0)
		{
			close(listenfd);
//			printf("ESP8266 TCP server task > failed to set listen queue!\r\n");
			vTaskDelay(1000 / portTICK_RATE_MS);
			rval = false;
		}
		else
		{
			rval = true;
//			printf("ESP8266 TCP server task > listen ok\r\n");
		}
	}

	return rval;
}

//listens for connections and accepts them
static bool Listen()
{
	bool rval = false;

//spawn new tasks as receivers.
//		Each task allocates its own buffer.
//		each task receives until connection closes or timeout expires
//			 then enqueues messages into incoming queue

	len = sizeof(struct sockaddr_in);
//	taskENTER_CRITICAL();
//	printf("wait client\r\n");
//	taskEXIT_CRITICAL();
	/*block here waiting remote connect request*/
	if ((client_sock = accept(listenfd, (struct sockaddr * )&lastSourceAddress,
			(socklen_t * )&len)) < 0)
	{
//		taskENTER_CRITICAL();
//		printf("accept fail\r\n");
//		taskEXIT_CRITICAL();
		rval = false;
	}
	else if (Task_Count <= CLIENT_MAX_CONN)
	{
		//timeout alive time in ms / 10. We should call this about 10 times before timing out.
		int millis = (CONNECTION_ALIVE_TIME_us / 1000) / 10;
		setsockopt(client_sock, SOL_SOCKET, SO_RCVTIMEO, &millis,
				sizeof(millis));

		rval = true;

		++Task_Count;
//		taskENTER_CRITICAL();
//		printf("tasks:%d\r\n", Task_Count);
//		taskEXIT_CRITICAL();

		//spawn new task to receive.
		xTaskCreate(ReceiveTask, "socket_rx", 256, ((void* )&client_sock), 2,
				NULL);

		taskENTER_CRITICAL();
		printf("Client: %s %d\r\n", inet_ntoa(lastSourceAddress.sin_addr),
				htons(lastSourceAddress.sin_port));
		taskEXIT_CRITICAL();
	}

//Wait until TCP client is connected with the server, then start receiving data packets when TCP
//communication is established:

	return rval;
}

static void ReceiveTask(void * pvParameters)
{
	int32 rxSocket = *((int32*) pvParameters);
	struct sockaddr_in sourceAddress;
	int32 addressSize = sizeof(sourceAddress);
	getpeername(rxSocket, (struct sockaddr* )&sourceAddress, &addressSize);

	uint8 * data = zalloc(RECEIVE_TASK_BUFFER_SIZE);
	int32 length = 0;
	int tempCount = 0;
	int indexOfMessageEnd;

	if (data != NULL)
	{
		//listen until socket is closed.
		while (rxSocket > 0)
		{
//			taskENTER_CRITICAL();
//			printf("receive\r\n");
//			taskEXIT_CRITICAL();

			tempCount = Receive(rxSocket, data + length,
			RECEIVE_TASK_BUFFER_SIZE - length);

//			taskENTER_CRITICAL();
//			printf("received\r\n");
//			taskEXIT_CRITICAL();

			if (tempCount > 0 && length + tempCount <= RECEIVE_TASK_BUFFER_SIZE)
			{
				length += tempCount;
				tempCount = 0;

				//check for end of message
				indexOfMessageEnd = Get_Index_Of_Message_End(data, length);

				if (indexOfMessageEnd > 0)
				{
//					taskENTER_CRITICAL();
//					printf("got a message\r\n");
//					taskEXIT_CRITICAL();

					//enqueue if we received message end.
					Enqueue(data, length, &sourceAddress);
					length = 0;
					data[0] = '\0';
				}
				else if (length >= RECEIVE_TASK_BUFFER_SIZE)
				{
//					taskENTER_CRITICAL();
//					printf("overflow\r\n");
//					taskEXIT_CRITICAL();

					//overflow. drop this message.
					length = 0;
				}
			}
//			else
//			{
//				taskENTER_CRITICAL();
//				printf("no data\r\n");
//				taskEXIT_CRITICAL();
//			}

//			taskENTER_CRITICAL();
//			printf("yield\r\n");
//			taskEXIT_CRITICAL();
			taskYIELD();
		}
	}

	free(data);
	lwip_close(rxSocket);
	--Task_Count;

	taskENTER_CRITICAL();
	printf("disconnected\r\n");
	taskEXIT_CRITICAL();

	vTaskDelete(NULL);
}

//reads data from the socket
static int32 Receive(int32 rxSocket, uint8_t * rxbuf, int32 maxRxCount)
{
//	taskENTER_CRITICAL();
//	printf("peek\r\n");
//	taskEXIT_CRITICAL();

	int32 rval = lwip_recv(rxSocket, (void*) rxbuf, maxRxCount, MSG_PEEK);

//	taskENTER_CRITICAL();
//	printf("peek returned %d\r\n", rval);
//	taskEXIT_CRITICAL();

	if (rval < 0)
	{
		int32 error;
		uint32 optionLength = sizeof(error);
		int getReturn = lwip_getsockopt(rxSocket, SOL_SOCKET, SO_ERROR, &error,
				&optionLength);
		//check errno to see if we timed out, or the connection's closed
		if (errno)
		{
			taskENTER_CRITICAL();
			printf("errno:%d", errno);
			taskEXIT_CRITICAL();
			rval = -1;
		}
		else
		{
			rval = 0;
		}
	}
	if (rval <= maxRxCount && rval > 0)
	{
		rval = lwip_recv(rxSocket, rxbuf, maxRxCount, 0);
		rxbuf[rval] = '\0';

//		taskENTER_CRITICAL();
//		printf("count: %d\r\nstr:[%s]\r\n", rval, rxbuf);
//		taskEXIT_CRITICAL();
	}

//	taskENTER_CRITICAL();
//	printf("receive done %d\r\n", rval);
//	taskEXIT_CRITICAL();

	return rval;
}

static int32 Get_Index_Of_Message_End(uint8 * buffer, int32 count)
{
	int32 rval = false;
	uint8 * bangIdx = strchr(buffer, '\n');

	if (bangIdx != NULL)
	{
		rval = (bangIdx - buffer);
	}

	return rval;
}

static bool Enqueue(uint8 * buffer, int32 count,
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
	rval = true;
	taskEXIT_CRITICAL();

//			taskENTER_CRITICAL();
////			printf("cont:[%s]\r\ndest:[%s]\r\nsource:[%s]",
////					Peek_Message(&incomingMessageQueue)->content,
////					Peek_Message(&incomingMessageQueue)->destination,
////					Peek_Message(&incomingMessageQueue)->source);
//			taskEXIT_CRITICAL();

//			taskENTER_CRITICAL();
//			Dequeue_Message(&incomingMessageQueue);
//			taskEXIT_CRITICAL();

//	taskENTER_CRITICAL();
//	buffer[count] = '\0';
//	printf("received: [%s]\r\n", tempMessage.content);
//	printf("rx serialized addr: [%s]\r\n", tempMessage.source);
//	printf("message was enqueued\r\n-----------------------------\r\n\r\n");
//	taskEXIT_CRITICAL();

	free(addrStringBuf);
//	taskENTER_CRITICAL();
//	printf("freed, returning\r\n");
//	taskEXIT_CRITICAL();

	return rval;
}
