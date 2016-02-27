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

#include "Serial_Transmitter.h"
#include "Clay_Config.h"
#include "Message_Queue.h"
#include "Clay_Message.h"

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

////Local vars/////////////////////////////////////////////////////
static Serial_Transmitter_States State;

static uint8 * Serial_Tx_Buffer;
static uint32 Serial_Tx_Count;
static Message * Temp_Message;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static bool Transmit();

////Global implementations ////////////////////////////////////////
bool Serial_Transmitter_Init()
{
   bool rval = true;

   State = Disable;
   Serial_Tx_Buffer = zalloc(SERIAL_TX_BUFFER_SIZE_BYTES);
   xTaskCreate(Serial_Transmitter_State_Step, "uarttx1", 256, NULL, 2, NULL);

   return rval;
}

void Serial_Transmitter_State_Step()
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
            if (Peek_Message(&incomingMessageQueue))
            {
               //TODO: check state with serial rx

               State = Message_Available;
            }
            break;
         }

         case Message_Available:
         {
            Temp_Message = Dequeue_Message(&incomingMessageQueue);

            Serial_Tx_Count = strlen(Temp_Message->content);
            strcpy(Serial_Tx_Buffer, Temp_Message->content);

//            printf("msg only: [%s]", Serial_Tx_Buffer);

            strcat(Serial_Tx_Buffer, Temp_Message->source);

//            printf("addr: [%s]", Temp_Message->source);
//            printf("msg + addr: [%s]", Serial_Tx_Buffer);

            State = Transmitting;

            GPIO_OUTPUT(BIT(0), 0);

            break;
         }

         case Wait_For_Transmit_Ok:
         {
            if (!GPIO_INPUT_GET(2))
            {
               State = Transmitting;
            }
            break;
         }

         case Transmitting:
         {
            printf(Serial_Tx_Buffer);
            State = Transmitting_Done;
            break;
         }

         case Transmitting_Done:
         {
            GPIO_OUTPUT(BIT(0), 1);
            State = Idle;
            break;
         }

         case UDP_STATE_MAX:
         default:
         {
            break;
         }
      }

      vTaskDelay(5 / portTICK_RATE_MS);
   }
}

////Local implementations /////////////////////////////////////////
static bool Connect()
{
   bool rval = false;
   return rval;
}

static bool Transmit()
{
   bool rval = false;
   return rval;
}
