////Includes //////////////////////////////////////////////////////
#include "GPIO.h"

#include "PWM_Utils.h"

#include "GPIO_PTB.h"
#include "GPIO_PTC.h"
#include "GPIO_PTD.h"
#include "GPIO_PTE.h"

#include "ADC1.h"
#include "PWM_OUT_1.h"

////Macros ////////////////////////////////////////////////////////
#define GPIO_ADC_SLOPE          ((double)4.98344E-5F)
#define GPIO_ADC_OFFSET         0.0F

//these are here to preserve the indexing when ptb4 and 6 are assigned to PWM and ADC
#ifndef GPIO_PTB_IO_4_MASK
#define GPIO_PTB_IO_4_MASK 0
#endif

#ifndef GPIO_PTB_IO_6_MASK
#define GPIO_PTB_IO_6_MASK 0
#endif

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
Channel updated_channel_profile[CHANNEL_COUNT];
Channel channel_profile[CHANNEL_COUNT];

////Local vars/////////////////////////////////////////////////////
static MCU_GPIO_Digital_Interface channel_map[CHANNEL_COUNT] = { { MCU_GPIO_PORT_PTE, GPIO_PTE_IO_1_MASK },            // PTE1
                                                                 { MCU_GPIO_PORT_PTE, GPIO_PTE_IO_2_MASK },            // PTE2
                                                                 { MCU_GPIO_PORT_PTE, GPIO_PTE_IO_3_MASK },            // PTE3
                                                                 { MCU_GPIO_PORT_PTB, GPIO_PTB_IO_4_MASK },            // PTB18
                                                                 { MCU_GPIO_PORT_PTB, GPIO_PTB_IO_5_MASK },            // PTB19
                                                                 { MCU_GPIO_PORT_PTB, GPIO_PTB_IO_6_MASK },            // PTB0
                                                                 { MCU_GPIO_PORT_PTB, GPIO_PTB_IO_7_MASK },            // PTB21
                                                                 { MCU_GPIO_PORT_PTB, GPIO_PTB_IO_8_MASK },            // PTB22
                                                                 { MCU_GPIO_PORT_PTB, GPIO_PTB_IO_9_MASK },            // PTB23
                                                                 { MCU_GPIO_PORT_PTC, GPIO_PTC_IO_10_MASK },           // PTC16
                                                                 { MCU_GPIO_PORT_PTC, GPIO_PTC_IO_11_MASK },           // PTC17
                                                                 { MCU_GPIO_PORT_PTD, GPIO_PTD_IO_12_MASK }            // PTD6
};

static LDD_TDeviceData * PTB_data;
static LDD_TDeviceData * PTC_data;
static LDD_TDeviceData * PTD_data;
static LDD_TDeviceData * PTE_data;

static LDD_TDeviceData * ADC1_data;
static LDD_TDeviceData * PWM_OUT_1_data;

////Local Prototypes///////////////////////////////////////////////
static bool Channel_Enable_Toggle(Channel_Number number);
static bool Channel_Enable_Waveform(Channel_Number number);
static bool Channel_Enable_Pulse(Channel_Number number);

static void Channel_Disable_Toggle(Channel_Number number);
static void Channel_Disable_Waveform(Channel_Number number);
static void Channel_Disable_Pulse(Channel_Number number);

static int32_t Channel_Read_Toggle(Channel_Number number);
static int32_t Channel_Read_Waveform(Channel_Number number);

static int32_t Channel_Write_Toggle(Channel_Number number, int32_t data);
static int32_t Channel_Write_Pulse(Channel_Number number, int32_t data);

static int32_t Channel_Set_Direction_Toggle(Channel_Number number, Channel_Direction direction);
static int32_t Channel_Set_Direction_Waveform(Channel_Number number, Channel_Direction direction);
static int32_t Channel_Set_Direction_Pulse(Channel_Number number, Channel_Direction direction);

