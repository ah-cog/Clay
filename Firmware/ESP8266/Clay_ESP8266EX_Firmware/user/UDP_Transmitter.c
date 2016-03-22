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

#include "uart.h"

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

////Local vars/////////////////////////////////////////////////////
static UDP_Transmitter_States State;

static int ret;

static uint8_t *UDP_Tx_Buffer;
static uint16_t UDP_Tx_Count;

static struct sockaddr_in DestinationAddr;
static struct sockaddr_in server_addr;

static int32 sock_fd;
static int32 testCounter;

static Message_Type tempIgnoredMessageType;

static Message * m;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static bool Transmit();
static bool Message_Available();

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR UDP_Transmitter_Init()
{
	bool rval = false;

	UDP_Tx_Buffer = zalloc(UDP_TX_BUFFER_SIZE_BYTES);
	State = Disable;

	Initialize_Message_Queue(&outgoingUdpMessageQueue);

	xTaskCreate(UDP_Transmitter_State_Step, "udptx1", 512, NULL, 2, NULL);

	testCounter = 0;

	return rval;
}

void ICACHE_RODATA_ATTR UDP_Transmitter_State_Step()
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
			if (Connect())
			{
				State = Idle;
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
			m = Dequeue_Message(&outgoingUdpMessageQueue);
			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			strncpy(UDP_Tx_Buffer, m->content, UDP_TX_BUFFER_SIZE_BYTES);
			UDP_Tx_Count = strlen(m->content);
			taskEXIT_CRITICAL();

			uint8* addrStr;

			taskENTER_CRITICAL();
			Deserialize_Address(m->destination, &DestinationAddr,
					&tempIgnoredMessageType);
			taskEXIT_CRITICAL();

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

		if (!Message_Available())
		{
			taskYIELD();
		}
	}
}

////Local implementations /////////////////////////////////////////
static bool ICACHE_RODATA_ATTR Connect()
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
			vTaskDelay(1000 / portTICK_RATE_MS);
		}
	} while (sock_fd == -1);

	//bind the socket
	do
	{
		ret = bind(sock_fd, (struct sockaddr * ) &server_addr,
				sizeof(server_addr));
		if (ret != 0)
		{
			vTaskDelay(1000 / portTICK_RATE_MS);
		}
	} while (ret != 0);
	rval = true;

	return rval;
}

static bool Transmit()
{
	bool rval = false;
	rval = UDP_Tx_Count
			== sendto(sock_fd, (uint8* ) UDP_Tx_Buffer, UDP_Tx_Count, 0,
					(struct sockaddr * ) &DestinationAddr,
					sizeof(DestinationAddr));

	return rval;
}

static bool Message_Available()
{
	bool rval = false;

	taskENTER_CRITICAL();
	m = Peek_Message(&outgoingUdpMessageQueue);
	taskEXIT_CRITICAL();

	if (m != NULL)
	{
		rval = true;
	}

	return rval;
}