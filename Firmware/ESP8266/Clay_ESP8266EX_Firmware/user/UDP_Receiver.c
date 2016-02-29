/*
 * UDP_Receive.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 *
 *      This class receives messages over UDP and puts them into a buffer.
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

#include "UDP_Receiver.h"
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
} UDP_Receiver_States;
////Globals   /////////////////////////////////////////////////////
bool Exclusive_Rx_Access;

////Local vars/////////////////////////////////////////////////////
static UDP_Receiver_States State;

static int ret;

static uint8_t *UDP_Rx_Buffer;
static uint16_t UDP_Rx_Count;

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

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static void Disconnect();
static bool Receive();

////Global implementations ////////////////////////////////////////
bool UDP_Receiver_Init()
{
	bool rval = false;
	UDP_Rx_Buffer = zalloc(UDP_RX_BUFFER_SIZE_BYTES);
	nNetTimeout = UDP_RX_TIMEOUT_MSEC;

	State = Disable;

	tempAddr = zalloc(32);
	Initialize_Message_Queue(&incomingMessageQueue);

//   printf("udp rx port: %u\n", htons(UDP_RX_PORT));
//   printf("start udp rx\n");
	xTaskCreate(UDP_Receiver_State_Step, "udprx1", 1024, NULL, 2, NULL);
//   printf("started udp rx\n");

	testCounter = 0;

	return rval;
}

void UDP_Receiver_State_Step()
{
	Connect();
	for (;;)
	{

		if (Receive())
		{
			taskENTER_CRITICAL();
			UDP_Rx_Buffer[UDP_Rx_Count] = '\0';
			printf("%d:[%s]\n", system_get_time(), UDP_Rx_Buffer);
			taskEXIT_CRITICAL();
		}
		taskYIELD();
	}

	for (;;)
	{
//      if (!(testCounter = (testCounter + 1) % 10000))
//      {
//         printf("udprx_state: %d\n", State);
//      }

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
//            vTaskDelay(2000 / portTICK_RATE_MS);
			if (Connect())
			{
//               printf("rx connected\n");
				State = Idle;
			}
			break;
		}

		case Idle:
		{
			if (Receive())
			{
				State = Enqueue_Message;
			}
			else if (Exclusive_Rx_Access)
			{
				State = Rx_Blocked;
			}
			break;
		}

		case Enqueue_Message:
		{
//            sinZeroSize = 0;
//            for (i = 0; i < SIN_ZERO_LEN; ++i)
//            {
//               sinZeroSize += sprintf(sinZeroStr + sinZeroSize, "%s%u", i == 0 ? "" : ",", lastSourceAddress.sin_zero[i]);
//            }

//            printf("original source addr: %u, fam: %u, len: %u, port: %u, zero: %s\n",
//                   ntohl(lastSourceAddress.sin_addr.s_addr),
//                   lastSourceAddress.sin_family,
//                   lastSourceAddress.sin_len,
//                   ntohs(lastSourceAddress.sin_port),
//                   sinZeroStr);
			//               printf("message addr rx %d\n", &tempMessage);
			Serialize_Address(&lastSourceAddress, tempAddr,
			MAXIMUM_DESTINATION_LENGTH);

//            printf("strlen addr: %d", strlen(tempAddr));
//            printf("rx'd from: [%s]\n", tempAddr);

			Initialize_Message(&tempMessage, tempAddr, tempAddr, UDP_Rx_Buffer);

//            printf("rx'd from: [%s]\n\n", tempAddr);
//            printf("message source: [%s]\n\n", tempMessage.source);

			//TODO: incoming queue
			Queue_Message(&incomingMessageQueue, &tempMessage);
//            Queue_Message(&outgoingMessageQueue, &tempMessage);

			//               printf("cont:[%s]\ndest:[%s]\nsource:[%s]",
			//                      Peek_Message(&outgoingMessageQueue)->content,
			//                      Peek_Message(&outgoingMessageQueue)->destination,
			//                      Peek_Message(&outgoingMessageQueue)->source);

			UDP_Rx_Buffer[UDP_Rx_Count] = '\0';
//            printf("received: [%s]\n", UDP_Rx_Buffer);
//            printf("rx serialized addr: [%s]\n", tempAddr);
//            printf("rx_done, going to data_received\n\n----------------\n");

			State = Idle;
			break;
		}

		case Rx_Blocked:
		{
			if (!Exclusive_Rx_Access)
			{
				State = Idle;
			}
			break;
		}

		case UDP_STATE_MAX:
		default:
		{
			break;
		}
		}

//      vTaskDelay(5 / portTICK_RATE_MS);
	}
}

////Local implementations /////////////////////////////////////////
static bool Connect()
{
	Connected = false;
	Exclusive_Rx_Access = false;

	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(UDP_RX_PORT);
	server_addr.sin_len = sizeof(server_addr);

	///create the socket
	do
	{
		sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock_fd == -1)
		{
			Connected = false;
			//         printf("ESP8266 UDP task > failed to create sock!\n");
			vTaskDelay(1000 / portTICK_RATE_MS);
		}
	} while (sock_fd == -1);
	//   printf("ESP8266 UDP task > socket OK!\n");

	//bind the socket
	do
	{
		ret = bind(sock_fd, (struct sockaddr * ) &server_addr,
				sizeof(server_addr));
		if (ret != 0)
		{
			//         printf("ESP8266 UDP task > captdns_task failed to bind sock!\n");
			vTaskDelay(1000 / portTICK_RATE_MS);
		}
	} while (ret != 0);
	Connected = true;
	//   printf("ESP8266 UDP task > bind OK!\n");

	return Connected;
}

static void Disconnect()
{
	if (UDP_Rx_Buffer)
	{
		free(UDP_Rx_Buffer);
		UDP_Rx_Buffer = NULL;
	}
	free(UDP_Rx_Buffer);
	close(sock_fd);
}

static bool Receive()
{
	bool rval = false;

	memset(UDP_Rx_Buffer, 0, UDP_RX_BUFFER_SIZE_BYTES);
	memset(&from, 0, sizeof(from));
	setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char * ) &nNetTimeout,
			sizeof(int));
	fromlen = sizeof(struct sockaddr_in);

	// attempt to receive
	ret = recvfrom(sock_fd, (uint8 * ) UDP_Rx_Buffer, UDP_RX_BUFFER_SIZE_BYTES,
			0, (struct sockaddr * ) &from, (socklen_t * ) &fromlen);

	if (ret > 0)
	{
		rval = true;
		UDP_Rx_Count = ret;

		//store the source address
		lastSourceAddress.sin_addr = from.sin_addr;
		lastSourceAddress.sin_family = from.sin_family;
		lastSourceAddress.sin_len = from.sin_len;
		lastSourceAddress.sin_port = from.sin_port;
		int i = 0;
		for (; i < SIN_ZERO_LEN; ++i)
		{
			lastSourceAddress.sin_zero[i] = from.sin_zero[i];
		}
	}

	return rval;
}

////cut snippets //////////////////////////////////////////////////////////////

//      ///this goes to the transmitter side.
//      if (pendingTxBytes)
//      {
//         //         printf("pending: %d - \"%s\"\r\n", pendingTxBytes, txBuf);
//         sendto(sock_fd, (uint8* ) txBuf, pendingTxBytes, 0, (struct sockaddr * ) &lastFrom, fromlen);
//         pendingTxBytes = 0;
//      }
//      ///end of transmitter side.