////Global implementations ////////////////////////////////////////
// Profile
int8_t Initialize_Channels() {
   int i;

   for (i = 0; i < CHANNEL_COUNT; i++) {
      // Initialize update channel profile
      updated_channel_profile[i].number = (Channel_Number)i;
      updated_channel_profile[i].enabled = FALSE;
      updated_channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      updated_channel_profile[i].type = CHANNEL_TYPE_TOGGLE;
      updated_channel_profile[i].value = CHANNEL_VALUE_TOGGLE_OFF;

      // Initialize channel profile
      channel_profile[i].number = (Channel_Number)i;
      channel_profile[i].enabled = FALSE;
      channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      channel_profile[i].type = CHANNEL_TYPE_TOGGLE;
      channel_profile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
   }

//   Initialize_Channel_Hardware_Profile();

   return TRUE;
}

// Profile
int8_t Reset_Channels() {
   int i;

   for (i = 0; i < CHANNEL_COUNT; i++) {

      // Initialize update channel profile
      updated_channel_profile[i].number = (Channel_Number)i;
      updated_channel_profile[i].enabled = FALSE;
      updated_channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      updated_channel_profile[i].type = CHANNEL_TYPE_TOGGLE;
      updated_channel_profile[i].value = CHANNEL_VALUE_TOGGLE_OFF;

//      // Initialize channel profile
//      channelProfile[i].number = (i + 1);
//      channelProfile[i].enabled = FALSE;
//      channelProfile[i].direction = CHANNEL_DIRECTION_OUTPUT;
//      channelProfile[i].type = CHANNEL_MODE_TOGGLE;
//      channelProfile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
   }

   return TRUE;
}

// Profiles -> Hardware
// TODO: Apply only changes! Compare current state to previous state or to actual hardware state. The former might be faster, but it's less "ground truth."
int8_t Apply_Channels() {
   int i;

   for (i = 0; i < CHANNEL_COUNT; i++) {

      // Check if the enable state changed. Apply the corresponding transform.
      if (updated_channel_profile[i].enabled != channel_profile[i].enabled) {
         if (channel_profile[i].enabled) {
            Channel_Enable(channel_profile[i].number);
         } else {
            Channel_Disable(channel_profile[i].number);
         }
      }

      // Update state.
      channel_profile[i].enabled = updated_channel_profile[i].enabled;

      if (channel_profile[i].enabled == TRUE) {

         // Apply state.
         Channel_Enable(channel_profile[i].number);

         // Check if the direction changed. Apply the corresponding transform if it changed.
         if (updated_channel_profile[i].direction != channel_profile[i].direction) {

            // Update direction.
            channel_profile[i].direction = updated_channel_profile[i].direction;

            // Apply direction.
            Channel_Set_Direction(channel_profile[i].number, channel_profile[i].direction);
         }

         // Check if the mode change. Apply the corresponding transform if it changed.
         if (updated_channel_profile[i].type != channel_profile[i].type) {

            // Update mode.
            channel_profile[i].type = updated_channel_profile[i].type;

            // Apply mode.
            Channel_Set_Direction(channel_profile[i].number, channel_profile[i].direction);
         }

         // Check if the value change. Apply the corresponding transform if it changed.
         if (updated_channel_profile[i].direction == CHANNEL_DIRECTION_OUTPUT
             && updated_channel_profile[i].value != channel_profile[i].value) {

            // Apply value.
            if (channel_profile[i].direction == CHANNEL_DIRECTION_OUTPUT) {
               Channel_Set_Data(channel_profile[i].number, updated_channel_profile[i].value);
            }
         }

      } else if (channel_profile[i].enabled == FALSE) {

         // Apply direction and mode.
         Channel_Set_Direction(channel_profile[i].number, CHANNEL_DIRECTION_OUTPUT);

         // Apply mode.
         Channel_Set_Type(channel_profile[i].number, CHANNEL_TYPE_TOGGLE);

         // Apply value.
         Channel_Set_Data(channel_profile[i].number, CHANNEL_VALUE_TOGGLE_OFF);

      }
//      }
   }

   return TRUE;
}

