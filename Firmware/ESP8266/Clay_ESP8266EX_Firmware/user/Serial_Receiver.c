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
#include "Serial_Transmitter.h"
#include "Clay_Config.h"
#include "Message_Queue.h"
#include "Message.h"
#include "Ring_Buffer.h"
#include "Priority_Manager.h"

////Defines ///////////////////////////////////////////////////////
#define RING_BUFFER_PROMOTION_THRESHOLD		30

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable, Configure, Idle, Receiving, Parsing, UDP_STATE_MAX
} Serial_Receiver_States;
////Globals   /////////////////////////////////////////////////////
volatile bool master_interrupt_received;

////Local vars/////////////////////////////////////////////////////
static Serial_Receiver_States State;

static uint32 bytes_received;
static uint8 * serial_rx_buffer;
static uint32 serial_rx_count;

static bool buffer_has_data;
static Message temp_msg;
static char * temp_content;
static char * temp_source_address;
static char * temp_type;
static char * temp_dest_address;
static uint32 state_time;
int i;

Message_Queue * selected_message_queue;

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
	serial_rx_buffer = zalloc(SERIAL_RX_BUFFER_SIZE_BYTES);
	Ring_Buffer_Init();
	Initialize_Message_Queue(&outgoing_UDP_message_queue);
	Initialize_Message_Queue(&outgoing_TCP_message_queue);
	Initialize_Message_Queue(&incoming_command_queue);
	Initialize_Message_Queue(&incoming_message_queue);
	taskEXIT_CRITICAL();

	State = Idle;

	xTaskHandle serial_rx_handle;

	xTaskCreate(Serial_Receiver_Task, "uartrx1", 128, NULL,
			Get_Task_Priority(TASK_TYPE_SERIAL_RX), serial_rx_handle);

	Register_Task(TASK_TYPE_SERIAL_RX, serial_rx_handle, Check_Needs_Promotion);

	return rval;
}

void ICACHE_RODATA_ATTR Serial_Receiver_Task()
{
	for (;;)
	{
		Priority_Check(TASK_TYPE_SERIAL_RX);

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

				serial_rx_count = 0;

				bytes_received = 0;

				taskENTER_CRITICAL();
				Ring_Buffer_Init();
				taskEXIT_CRITICAL();

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
			taskENTER_CRITICAL();
			buffer_has_data = Ring_Buffer_Has_Data();
			taskEXIT_CRITICAL();

			if (buffer_has_data)
			{
				taskENTER_CRITICAL();
				Ring_Buffer_Get(serial_rx_buffer + bytes_received);
//				taskEXIT_CRITICAL(); //moved from below

				if (bytes_received == 0
						&& serial_rx_buffer[0] == message_start[0])
				{
					++bytes_received;
				}
				else if (bytes_received > 0
						&& serial_rx_buffer[bytes_received++] == message_end[0])
				{
					serial_rx_buffer[bytes_received] = '\0';
					State = Parsing;
				}

				//Moved this above.
				taskEXIT_CRITICAL();
			}
			else if ((system_get_time() - state_time) > 1000000) //system_get_time returns us
			{
				State = Idle;
			}
			break;
		}

		case Parsing:
		{
#ifdef PRINT_HIGH_WATER
			taskENTER_CRITICAL();
			printf("\r\nsrx parse\r\n");
			taskEXIT_CRITICAL();
			portENTER_CRITICAL();
			UART_WaitTxFifoEmpty(UART0);
			portEXIT_CRITICAL();

			DEBUG_Print_High_Water();
#endif

			//New message format:
			//!<type>\t<source>\t<destination>\t<content>\n

			taskENTER_CRITICAL();
			temp_type = strtok(serial_rx_buffer + 1, message_field_delimiter); //offset to skip start char
			temp_source_address = strtok(NULL, message_field_delimiter);
			temp_dest_address = strtok(NULL, message_field_delimiter);
			temp_content = strtok(NULL, message_end);
			taskEXIT_CRITICAL();

			if (temp_content != NULL && temp_type != NULL
					&& temp_source_address != NULL && temp_dest_address != NULL)
			{
				taskENTER_CRITICAL();
				received_message_type = Get_Message_Type_From_Str(temp_type);
				taskEXIT_CRITICAL();

				taskENTER_CRITICAL();
				Initialize_Message(&temp_msg,
						message_type_strings[received_message_type],
						temp_source_address, temp_dest_address, temp_content);
				taskEXIT_CRITICAL();

				switch (received_message_type)
				{
#if ENABLE_UDP_SENDER
				case MESSAGE_TYPE_UDP:
				{
					selected_message_queue = &outgoing_UDP_message_queue;
					break;
				}
#endif
#if ENABLE_TCP_SENDER || ENABLE_TCP_COMBINED
				case MESSAGE_TYPE_TCP:
				{
//					taskENTER_CRITICAL();
//					printf("\r\ngot tcp msg: %s,%s,%s,%s\r\n", temp_msg.content,
//							temp_msg.message_type, temp_msg.destination,
//							temp_msg.source);
//					taskEXIT_CRITICAL();

//					portENTER_CRITICAL();
//					UART_WaitTxFifoEmpty(UART0);
//					portEXIT_CRITICAL();
					selected_message_queue = &outgoing_TCP_message_queue;
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
					Queue_Message(selected_message_queue, &temp_msg);
					taskEXIT_CRITICAL();
				}

			}

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
static bool Check_Needs_Promotion()
{
//	return false;
	return Ring_Buffer_NofElements() > RING_BUFFER_PROMOTION_THRESHOLD
			&& State == Idle;
}
