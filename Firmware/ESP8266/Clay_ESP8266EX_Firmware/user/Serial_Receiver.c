/*
 * Serial_Receiver.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 *
 *      This class will consume messages from the serial lines and parse them into Clay_Message types.
 *      The messages are \n terminated strings.
 *
 */

////Includes //////////////////////////////////////////////////////
#include "../include/AddressSerialization.h"

#include "esp_common.h"
#include "UART.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "UDP_Transmitter.h"
#include "Serial_Receiver.h"

#include "Wifi_Message_Serialization.h"
#include "System_Monitor.h"
#include "Serial_Transmitter.h"
#include "Clay_Config.h"
#include "Message_Queue.h"
#include "Message.h"
#include "Queues.h"

////Defines ///////////////////////////////////////////////////////
#define RING_BUFFER_PROMOTION_THRESHOLD		512
#define SERIAL_RX_TIMEOUT_us				100000

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable,
	Configure,
	Idle,
	Deserialize_Received_Message,
	Parsing,
	UDP_STATE_MAX
} Serial_Receiver_States;
////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static Serial_Receiver_States State;

static Message * temp_msg_ptr;
int i;

Message ** selected_message_queue;

static uint8_t * message_serial;
static int dequeue_count;
static Message_Type received_message_type;

uint32 counter;

////Local Prototypes///////////////////////////////////////////////
static bool Check_Needs_Promotion();

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR Serial_Receiver_Init()
{
	bool rval = true;

	State = Idle;

	xTaskHandle serial_rx_handle;

	xTaskCreate(Serial_Receiver_Task, "uartrx1", configMINIMAL_STACK_SIZE, NULL,
			DEFAULT_PRIORITY, &serial_rx_handle);

	System_Register_Task(TASK_TYPE_SERIAL_RX, serial_rx_handle,
			Check_Needs_Promotion);

	return rval;
}

void ICACHE_RODATA_ATTR Serial_Receiver_Task()
{
	for (;;)
	{
		switch (State)
		{
		case Disable:
		{
			if (wifi_station_get_connect_status() == STATION_GOT_IP)
			{
				taskENTER_CRITICAL();
				UART_ResetRxFifo(UART0);
				taskEXIT_CRITICAL();
				State = Idle;
			}
			break;
		}

		case Configure:
		{
			break;
		}

		case Idle:
		{
			message_serial = NULL;

			//crit sections are internal to ring buffer, because of the length of some of its functions.
			dequeue_count =
					Multibyte_Ring_Buffer_Dequeue_Serialized_Message_With_Message_Header(
							&serial_rx_multibyte, &message_serial);

//			if (dequeue_count > 0)
//			{
//				taskENTER_CRITICAL();
//				printf("dequeued %d\r\n", dequeue_count);
//				taskEXIT_CRITICAL();
//			}

			if (message_serial != NULL) //state transition
			{
//				taskENTER_CRITICAL();
//				printf("message\f  [%s]", message_serial);
//				taskEXIT_CRITICAL();

				State = Deserialize_Received_Message;
				temp_msg_ptr = NULL;
			}
			else
			{
				//crit sections are internal to ring buffer, because of the length of some of its functions.
				uint32_t free_size = Multibyte_Ring_Buffer_Get_Free_Size(
						&serial_rx_multibyte);

				if (free_size < 1)
				{
					//full of garbage.
					//crit sections are internal to ring buffer, because of the length of some of its functions.
					Multibyte_Ring_Buffer_Reset(&serial_rx_multibyte);
				}
			}
			break;
		}

		case Deserialize_Received_Message:
		{
			if (message_serial != NULL)
			{
				DEBUG_Print("deserialize.");

				taskENTER_CRITICAL();
				temp_msg_ptr = Deserialize_Message_With_Message_Header(
						message_serial);
				taskEXIT_CRITICAL();

				if (temp_msg_ptr != NULL)
				{
					DEBUG_Print("message not null");

					taskENTER_CRITICAL();
					received_message_type = Get_Message_Type_From_Str(
							temp_msg_ptr->message_type);
					taskEXIT_CRITICAL();

					switch (received_message_type)
					{
#if ENABLE_UDP_SENDER
					case MESSAGE_TYPE_UDP:
					{

						selected_message_queue = &outgoing_udp_message_queue;
						++outgoing_tcp_message_queue;

						DEBUG_Print("udp msg");

						break;
					}
#endif
#if ENABLE_TCP_SENDER || ENABLE_TCP_COMBINED_TX
					case MESSAGE_TYPE_HTTP:
					case MESSAGE_TYPE_TCP:
					{
						DEBUG_Print("tcp msg");

						selected_message_queue = &outgoing_tcp_message_queue;
						++outgoing_tcp_message_count;
						break;
					}
#endif
					case MESSAGE_TYPE_COMMAND:
					{

						selected_message_queue = &incoming_command_queue;
						++incoming_command_message_count;
						break;
					}

					default:
					{

						selected_message_queue = NULL;
						break;
					}
					}

					if (selected_message_queue != NULL)
					{
						taskENTER_CRITICAL();
						Queue_Message(selected_message_queue, temp_msg_ptr);
						taskEXIT_CRITICAL();

						DEBUG_Print("nq'd srx");
					}
					else if (temp_msg_ptr != NULL)
					{

						Delete_Message(temp_msg_ptr);
					}

					temp_msg_ptr = NULL;
				}

				free(message_serial);
				message_serial = NULL;
			}
			State = Idle;

			break;
		}

		case UDP_STATE_MAX:
		default:
		{
			State = Idle;
			break;
		}
		}
		taskYIELD();
	}
}

////Local implementations /////////////////////////////////////////
static bool ICACHE_RODATA_ATTR Check_Needs_Promotion()
{
	//crit sections are internal to ring buffer, because of the length of some of its functions.
	bool rval = Multibyte_Ring_Buffer_Get_Count(&serial_rx_multibyte)
			> RING_BUFFER_PROMOTION_THRESHOLD && State == Idle;

	return rval;
}