bool Channel_Enable_All() {

   bool result = TRUE;

   for (int i = 0; i < CHANNEL_COUNT; ++i) {
      result &= Channel_Enable((Channel_Number) i);
   }

   return result;
}

void Channel_Disable_All() {

   for (int i = 0; i < CHANNEL_COUNT; ++i) {
      Disable_Enable((Channel_Number) i);
   }
}

bool Channel_Enable(Channel_Number number) {

   bool rval = FALSE;

   switch (channel_profile[number].type) {

      case CHANNEL_TYPE_TOGGLE: {
         rval = Channel_Enable_Toggle(number);
         break;
      }

      case CHANNEL_TYPE_WAVEFORM: {
         rval = Channel_Enable_Waveform(number);
         break;
      }

      case CHANNEL_TYPE_PULSE: {
         rval = Channel_Enable_Pulse(number);
         break;
      }

      case CHANNEL_TYPE_COUNT: {
         rval = FALSE;
         break;
      }

      default: {
         break;
      }
   }

   if (rval) {
      channel_profile[number].enabled = TRUE;
   }

   return rval;
}

void Channel_Disable(Channel_Number number) {

   switch (channel_profile[number].type) {

      case CHANNEL_TYPE_TOGGLE: {
         Channel_Disable_Toggle(number);
         break;
      }

      case CHANNEL_TYPE_WAVEFORM: {
         Channel_Disable_Waveform(number);
         break;
      }

      case CHANNEL_TYPE_PULSE: {
         Channel_Disable_Pulse(number);
         break;
      }

      case CHANNEL_TYPE_COUNT: {
         break;
      }

      default: {
         break;
      }
   }

   channel_profile[number].enabled = FALSE;
}

bool Channel_Set_Type(Channel_Number number, Channel_Type type) {

   bool result = FALSE;

   channel_profile[number].type = type;

   //TODO: reinit as new type or disable -- we need to make sure the hardware is consistent with channel_profile

   return result;
}

Channel_Type Channel_Get_Type(Channel_Number number) {
   return channel_profile[number].type;
}

// Hardware
int32_t Channel_Set_Direction(Channel_Number number, Channel_Direction direction) {

   int32_t rval = -1;

   // Update Hardware
   switch (channel_profile[number].type) {
      case CHANNEL_TYPE_TOGGLE: {
         rval = Channel_Set_Direction_Toggle(number, direction);
         break;
      }
      case CHANNEL_TYPE_WAVEFORM: {
         rval = Channel_Set_Direction_Waveform(number, direction);
         break;
      }
      case CHANNEL_TYPE_PULSE: {
         rval = Channel_Set_Direction_Pulse(number, direction);
         break;
      }
      default: {
         break;
      }
   }

   if (rval == 0) {
      // Update Profile
      channel_profile[number].direction = direction;
   }

   return rval;
}

Channel_Direction Channel_Get_Direction(Channel_Number number) {
   return channel_profile[number].direction;
}

int32_t Channel_Set_Data(Channel_Number number, int32_t data) {

   int32_t result = -1;

   switch (channel_profile[number].type) {

      case CHANNEL_TYPE_TOGGLE: {
         // channel_profile[number].value = data;
         // result = Write_Digital(number, channel_profile[number]);
         result = Channel_Write_Toggle(number, data);
         break;
      }

      case CHANNEL_TYPE_WAVEFORM: {
         // Unsupported. Only ADC is available in the hardware right now.
         break;
      }

      case CHANNEL_TYPE_PULSE: {
         result = Channel_Write_Pulse(number, data);
         break;
      }

      case CHANNEL_TYPE_COUNT:
      default: {
         break;
      }
   }

   if (result != -1) {
      channel_profile[number].value = data;
   }

   return result;
}

