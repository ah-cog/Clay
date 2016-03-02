/*
 * UDP_Transmitter.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 *
 *      This class consumes (Clay_Message)s from a queue and transmits them over UDP
 */

/*
 * States:
 *      Disabled -- no transmissions occur
 *      Configure -- Create a UDP socket and prepare it for listening.
 *          -upon completion, we go to Idle
 *      Idle -- no messages available in buffer
 *          -messages become available, we go to Buffer_Message
 *          -Disable message sends us back to Disabled
 *      Buffer_Message -- message was available in queue
 *          -Message consumed out of queue into transmit buffer. Go to Send_Message. Leave message in queue for now.
 *          -Disable message sends us back to Disabled.
 *      Send_Message (combine with Buffer_Message?)
 *          -Send the message waiting in the buffer. Return to idle upon successful completion
 *      Retry?
 * */

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "UDP_Transmitter.h"
#include "Clay_Config.h"

#include "Message_Queue.h"
#include "Message.h"

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable, Configure, Idle, Buffer_Message, Send_Message, UDP_STATE_MAX
} UDP_Transmitter_States;
////Globals   /////////////////////////////////////////////////////
volatile bool OutgoingQueueLock;

////Local vars/////////////////////////////////////////////////////
static UDP_Transmitter_States State;

static int ret;

static uint8_t *UDP_Tx_Buffer;
static uint16_t UDP_Tx_Count;

static size_t fromlen;

static struct sockaddr_in DestinationAddr;
static struct sockaddr_in from;
static struct sockaddr_in lastFrom;
static struct sockaddr_in server_addr;

static int nNetTimeout;

static int32 sock_fd;
static bool Connected;
static int32 testCounter;

static Message * m;

//static char sinZeroStr[50];
//static int sinZeroSize;
//static int i;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static void Disconnect();
static bool Transmit();

////Global implementations ////////////////////////////////////////
bool UDP_Transmitter_Init()
{
	bool rval = false;

//   printf("udp_tx_init\n");
	UDP_Tx_Buffer = zalloc(UDP_TX_BUFFER_SIZE_BYTES);
	State = Disable;

	OutgoingQueueLock = false; //init
	Initialize_Message_Queue(&outgoingMessageQueue);

//   Initialize_Message(&mm, source, source, content);
//   m = &mm;

//   printf("udp tx port: %u\n", htons(UDP_TX_PORT));
//   printf("start udp tx\n");
	xTaskCreate(UDP_Transmitter_State_Step, "udptx1", 1024, NULL, 2, NULL);
//   printf("started udp tx\n");

	testCounter = 0;

	return rval;
}

void UDP_Transmitter_State_Step()
{
//	Connect();
//
//	memset(&DestinationAddr, 0, sizeof(DestinationAddr));
//
//	DestinationAddr.sin_family = AF_INET;
//	DestinationAddr.sin_addr.s_addr = htonl(3232235778U);
//	DestinationAddr.sin_port = htons(1201);
//	DestinationAddr.sin_len = sizeof(DestinationAddr);
//
//	taskENTER_CRITICAL();
//	sprintf(UDP_Tx_Buffer, "test message\n");
//	UDP_Tx_Count = 13;
//	taskEXIT_CRITICAL();
//
//	for (;;)
//	{
//		Transmit();
//		vTaskDelay(2 / portTICK_RATE_MS);
////		taskYIELD();
//	}

	for (;;)
	{
//      if (!(testCounter = (testCounter + 1) % 10000))
//      {
//         printf("udptx_state: %d\n", State);
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
			if (Connect())
			{
//               printf("tx connected\n");
				State = Idle;
			}
			break;
		}

		case Idle:
		{
//          if (1 || Peek_Message(&outgoingMessageQueue) != NULL)
			taskENTER_CRITICAL();
			m = Peek_Message(&outgoingMessageQueue);
			taskEXIT_CRITICAL();

			if (m != NULL)
			{
//				printf("cont:[%s]\ndest:[%s]\nsource:[%s]",
//						Peek_Message(&outgoingMessageQueue)->content,
//						Peek_Message(&outgoingMessageQueue)->destination,
//						Peek_Message(&outgoingMessageQueue)->source);
//
//				taskENTER_CRITICAL();
//				printf("message available\n");
//				taskEXIT_CRITICAL();
				State = Buffer_Message;
			}
			break;
		}

		case Buffer_Message:
		{
			memset(&DestinationAddr, 0, sizeof(DestinationAddr));

			taskENTER_CRITICAL();
			m = Dequeue_Message(&outgoingMessageQueue);
			taskEXIT_CRITICAL();

//			printf("message addr tx %d\n", m);
//			printf("lookin for newline in [%s]\n", m->content);
//			taskENTER_CRITICAL();
//			char* mLen = strchr(m->content, '\n') + 1; //+1 as strchr rval points to the chr.
//			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
//			printf("copy content to buffer. %d bytes, %s\n", mLen - m->content,
//					m->content);
			strncpy(UDP_Tx_Buffer, m->content, UDP_TX_BUFFER_SIZE_BYTES);
			UDP_Tx_Count = strlen(m->content);
//			printf("done\n");
			taskEXIT_CRITICAL();

//			printf("tx serialized addr: [%s]\n", m->destination);
			taskENTER_CRITICAL();
			Deserialize_Address(m->destination, MAXIMUM_DESTINATION_LENGTH,
					&DestinationAddr);
			taskEXIT_CRITICAL();

//            printf("message available\n");
//            sinZeroSize = 0;
//            for (i = 0; i < SIN_ZERO_LEN; ++i)
//            {
//               sinZeroSize += sprintf(sinZeroStr + sinZeroSize, "%s%u", i == 0 ? "" : ",", DestinationAddr.sin_zero[i]);
//            }

//            printf("tx msg: [%s]\n", UDP_Tx_Buffer);
//            printf("deserialized addr: %u, fam: %u, len: %u, port: %u, zero: %s\n",
//                   ntohl(DestinationAddr.sin_addr.s_addr),
//                   DestinationAddr.sin_family,
//                   DestinationAddr.sin_len,
//                   ntohs(DestinationAddr.sin_port),
//                   sinZeroStr);
//            printf("buffer_message done, going to send_message\n\n----------------\n\n\n");
			State = Send_Message;
			break;
		}

		case Send_Message:
		{
			Transmit();
			State = Idle;
			break;
		}

		case UDP_STATE_MAX:
		default:
		{
			break;
		}
		}
		taskYIELD();
