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
#define VOLTAGE_TO_POSITION_SLOPE       0.08844f
#define VOLTAGE_TO_POSITION_OFFSET      57700

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static RGB_Color color;
static bool scale_mv_up;
static uint32_t scale_factor = 100;
static uint32_t input_voltage;
static uint32_t wait_time = 50;

////Local Prototypes///////////////////////////////////////////////
static void Toggle_Scale();
static double Scale_Adc_Counts_To_Servo_Range(uint32_t voltage_mv);

////Global implementations ////////////////////////////////////////
void Voltage_Controlled_Servo_Demo() {

   Power_Manager_Enable();
   Button_Enable();

   Enable_Clock();
   Start_Clock();

   Start_MPU9250();
   RGB_LED_Enable();

   Initialize_Channels();

   updated_channel_profile[CHANNEL_3].enabled = TRUE;
   updated_channel_profile[CHANNEL_3].type = CHANNEL_TYPE_WAVEFORM;
   updated_channel_profile[CHANNEL_3].direction = CHANNEL_DIRECTION_INPUT;

   updated_channel_profile[CHANNEL_4].enabled = TRUE;
   updated_channel_profile[CHANNEL_4].type = CHANNEL_TYPE_PULSE;
   updated_channel_profile[CHANNEL_4].direction = CHANNEL_DIRECTION_OUTPUT;

//   updated_channel_profile[CHANNEL_4].data->pulse_period_seconds = 0.02;
//   updated_channel_profile[CHANNEL_4].data->pulse_duty_cycle = 90;

   // <OPTIMIZE> (Optimize syntax to be smaller, preferably one line.)

   // Get observable set...
   //Observable_Set *observable_set = updated_channel_profile[CHANNEL_4].observable_set;
   Observable_Set *observable_set = channel_profile[CHANNEL_4].observable_set;
   Observable *observable = NULL;

   // ...then get data from channel profile... then update the date.
   observable = Get_Observable (observable_set, "pulse_period_seconds");
   float default_pulse_period_seconds = 0.02;
   Set_Observable_Content (observable, CONTENT_TYPE_FLOAT, &default_pulse_period_seconds);

   // ...then get data from channel profile... then update the date.
   observable = Get_Observable (observable_set, "pulse_duty_cycle");
   float default_pulse_duty_cycle = 90;
   Set_Observable_Content (observable, CONTENT_TYPE_INT16, &default_pulse_duty_cycle);

   // </OPTIMIZE>


   // Propagate state
   Observable_Set *source_observable_set = channel_profile[CHANNEL_3].observable_set;
   Propagator *propagator = Create_Propagator (
	   Get_Observable (source_observable_set, "waveform_sample_value"),
	   "waveform_sample_value",
	   Get_Observable (observable_set, "pulse_duty_cycle"),
	   "pulse_duty_cycle");
   Add_Propagator (
	   Get_Observable (source_observable_set, "waveform_sample_value"),
	   propagator);


   Apply_Channels();

   Channel_Enable_All();     //or the IMU won't initialize, which fucks with the RGB LEDs.

   Perform_Channel_Light_Effect(TRUE);

   Button_Register_Press_Response(Toggle_Scale);

   for (;;) {
      Channel_Periodic_Call();
      Button_Periodic_Call();

      //this value is set in channel_periodic_call
//      input_voltage = channel_profile[CHANNEL_3].data->waveform_sample_value;

      /*
      // <OPTIMIZE>
      observable_set = channel_profile[CHANNEL_3].observable_set;
      observable = Get_Observable (observable_set, "waveform_sample_value");
      int32 waveform_sample_value = Get_Observable_Data_Int32 (observable);
      input_voltage = (uint32_t) waveform_sample_value;
      // </OPTIMIZE>
      */

      // <HACK>
      // TODO: Update LEDs to use state structures for red, green, and blue observables for each LED channel (12)
      int32 waveform_sample_value = Get_Observable_Data_Int32 (observable);
      input_voltage = (uint32_t) waveform_sample_value;
      // </HACK>


      // TODO: Propagate state


      /*
      // ...then perform intermediate transformations...
      int16_t scaled_content = (int16_t) Scale_Adc_Counts_To_Servo_Range(input_voltage);
      */

      // TODO: Create ADC -> PWM mapping dynamically.

      //this value is an output, we need to call apply_channels to update the output.
//      updated_channel_profile[CHANNEL_4].data->pulse_duty_cycle = scaled_content;

      /*
      // <OPTIMIZE>
      observable_set = updated_channel_profile[CHANNEL_4].observable_set;
      observable = Get_Observable (observable_set, "pulse_duty_cycle");
      Set_Observable_Content (observable, CONTENT_TYPE_INT16, &scaled_content);
      // </OPTIMIZE>
      */

      //set the output.
      Apply_Channels();

      //just LED output for fun.
      color.R = input_voltage & 0xFF;
      color.G = (input_voltage >> 8) & 0xFF;
      color.B = (input_voltage >> 16) & 0xFF;

      for (int i = 0; i < RGB_MAX; ++i) {
         RGB_LED_SetColor((RGB_LED) i, &color);
      }

      Wait(wait_time);
   }

}

////Local implementations /////////////////////////////////////////
static void Toggle_Scale() {
   wait_time = (wait_time + 25) % 1000;
}

/*
double Band_Pass_Filter () {

}

double Scale (uint32_t value, uint32_t domain_lower_limit, uint32_t domain_upper_limit, uint32_t range_lower_limit, uint32_t range_upper_limit) {
	//adc count range is 0-65535
	//usable count range on pwm ratio is 63500-57700
	//(63500-57700) / 65535 = 0.08844
	//0.08844x + 57700 = y

	///we clipped the voltage input range because the ratio we get out from
	///   any voltage greater than this value will drive the servo beyond its end stop.
	int servo_max_voltage_before_end_stop = 56645; // TODO (?): High_Pass_Filter()/Band_Pass_Filter()

	//limiting to keep in range.
	if (value > servo_max_voltage_before_end_stop) {
		value = servo_max_voltage_before_end_stop;
	}

	return voltage_mv * VOLTAGE_TO_POSITION_SLOPE + VOLTAGE_TO_POSITION_OFFSET;
}
*/

static double Scale_Adc_Counts_To_Servo_Range(uint32_t voltage_mv) {

   //adc count range is 0-65535
   //usable count range on pwm ratio is 63500-57700
   //(63500-57700) / 65535 = 0.08844
   //0.08844x + 57700 = y

   ///we clipped the voltage input range because the ratio we get out from
   ///   any voltage greater than this value will drive the servo beyond its end stop.
   int servo_max_voltage_before_end_stop = 56645;

   //limiting to keep in range.
   if (voltage_mv > servo_max_voltage_before_end_stop) {
      voltage_mv = servo_max_voltage_before_end_stop;
   }

   return voltage_mv * VOLTAGE_TO_POSITION_SLOPE + VOLTAGE_TO_POSITION_OFFSET;
}