int32_t Channel_Get_Data(Channel_Number number) {

   int32_t result = -1;

   //TODO: return the output data when in output mode?

   switch (channel_profile[number].type) {

      case CHANNEL_TYPE_TOGGLE: {
         result = Channel_Read_Toggle(number);
         break;
      }

      case CHANNEL_TYPE_WAVEFORM: {
         result = Channel_Read_Waveform(number);
         break;
      }

      case CHANNEL_TYPE_PULSE: {
         //TODO: hook up frequency read somewhere. Probably should call it a different pin type frequency_in or counter or something like that.
         break;
      }

      case CHANNEL_TYPE_COUNT:
      default: {
         break;
      }
   }

   return result;
}

////Local implementations /////////////////////////////////////////

// i.e., Digital
static bool Channel_Enable_Toggle(Channel_Number number) {

   if (number == CHANNEL_6 || number == CHANNEL_4) return FALSE;

   switch (channel_map[number].port) {
      case MCU_GPIO_PORT_PTB: {
         if (PTB_data == NULL) {
            PTB_data = GPIO_PTB_Init(NULL);
         }
         break;
      }

      case MCU_GPIO_PORT_PTC: {
         if (PTC_data == NULL) {
            PTC_data = GPIO_PTC_Init(NULL);
         }
         break;
      }

      case MCU_GPIO_PORT_PTD: {
         if (PTD_data == NULL) {
            PTD_data = GPIO_PTD_Init(NULL);
         }
         break;
      }

      case MCU_GPIO_PORT_PTE: {
         if (PTE_data == NULL) {
            PTE_data = GPIO_PTE_Init(NULL);
         }
         break;
      }

      case MCU_GPIO_PORT_COUNT:
      default: {
         break;
      }
   }

   return TRUE;
}

// i.e., Analog
static bool Channel_Enable_Waveform(Channel_Number number) {

   // <HACK>
   if (number != CHANNEL_6) return FALSE;
   // </HACK>

   ADC1_data = ADC1_Init(NULL);

   ADC1_StartCalibration(ADC1_data);

   while (!ADC1_GetMeasurementCompleteStatus(ADC1_data))
      ;

   LDD_TError adcCalOk = ADC1_GetCalibrationResultStatus(ADC1_data);

   return TRUE;
}

// i.e., PWM
static bool Channel_Enable_Pulse(Channel_Number number) {

   // <HACK>
   if (number != CHANNEL_4) return FALSE;
   // </HACK>

   LDD_TError err;

   PWM_OUT_1_data = PWM_OUT_1_Init(NULL);

   err = PWM_OUT_1_SetFrequencyHz(PWM_OUT_1_data, 0);
   PWM_OUT_1_SetRatio16(PWM_OUT_1_data, Scale_Percent_Uint16(0));

   return TRUE;
}

// Hardware. General-purpose GPIO control.
static int32_t Channel_Read_Toggle(Channel_Number number) {

   // <HACK>
   if (number == CHANNEL_6 || number == CHANNEL_4) return -1;
   // </HACK>

   int32_t result = -1;

   switch (channel_map[number].port) {
      case MCU_GPIO_PORT_PTB: {

         result = (GPIO_PTB_GetPortValue(PTB_data) & channel_map[number].mask) ? 1 : 0;

         break;
      }

      case MCU_GPIO_PORT_PTC: {

         result = (GPIO_PTC_GetPortValue(PTC_data) & channel_map[number].mask) ? 1 : 0;

         break;
      }

      case MCU_GPIO_PORT_PTD: {

         result = (GPIO_PTC_GetPortValue(PTC_data) & channel_map[number].mask) ? 1 : 0;

         break;
      }

      case MCU_GPIO_PORT_PTE: {

         result = (GPIO_PTC_GetPortValue(PTC_data) & channel_map[number].mask) ? 1 : 0;

         break;
      }

      case MCU_GPIO_PORT_COUNT:
      default: {
         break;
      }
   }

   return result;
}

