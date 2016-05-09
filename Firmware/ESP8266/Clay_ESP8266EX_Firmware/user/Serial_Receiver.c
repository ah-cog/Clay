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
#define RING_BUFFER_PROMOTION_THRESHOLD		30
#define SERIAL_RX_TIMEOUT_us				100000

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable, Configure, Idle, Receiving, Parsing, UDP_STATE_MAX
} Serial_Receiver_States;
////Globals   /////////////////////////////////////////////////////
volatile bool master_interrupt_received;

////Local vars/////////////////////////////////////////////////////
static Serial_Receiver_States State;

static bool message_received;

static Message * temp_msg_ptr;
static uint32 state_time;
int i;

Message ** selected_message_queue;

static Message_Type received_message_type;

uint32 counter;

////Local Prototypes///////////////////////////////////////////////
static bool Check_Needs_Promotion();

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR Serial_Receiver_Init()
{
	bool rval = true;
	master_interrupt_received = false;

	taskENTER_CRITICAL();
	//multibyte ring buffer initialized in user_main
	Initialize_Message_Queue(&outgoing_udp_message_queue);
	Initialize_Message_Queue(&outgoing_tcp_message_queue);
	Initialize_Message_Queue(&incoming_command_queue);
	Initialize_Message_Queue(&incoming_message_queue);
	taskEXIT_CRITICAL();

	State = Idle;

	xTaskHandle serial_rx_handle;

	xTaskCreate(Serial_Receiver_Task, "uartrx1", configMINIMAL_STACK_SIZE, NULL,
			Get_Task_Priority(TASK_TYPE_SERIAL_RX), &serial_rx_handle);

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
			if (master_interrupt_received) //state transition
			{
				master_interrupt_received = false;

				message_received = FALSE;
				state_time = system_get_time();

				State = Receiving;
			}
			else
			{
				taskENTER_CRITICAL();
				UART_ResetRxFifo(UART0);
				taskEXIT_CRITICAL();
			}
			break;
		}

		case Receiving:
		{
			uint8_t * serialized_message = NULL;
			temp_msg_ptr = NULL;
			taskENTER_CRITICAL();
			int dequeue_count =
					Multibyte_Ring_Buffer_Dequeue_Serialized_Message_With_Message_Header(
							&serial_rx_multibyte, &serialized_message);
			taskEXIT_CRITICAL();

			if (serialized_message != NULL)
			{
				taskENTER_CRITICAL();
				temp_msg_ptr = Deserialize_Message_With_Message_Header(
						serialized_message);
				taskEXIT_CRITICAL();

				if (temp_msg_ptr != NULL)
				{
					message_received = TRUE;

					received_message_type = Get_Message_Type_From_Str(
							temp_msg_ptr->message_type);

					switch (received_message_type)
					{
#if ENABLE_UDP_SENDER
					case MESSAGE_TYPE_UDP:
					{
						selected_message_queue = &outgoing_udp_message_queue;
						break;
					}
#endif
#if ENABLE_TCP_SENDER || ENABLE_TCP_COMBINED_TX
					case MESSAGE_TYPE_HTTP:
					case MESSAGE_TYPE_TCP:
					{
						selected_message_queue = &outgoing_tcp_message_queue;
						break;
					}
#endif
					case MESSAGE_TYPE_COMMAND:
					{
						selected_message_queue = &incoming_command_queue;

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
					}
					else if (temp_msg_ptr != NULL)
					{
						Delete_Message(temp_msg_ptr);
					}
				}

				free(serialized_message);
				serialized_message = NULL;
			}

			if (!message_received
					&& system_get_time() - state_time > SERIAL_RX_TIMEOUT_us)
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
		taskYIELD();
	}
}

////Local implementations /////////////////////////////////////////
static bool ICACHE_RODATA_ATTR Check_Needs_Promotion()
{
	return Multibyte_Ring_Buffer_Get_Count(&serial_rx_multibyte)
			> RING_BUFFER_PROMOTION_THRESHOLD && State == Idle;
}
