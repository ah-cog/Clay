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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Clay_Config.h"

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
   Disable,
   Configure,
   Idle,
   Receiving,
   Parsing,
   UDP_STATE_MAX
} Serial_Receiver_States;
////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static Serial_Receiver_States CurrentState;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static bool Receive();

////Global implementations ////////////////////////////////////////
bool Serial_Receiver_Init()
{
   bool rval = false;

   CurrentState = Configure;
   return rval;
}

void Serial_Receiver_State_Step()
{
   for (;;)
   {
      switch (CurrentState)
      {
         case Disable:
         {
            break;
         }

         case Configure:
         {
            break;
         }

         case Idle:
         {
            break;
         }

         case Receiving:
         {
            break;
         }

         case Parsing:
         {
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

static bool Receive()
{
   bool rval = false;
   return rval;
}
