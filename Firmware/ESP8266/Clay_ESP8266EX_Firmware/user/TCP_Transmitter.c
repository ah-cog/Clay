/*
 * TCP_Transmitter.c
 *
 *  Created on: Mar 12, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "uart.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "TCP_Transmitter.h"
#include "Clay_Config.h"

#include "Message_Queue.h"
#include "Message.h"

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable, Configure, Idle, Buffer_Message, Send_Message, TCP_STATE_MAX
} TCP_Transmitter_States;
////Globals   /////////////////////////////////////////////////////
volatile bool OutgoingQueueLock;

////Local vars/////////////////////////////////////////////////////
static TCP_Transmitter_States State;

static int ret;

static uint8_t *TCP_Tx_Buffer;
static uint16_t TCP_Tx_Count;

static size_t fromlen;

static struct sockaddr_in DestinationAddr;
static struct sockaddr_in from;
static struct sockaddr_in lastFrom;
static struct sockaddr_in server_addr;

static int nNetTimeout;

static int32 sock_fd;
static bool Connected;
static int32 testCounter;

Message_Type tempIgnoredMessageType;

static Message * m;

static char sinZeroStr[50];
static int sinZeroSize;
static int i;

////Local Prototypes///////////////////////////////////////////////
static bool Connect(struct sockaddr_in * destinationAddr, int * txSocket);
static void Disconnect();

static int tcpCreateSocket();
static bool tcpConnect(int txSocket, struct sockaddr_in * remote_ip);
static bool tcpSend(int * txSocket, uint8* data, uint32 length);

////Global implementations ////////////////////////////////////////
bool TCP_Transmitter_Init()
{
	bool rval = false;

	TCP_Tx_Buffer = zalloc(TCP_TX_BUFFER_SIZE_BYTES);
	State = Disable;

	OutgoingQueueLock = false; //init
	Initialize_Message_Queue(&outgoingTcpMessageQueue);

	xTaskCreate(TCP_Transmitter_State_Step, "TCPtx1", 1024, NULL, 2, NULL);

	testCounter = 0;

	return rval;
}

void TCP_Transmitter_State_Step()
{
//	memset(&DestinationAddr, 0, sizeof(DestinationAddr));
//	char addrStr[] = "192.168.1.2";
//	char serializedAddr[100] = "TCP,192.168.1.2:9999";
//	Message_Type mt;
//	bool txOk;
//
//	sprintf(TCP_Tx_Buffer, "test message");
//	TCP_Tx_Count = 13;
//
//	Deserialize_Address(serializedAddr, 100, &DestinationAddr, &mt);
//
//	for (;;)
//	{
//		if (Connect(&DestinationAddr))
//		{
//			taskENTER_CRITICAL();
//			printf("sending %d bytes: [%s]\r\n", TCP_Tx_Count, TCP_Tx_Buffer);
//			printf("to %u.%u.%u.%u:%u\r\n\r\n-----\r\n",
//					DestinationAddr.sin_addr.s_addr & 0xFF,
//					(DestinationAddr.sin_addr.s_addr >> 8) & 0xFF,
//					(DestinationAddr.sin_addr.s_addr >> 16) & 0xFF,
//					(DestinationAddr.sin_addr.s_addr >> 24) & 0xFF,
//					ntohs(DestinationAddr.sin_port));
//			UART_WaitTxFifoEmpty(UART0);
//			taskEXIT_CRITICAL();
//
//			tcpSend(sock_fd, TCP_Tx_Buffer, TCP_Tx_Count);
//		}
//		else
//		{
//			taskENTER_CRITICAL();
//			printf("no connect\r\n");
//			taskEXIT_CRITICAL();
//		}
//	}

	for (;;)
	{
//      if (!(testCounter = (testCounter + 1) % 10000))
//      {
//         printf("TCPtx_state: %d\r\n", State);
//      }

		switch (State)
		{
		case Disable:
		{
			if (wifi_station_get_connect_status() == STATION_GOT_IP)
			{
				State = Idle;
				sock_fd = -1;
			}
			break;
		}

		case Configure:
		{
//			if (Connect())
//			{
//				State = Idle;
//			}
			break;
		}

		case Idle:
		{
			taskENTER_CRITICAL();
			m = Peek_Message(&outgoingTcpMessageQueue);
			taskEXIT_CRITICAL();

			if (m != NULL)
			{
//				taskENTER_CRITICAL();
//				printf("cont:[%s]\r\ndest:[%s]\r\nsource:[%s]",
//						Peek_Message(&outgoingTcpMessageQueue)->content,
//						Peek_Message(&outgoingTcpMessageQueue)->destination,
//						Peek_Message(&outgoingTcpMessageQueue)->source);
//				taskEXIT_CRITICAL();
				State = Buffer_Message;
			}
			break;
		}

		case Buffer_Message:
		{
			memset(&DestinationAddr, 0, sizeof(DestinationAddr));

			taskENTER_CRITICAL();
			m = Dequeue_Message(&outgoingTcpMessageQueue);
			taskEXIT_CRITICAL();

//			printf("message addr tx %d\r\n", m);
//			printf("lookin for newline in [%s]\r\n", m->content);
//			taskENTER_CRITICAL();
//			char* mLen = strchr(m->content, '\r\n') + 1; //+1 as strchr rval points to the chr.
//			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
//			printf("copy content to buffer. %d bytes, %s\r\n", mLen - m->content,
//					m->content);
			strncpy(TCP_Tx_Buffer, m->content, TCP_TX_BUFFER_SIZE_BYTES);
			TCP_Tx_Count = strlen(m->content);
//			printf("done\r\n");
			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
//			printf("tx serialized addr: [%s]\r\n", m->destination);
			Deserialize_Address(m->destination, MAXIMUM_DESTINATION_LENGTH,
					&DestinationAddr, &tempIgnoredMessageType);
			taskEXIT_CRITICAL();

//			taskENTER_CRITICAL();
//			printf("message available\r\n");
//			sinZeroSize = 0;
//			for (i = 0; i < SIN_ZERO_LEN; ++i)
//			{
//				sinZeroSize += sprintf(sinZeroStr + sinZeroSize, "%s%u",
//						i == 0 ? "" : ",", DestinationAddr.sin_zero[i]);
//			}
//
////            printf("tx msg: [%s]\r\n", TCP_Tx_Buffer);
//			printf(
//					"deserialized addr: %s, fam: %u, len: %u, port: %u, zero: %s\r\n",
//					inet_ntoa(DestinationAddr.sin_addr.s_addr),
//					DestinationAddr.sin_family, DestinationAddr.sin_len,
//					ntohs(DestinationAddr.sin_port), sinZeroStr);
//			taskEXIT_CRITICAL();
//            printf("buffer_message done, going to send_message\r\n\r\n----------------\r\n\r\n\r\n");
			State = Send_Message;
			break;
		}

		case Send_Message:
		{
			if (sock_fd != -1 || Connect(&DestinationAddr, &sock_fd))
			{
				tcpSend(&sock_fd, TCP_Tx_Buffer, TCP_Tx_Count);
			}

			State = Idle;
			break;
		}

		case TCP_STATE_MAX:
		default:
		{
			break;
		}
		}
//		taskYIELD();
//      vTaskDelay(5 / portTICK_RATE_MS);
	}
}

////Local implementations /////////////////////////////////////////
static bool Connect(struct sockaddr_in * destinationAddr, int * txSocket)
{
	bool rval;

	*txSocket = tcpCreateSocket();

	if (*txSocket > 0)
	{
		rval = tcpConnect(*txSocket, destinationAddr);
	}
	else
	{
		rval = false;
	}

	return rval;
}

static void Disconnect(int * txSocket)
{
	lwip_shutdown(*txSocket, 0);
	lwip_close(*txSocket);
	*txSocket = -1;
}

static int tcpCreateSocket()
{
	int txSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (-1 == txSocket)
	{
		close(txSocket);
		vTaskDelay(1000 / portTICK_RATE_MS);

		taskENTER_CRITICAL();
		printf("tcp socket fail!\r\n");
		taskEXIT_CRITICAL();
	}
	//connect timeout not implemented.
//	else
//	{
//		int millis = TCP_TRANSMIT_CONNECT_TIMEOUT_ms;
//		setsockopt(txSocket, SOL_SOCKET, SO_CONTIMEO, &millis, sizeof(millis));
//	}

	return txSocket;
}

static bool tcpConnect(int txSocket, struct sockaddr_in * remote_ip)
{
	bool rval = false;

	taskENTER_CRITICAL();
//	printf("connect to %u.%u.%u.%u:%u\r\n", remote_ip->sin_addr.s_addr & 0xFF,
//			(remote_ip->sin_addr.s_addr >> 8) & 0xFF,
//			(remote_ip->sin_addr.s_addr >> 16) & 0xFF,
//			(remote_ip->sin_addr.s_addr >> 24) & 0xFF,
//			ntohs(remote_ip->sin_port));
//	printf("socket:%d\r\n", txSocket);
	UART_WaitTxFifoEmpty(UART0);
	taskEXIT_CRITICAL();

	int connectResult = connect(txSocket, (struct sockaddr * )(remote_ip),
			sizeof(struct sockaddr));

	if (connectResult != 0)
	{

		int32 error = 0;
		uint32 optionLength = sizeof(error);
		int getReturn = lwip_getsockopt(txSocket, SOL_SOCKET, SO_ERROR, &error,
				&optionLength);

//		taskENTER_CRITICAL();
//		printf("connect error:%d\r\n\r\n", error);
//		taskEXIT_CRITICAL();

		close(txSocket);

		rval = false;
	}
	else
	{
		rval = true;
	}

	return rval;
}

static bool tcpSend(int * txSocket, uint8 * data, uint32 length)
{
	bool rval = write(*txSocket, data, length) == length;

	if (!rval)
	{
//		taskENTER_CRITICAL();
//		printf("tcp send fail\r\n");
//		taskEXIT_CRITICAL();
		Disconnect(txSocket);
	}
	else
	{
//		taskENTER_CRITICAL();
//		printf("tcp send success\r\n");
//		taskEXIT_CRITICAL();
	}

	return true;
}
