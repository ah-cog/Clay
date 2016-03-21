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
static const char * MessageDelimiter = "\n";
static uint32 stateTime;
int i;

Message_Queue * selected_message_queue;

static struct sockaddr_in tempAddressIgnore;
static Message_Type receivedMessageType;

uint32 counter;

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR Serial_Receiver_Init()
{
	bool rval = true;

	Serial_Rx_Buffer = zalloc(SERIAL_RX_BUFFER_SIZE_BYTES);

	Serial_Rx_In_Progress = false;

	State = Idle;
	Ring_Buffer_Init();

	Initialize_Message_Queue(&outgoingUdpMessageQueue);

	xTaskCreate(Serial_Receiver_State_Step, "uartrx1", 256, NULL, 2, NULL);

	return rval;
}
int x = 0;
uint8 temp;
bool DataInBuffer;
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
			if (!Serial_Tx_In_Progress && !GPIO_INPUT_GET(CLAY_INTERRUPT_IN_PIN)) //state transition
			{

				Serial_Rx_In_Progress = true;

				Serial_Rx_Count = 0;

				taskENTER_CRITICAL();
				UART_ResetRxFifo(UART0);
				taskEXIT_CRITICAL();

				BytesReceived = 0;
				Newline_Count = 0;

				taskENTER_CRITICAL();
				Ring_Buffer_Init();
				taskEXIT_CRITICAL();

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
			DataInBuffer = Ring_Buffer_Has_Data();

			if (DataInBuffer)
			{
				taskENTER_CRITICAL();
				Ring_Buffer_Get(Serial_Rx_Buffer + BytesReceived);
				taskEXIT_CRITICAL();

				if (Serial_Rx_Buffer[BytesReceived++] == address_terminator[0])
				{
					Serial_Rx_Buffer[BytesReceived] = '\0';

					Serial_Rx_In_Progress = false;

#if(CLAY_INTERRUPT_OUT_PIN == 16)
					gpio16_output_set(1);
#else
					GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 1);
#endif

					State = Parsing;
				}
			}
			else if ((system_get_time() - stateTime) > 1000000) //GPIO_INPUT_GET(CLAY_INTERRUPT_IN_PIN)) //state transition
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
			tempContent = strtok(Serial_Rx_Buffer, MessageDelimiter);
			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			tempAddr = strtok(NULL, MessageDelimiter);
			taskEXIT_CRITICAL();

			if (tempContent != NULL && tempAddr != NULL)
			{
				taskENTER_CRITICAL();
				Initialize_Message(&tempMsg, tempAddr, tempAddr, tempContent);
				taskEXIT_CRITICAL();

				taskENTER_CRITICAL();
				Deserialize_Address(tempAddr, &tempAddressIgnore,
						&receivedMessageType);
				taskEXIT_CRITICAL();

				switch (receivedMessageType)
				{
				case MESSAGE_TYPE_UDP:
				{
					selected_message_queue = &outgoingUdpMessageQueue;
					break;
				}
				case MESSAGE_TYPE_TCP:
				{
					selected_message_queue = &outgoingTcpMessageQueue;
					break;
				}
				case MESSAGE_TYPE_COMMAND:
				{
					selected_message_queue = &incomingCommandMessageQueue;
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
					Queue_Message(selected_message_queue, &tempMsg);
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