// Hardware. General-purpose GPIO control.
static int32_t Channel_Read_Waveform(Channel_Number number) {

   if (number != CHANNEL_6) return -1;
   //TODO: get adc1 or adc0 and sample group from channel_map. For now, we just have CHANNEL_6 to worry about.

   int32_t result = -1;

   //select sample group. This in preconfigured in processor expert. port 6 is in sample group 0
   ADC1_SelectSampleGroup(ADC1_data, 0);

   //tell the ADC to start a measurement.
   ADC1_StartSingleMeasurement(ADC1_data);

   //Block while it measures. You could alternatively do this elsewhere. We may want to periodically read and cache the adc value for each active channel to avoid this
   while (!ADC1_GetMeasurementCompleteStatus(ADC1_data))
      ;

   //get the value
   ADC1_GetMeasuredValues(ADC1_data, &result);

   //apply voltage slope and offset. Because we're returning an int32, this return value is in millivolts.
   result = (((double) result * GPIO_ADC_SLOPE) + GPIO_ADC_OFFSET) * 1000;

   return result;
}

// Hardware. General-purpose GPIO control.
static int32_t Channel_Write_Toggle(Channel_Number number, int32_t data) {

   if (number == CHANNEL_6 || number == CHANNEL_4) return -1;

   int32_t result = 0;

   switch (channel_map[number].port) {
      case MCU_GPIO_PORT_PTB: {

         if (data) {
            GPIO_PTB_SetPortBits(PTB_data, channel_map[number].mask);
         } else {
            GPIO_PTB_ClearPortBits(PTB_data, channel_map[number].mask);
         }

         break;
      }

      case MCU_GPIO_PORT_PTC: {

         if (data) {
            GPIO_PTC_SetPortBits(PTC_data, channel_map[number].mask);
         } else {
            GPIO_PTC_ClearPortBits(PTC_data, channel_map[number].mask);
         }

         break;
      }

      case MCU_GPIO_PORT_PTD: {

         if (data) {
            GPIO_PTD_SetPortBits(PTD_data, channel_map[number].mask);
         } else {
            GPIO_PTD_ClearPortBits(PTD_data, channel_map[number].mask);
         }

         break;
      }

      case MCU_GPIO_PORT_PTE: {

         if (data) {
            GPIO_PTE_SetPortBits(PTE_data, channel_map[number].mask);
         } else {
            GPIO_PTE_ClearPortBits(PTE_data, channel_map[number].mask);
         }

         break;
      }

      case MCU_GPIO_PORT_COUNT:
      default: {
         break;
      }
   }

   return result;
}

// Hardware. General-purpose GPIO control.
static int32_t Channel_Write_Pulse(Channel_Number number, int32_t data) {

   if (number != CHANNEL_4) return -1;

   int32_t result = 0;

   if (data > 0) {

      //set the frequency
      PWM_OUT_1_SetFrequencyHz(PWM_OUT_1_data, data);

      //this is how we set the ratio. The ratio is set by a 16-bit value. We scale a percentage up to the full scale of that 16 bit value. example: 50% = 32768
      PWM_OUT_1_SetRatio16(PWM_OUT_1_data, Scale_Percent_Uint16(75));
   } else {

      //if we set the ratio to 0, the output will never change states.
      PWM_OUT_1_SetRatio16(PWM_OUT_1_data, 0);
   }

   return result;
}

