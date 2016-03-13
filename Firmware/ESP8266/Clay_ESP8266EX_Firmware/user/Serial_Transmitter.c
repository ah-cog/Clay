/*
 * Serial_Transmitter.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 *
 *      This class consumes Clay_Message types from a buffer and transmits them over serial to a microcontroller.
 */

/*
 * States:
 *      Disable -- No transmission occurs.
 *          -Go to configure when enabled
 *      Configure -- set up serial port, interrupts, etc
 *          -Go to Idle upon completion
 *      Idle
 *          -No messages in queue that need to go to micro.
 *          -When a message appears in queue, go to Message_available
 *          -Disable can send us back to Disabled state
 *      Message_Available
 *          -Set interrupt output line low, wait for uC to acknowledge.
 *          -When uC interrupt comes in, go to Transmitting
 *          -Disable command will reset interrupt output and send us to Disable.
 *      Transmitting
 *          -Send one message.
 *          -Reset interrupt output and return to Idle upon completion.
 * */

//dequeue message before resetting GPIO line to prevent us from receiving a message twice.
//TODO: look into doing parity, rechecks.
////Includes //////////////////////////////////////////////////////
#include "esp_common.h"
#include "GPIO.h"
#include "UART.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "UDP_Transmitter.h"
#include "Serial_Receiver.h"
#include "Serial_Transmitter.h"

#include "../include/AddressSerialization.h"
#include "Clay_Config.h"
#include "Message_Queue.h"

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable,
	Configure,
	Idle,
	Message_Available,
	Wait_For_Transmit_Ok,
	Transmitting,
	Transmitting_Done,
	UDP_STATE_MAX
} Serial_Transmitter_States;
////Globals   /////////////////////////////////////////////////////
volatile bool Serial_Tx_In_Progress;

////Local vars/////////////////////////////////////////////////////
static Serial_Transmitter_States State;

static uint8 * Serial_Tx_Buffer;
static uint32 Serial_Tx_Count;
static Message * Temp_Message;

static uint32 timeTemp;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static bool Transmit();

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR Serial_Transmitter_Init()
{
	bool rval = true;

	State = Disable;
	Serial_Tx_Buffer = zalloc(SERIAL_TX_BUFFER_SIZE_BYTES);

	Initialize_Message_Queue(&incomingMessageQueue);

	xTaskCreate(Serial_Transmitter_State_Step, "uarttx1", 256, NULL, 2, NULL);

	return rval;
}

void ICACHE_RODATA_ATTR Serial_Transmitter_State_Step()
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
			}
			break;
		}

		case Configure:
		{
			break;
		}

		case Idle:
		{
			taskENTER_CRITICAL();
			Temp_Message = Peek_Message(&incomingMessageQueue);
			taskEXIT_CRITICAL();

			if (!Serial_Rx_In_Progress && Temp_Message != NULL)
			{
				State = Message_Available;
				UART_ResetTxFifo(UART0);
			}
			break;
		}

		case Message_Available:
		{
			Serial_Tx_In_Progress = true;

			taskENTER_CRITICAL();
			Temp_Message = Dequeue_Message(&incomingMessageQueue);
			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			Serial_Tx_Count = strlen(Temp_Message->content);
			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			strcpy(Serial_Tx_Buffer, Temp_Message->content);
			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			strcat(Serial_Tx_Buffer, Temp_Message->source);
			taskEXIT_CRITICAL();

			State = Wait_For_Transmit_Ok;

			timeTemp = system_get_time();
#if(CLAY_INTERRUPT_OUT_PIN == 16)
			gpio16_output_set(0);
#else
			GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 0);
#endif

			break;
		}

		case Wait_For_Transmit_Ok:
		{
			if (!GPIO_INPUT_GET(CLAY_INTERRUPT_IN_PIN))
			{
				taskENTER_CRITICAL();
				printf(Serial_Tx_Buffer);
				taskEXIT_CRITICAL();
				State = Transmitting;
			}
			break;
		}

		case Transmitting:
		{
			if (UART_CheckTxFifoEmpty(UART0))
			{
				State = Transmitting_Done;

#if(CLAY_INTERRUPT_OUT_PIN == 16)
				gpio16_output_set(1);
#else
				GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 1);
#endif

			}
			break;
		}

		case Transmitting_Done:
		{
			//TODO: use pulses rather than levels, and the receiving side should receive until it gets a newline.
			Serial_Tx_In_Progress = FALSE;
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
	bool rval = false;
	return rval;
}

static bool ICACHE_RODATA_ATTR Transmit()
{
	bool rval = false;
	return rval;
}
