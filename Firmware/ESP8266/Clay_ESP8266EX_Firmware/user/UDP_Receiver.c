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

#include "uart.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "UDP_Receiver.h"

#include "../include/AddressSerialization.h"
#include "../include/System_Monitor.h"
#include "Clay_Config.h"

#include "Wifi_Message_Serialization.h"
#include "Message_Queue.h"
#include "Queues.h"
////Macros ////////////////////////////////////////////////////////
#define RECEIVE_BYTES_TRIGGER_LEVEL 512

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

////Local vars/////////////////////////////////////////////////////
static UDP_Receiver_States State;

static int ret;

static uint8_t *udp_serialized_rx_buffer;
static uint16_t udp_rx_count;

static size_t fromlen;

static struct sockaddr_in from;

static struct sockaddr_in lastSourceAddress;
static struct sockaddr_in server_addr;

static int nNetTimeout;

static int32 receive_sock;
static bool Connected;
static int32 testCounter;

static Message * temp_msg_ptr;
static Message tempMessage;
static char * source_addr;
static char * dest_addr;

static bool task_running = false;

static Multibyte_Ring_Buffer udp_rx_multibyte;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static bool Receive();
static bool Check_Needs_Promotion();

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR UDP_Receiver_Init()
{
	bool rval = true;

	if (!task_running)
	{
		nNetTimeout = UDP_RX_TIMEOUT_MSEC;

		State = Disable;

		taskENTER_CRITICAL();
		Multibyte_Ring_Buffer_Init(&udp_rx_multibyte, UDP_RX_BUFFER_SIZE_BYTES);
		source_addr = zalloc(CLAY_ADDR_STRING_BUF_LENGTH);
		dest_addr = zalloc(CLAY_ADDR_STRING_BUF_LENGTH);
		Initialize_Message_Queue(&incoming_message_queue);
		taskEXIT_CRITICAL();

		xTaskHandle UDP_receive_handle;

		xTaskCreate(UDP_Receiver_Task, "udprx1", 512, NULL,
				Get_Task_Priority(TASK_TYPE_UDP_RX), &UDP_receive_handle);

		System_Register_Task(TASK_TYPE_UDP_RX, UDP_receive_handle,
				Check_Needs_Promotion);

		testCounter = 0;

		task_running = true;
	}
	else
	{
		rval = false;
	}

	return rval;
}

void ICACHE_RODATA_ATTR UDP_Receiver_Deinit()
{
	if (task_running)
	{
		lwip_close(receive_sock);
		receive_sock = -1;

		Multibyte_Ring_Buffer_Free(&udp_rx_multibyte);
		free(source_addr);
		free(dest_addr);

		task_running = false;
		Stop_Task(TASK_TYPE_UDP_RX);
	}
}

void ICACHE_RODATA_ATTR UDP_Receiver_Task()
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
			Receive();

			taskENTER_CRITICAL();
			udp_serialized_rx_buffer = NULL;
			Multibyte_Ring_Buffer_Dequeue_Serialized_Message_Content(
					&udp_rx_multibyte, &udp_serialized_rx_buffer);
			taskEXIT_CRITICAL();

			if (udp_serialized_rx_buffer != NULL)
			{
				State = Enqueue_Message;
			}
			break;
		}

		case Enqueue_Message:
		{
			if (udp_serialized_rx_buffer != NULL)
			{
				taskENTER_CRITICAL();
				temp_msg_ptr = Deserialize_Message_Content(
						udp_serialized_rx_buffer);
				taskEXIT_CRITICAL();

				free(udp_serialized_rx_buffer);

				taskENTER_CRITICAL();
				Serialize_Address(lastSourceAddress.sin_addr.s_addr,
						ntohs(lastSourceAddress.sin_port), source_addr,
						MAXIMUM_DESTINATION_LENGTH);
				taskEXIT_CRITICAL();

				taskYIELD();

				if (temp_msg_ptr != NULL)
				{
					taskENTER_CRITICAL();
					Set_Message_Type(temp_msg_ptr,
							message_type_strings[MESSAGE_TYPE_UDP]);
					Set_Message_Source(temp_msg_ptr, source_addr);
					Set_Message_Destination(temp_msg_ptr, dest_addr);
					taskEXIT_CRITICAL();

					taskYIELD();

					taskENTER_CRITICAL();
					Queue_Message(&incoming_message_queue, temp_msg_ptr);
					taskEXIT_CRITICAL();
				}
			}

			State = Idle;
			break;
		}

		case Rx_Blocked:
		{
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
	}
}

////Local implementations /////////////////////////////////////////
static bool ICACHE_RODATA_ATTR Connect()
{
	Connected = false;

	taskENTER_CRITICAL();
	memset(&server_addr, 0, sizeof(server_addr));
	taskEXIT_CRITICAL();

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(UDP_RX_PORT);
	server_addr.sin_len = sizeof(server_addr);

	taskENTER_CRITICAL();
	Serialize_Address(Get_IP_Address(), UDP_RX_PORT, dest_addr,
	CLAY_ADDR_STRING_BUF_LENGTH);
	taskEXIT_CRITICAL();

	///create the socket
	do
	{
		receive_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (receive_sock == -1)
		{
			Connected = false;
			vTaskDelay(1000 / portTICK_RATE_MS);
		}
	} while (receive_sock == -1);

	//bind the socket
	do
	{
		ret = bind(receive_sock, (struct sockaddr * ) &server_addr,
				sizeof(server_addr));
		if (ret != 0)
		{
			vTaskDelay(1000 / portTICK_RATE_MS);
		}
	} while (ret != 0);
	Connected = true;

	setsockopt(receive_sock, SOL_SOCKET, SO_RCVTIMEO, (char * ) &nNetTimeout,
			sizeof(int));

	return Connected;
}

//TODO: combine TCP and UDP operations. They don't need to be separate.
static bool ICACHE_RODATA_ATTR Receive()
{
	bool rval = false;
	char * rx_temp = zalloc(
			Multibyte_Ring_Buffer_Get_Free_Size(&udp_rx_multibyte));

	taskENTER_CRITICAL();
	memset(&from, 0, sizeof(from));
	taskEXIT_CRITICAL();

	taskYIELD();

	fromlen = sizeof(struct sockaddr_in);

	// attempt to receive
	ret = recvfrom(receive_sock, (uint8 * ) rx_temp, UDP_RX_BUFFER_SIZE_BYTES,
			0, (struct sockaddr * ) &from, (socklen_t * ) &fromlen);

	taskYIELD();

	if (ret > 0)
	{
		rval = true;
		udp_rx_count = ret;

		Multibyte_Ring_Buffer_Enqueue(&udp_rx_multibyte, rx_temp, ret);

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

	free(rx_temp);

	return rval;
}

static bool ICACHE_RODATA_ATTR Check_Needs_Promotion()
{
	bool rval = false;

//	taskENTER_CRITICAL();
//	rval = (Multibyte_Ring_Buffer_Get_Count(&udp_rx_multibyte)
//			> RECEIVE_BYTES_TRIGGER_LEVEL);
//	taskEXIT_CRITICAL();

	return rval;
}
