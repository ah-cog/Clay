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
#define VOLTAGE_TO_POSITION_SLOPE       0.0001709f
#define VOLTAGE_TO_POSITION_OFFSET      86.8f

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static RGB_Color color;
static bool scale_mv_up;
static uint32_t scale_factor = 100;
static uint32_t input_voltage;
static uint32_t wait_time = 50;

static double channel_ratio = 90.0f;
static double min_ratio = 86.8f;
static double max_ratio = 98.0f;
static double range;
static double increment = 0.1f;

////Local Prototypes///////////////////////////////////////////////
static void Toggle_Scale();
static double Scale_Voltage_To_Position(uint32_t voltage_mv);

////Global implementations ////////////////////////////////////////
void Voltage_Controlled_Servo_Demo() {

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

   range = max_ratio - min_ratio;

   for (;;) {
      Channel_Periodic_Call();
      Button_Periodic_Call();

      //this value is set in channel_periodic_call
      input_voltage = channel_profile[CHANNEL_6].waveform_value;

      //this value is an output, we need to call apply_channels to update the output.
      updated_channel_profile[CHANNEL_4].pulse_duty = Scale_Voltage_To_Position(input_voltage);

      //set the output.
      Apply_Channels();

      //just LED output for fun.
      color.R = input_voltage & 0xFF;
      color.G = (input_voltage >> 8) & 0xFF;
      color.B = (input_voltage >> 16) & 0xFF;

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

static double Scale_Voltage_To_Position(uint32_t voltage_mv) {

   //ADC count range is 0 - 65535
   //(98.0 - 86.8) / 65535 = .0001709 slope. 86.8 is offset.
   //.0001709x + 86.8 = y

   ///we clipped the voltage input range because the ratio we get out from
   ///   any voltage greater than this value will drive the servo beyond its end stop.
   int servo_max_voltage_before_end_stop = 56645;

   //limiting to keep in range.
   if (voltage_mv > servo_max_voltage_before_end_stop) {
      voltage_mv = servo_max_voltage_before_end_stop;
   }

   return voltage_mv * VOLTAGE_TO_POSITION_SLOPE + VOLTAGE_TO_POSITION_OFFSET;
}
