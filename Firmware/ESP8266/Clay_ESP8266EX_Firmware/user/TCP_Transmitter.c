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

static struct sockaddr_in destination_addr;

static int32 sock_fd;
static int32 test_counter;
static int32 tx_fail_count;

Message_Type temp_ignored_message_type;

static Message * m;
static Message message_temp;

////Local Prototypes///////////////////////////////////////////////
static int TCP_Connect_Socket(struct sockaddr_in * remote_addr);
static bool TCP_Send(int tx_socket, uint8* data, uint32 length);
static bool Message_Available();

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR TCP_Transmitter_Init()
{
	bool rval = false;

	TCP_Tx_Buffer = zalloc(TCP_TX_BUFFER_SIZE_BYTES);
	State = Disable;

	SocketListInitialize();
	Initialize_Message_Queue(&outgoing_TCP_message_queue);

	xTaskCreate(TCP_Transmitter_State_Step, "TCPtx1", 512, NULL, 2, NULL);

	test_counter = 0;

	return rval;
}

void ICACHE_RODATA_ATTR TCP_Transmitter_State_Step()
{
//	Message test_message;

//	Initialize_Message(&test_message, "TCP,10.0.0.6:1002\x12",
//			"TCP,10.0.0.2:1002\x12", "a test\n");

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
//			Queue_Message(&outgoingTcpMessageQueue, &test_message);

			if (Message_Available())
			{
				State = Buffer_Message;
			}
			break;
		}

		case Buffer_Message:
		{
			memset(&destination_addr, 0, sizeof(destination_addr));

			taskENTER_CRITICAL();
			m = Dequeue_Message(&outgoing_TCP_message_queue);

			Initialize_Message(&message_temp, message_type_strings[MESSAGE_TYPE_TCP],
					m->source, m->destination, m->content);
			m = &message_temp;
			taskEXIT_CRITICAL();

			sock_fd = SocketListQuery(message_temp.destination);

			taskENTER_CRITICAL();
			strncpy(TCP_Tx_Buffer, message_temp.content,
			TCP_TX_BUFFER_SIZE_BYTES);
			TCP_Tx_Count = strlen(message_temp.content);
			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			Deserialize_Address(message_temp.destination, &destination_addr,
					&temp_ignored_message_type);
			taskEXIT_CRITICAL();

//			taskENTER_CRITICAL();
//			printf("remote addr:%s:%d, size:%d\r\n",
//					inet_ntoa(destination_addr.sin_addr.s_addr),
//					ntohs(destination_addr.sin_port),
//					sizeof(struct sockaddr_in));
//			taskEXIT_CRITICAL();

			tx_fail_count = 0;
			State = Send_Message;
			break;
		}

		case Send_Message:
		{
			if (sock_fd == -1)
			{
				sock_fd = TCP_Connect_Socket(&destination_addr);

//				taskENTER_CRITICAL();
//				printf("\r\n\r\nsock:%d\r\n", sock_fd);
//				taskEXIT_CRITICAL();

				if (sock_fd != -1)
				{
//					taskENTER_CRITICAL();
//					printf("connected tx sock:%d\r\n", sock_fd);
//					taskEXIT_CRITICAL();

					if (!TCP_Start_Task(&sock_fd))
					{
//						taskENTER_CRITICAL();
//						printf("start task failed\r\n");
//						taskEXIT_CRITICAL();

						lwip_close(sock_fd);
						sock_fd = -1;
					}
				}
//				else
//				{
//					taskENTER_CRITICAL();
//					printf("open sock failed\r\n", sock_fd);
//					taskEXIT_CRITICAL();
//				}
			}
			else
			{
//				taskENTER_CRITICAL();
//				printf("sock already open\r\n");
//				taskEXIT_CRITICAL();
			}

			if (sock_fd != -1)
			{
//				taskENTER_CRITICAL();
//				printf("start sock ok:%d\r\n", sock_fd);
//				printf("send [%s]", TCP_Tx_Buffer);
//				taskEXIT_CRITICAL();

				TCP_Send(sock_fd, TCP_Tx_Buffer, TCP_Tx_Count);
				State = Idle;
			}
			else if (tx_fail_count++ > 10)
			{
//				taskENTER_CRITICAL();
//				printf("start sock failed\r\n\r\n");
//				taskEXIT_CRITICAL();
				State = Idle;
			}

			break;
		}

		case TCP_STATE_MAX:
		default:
		{
			State = Idle;
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
static int ICACHE_RODATA_ATTR TCP_Connect_Socket(
		struct sockaddr_in * remote_addr)
{
//	taskENTER_CRITICAL();
//	printf("sock to [%s]\r\n", message_temp.destination);
//	taskEXIT_CRITICAL();

	int tx_socket = socket(PF_INET, SOCK_STREAM, 0);

//	taskENTER_CRITICAL();
//	printf("tx socket:%d\r\n", tx_socket);
//	taskEXIT_CRITICAL();

//	taskENTER_CRITICAL();
//	printf("remote addr:%s:%d, size:%d\r\n",
//			inet_ntoa(remote_addr->sin_addr.s_addr),
//			ntohs(remote_addr->sin_port), sizeof(struct sockaddr_in));
//	taskEXIT_CRITICAL();

	if (tx_socket == -1)
	{
//		taskENTER_CRITICAL();
//		printf("sock create fail\r\n");
//		taskEXIT_CRITICAL();

		lwip_close(tx_socket);
	}
	else if (0
			!= connect(tx_socket, (struct sockaddr * )(remote_addr),
					sizeof(struct sockaddr_in)))
	{
//		int32 error = 0;
//		uint32 optionLength = sizeof(error);
//		int getReturn = lwip_getsockopt(tx_socket, SOL_SOCKET, SO_ERROR, &error,
//				&optionLength);

//		taskENTER_CRITICAL();
//		printf("connect fail: %d\r\n", error);
//		taskEXIT_CRITICAL();

		lwip_close(tx_socket);
		tx_socket = -1;
	}

	if (tx_socket != -1)
	{
		int millis = TCP_RECEIVE_CONNECTION_TIMEOUT_ms;
		setsockopt(tx_socket, SOL_SOCKET, SO_RCVTIMEO, &millis, sizeof(millis));
	}

//	taskENTER_CRITICAL();
//	printf("connect leave:%d\r\n", tx_socket);
//	taskEXIT_CRITICAL();

	return tx_socket;
}

static bool ICACHE_RODATA_ATTR TCP_Send(int tx_socket, uint8 * data,
		uint32 length)
{
//	char addr_str[50];
//
//	taskENTER_CRITICAL();
//	Serialize_Address(destination_addr.sin_addr.s_addr,
//			ntohs(destination_addr.sin_port), addr_str, 50);
//	taskEXIT_CRITICAL();

//	taskENTER_CRITICAL();
//	printf("sending:[%s] to %s on sock %d\r\n", data, addr_str, tx_socket);
//	taskEXIT_CRITICAL();

	bool rval = write(tx_socket, data, length) == length;

	return true;
}

static bool Message_Available()
{
	bool rval = false;

	taskENTER_CRITICAL();
	m = Peek_Message(&outgoing_TCP_message_queue);
	taskEXIT_CRITICAL();

	if (m != NULL)
	{
		rval = true;
	}

	return rval;
}
