/*
 * StringMessageParser.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 *
 *      This class has functions to parse a byte array into a Clay_Message type, which can be queued to be sent
 *          over the serial lines to the microcontroller or over UDP to a remote device.
 */

/*
 * States:
 *      Disable -- no parsing happens
 *          - Go to idle when enabled
 *      Idle
 *          -Watch specified buffer for data. When data available go to Parsing
 *          -Look for Newline, then take exclusive access to buffer.
 *      Parsing
 *          -Parse message into message queue, update buffer information.
 *          -Release exclusive access to buffer
 *          -Return to idle
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
   Idle,
   Parsing,
   UDP_STATE_MAX
} String_Message_Parser_States;
////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static String_Message_Parser_States State;

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
bool String_Message_Parser_Init()
{
   bool rval = false;

   return rval;
}

void String_Message_Parser_State_Step()
{
   for (;;)
   {
      switch (State)
      {
         case Disable:
         {
            break;
         }

         case Idle:
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