static int32_t Channel_Set_Direction_Toggle(Channel_Number number, Channel_Direction direction) {

   int rval = 0;

   switch (channel_map[number].port) {
      case MCU_GPIO_PORT_PTB: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTB_SetPortInputDirection(PTB_data, channel_map[number].mask);
         } else {
            GPIO_PTB_SetPortOutputDirection(PTB_data, channel_map[number].mask, 0);
         }

         break;
      }

      case MCU_GPIO_PORT_PTC: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTC_SetPortInputDirection(PTC_data, channel_map[number].mask);
         } else {
            GPIO_PTC_SetPortOutputDirection(PTC_data, channel_map[number].mask, 0);
         }

         break;
      }

      case MCU_GPIO_PORT_PTD: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTD_SetPortInputDirection(PTD_data, channel_map[number].mask);
         } else {
            GPIO_PTD_SetPortOutputDirection(PTD_data, channel_map[number].mask, 0);
         }

         break;
      }

      case MCU_GPIO_PORT_PTE: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTE_SetPortInputDirection(PTE_data, channel_map[number].mask);
         } else {
            GPIO_PTE_SetPortOutputDirection(PTE_data, channel_map[number].mask, 0);
         }

         break;
      }

      case MCU_GPIO_PORT_COUNT:
      default: {
         break;
      }
   }

   return rval;
}

static int32_t Channel_Set_Direction_Waveform(Channel_Number number, Channel_Direction direction) {

   //HACK
   if (direction == CHANNEL_DIRECTION_INPUT) {
      return 0;
   } else {
      return -1;
   }
}

static int32_t Channel_Set_Direction_Pulse(Channel_Number number, Channel_Direction direction) {

   //HACK
   if (direction == CHANNEL_DIRECTION_OUTPUT) {
      return 0;
   } else {
      return -1;
   }
}

static void Channel_Disable_Toggle(Channel_Number number) {

   //TODO: this needs some more work when we get to the point where we're able to reconfig pins for different operations.
   //      the code below would disable the ports, but the ports are currently shared between I/O pins.
   return;

   if (number == CHANNEL_6 || number == CHANNEL_4) return;

   switch (channel_map[number].port) {
      case MCU_GPIO_PORT_PTB: {
         if (PTB_data != NULL) {
            GPIO_PTB_Deinit(PTB_data);
            PTB_data = NULL;
         }
         break;
      }

      case MCU_GPIO_PORT_PTC: {
         if (PTC_data != NULL) {
            GPIO_PTC_Deinit(PTC_data);
            PTC_data = NULL;
         }
         break;
      }

      case MCU_GPIO_PORT_PTD: {
         if (PTD_data != NULL) {
            GPIO_PTD_Deinit(PTD_data);
            PTD_data = NULL;
         }
         break;
      }

      case MCU_GPIO_PORT_PTE: {
         if (PTE_data != NULL) {
            GPIO_PTE_Deinit(PTE_data);
            PTE_data = NULL;
         }
         break;
      }

      case MCU_GPIO_PORT_COUNT:
      default: {
         break;
      }
   }
}

static void Channel_Disable_Waveform(Channel_Number number) {

   if (number != CHANNEL_6) return;
   ADC1_Deinit(ADC1_data);
   ADC1_data = NULL;
}

static void Channel_Disable_Pulse(Channel_Number number) {

   if (number != CHANNEL_4) return;
   PWM_OUT_1_Deinit(PWM_OUT_1_data);
   PWM_OUT_1_data = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//test code for digital, adc, pwm.
//Channel_Set_Type(CHANNEL_4, CHANNEL_TYPE_PULSE);
//Channel_Set_Type(CHANNEL_6, CHANNEL_TYPE_WAVEFORM);
//Channel_Enable_All();
//
//for (i = 0; i < CHANNEL_COUNT; ++i) {
//   Channel_Set_Direction(i, CHANNEL_DIRECTION_OUTPUT);
//}
//
//int adc;
//int pwm_freq_hz = 1000;
//bool on = FALSE;
//
//for (;;) {
//
//   adc = Channel_Get_Data(CHANNEL_6);
//   Channel_Set_Data(CHANNEL_4, pwm_freq_hz);
//
//   pwm_freq_hz = (pwm_freq_hz + 1000) % 10000;
//
//   Wait(1000);
//
//   for (i = 0; i < 12; i++) {
//      Channel_Set_Data(i, on);
//   }
//   on = !on;
//}
