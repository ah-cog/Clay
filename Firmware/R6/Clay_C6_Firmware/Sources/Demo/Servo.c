/*
 * Servo.c
 *
 *  Created on: Apr 18, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "Clock.h"
#include "IR_Range.h"
#include "GPIO.h"
#include "RGB_LED.h"
#include "Button.h"
#include "Power_Manager.h"
#include "MPU9250.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static RGB_Color color;
static bool scale_mv_up;
static uint32_t scale_factor = 100;
static uint32_t color_set;
static uint32_t wait_time = 50;

////Local Prototypes///////////////////////////////////////////////
static void Toggle_Scale();

////Global implementations ////////////////////////////////////////
extern void Servo_Demo() {

   Power_Manager_Enable();
   Button_Enable();

   Enable_Clock();
   Start_Clock();

   Start_MPU9250();
   RGB_LED_Enable();

   Initialize_Channels();

   updated_channel_profile[CHANNEL_6].enabled = TRUE;
   updated_channel_profile[CHANNEL_6].type = CHANNEL_TYPE_WAVEFORM;
   updated_channel_profile[CHANNEL_6].direction = CHANNEL_DIRECTION_INPUT;

   updated_channel_profile[CHANNEL_4].enabled = TRUE;
   updated_channel_profile[CHANNEL_4].type = CHANNEL_TYPE_PULSE;
   updated_channel_profile[CHANNEL_4].direction = CHANNEL_DIRECTION_OUTPUT;
   updated_channel_profile[CHANNEL_4].pulse_frequency = 50;
   updated_channel_profile[CHANNEL_4].pulse_duty = 90;

   Apply_Channels();

   Channel_Enable_All();     //or the IMU won't initialize, which fucks with the RGB LEDs.



   for (int i = 0; i < RGB_MAX; ++i) {
      RGB_LED_SetState((RGB_LED) i, TRUE, LED_CURRENT_QUARTER);
   }

   Button_Register_Press_Response(Toggle_Scale);

   scale_mv_up = TRUE;

   double channel_ratio = 90.0f;

   double min_ratio = 87.0f;
   double max_ratio = 98.2f;

   double range = max_ratio - min_ratio;
   double increment = 0.1f;

   for (;;) {
      Channel_Periodic_Call();
      Button_Periodic_Call();

      range = max_ratio - min_ratio;

      //the steppers I have tried work at 59200-63850 (90.3% - 98.4%). Make sure you connect your ground well!
      //
      channel_ratio = channel_ratio + increment;
      if (channel_ratio > max_ratio) {
         channel_ratio = min_ratio;
      }

      updated_channel_profile[CHANNEL_4].pulse_duty = channel_ratio;

      Apply_Channels();

//      channel_ratio = (channel_ratio + 1) % 100;
//      channel_ratio = (channel_ratio + 100) % 65535;

      color_set = channel_profile[CHANNEL_6].waveform_value * (scale_mv_up ? scale_factor : 1);

      color.R = color_set & 0xFF;
      color.G = (color_set >> 8) & 0xFF;
      color.B = (color_set >> 16) & 0xFF;

      for (int i = 0; i < RGB_MAX; ++i) {
         RGB_LED_SetColor((RGB_LED) i, &color);
      }

      RGB_LED_UpdateOutput();

      Wait(wait_time);
   }

}

////Local implementations /////////////////////////////////////////
static void Toggle_Scale() {
   wait_time = (wait_time + 25) % 1000;
}
