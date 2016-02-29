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
#include "Clay_Message.h"
#include "Message.h"
#include "Ring_Buffer.h"

////Defines ///////////////////////////////////////////////////////
#define RX_WAIT_FOR_DATA_us				200000
////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable, Configure, Idle, Receiving, Parsing, UDP_STATE_MAX
} Serial_Receiver_States;
////Globals   /////////////////////////////////////////////////////
volatile bool Serial_Rx_In_Progress;

////Local vars/////////////////////////////////////////////////////
static Serial_Receiver_States State;

static uint32 BytesReceived;
static uint8 * Serial_Rx_Buffer;
static uint32 Serial_Rx_Count;

static uint8 Newline_Count;
static Message tempMsg;
static char * tempContent;
static char * tempAddr;
static char Newline = '\n';
static uint32 stateTime;
int i;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static bool Receive();

////Global implementations ////////////////////////////////////////
bool Serial_Receiver_Init()
{
	bool rval = true;

	Serial_Rx_Buffer = zalloc(SERIAL_RX_BUFFER_SIZE_BYTES);

	OutgoingQueueLock = false; //init
	State = Disable;
	Ring_Buffer_Init();

	Initialize_Message_Queue(&incomingMessageQueue);

	xTaskCreate(Serial_Receiver_State_Step, "uartrx1", 256, NULL, 2, NULL);
	return rval;
}
int x = 0;
void Serial_Receiver_State_Step()
{
	for (;;)
	{
		if (InterruptFifoWriteIndex > 0)
		{
			taskENTER_CRITICAL();
			for (x = 0; x < InterruptFifoWriteIndex; ++x)
			{
				printf("%c", fifo_tmp[x]);
			}
			InterruptFifoWriteIndex = 0;
			taskEXIT_CRITICAL();
		}
		taskYIELD();
	}

	for (;;)
	{
		switch (State)
		{
		case Disable:
		{
			if (wifi_station_get_connect_status() == STATION_GOT_IP)
			{
				UART_ResetRxFifo(UART0);
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
			if (!Serial_Tx_In_Progress && !GPIO_INPUT_GET(CLAY_INTERRUPT_IN_PIN)) //state transition
			{
				Serial_Rx_In_Progress = true;

				Serial_Rx_Count = 0;
				UART_ResetRxFifo(UART0);
				BytesReceived = 0;
				Newline_Count = 0;
				Ring_Buffer_Init();

#if(CLAY_INTERRUPT_OUT_PIN == 16)
				gpio16_output_set(0);
#else
				GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 0);
#endif
				stateTime = system_get_time();
				State = Receiving;
			}
			break;
		}

		case Receiving:
		{
			if (InterruptFifoWriteIndex > 0)
//			if (Ring_Buffer_Has_Data())
			{
				i = BytesReceived;

//				Ring_Buffer_Get(Serial_Rx_Buffer + BytesReceived);
//				printf("%d:'%c'\n", BytesReceived,
//						Serial_Rx_Buffer[BytesReceived - 1]);
//
//				if (Serial_Rx_Buffer[BytesReceived++] == '\n')
//				{
//					++Newline_Count;
//				}

				memcpy(Serial_Rx_Buffer + BytesReceived, fifo_tmp, fifo_len);
//				printf("copied\n");

				BytesReceived += InterruptFifoWriteIndex;

				InterruptFifoWriteIndex = 0;

				for (; i < BytesReceived; ++i)
				{
					if (Serial_Rx_Buffer[i] == '\n')
					{
						++Newline_Count;
					}
				}

//				printf("newline:%d\n", Newline_Count);
//				printf("RxFifoIdx:%d\n", BytesReceived);

				if (Newline_Count >= CLAY_SERIAL_MESSAGE_NEWLINE_COUNT)
				{
					//TODO: update message to not require null termination?
					Serial_Rx_Buffer[BytesReceived] = '\0';

					taskENTER_CRITICAL();
					printf("enough newlines\n\n");
					taskEXIT_CRITICAL();
					Serial_Rx_In_Progress = false;

#if(CLAY_INTERRUPT_OUT_PIN == 16)
					gpio16_output_set(1);
#else
					GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 1);
#endif
					State = Parsing;
				}
			}
			else if (system_get_time() - stateTime > 1000000) //GPIO_INPUT_GET(CLAY_INTERRUPT_IN_PIN)) //state transition
			{
#if(CLAY_INTERRUPT_OUT_PIN == 16)
				gpio16_output_set(1);
#else
				GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 1);
#endif

				Serial_Rx_In_Progress = false;
				State = Idle;
			}
			break;
		}

		case Parsing:
		{
			taskENTER_CRITICAL();
			printf("parsing\n");

			tempContent = strtok(Serial_Rx_Buffer, &Newline);

			printf("content: [%s]\n", tempContent);

			tempAddr = strtok(NULL, &Newline);

			printf("addr: [%s]\n", tempAddr);
			taskEXIT_CRITICAL();

			if (tempContent != NULL && tempAddr != NULL)
			{
				taskENTER_CRITICAL();
				printf("not null, init message\n");
				Initialize_Message(&tempMsg, tempAddr, tempAddr, tempContent);
				printf("init message done\n");
				taskEXIT_CRITICAL();
			}

//			printf("queue message \n");
			taskENTER_CRITICAL();
			WAIT_FOR_OUTGOING_QUEUE();
			Queue_Message(&outgoingMessageQueue, &tempMsg);
			RELEASE_OUTGOING_QUEUE();
			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			printf("queue message done, go to idle.\n\n\n");
			taskEXIT_CRITICAL();

			while (GPIO_INPUT_GET(CLAY_INTERRUPT_IN_PIN))
				;

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
static bool Connect()
{
	bool rval = false;
	return rval;
}

static bool Receive()
{
	bool rval = false;
	return rval;
}
