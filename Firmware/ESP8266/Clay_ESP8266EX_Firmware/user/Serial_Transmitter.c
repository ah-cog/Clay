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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Clay_Config.h"

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
   Disable,
   Configure,
   Idle,
   Message_Available,
   Transmitting,
   UDP_STATE_MAX
} Serial_Transmitter_States;
////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static Serial_Transmitter_States CurrentState;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static bool Transmit();

////Global implementations ////////////////////////////////////////
bool Serial_Transmitter_Init()
{
   bool rval = false;

   CurrentState = Configure;
   return rval;
}

void Serial_Transmitter_State_Step()
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

         case Message_Available:
         {
            break;
         }

         case Transmitting:
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

static bool Transmit()
{
   bool rval = false;
   return rval;
}
