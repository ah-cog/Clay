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

uint32 counter;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static bool Receive();

////Global implementations ////////////////////////////////////////
bool Serial_Receiver_Init()
{
	bool rval = true;

	Serial_Rx_Buffer = zalloc(SERIAL_RX_BUFFER_SIZE_BYTES);

//	printf("serial rx init\n");

//	Serial_Tx_In_Progress = false;
	Serial_Rx_In_Progress = false;

	OutgoingQueueLock = false; //init
	State = Idle;
	Ring_Buffer_Init();

//	printf("done ring init\n");

	Initialize_Message_Queue(&outgoingMessageQueue);

//	printf("done incoming queue init\n");

	xTaskCreate(Serial_Receiver_State_Step, "uartrx1", 256, NULL, 2, NULL);

//	printf("create task and returning.\n");

	return rval;
}
int x = 0;
uint8 temp;
bool DataInBuffer;
void Serial_Receiver_State_Step()
{
//	taskENTER_CRITICAL();
//	if (Ring_Buffer_Lock)
//	{
//		taskEXIT_CRITICAL();
//	}
//	else
//	{
//		DataInBuffer = Ring_Buffer_Has_Data();
//		taskEXIT_CRITICAL();
//	}
//
//	if (DataInBuffer)
//	{
//		taskENTER_CRITICAL();
//		if (Ring_Buffer_Lock)
//		{
//			taskEXIT_CRITICAL();
//		}
//		else
//		{
//			Ring_Buffer_Get(&temp);
//			taskEXIT_CRITICAL();
//		}
//
////			taskENTER_CRITICAL();
////			printf("%c", temp);
////			taskEXIT_CRITICAL();
//
//		vTaskDelay(1 / portTICK_RATE_MS);
//	}
//	else
//	{
//		vTaskDelay(1 / portTICK_RATE_MS);
//	}

//	for (;;)
//	{
//
//		taskENTER_CRITICAL();
//		if (Ring_Buffer_Has_Data())
//		{
//
////			WAIT_FOR_RING_BUF();
//			Ring_Buffer_Get(&temp);
////			RELEASE_RING_BUF();
//
//			printf("%c", temp);
//		}
//		taskEXIT_CRITICAL();
//		taskYIELD();
//	}

	for (;;)
	{
//		if (State != Disable && !(counter = (counter + 1) % 10000))
//		{
//			taskENTER_CRITICAL();
//			printf("rxstate: %d\n", State);
//			taskEXIT_CRITICAL();
//			Serial_Tx_In_Progress = false;
//		}

		switch (State)
		{
		case Disable:
		{
			if (wifi_station_get_connect_status() == STATION_GOT_IP)
			{
//				taskENTER_CRITICAL();
//				printf("reset fifo\n");
//				taskEXIT_CRITICAL();

				taskENTER_CRITICAL();
				UART_ResetRxFifo(UART0);
				taskEXIT_CRITICAL();

//				taskENTER_CRITICAL();
//				printf("fifo reset, goto idle\n");
//				taskEXIT_CRITICAL();
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

//			if (InterruptFifoWriteIndex > 0)
//			if (Ring_Buffer_Has_Data())
			if (DataInBuffer)
			{
//				i = BytesReceived;

				//critical sections are inside of ring_buffer functions.
				taskENTER_CRITICAL();
				Ring_Buffer_Get(Serial_Rx_Buffer + BytesReceived);
//				printf("%c", Serial_Rx_Buffer[BytesReceived]);
				taskEXIT_CRITICAL();

//				taskENTER_CRITICAL();
//				printf("%d:'%c'\n", BytesReceived,
//						Serial_Rx_Buffer[BytesReceived]);
//				taskEXIT_CRITICAL();

//				if (Serial_Rx_Buffer[BytesReceived++] == '\n')
//				{
//					++Newline_Count;
//				}

//				memcpy(Serial_Rx_Buffer + BytesReceived, fifo_tmp, fifo_len);
//				printf("copied\n");

//				BytesReceived += InterruptFifoWriteIndex;
//
//				InterruptFifoWriteIndex = 0;
//
//				for (; i < BytesReceived; ++i)
//				{
//					if (Serial_Rx_Buffer[i] == '\n')
//					{
//						++Newline_Count;
//					}
//				}

//				printf("newline:%d\n", Newline_Count);
//				printf("RxFifoIdx:%d\n", BytesReceived);

//				if (Newline_Count >= CLAY_SERIAL_MESSAGE_NEWLINE_COUNT)
				if (Serial_Rx_Buffer[BytesReceived++] == '!')
				{
//					taskENTER_CRITICAL();
//					printf("enough newlines\n\n");
//					taskEXIT_CRITICAL();

					//TODO: update message to not require null termination?
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
//				taskENTER_CRITICAL();
//				printf("come on yo\n");
//				taskEXIT_CRITICAL();
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
//			taskENTER_CRITICAL();
//			printf("parsing\n");
//			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			tempContent = strtok(Serial_Rx_Buffer, &Newline);
			taskEXIT_CRITICAL();

//			taskENTER_CRITICAL();
//			printf("content: [%s]\n", tempContent);
//			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			tempAddr = strtok(NULL, &Newline);
			taskEXIT_CRITICAL();

//			taskENTER_CRITICAL();
//			printf("addr: [%s]\n", tempAddr);
//			taskEXIT_CRITICAL();

			if (tempContent != NULL && tempAddr != NULL)
			{
//				taskENTER_CRITICAL();
//				printf("not null, init message\n");
//				taskEXIT_CRITICAL();

				taskENTER_CRITICAL();
				Initialize_Message(&tempMsg, tempAddr, tempAddr, tempContent);
				taskEXIT_CRITICAL();

//				taskENTER_CRITICAL();
//				printf("init message done\n");
//				taskEXIT_CRITICAL();
			}

//			printf("queue message \n");
//			WAIT_FOR_OUTGOING_QUEUE();
			taskENTER_CRITICAL();
			Queue_Message(&outgoingMessageQueue, &tempMsg);
			taskEXIT_CRITICAL();
//			RELEASE_OUTGOING_QUEUE();

//			taskENTER_CRITICAL();
//			printf("queue message done, go to idle.\n\n\n");
//			taskEXIT_CRITICAL();

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
