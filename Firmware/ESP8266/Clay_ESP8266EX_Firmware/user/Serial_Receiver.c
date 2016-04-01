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

/*
 * States:
 *      Disable -- No receiving occurs.
 *          -Go to configure when enable received
 *      Configure -- set up serial port, interrupts, etc
 *          -Go to Idle upon completion
 *      Idle
 *          -Awaiting interrupt from uC with data to send.
 *          -When not transmitting serial data and uC interrupt received.
 *          -go to Interrupt_Received when interrupt comes, but put GPIO line low first so the data will start coming.
 *          -Disable sends us back to Disable state.
 *      Receiving
 *          -Read data until uC releases its interrupt line
 *          -Go to Receive_Complete
 *          -Disable sends us back to Disable state.
 *      Parsing
 *          -Parse message into message queue. Increment queue counters _after_ the data is valid.
 *          -Return to idle after message is parsed
 * */

////Includes //////////////////////////////////////////////////////
#include "../include/AddressSerialization.h"

#include "esp_common.h"
#include "GPIO.h"
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

////Defines ///////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable, Configure, Idle, Receiving, Parsing, UDP_STATE_MAX
} Serial_Receiver_States;
////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static Serial_Receiver_States State;

static uint32 bytes_received;
static uint8 * serial_rx_buffer;
static uint32 serial_rx_count;

static bool buffer_has_data;
static Message temp_msg;
static char * temp_content;
static char * temp_source_ptr;
static char * temp_type_ptr;
static char * temp_dest_ptr;
static uint32 state_time;
int i;

Message_Queue * selected_message_queue;

static Message_Type received_message_type;
static xTaskHandle serial_rx_task;

uint32 counter;

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR Serial_Receiver_Init()
{
	bool rval = true;

	taskENTER_CRITICAL();
	serial_rx_buffer = zalloc(SERIAL_RX_BUFFER_SIZE_BYTES);
	Ring_Buffer_Init();
	Initialize_Message_Queue(&outgoing_UDP_message_queue);
	Initialize_Message_Queue(&outgoing_TCP_message_queue);
	Initialize_Message_Queue(&incoming_command_queue);
	Initialize_Message_Queue(&incoming_message_queue);
	taskEXIT_CRITICAL();

	State = Idle;

	xTaskCreate(Serial_Receiver_State_Step, "uartrx1", 128, NULL, 2,
			serial_rx_task);

	return rval;
}

void ICACHE_RODATA_ATTR Serial_Receiver_State_Step()
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
			if (!GPIO_INPUT_GET(CLAY_INTERRUPT_IN_PIN)) //state transition
			{
				serial_rx_count = 0;

				taskENTER_CRITICAL();
				UART_ResetRxFifo(UART0);
				taskEXIT_CRITICAL();

				bytes_received = 0;

				taskENTER_CRITICAL();
				Ring_Buffer_Init();
				taskEXIT_CRITICAL();

#if(CLAY_INTERRUPT_OUT_PIN == 16)
				gpio16_output_set(0);
#else
				GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 0);
#endif

				state_time = system_get_time();
				State = Receiving;
			}
			break;
		}

		case Receiving:
		{
			buffer_has_data = Ring_Buffer_Has_Data();

			if (buffer_has_data)
			{
				taskENTER_CRITICAL();
				Ring_Buffer_Get(serial_rx_buffer + bytes_received);
				taskEXIT_CRITICAL();

				if (serial_rx_buffer[bytes_received++] == address_terminator[0])
				{
					serial_rx_buffer[bytes_received] = '\0';

#if(CLAY_INTERRUPT_OUT_PIN == 16)
					gpio16_output_set(1);
#else
					GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 1);
#endif

					State = Parsing;
				}
			}
			else if ((system_get_time() - state_time) > 1000000) //GPIO_INPUT_GET(CLAY_INTERRUPT_IN_PIN)) //state transition
			{
#if(CLAY_INTERRUPT_OUT_PIN == 16)
				gpio16_output_set(1);
#else
				GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 1);
#endif

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

			taskENTER_CRITICAL();
			temp_content = strtok(serial_rx_buffer, message_delimiter);
			temp_type_ptr = strtok(NULL, type_delimiter);
			temp_source_ptr = strtok(NULL, address_delimiter);
			temp_dest_ptr = strtok(NULL, address_terminator);
			taskEXIT_CRITICAL();

			if (temp_content != NULL && temp_type_ptr != NULL
					&& temp_source_ptr != NULL && temp_dest_ptr != NULL)
			{
				taskENTER_CRITICAL();
				received_message_type = Get_Message_Type_From_Str(
						temp_type_ptr);
				taskEXIT_CRITICAL();

				taskENTER_CRITICAL();
				Initialize_Message(&temp_msg,
						message_type_strings[received_message_type],
						temp_source_ptr, temp_dest_ptr, temp_content);
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
					taskENTER_CRITICAL();
					printf("\r\ngot tcp msg: %s,%s,%s,%s\r\n", temp_msg.content,
							temp_msg.message_type, temp_msg.destination,
							temp_msg.source);
					taskEXIT_CRITICAL();

					portENTER_CRITICAL();
					UART_WaitTxFifoEmpty(UART0);
					portEXIT_CRITICAL();

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
					printf("nq msg");
					taskEXIT_CRITICAL();

					taskENTER_CRITICAL();
					Queue_Message(selected_message_queue, &temp_msg);
					taskEXIT_CRITICAL();
				}

			}

			while (GPIO_INPUT_GET(CLAY_INTERRUPT_IN_PIN))
			{
				taskYIELD();
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
