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
	Idle,
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
static uint16_t TCP_Rx_Count;

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

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static void Disconnect();
static bool Receive();

////Local implementations /////////////////////////////////////////
bool TCP_Receiver_Init()
{
	bool rval = false;
	TCP_Rx_Buffer = zalloc(UDP_RX_BUFFER_SIZE_BYTES);
	nNetTimeout = UDP_RX_TIMEOUT_MSEC;

	State = Disable;

	tempAddr = zalloc(SOCKADDR_IN_SIZE_BYTES * 2); //*2 for safety.
	Initialize_Message_Queue(&incomingMessageQueue);

//   printf("udp rx port: %u\n", htons(UDP_RX_PORT));
//   printf("start udp rx\n");
	xTaskCreate(TCP_Receiver_State_Step, "tcprx1", 1024, NULL, 2, NULL);
//   printf("started udp rx\n");

	testCounter = 0;

	return rval;
}

void TCP_Receiver_State_Step()
{
	while (!Connect())
		;
	for (;;)
	{

		if (Receive())
		{
			taskENTER_CRITICAL();
			TCP_Rx_Buffer[TCP_Rx_Count] = '\0';
			printf("%d:[%s]\n", system_get_time(), TCP_Rx_Buffer);
			taskEXIT_CRITICAL();
		}
		taskYIELD();
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
		printf("ESP8266 TCP server task > socket error\n");
		vTaskDelay(1000 / portTICK_RATE_MS);
		rval = false;
	}
	else
	{
		rval = true;
		printf("ESP8266 TCP server task > create socket: %d\n", listenfd);
	}

	if (rval)
	{
		/* Bind to the local port */
		ret = bind(listenfd, (struct sockaddr * )&server_addr,
				sizeof(server_addr));
		if (ret != 0)
		{
			printf("ESP8266 TCP server task > bind fail\n");
			vTaskDelay(1000 / portTICK_RATE_MS);
			rval = false;
			close(listenfd);
		}
		else
		{
			rval = true;
			printf("ESP8266 TCP server task > port:%d\n",
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
			printf("ESP8266 TCP server task > failed to set listen queue!\n");
			vTaskDelay(1000 / portTICK_RATE_MS);
			rval = false;
		}
		else
		{
			rval = true;
			printf("ESP8266 TCP server task > listen ok\n");
		}

	}

	return rval;
}

static bool Receive()
{
	bool rval = false;

	//Wait until TCP client is connected with the server, then start receiving data packets when TCP
	//communication is established:

	len = sizeof(struct sockaddr_in);
	printf("ESP8266 TCP server task > wait client\n");
	/*block here waiting remote connect request*/
	if ((client_sock = accept(listenfd, (struct sockaddr * )&remote_addr,
			(socklen_t * )&len)) < 0)
	{
		printf("ESP8266 TCP server task > accept fail\n");
		rval = false;
	}
	else
	{
		rval = true;
	}

	if (rval)
	{
		printf("ESP8266 TCP server task > Client from %s %d\n",
				inet_ntoa(remote_addr.sin_addr), htons(remote_addr.sin_port));

		while ((TCP_Rx_Count = read(client_sock, TCP_Rx_Buffer, 128)) > 0)
		{
			TCP_Rx_Buffer[TCP_Rx_Count] = 0;
			printf(
					"ESP8266 TCP server task > read data success %d!\nESP8266 TCP server task > %s\n",
					TCP_Rx_Count, TCP_Rx_Buffer);
			rval = true;
		}

		if (TCP_Rx_Count <= 0)
		{
			printf("ESP8266 TCP server task > read data fail!\n");
			rval = false;
		}
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

///may be useful for transmit

//////working demo:
//#define SERVER_IP "192.168.1.12"
////#define SERVER_PORT 1001
//
//int sta_socket;
//struct sockaddr_in remote_ip;
//uint8 * pbuf;
//int recbytes;
//
//////////////////////////////////////////////////////////////////////////////
//#define SERVER_PORT 1002
//#define MAX_CONN    10
//
//bool Connect_Server()
//{
//	int32 listenfd;
//	//int32 ret;
//	struct sockaddr_in server_addr, remote_addr;
//	int stack_counter = 0;
//	uint16 httpd_server_port = 1002;
//
//	/* Construct local address structure */
//	memset(&server_addr, 0, sizeof(server_addr)); /* Zero out structure */
//	server_addr.sin_family = AF_INET; /* Internet address family */
//	server_addr.sin_addr.s_addr = INADDR_ANY; /* Any incoming interface */
//	server_addr.sin_len = sizeof(server_addr);
//	server_addr.sin_port = htons(httpd_server_port); /* Local port */
//	/* Create socket for incoming connections */
//	do
//	{
//		listenfd = socket(AF_INET, SOCK_STREAM, 0);
//		if (listenfd == -1)
//		{
//			printf("ESP8266 TCP server task > socket error\n");
//			vTaskDelay(1000 / portTICK_RATE_MS);
//		}
//	} while (listenfd == -1);
//	printf("ESP8266 TCP server task > create socket: %d\n", listenfd);
//	/* Bind to the local port */
//	do
//	{
//		ret = bind(listenfd, (struct sockaddr * )&server_addr,
//				sizeof(server_addr));
//		if (ret != 0)
//		{
//			printf("ESP8266 TCP server task > bind fail\n");
//			vTaskDelay(1000 / portTICK_RATE_MS);
//		}
//	} while (ret != 0);
//	printf("ESP8266 TCP server task > port:%d\n", ntohs(server_addr.sin_port));
////Establish TCP server interception:
//	do
//	{
//		/* Listen to the local connection */
//		ret = listen(listenfd, MAX_CONN);
//		if (ret != 0)
//		{
//			printf("ESP8266 TCP server task > failed to set listen queue!\n");
//			vTaskDelay(1000 / portTICK_RATE_MS);
//		}
//	} while (ret != 0);
//	printf("ESP8266 TCP server task > listen ok\n");
////Wait until TCP client is connected with the server, then start receiving data packets when TCP
////communication is established
//
//	int32 client_sock;
//	int32 len = sizeof(struct sockaddr_in);
//	for (;;)
//	{
//		printf("ESP8266 TCP server task > wait client\n");
//		/*block here waiting remote connect request*/
//		if ((client_sock = accept(listenfd, (struct sockaddr * )&remote_addr,
//				(socklen_t * )&len)) < 0)
//		{
//			printf("ESP8266 TCP server task > accept fail\n");
//			continue;
//		}
//		printf("ESP8266 TCP server task > Client from %s %d\n",
//				inet_ntoa(remote_addr.sin_addr),
//				 htons(remote_addr.sin_port));
//		char *recv_buf = (char *) zalloc(128);
//		while ((recbytes = read(client_sock, recv_buf, 128)) > 0)
//		{
//			recv_buf[recbytes] = 0;
//			printf(
//					"ESP8266 TCP server task > read data success %d!\nESP8266 TCP server task > %s\n",
//					recbytes, recv_buf);
//		}
//		free(recv_buf);
//		if (recbytes <= 0)
//		{
//			printf("ESP8266 TCP server task > read data fail!\n");
//			close(client_sock);
//		}
//	}
//
//}

