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
	Disable,
	Configure,
	ListenForConnect,
	ReceiveFromClient,
	Enqueue_Message,
	Rx_Blocked,
	Data_Received,
	UDP_STATE_MAX
} TCP_Receiver_States;

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static TCP_Receiver_States State;

static int ret;

static uint8_t *TCP_Rx_Buffer;
static int32 TCP_Rx_Count;

static size_t fromlen;

static struct sockaddr_in from;

static struct sockaddr_in lastSourceAddress;
static struct sockaddr_in server_addr;

static int nNetTimeout;

static int32 sock_fd;
static bool Connected;
static int32 testCounter;

//static char sinZeroStr[50];
//static int sinZeroSize;
//static int i;

Message tempMessage;
char * tempAddr;

//TODO: move to clay_config.
#define CONNECTION_ALIVE_TIME_us 200000
#define SERVER_PORT 1002
#define MAX_CONN    10
#define SERVER_IP "192.168.1.11"
//#define SERVER_PORT 1001

static int32 listenfd;
static int32 len;
static int sta_socket;
static struct sockaddr_in remote_ip;
static int32 client_sock;
static struct sockaddr_in remote_addr;
static uint16 httpd_server_port = 1002;

static uint32 Rx_Start_Time;
static uint32 Rx_Start_Time_temp;
static int temp_rx_counter;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static void Disconnect();
static bool Listen();
static int32 Receive();

////Local implementations /////////////////////////////////////////
bool TCP_Receiver_Init()
{
	bool rval = false;
	TCP_Rx_Buffer = zalloc(UDP_RX_BUFFER_SIZE_BYTES);
	nNetTimeout = UDP_RX_TIMEOUT_MSEC;

	State = Disable;

	tempAddr = zalloc(SOCKADDR_IN_SIZE_BYTES * 2); //*2 for safety.
	Initialize_Message_Queue(&incomingMessageQueue);

//   printf("udp rx port: %u\r\n", htons(UDP_RX_PORT));
//   printf("start udp rx\r\n");
	xTaskCreate(TCP_Receiver_State_Step, "tcprx1", 1024, NULL, 2, NULL);
//   printf("started udp rx\r\n");

	testCounter = 0;

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

				taskENTER_CRITICAL();
				printf("rx connected\r\n");
				taskEXIT_CRITICAL();
				State = ListenForConnect;
			}
			break;
		}

		case ListenForConnect:
		{
			if (Listen())
			{
				taskENTER_CRITICAL();
				printf("heard summat\r\n");
				taskEXIT_CRITICAL();
				TCP_Rx_Count = 0;
				Rx_Start_Time = system_get_time();
				Rx_Start_Time_temp = Rx_Start_Time;
				State = ReceiveFromClient;
			}
			break;
		}

		case ReceiveFromClient:
		{
			printf("time %d\r\n", system_get_time() / 1000);
			if ((system_get_time() - Rx_Start_Time_temp)
					< CONNECTION_ALIVE_TIME_us)
			{
				//TODO: combine receipts
				//TODO: return received count
				temp_rx_counter = Receive();
				TCP_Rx_Count += temp_rx_counter;
				if (temp_rx_counter > 0)
				{
					Rx_Start_Time_temp = system_get_time();
				}
			}
			else if (TCP_Rx_Count > 0)
			{
				//TODO: save the address from this connection so we can put into the message object.
				taskENTER_CRITICAL();
				printf("done receive\r\n");
				taskEXIT_CRITICAL();
				State = Enqueue_Message;
			}
			else
			{
				//TODO: disconnect here?
				printf("back to listen.\r\n");
				State = ListenForConnect;
			}
			break;
		}

		case Enqueue_Message:
		{
			taskENTER_CRITICAL();
			printf("enqueue.\r\n");
			taskEXIT_CRITICAL();
//            sinZeroSize = 0;
//            for (i = 0; i < SIN_ZERO_LEN; ++i)
//            {
//               sinZeroSize += sprintf(sinZeroStr + sinZeroSize, "%s%u", i == 0 ? "" : ",", lastSourceAddress.sin_zero[i]);
//            }

//            printf("original source addr: %u, fam: %u, len: %u, port: %u, zero: %s\r\n",
//                   ntohl(lastSourceAddress.sin_addr.s_addr),
//                   lastSourceAddress.sin_family,
//                   lastSourceAddress.sin_len,
//                   ntohs(lastSourceAddress.sin_port),
//                   sinZeroStr);
			//               printf("message addr rx %d\r\n", &tempMessage);
			taskENTER_CRITICAL();
			Serialize_Address(&lastSourceAddress, tempAddr,
			MAXIMUM_DESTINATION_LENGTH);
			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
//            printf("strlen addr: %d", strlen(tempAddr));
			printf("rx'd from: [%s]\r\n", tempAddr);
			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			Initialize_Message(&tempMessage, tempAddr, tempAddr, TCP_Rx_Buffer);
			taskEXIT_CRITICAL();

//            printf("rx'd from: [%s]\r\n\r\n", tempAddr);
//            printf("message source: [%s]\r\n\r\n", tempMessage.source);

			//TODO: incoming queue
//			WAIT_FOR_INCOMING_QUEUE();
			taskENTER_CRITICAL();
			Queue_Message(&incomingMessageQueue, &tempMessage);
			taskEXIT_CRITICAL();
//			RELEASE_INCOMING_QUEUE();
//            Queue_Message(&outgoingMessageQueue, &tempMessage);

//			taskENTER_CRITICAL();
////			printf("cont:[%s]\r\ndest:[%s]\r\nsource:[%s]",
////					Peek_Message(&incomingMessageQueue)->content,
////					Peek_Message(&incomingMessageQueue)->destination,
////					Peek_Message(&incomingMessageQueue)->source);
//			taskEXIT_CRITICAL();

//			taskENTER_CRITICAL();
//			WAIT_FOR_INCOMING_QUEUE();
//			Dequeue_Message(&incomingMessageQueue);
//			RELEASE_INCOMING_QUEUE();
//			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			TCP_Rx_Buffer[TCP_Rx_Count] = '\0';
			printf("received: [%s]\r\n", TCP_Rx_Buffer);
			printf("rx serialized addr: [%s]\r\n", tempAddr);
			printf(
					"rx_done, going to data_received\r\n\r\n----------------\r\n");
			taskEXIT_CRITICAL();

			State = ListenForConnect;
			break;
		}

		case Rx_Blocked:
		{
//			if (!Exclusive_Rx_Access)
//			{
			State = ListenForConnect;
//			}
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
		printf("ESP8266 TCP server task > socket error\r\n");
		vTaskDelay(1000 / portTICK_RATE_MS);
		rval = false;
	}
	else
	{
		rval = true;
		printf("ESP8266 TCP server task > create socket: %d\r\n", listenfd);
	}

	if (rval)
	{
		/* Bind to the local port */
		ret = bind(listenfd, (struct sockaddr * )&server_addr,
				sizeof(server_addr));
		if (ret != 0)
		{
			printf("ESP8266 TCP server task > bind fail\r\n");
			vTaskDelay(1000 / portTICK_RATE_MS);
			rval = false;
			close(listenfd);
		}
		else
		{
			rval = true;
			printf("ESP8266 TCP server task > port:%d\r\n",
					ntohs(server_addr.sin_port));
		}
	}
