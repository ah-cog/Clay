///////////////////////////////////////////////////////////////////
////Demo for Sharp GP2Y0A21YK IR range finder.

////Includes //////////////////////////////////////////////////////
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
static uint32_t range_mv;
static RGB_Color color;
static bool scale_mv_up;
static uint32_t scale_factor = 100;
static uint32_t color_set;

////Local Prototypes///////////////////////////////////////////////
static void Toggle_Scale();

////Global implementations ////////////////////////////////////////
void IR_Range_Demo() {

   Power_Manager_Enable();

   Button_Enable();
   Start_MPU9250();
   RGB_LED_Enable();

   updated_channel_profile[CHANNEL_6].enabled = TRUE;
   updated_channel_profile[CHANNEL_6].type = CHANNEL_TYPE_WAVEFORM;
   updated_channel_profile[CHANNEL_6].direction = CHANNEL_DIRECTION_INPUT;

   Apply_Channels();

   Channel_Enable_All();     //or the IMU won't initialize, which fucks with the RGB LEDs.

   for (int i = 0; i < RGB_MAX; ++i) {
      RGB_LED_SetState((RGB_LED) i, TRUE, LED_CURRENT_QUARTER);
   }

   Button_Register_Press_Response(Toggle_Scale);

   scale_mv_up = FALSE;

   for (;;) {
      Channel_Periodic_Call();
      Button_Periodic_Call();

      color_set = channel_profile[CHANNEL_6].waveform_value * (scale_mv_up ? scale_factor : 1);

      color.R = color_set & 0xFF;
      color.G = (color_set >> 8) & 0xFF;
      color.B = (color_set >> 16) & 0xFF;

      for (int i = 0; i < RGB_MAX; ++i) {
         RGB_LED_SetColor((RGB_LED) i, &color);
      }
      RGB_LED_UpdateOutput();
   }

}

////Local implementations /////////////////////////////////////////
static void Toggle_Scale() {
   scale_mv_up = !scale_mv_up;
}

