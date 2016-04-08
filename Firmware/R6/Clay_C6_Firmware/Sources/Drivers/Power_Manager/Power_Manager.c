/*
 * Power_Manager.c
 *
 *  Created on: Mar 27, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "Power_Manager.h"
#include "Button.h"
#include "PowerOn.h"
#include "Clock.h"

////Macros ////////////////////////////////////////////////////////
#define BUTTON_SHUTDOWN_HOLD_TIME_ms         3000
#define BUTTON_STARTUP_HOLD_TIME_ms         500

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static LDD_TDeviceData * power_on_data;

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////

//enable ADC and register button.
bool Power_Manager_Enable() {

   bool rval = TRUE;
   Button_Register_Hold_Response(BUTTON_SHUTDOWN_HOLD_TIME_ms, Power_Manager_Power_Off);

   //init power on line and set high so we stay on.
   power_on_data = PowerOn_Init(NULL);
   PowerOn_PutVal(power_on_data, 1);

   return rval;
}

//call on startup; watch button and make sure user holds it for a certain period of time. We should do this to prevent unintentional power-on
void Power_Manager_Check_Startup() {

   //Comment this out ONLY for release. It becomes very difficult to connect and debug with this enabled.
   return;

   while ((Millis() < BUTTON_STARTUP_HOLD_TIME_ms)) {
      if (!Button_Get_Status()) {
         Power_Manager_Power_Off();
      }
   }
}

//pulls the UVLO line low to turn off the regulator.
void Power_Manager_Power_Off() {

   //wait for button to be released so we don't immediately turn on again.
   while (Button_Get_Status()) {
      Wait(10);
   }

   PowerOn_PutVal(power_on_data, 0);

   for (;;)
      ;
}

//looks at ADC to see if user wants to shut down.
void Power_Manager_Check_For_Power_Off_Conditions() {

}

////Local implementations /////////////////////////////////////////

//      //monitor the input voltage line. We need to shut down on low battery ~3.2v. See schematic for resistor divider and input scaling.
//      if ((vBat != 0 && vBat < 3.2) || Button_Press_Time > 0 && (Millis() - Button_Press_Time) > 1500) {
//
//         //TODO: We may need a watchdog or high priority timer interrupt, or task, that
//         //      checks to see if the user is holding down the button. Perhaps we just
//         //      make it a high priority double-edge
//
//         //IDEA: start flashing LEDs to signal to the user that they are about to shut
//         //      the module down. If the user releases the button, continue operation
//         //      as usual. Otherwise:
//
//         //TODO: stop doing things, shut down gracefully,  and then:
//
//         //TODO: Make it apparent that Clay is ready to turn off. Stop flashing things. The power LED will remain on.
//         //We wait for the user to release the button so that they don't immediately turn the module back on again.
//
//         LED2_PutVal(NULL, FALSE);
//         LED1_PutVal(NULL, FALSE);
//         while (Read_Button_In()) {
//            Wait(1);
//         }
//
//         //Pull the PowerOn line low. Regulator's UVLO will drop below 0 and shut off the board.
//         PowerOn_PutVal(NULL, 0);
//         for (;;)
//            ;
//      } else if (Button_Press_Time == 0 && Read_Button_In()) {
//         Button_Press_Time = Millis();
//      } else if (Button_Press_Time > 0 && !Read_Button_In()) {
//         Button_Press_Time = 0;
//      }
