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
#include "TCP_Receiver.h"
#include "Clay_Config.h"

#include "Message_Queue.h"
#include "Message.h"

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable, Configure, Idle, Buffer_Message, Send_Message, TCP_STATE_MAX
} TCP_Transmitter_States;
////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static TCP_Transmitter_States State;

static uint8_t *TCP_Tx_Buffer;
static uint16_t TCP_Tx_Count;

static struct sockaddr_in DestinationAddr;

static int32 sock_fd;
static int32 testCounter;

Message_Type tempIgnoredMessageType;

static Message * m;

////Local Prototypes///////////////////////////////////////////////
static int tcpCreateSocket();
static bool tcpSend(int txSocket, uint8* data, uint32 length);
static bool Message_Available();

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR TCP_Transmitter_Init()
{
	bool rval = false;

	TCP_Tx_Buffer = zalloc(TCP_TX_BUFFER_SIZE_BYTES);
	State = Disable;

	Initialize_Message_Queue(&outgoingTcpMessageQueue);

	xTaskCreate(TCP_Transmitter_State_Step, "TCPtx1", 512, NULL, 2, NULL);

	testCounter = 0;

	return rval;
}

void ICACHE_RODATA_ATTR TCP_Transmitter_State_Step()
{
	for (;;)
	{
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

		case Idle:
		{
			if (Message_Available())
			{
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

			sock_fd = SocketListQuery(m->destination);

			taskENTER_CRITICAL();
			strncpy(TCP_Tx_Buffer, m->content, TCP_TX_BUFFER_SIZE_BYTES);
			TCP_Tx_Count = strlen(m->content);
			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			Deserialize_Address(m->destination, &DestinationAddr,
					&tempIgnoredMessageType);
			taskEXIT_CRITICAL();

			State = Send_Message;
			break;
		}

		case Send_Message:
		{
			//TODO: determine which socket the communication goes back to
			//	    if there's a socket open to the destination addr, use it
			//		otherwise create a socket and leave it open.

			if (sock_fd == -1)
			{
				sock_fd = tcpCreateSocket();
				if (!TCP_Open_Connection(sock_fd))
				{
					lwip_close(sock_fd);
				}
			}

			tcpSend(sock_fd, TCP_Tx_Buffer, TCP_Tx_Count);

			State = Idle;
			break;
		}

		case TCP_STATE_MAX:
		default:
		{
			break;
		}
		}
		if (!Message_Available())
		{
			taskYIELD();
		}
	}
}

////Local implementations /////////////////////////////////////////
static int ICACHE_RODATA_ATTR tcpCreateSocket()
{
	int txSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (-1 == txSocket)
	{
		lwip_close(txSocket);
	}

	return txSocket;
}

static bool ICACHE_RODATA_ATTR tcpSend(int txSocket, uint8 * data,
		uint32 length)
{
	bool rval = write(txSocket, data, length) == length;

	return true;
}

static bool Message_Available()
{
	bool rval = false;

	taskENTER_CRITICAL();
	m = Peek_Message(&outgoingTcpMessageQueue);
	taskEXIT_CRITICAL();

	if (m != NULL)
	{
		rval = true;
	}

	return rval;
}