//Establish TCP server interception:
	if (rval)
	{
		/* Listen to the local connection */
		ret = listen(listenfd, MAX_CONN);
		if (ret != 0)
		{
			close(listenfd);
			printf("ESP8266 TCP server task > failed to set listen queue!\r\n");
			vTaskDelay(1000 / portTICK_RATE_MS);
			rval = false;
		}
		else
		{
			rval = true;
			printf("ESP8266 TCP server task > listen ok\r\n");
		}

	}

	return rval;
}

static bool Listen()
{
	bool rval = false;

	len = sizeof(struct sockaddr_in);
	printf("ESP8266 TCP server task > wait client\r\n");
	/*block here waiting remote connect request*/
	if ((client_sock = accept(listenfd, (struct sockaddr * )&remote_addr,
			(socklen_t * )&len)) < 0)
	{
		printf("ESP8266 TCP server task > accept fail\r\n");
		rval = false;
	}
	else
	{
		//timeout alive time in ms / 10. We should call this about 10 times before timing out.
		int millis = (CONNECTION_ALIVE_TIME_us / 1000) / 10;
		setsockopt(client_sock, SOL_SOCKET, SO_RCVTIMEO, &millis,
				sizeof(millis));

		rval = true;
	}

	//Wait until TCP client is connected with the server, then start receiving data packets when TCP
	//communication is established:

	printf("ESP8266 TCP server task > Client from %s %d\r\n",
			inet_ntoa(remote_addr.sin_addr), htons(remote_addr.sin_port));

	return rval;
}

static int32 Receive()
{
	int32 rval = -1;

	if ((rval = read(client_sock, TCP_Rx_Buffer, UDP_RX_BUFFER_SIZE_BYTES)) > 0)
	{
		printf("read:%d\r\n", rval);
		TCP_Rx_Buffer[rval] = '\0';
		printf("wrote null\r\n", rval);
		printf(
				"ESP8266 TCP server task > read data success %d!\r\nESP8266 TCP server task > %s\r\n",
				rval, TCP_Rx_Buffer);
	}

	return rval;
}

static void Disconnect()
{
	if (TCP_Rx_Buffer)
	{
		free(TCP_Rx_Buffer);
		TCP_Rx_Buffer = NULL;
	}
	free(TCP_Rx_Buffer);
	close(sock_fd);
}