//      vTaskDelay(5 / portTICK_RATE_MS);
	}
}

////Local implementations /////////////////////////////////////////
static bool Connect()
{
	bool rval = false;

	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(UDP_TX_PORT);
	server_addr.sin_len = sizeof(server_addr);

	///create the socket
	do
	{
		sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock_fd == -1)
		{
//         printf("ESP8266 UDP task > failed to create sock!\n");
			vTaskDelay(1000 / portTICK_RATE_MS);
		}
	} while (sock_fd == -1);
//   printf("ESP8266 UDP task > socket OK!\n");

	//bind the socket
	do
	{
//      printf("sock_fd: %d", sock_fd);
		ret = bind(sock_fd, (struct sockaddr * ) &server_addr,
				sizeof(server_addr));
		if (ret != 0)
		{
//         printf("ESP8266 UDP task > captdns_task failed to bind sock!\n");
			vTaskDelay(1000 / portTICK_RATE_MS);
		}
	} while (ret != 0);
//   printf("ESP8266 UDP task > bind OK!\n");
	rval = true;

	return rval;
}

static void Disconnect()
{
	if (UDP_Tx_Buffer)
	{
		free(UDP_Tx_Buffer);
		UDP_Tx_Buffer = NULL;
	}
	free(UDP_Tx_Buffer);
	close(sock_fd);
}

static bool Transmit()
{
	//TODO: there is probably still something wrong with the serialization; I would expect to be able to return the message
	//      back to the same port. This works with nc64 -u -l -p UDP_RX_PORT, though. Gonna run with it for now.
	DestinationAddr.sin_port = htons(UDP_TX_PORT);
//	taskENTER_CRITICAL();
//	printf("sending %d bytes: [%s]\n", UDP_Tx_Count, UDP_Tx_Buffer);
//	printf("to %u.%u.%u.%u:%u\n\n-----\n",
//			DestinationAddr.sin_addr.s_addr & 0xFF,
//			(DestinationAddr.sin_addr.s_addr >> 8) & 0xFF,
//			(DestinationAddr.sin_addr.s_addr >> 16) & 0xFF,
//			(DestinationAddr.sin_addr.s_addr >> 24) & 0xFF,
//			ntohs(DestinationAddr.sin_port));
//	taskEXIT_CRITICAL();

	bool rval = false;
	rval = UDP_Tx_Count
			== sendto(sock_fd, (uint8* ) UDP_Tx_Buffer, UDP_Tx_Count, 0,
					(struct sockaddr * ) &DestinationAddr,
					sizeof(DestinationAddr));

	return rval;
}

////cut snippets //////////////////////////////////////////////////////////////

//   //cleanup stuff. gone, or maybe we create another state?
//   if (UDP_Rx_Buffer)
//   {
//      free(UDP_Rx_Buffer);
//      UDP_Rx_Buffer = NULL;
//   }
//   free(UDP_Rx_Buffer);
//   close(sock_fd);
