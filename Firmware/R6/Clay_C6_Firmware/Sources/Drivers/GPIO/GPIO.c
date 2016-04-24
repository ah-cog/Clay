////Includes //////////////////////////////////////////////////////
#include "stdlib.h"
#include "string.h"
#include "stdint.h"

#include "GPIO.h"

#include "PWM_Utils.h"

#include "GPIO_PTB.h"
#include "GPIO_PTC.h"
#include "GPIO_PTD.h"
#include "GPIO_PTE.h"

#include "ADC1.h"
#include "PWM_OUT_1.h"

//TODO: lose ADC calibration
//      get channel hardware put into this code
//      document channel hardware on notion

////Macros ////////////////////////////////////////////////////////

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
//static MCU_GPIO_Digital_Interface channel_map[CHANNEL_COUNT] = { { MCU_GPIO_PORT_PTE, GPIO_PTE_IO_1_MASK },            // PTE1
//                                                                 { MCU_GPIO_PORT_PTE, GPIO_PTE_IO_2_MASK },            // PTE2
//                                                                 { MCU_GPIO_PORT_PTE, GPIO_PTE_IO_3_MASK },            // PTE3
//                                                                 { MCU_GPIO_PORT_PTB, GPIO_PTB_IO_4_MASK },            // PTB18
//                                                                 { MCU_GPIO_PORT_PTB, GPIO_PTB_IO_5_MASK },            // PTB19
//                                                                 { MCU_GPIO_PORT_PTB, GPIO_PTB_IO_6_MASK },            // PTB0
//                                                                 { MCU_GPIO_PORT_PTB, GPIO_PTB_IO_7_MASK },            // PTB21
//                                                                 { MCU_GPIO_PORT_PTB, GPIO_PTB_IO_8_MASK },            // PTB22
//                                                                 { MCU_GPIO_PORT_PTB, GPIO_PTB_IO_9_MASK },            // PTB23
//                                                                 { MCU_GPIO_PORT_PTC, GPIO_PTC_IO_10_MASK },           // PTC16
//                                                                 { MCU_GPIO_PORT_PTC, GPIO_PTC_IO_11_MASK },           // PTC17
//                                                                 { MCU_GPIO_PORT_PTD, GPIO_PTD_IO_12_MASK }            // PTD6
//};

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
static int32_t Channel_Write_Pulse(Channel_Number number, LDD_PPG_Tfloat period_s, uint16_t ratio);

static int32_t Channel_Set_Direction_Toggle(Channel_Number number, Channel_Direction direction);
static int32_t Channel_Set_Direction_Waveform(Channel_Number number, Channel_Direction direction);
static int32_t Channel_Set_Direction_Pulse(Channel_Number number, Channel_Direction direction);

static void Channel_Apply_Output(Channel_Number number);

static void Initialize_Hardware_Profile();
static void Initialize_Channel_Hardware_Profile(Channel_Number number);

////Global implementations ////////////////////////////////////////
// Profile
int8_t Initialize_Channels() {
   int i;

   for (i = 0; i < CHANNEL_COUNT; i++) {
      // Initialize update channel profile
      updated_channel_profile[i].number = (Channel_Number) i;
      updated_channel_profile[i].enabled = FALSE;
      updated_channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      updated_channel_profile[i].type = CHANNEL_TYPE_TOGGLE;
      updated_channel_profile[i].toggle_value = CHANNEL_VALUE_TOGGLE_OFF;
      updated_channel_profile[i].waveform_value = -1;
      updated_channel_profile[i].pulse_period_s = 0;
      updated_channel_profile[i].pulse_duty = 0;

      // Initialize channel profile
      channel_profile[i].number = (Channel_Number) i;
      channel_profile[i].enabled = FALSE;
      channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      channel_profile[i].type = CHANNEL_TYPE_TOGGLE;
      channel_profile[i].toggle_value = CHANNEL_VALUE_TOGGLE_OFF;
      channel_profile[i].waveform_value = -1;
      channel_profile[i].pulse_period_s = 0;
      channel_profile[i].pulse_duty = 0;

   }

   Initialize_Hardware_Profile();

   return TRUE;
}

// Profile
int8_t Reset_Channels() {
   int i;

   for (i = 0; i < CHANNEL_COUNT; i++) {

      // Initialize update channel profile
      updated_channel_profile[i].number = (Channel_Number) i;
      updated_channel_profile[i].enabled = FALSE;
      updated_channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      updated_channel_profile[i].type = CHANNEL_TYPE_TOGGLE;
      updated_channel_profile[i].toggle_value = CHANNEL_VALUE_TOGGLE_OFF;
      updated_channel_profile[i].waveform_value = -1;
      updated_channel_profile[i].pulse_period_s = 0;
      updated_channel_profile[i].pulse_duty = 0;

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

      if (updated_channel_profile[i].enabled = TRUE) {
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
            Channel_Set_Type(channel_profile[i].number, channel_profile[i].type);
         }

         // Check if the enable state changed. Apply the corresponding transform.
         if (updated_channel_profile[i].enabled != channel_profile[i].enabled) {
            if (updated_channel_profile[i].enabled) {
               Channel_Enable(channel_profile[i].number);
            } else {
               Channel_Disable(channel_profile[i].number);
            }
         }

         // Check if the value change. Apply the corresponding transform if it changed.
         if (updated_channel_profile[i].direction == CHANNEL_DIRECTION_OUTPUT
             && (channel_profile[i].toggle_value != updated_channel_profile[i].toggle_value
                 || channel_profile[i].waveform_value != updated_channel_profile[i].waveform_value
                 || channel_profile[i].pulse_period_s != updated_channel_profile[i].pulse_period_s
                 || channel_profile[i].pulse_duty != updated_channel_profile[i].pulse_duty)) {

            channel_profile[i].toggle_value = updated_channel_profile[i].toggle_value;
            channel_profile[i].waveform_value = updated_channel_profile[i].waveform_value;
            channel_profile[i].pulse_period_s = updated_channel_profile[i].pulse_period_s;
            channel_profile[i].pulse_duty = updated_channel_profile[i].pulse_duty;

            // Apply value.
            Channel_Apply_Output((Channel_Number) i);

         } else if (updated_channel_profile[i].direction == CHANNEL_DIRECTION_INPUT) {
            channel_profile[i].toggle_value = updated_channel_profile[i].toggle_value;
            channel_profile[i].waveform_value = updated_channel_profile[i].waveform_value;
            channel_profile[i].pulse_period_s = updated_channel_profile[i].pulse_period_s;
            channel_profile[i].pulse_duty = updated_channel_profile[i].pulse_duty;
         }

      } else if (updated_channel_profile[i].enabled == FALSE
                 && updated_channel_profile[i].enabled != channel_profile[i].enabled) {

         // Apply direction and mode.
         Channel_Set_Direction(channel_profile[i].number, CHANNEL_DIRECTION_OUTPUT);

         // Apply mode.
         Channel_Set_Type(channel_profile[i].number, CHANNEL_TYPE_TOGGLE);

         // Apply value.
         Channel_Set_Data(channel_profile[i].number, CHANNEL_VALUE_TOGGLE_OFF);

      }
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
      Channel_Disable((Channel_Number) i);
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

   channel_profile[number].enabled = FALSE;

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

//   channel_profile[number].enabled = FALSE;
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

         result = Channel_Write_Toggle(number, data);

         if (result != -1) {
            channel_profile[number].toggle_value = data;
         }

         break;
      }

      case CHANNEL_TYPE_WAVEFORM: {
         // Unsupported. Only ADC is available in the hardware right now.
         break;
      }

      case CHANNEL_TYPE_PULSE: {
         result = Channel_Write_Pulse(number, data, channel_profile[number].pulse_duty);

         if (result != -1) {
            channel_profile[number].pulse_period_s = data;
         }

         break;
      }

      case CHANNEL_TYPE_COUNT:
      default: {
         break;
      }
   }

   return result;
}

int32_t Channel_Get_Data(Channel_Number number) {

   int32_t result = -1;

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

void Channel_Periodic_Call() {

   for (int i = 0; i < CHANNEL_COUNT; ++i) {
      if (channel_profile[i].direction == CHANNEL_DIRECTION_INPUT) {
         switch (channel_profile[i].type) {
            case CHANNEL_TYPE_WAVEFORM: {
               updated_channel_profile[i].waveform_value = Channel_Get_Data((Channel_Number) i);
               break;
            }
            case CHANNEL_TYPE_TOGGLE: {
               updated_channel_profile[i].toggle_value = Channel_Get_Data((Channel_Number) i);
               break;
            }
            default: {
               break;
            }
         }
      }
   }

// <HACK>
   Apply_Channels();
// </HACK>
}

////Local implementations /////////////////////////////////////////

// i.e., Digital
static bool Channel_Enable_Toggle(Channel_Number number) {

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_TOGGLE)
       || channel_profile[number].type != CHANNEL_TYPE_TOGGLE) return FALSE;

   switch (channel_profile[number].mcu_hardware_profile.digital_interface->port) {
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

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_WAVEFORM)
       || channel_profile[number].type != CHANNEL_TYPE_WAVEFORM) return FALSE;

   bool rval = FALSE;

   switch (channel_profile[number].mcu_hardware_profile.adc_interface->adc_channel) {
      case MCU_ADC0: {

         //TODO: Config ADC0 . we'll have to share it with the vbat adc line.

//            ADC0_data = ADC0_Init(NULL);
//
//            ADC0_StartCalibration(ADC0_data);
//
//            while (!ADC0_GetMeasurementCompleteStatus(ADC0_data))
//               ;
//
//            LDD_TError adcCalOk = ADC0_GetCalibrationResultStatus(ADC0_data);
//            rval = TRUE;

         break;
      }

      case MCU_ADC1: {

         ADC1_data = ADC1_Init(NULL);

         ADC1_StartCalibration(ADC1_data);

         while (!ADC1_GetMeasurementCompleteStatus(ADC1_data))
            ;

         LDD_TError adcCalOk = ADC1_GetCalibrationResultStatus(ADC1_data);

         rval = TRUE;
         break;
      }

      default: {
         break;
      }
   }

   return rval;
}

// i.e., PWM
static bool Channel_Enable_Pulse(Channel_Number number) {

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_PULSE)
       || channel_profile[number].type != CHANNEL_TYPE_PULSE) return FALSE;

   bool rval = FALSE;

   switch (channel_profile[number].mcu_hardware_profile.pwm_interface->pwm_channel) {
      case MCU_PWM_OUT_1: {

         LDD_TError err;

         PWM_OUT_1_data = PWM_OUT_1_Init(NULL);

         err = PWM_OUT_1_SetFrequencyHz(PWM_OUT_1_data, 0);
         PWM_OUT_1_SetRatio16(PWM_OUT_1_data, 0);

         rval = TRUE;

         break;
      }

      case MCU_PWM_OUT_2: {

         //PWM_OUT_2 not implemented
//         LDD_TError err;
//
//         PWM_OUT_2_data = PWM_OUT_2_Init(NULL);
//
//         err = PWM_OUT_2_SetFrequencyHz(PWM_OUT_2_data, 0);
//         PWM_OUT_2_SetRatio16(PWM_OUT_2_data, 0);
//
//         rval = TRUE;

         break;
      }

      case MCU_PWM_OUT_3: {

         //PWM_OUT_3 not implemented
//         LDD_TError err;
//
//         PWM_OUT_3_data = PWM_OUT_3_Init(NULL);
//
//         err = PWM_OUT_3_SetFrequencyHz(PWM_OUT_3_data, 0);
//         PWM_OUT_3_SetRatio16(PWM_OUT_3_data, 0);
//
//         rval = TRUE;

         break;
      }

      case MCU_PWM_OUT_4: {

         //PWM_OUT_3 not implemented
//         LDD_TError err;
//
//         PWM_OUT_4_data = PWM_OUT_4_Init(NULL);
//
//         err = PWM_OUT_4_SetFrequencyHz(PWM_OUT_4_data, 0);
//         PWM_OUT_4_SetRatio16(PWM_OUT_4_data, 0);
//
//         rval = TRUE;

         break;
      }

      default: {
         break;
      }
   }

   return rval;

}

// Hardware. General-purpose GPIO control.
static int32_t Channel_Read_Toggle(Channel_Number number) {

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_TOGGLE)
       || channel_profile[number].type != CHANNEL_TYPE_TOGGLE) return -1;

   int32_t result = -1;

   switch (channel_profile[number].mcu_hardware_profile.digital_interface->port) {
      case MCU_GPIO_PORT_PTB: {

         result =
               (GPIO_PTB_GetPortValue(PTB_data) & channel_profile[number].mcu_hardware_profile.digital_interface->mask) ? 1 : 0;

         break;
      }

      case MCU_GPIO_PORT_PTC: {

         result =
               (GPIO_PTC_GetPortValue(PTC_data) & channel_profile[number].mcu_hardware_profile.digital_interface->mask) ? 1 : 0;

         break;
      }

      case MCU_GPIO_PORT_PTD: {

         result =
               (GPIO_PTC_GetPortValue(PTC_data) & channel_profile[number].mcu_hardware_profile.digital_interface->mask) ? 1 : 0;

         break;
      }

      case MCU_GPIO_PORT_PTE: {

         result =
               (GPIO_PTC_GetPortValue(PTC_data) & channel_profile[number].mcu_hardware_profile.digital_interface->mask) ? 1 : 0;

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

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_WAVEFORM)
       || channel_profile[number].type != CHANNEL_TYPE_WAVEFORM) return -1;

   int rval;

   switch (channel_profile[number].mcu_hardware_profile.adc_interface->adc_channel) {
      case MCU_ADC0: {
         //TODO: Config ADC0 . we'll have to share it with the vbat adc line.
//         ADC0_SelectSampleGroup(ADC0_data, channel_profile[number].mcu_hardware_profile.adc_interface->sample_group);

//tell the ADC to start a measurement.
//         ADC0_StartSingleMeasurement(ADC0_data);
//
//         //Block while it measures. You could alternatively do this elsewhere. We may want to periodically read and cache the adc value for each active channel to avoid this
//         while (!ADC0_GetMeasurementCompleteStatus(ADC0_data))
//            ;
//
//         //get the value
//         ADC0_GetMeasuredValues(ADC0_data, &rval);

         break;
      }

      case MCU_ADC1: {
         ADC1_SelectSampleGroup(ADC1_data, channel_profile[number].mcu_hardware_profile.adc_interface->sample_group);

         //tell the ADC to start a measurement.
         ADC1_StartSingleMeasurement(ADC1_data);

         //Block while it measures. You could alternatively do this elsewhere. We may want to periodically read and cache the adc value for each active channel to avoid this
         while (!ADC1_GetMeasurementCompleteStatus(ADC1_data))
            ;

         //get the value
         ADC1_GetMeasuredValues(ADC1_data, &rval);

         break;
      }

      default: {
         break;
      }
   }

   return rval;
}

// Hardware. General-purpose GPIO control.
static int32_t Channel_Write_Toggle(Channel_Number number, int32_t data) {

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_TOGGLE)
       || channel_profile[number].type != CHANNEL_TYPE_TOGGLE) return -1;

   int32_t result = 0;

   switch (channel_profile[number].mcu_hardware_profile.digital_interface->port) {
      case MCU_GPIO_PORT_PTB: {

         if (data) {
            GPIO_PTB_SetPortBits(PTB_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
         } else {
            GPIO_PTB_ClearPortBits(PTB_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
         }

         break;
      }

      case MCU_GPIO_PORT_PTC: {

         if (data) {
            GPIO_PTC_SetPortBits(PTC_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
         } else {
            GPIO_PTC_ClearPortBits(PTC_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
         }

         break;
      }

      case MCU_GPIO_PORT_PTD: {

         if (data) {
            GPIO_PTD_SetPortBits(PTD_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
         } else {
            GPIO_PTD_ClearPortBits(PTD_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
         }

         break;
      }

      case MCU_GPIO_PORT_PTE: {

         if (data) {
            GPIO_PTE_SetPortBits(PTE_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
         } else {
            GPIO_PTE_ClearPortBits(PTE_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
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
static int32_t Channel_Write_Pulse(Channel_Number number, LDD_PPG_Tfloat period_s, uint16_t ratio) {

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_PULSE)
       || channel_profile[number].type != CHANNEL_TYPE_PULSE) return -1;

   int32_t rval = 0;

   switch (channel_profile[number].mcu_hardware_profile.pwm_interface->pwm_channel) {
      case MCU_PWM_OUT_1: {

         if (period_s > 0 && ratio > 0) {

            //set the frequency
            PWM_OUT_1_SetPeriodReal(PWM_OUT_1_data, period_s);     //50 hz for motor drive

            //this is how we set the ratio. The ratio is set by a 16-bit value. We scale a percentage up to the full scale of that 16 bit value. example: 50% = 32768
            PWM_OUT_1_SetRatio16(PWM_OUT_1_data, ratio);     //when changing frequency, fix the ratio
         } else {

            //if we set the ratio to 0, the output will never change states.
            PWM_OUT_1_SetRatio16(PWM_OUT_1_data, 0);
         }

         break;
      }

      case MCU_PWM_OUT_2: {
         break;
      }

      case MCU_PWM_OUT_3: {
         break;
      }

      case MCU_PWM_OUT_4: {
         break;
      }

      default: {
         break;
      }
   }

   return rval;
}

static int32_t Channel_Set_Direction_Toggle(Channel_Number number, Channel_Direction direction) {

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_TOGGLE)
       || channel_profile[number].type != CHANNEL_TYPE_TOGGLE) return -1;

   int rval = 0;

   switch (channel_profile[number].mcu_hardware_profile.digital_interface->port) {
      case MCU_GPIO_PORT_PTB: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTB_SetPortInputDirection(PTB_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
         } else {
            GPIO_PTB_SetPortOutputDirection(PTB_data,
                                            channel_profile[number].mcu_hardware_profile.digital_interface->mask,
                                            channel_profile[number].toggle_value);
         }

         break;
      }

      case MCU_GPIO_PORT_PTC: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTC_SetPortInputDirection(PTC_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
         } else {
            GPIO_PTC_SetPortOutputDirection(PTC_data,
                                            channel_profile[number].mcu_hardware_profile.digital_interface->mask,
                                            channel_profile[number].toggle_value);
         }

         break;
      }

      case MCU_GPIO_PORT_PTD: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTD_SetPortInputDirection(PTD_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
         } else {
            GPIO_PTD_SetPortOutputDirection(PTD_data,
                                            channel_profile[number].mcu_hardware_profile.digital_interface->mask,
                                            channel_profile[number].toggle_value);
         }

         break;
      }

      case MCU_GPIO_PORT_PTE: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTE_SetPortInputDirection(PTE_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
         } else {
            GPIO_PTE_SetPortOutputDirection(PTE_data,
                                            channel_profile[number].mcu_hardware_profile.digital_interface->mask,
                                            channel_profile[number].toggle_value);
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

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_WAVEFORM)
       || channel_profile[number].type != CHANNEL_TYPE_WAVEFORM) return -1;

//HACK
   if (direction == CHANNEL_DIRECTION_INPUT) {
      return 0;
   } else {
      return -1;
   }
}

static int32_t Channel_Set_Direction_Pulse(Channel_Number number, Channel_Direction direction) {

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_PULSE)
       || channel_profile[number].type != CHANNEL_TYPE_PULSE) return -1;

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

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_TOGGLE)
       || channel_profile[number].type != CHANNEL_TYPE_TOGGLE) return;

   switch (channel_profile[number].mcu_hardware_profile.digital_interface->port) {
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

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_PULSE)
       || channel_profile[number].type != CHANNEL_TYPE_PULSE) return;

   int rval;

   switch (channel_profile[number].mcu_hardware_profile.adc_interface->adc_channel) {
      case MCU_ADC0: {

         //TODO: check for other ADC's still live before de-init. We'll have to figure out how to free the pin back up for reassignment.
         //ADC 0 not config'd yet.
//         ADC0_Deinit(ADC0_data);
//         ADC0_data = NULL;

         break;
      }

      case MCU_ADC1: {

         //TODO: check for other ADC's still live before de-init. We'll have to figure out how to free the pin back up for reassignment.
         ADC1_Deinit(ADC1_data);
         ADC1_data = NULL;

         break;
      }

      default: {
         break;
      }
   }

   return rval;
}

static void Channel_Disable_Pulse(Channel_Number number) {

   if (!(channel_profile[number].mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_PULSE)
       || channel_profile[number].type != CHANNEL_TYPE_PULSE) return;

   PWM_OUT_1_Deinit(PWM_OUT_1_data);
   PWM_OUT_1_data = NULL;
}

static void Channel_Apply_Output(Channel_Number number) {

   switch (channel_profile[number].type) {
      case CHANNEL_TYPE_PULSE: {
         Channel_Write_Pulse(number, channel_profile[number].pulse_period_s, channel_profile[number].pulse_duty);
         break;
      }
      case CHANNEL_TYPE_TOGGLE: {
         Channel_Write_Toggle(number, channel_profile[number].toggle_value);
         break;
      }
      default: {
         break;
      }
   }

}

static void Initialize_Hardware_Profile() {

   for (int i = 0; i < CHANNEL_COUNT; ++i) {
      Initialize_Channel_Hardware_Profile((Channel_Number) i);
   }
}

static void Initialize_Channel_Hardware_Profile(Channel_Number number) {

   MCU_GPIO_Profile * profile = &channel_profile[number].mcu_hardware_profile;

   switch (number) {

      case CHANNEL_1: {
         //      1,PTE1,LLWU_P0,ADC1_SE5a,SPI1_SOUT,UART1_RX,SDHC_D0,I2C1_SCL,SPI1_SIN

         profile->adc_interface = calloc(1, sizeof(MCU_GPIO_ADC_Interface));
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->adc_interface->adc_channel = MCU_ADC1;
         profile->adc_interface->sample_group = 0;

         profile->digital_interface->port = MCU_GPIO_PORT_PTE;
         profile->digital_interface->mask = GPIO_PTE_IO_1_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE | CHANNEL_TYPE_WAVEFORM;

         break;
      }

      case CHANNEL_2: {
         //      2,PTE2,LLWU_P1,ADC0_DP2,ADC1_SE6a,SPI1_SCK,UART1_CTS_b,SDHC0_DCLK

         profile->adc_interface = calloc(1, sizeof(MCU_GPIO_ADC_Interface));
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->adc_interface->adc_channel = MCU_ADC1;
         profile->adc_interface->sample_group = 0;

         profile->digital_interface->port = MCU_GPIO_PORT_PTE;
         profile->digital_interface->mask = GPIO_PTE_IO_2_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE | CHANNEL_TYPE_WAVEFORM;

         break;
      }

      case CHANNEL_3: {
         //      3,PTE3,ADC0_DM2,ADC1_SE7a,SPI1_SIN,UART1_RTS_b,SDHC0_CMD,SPI1_SOUT

         profile->adc_interface = calloc(1, sizeof(MCU_GPIO_ADC_Interface));
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->adc_interface->adc_channel = MCU_ADC1;
         profile->adc_interface->sample_group = 0;

         profile->digital_interface->port = MCU_GPIO_PORT_PTE;
         profile->digital_interface->mask = GPIO_PTE_IO_3_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE | CHANNEL_TYPE_WAVEFORM;

         break;
      }

      case CHANNEL_4: {

         //      4,PTB18,CAN0_TX,FTM2_CH0,I2S0_TX_BCLK,FTM2_QD_PHA7,PTB21,SPI2_SCK,CMP1_OUT

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = calloc(1, sizeof(MCU_GPIO_PWM_Interface));

         profile->digital_interface->port = MCU_GPIO_PORT_PTB;
         profile->digital_interface->mask = GPIO_PTB_IO_4_MASK;

         profile->pwm_interface->pwm_channel = MCU_PWM_OUT_1;

         profile->supported_interfaces = CHANNEL_TYPE_WAVEFORM | CHANNEL_TYPE_PULSE;

         break;
      }

      case CHANNEL_5: {
         //      5,PTB19,CAN0_RX,FTM2_CH1,I2S0_TX_FS,FTM2_QD_PHA

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = calloc(1, sizeof(MCU_GPIO_PWM_Interface));

         profile->digital_interface->port = MCU_GPIO_PORT_PTB;
         profile->digital_interface->mask = GPIO_PTB_IO_5_MASK;

         profile->pwm_interface->pwm_channel = MCU_PWM_OUT_2;

         profile->supported_interfaces = CHANNEL_TYPE_WAVEFORM | CHANNEL_TYPE_PULSE;

         break;
      }

      case CHANNEL_6: {

         //      6,PTB0,LLWU_P5,ADC0_SE8,ADC1_SE8,I2C0_SCL,FTM1_CH0,FTM1_QD_PHA

         profile->adc_interface = calloc(1, sizeof(MCU_GPIO_ADC_Interface));
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = calloc(1, sizeof(MCU_GPIO_PWM_Interface));

         profile->adc_interface->adc_channel = MCU_ADC1;
         profile->adc_interface->sample_group = 0;

         profile->digital_interface->port = MCU_GPIO_PORT_PTB;
         profile->digital_interface->mask = GPIO_PTB_IO_6_MASK;

         profile->pwm_interface->pwm_channel = MCU_PWM_OUT_3;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE | CHANNEL_TYPE_WAVEFORM | CHANNEL_TYPE_PULSE;

         break;
      }

      case CHANNEL_7: {
         //      7,PTB21,SPI2_SCK,CMP1_OUT

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->digital_interface->port = MCU_GPIO_PORT_PTB;
         profile->digital_interface->mask = GPIO_PTB_IO_7_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE;

         break;
      }

      case CHANNEL_8: {
         //      8,PTB22,SPI2_SOUT,CMP2_OUT

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->digital_interface->port = MCU_GPIO_PORT_PTB;
         profile->digital_interface->mask = GPIO_PTB_IO_8_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE;

         break;
      }

      case CHANNEL_9: {
         //      9,PTB23,SPI2_SIN,SPI0_PCS5

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->digital_interface->port = MCU_GPIO_PORT_PTB;
         profile->digital_interface->mask = GPIO_PTB_IO_9_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE;

         break;
      }

      case CHANNEL_10: {
         //      10,PTC16,UART3_RX

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->digital_interface->port = MCU_GPIO_PORT_PTC;
         profile->digital_interface->mask = GPIO_PTC_IO_10_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE;

         break;
      }

      case CHANNEL_11: {
         //      11,PTC17,UART3_TX

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->digital_interface->port = MCU_GPIO_PORT_PTC;
         profile->digital_interface->mask = GPIO_PTC_IO_11_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE;

         break;
      }

      case CHANNEL_12: {
         //      12,PTD6,LLWU_P16,ADC0_SE7b,SPI0_PCS3,UART0_RX,FTM0_CH6,FTM0_FLT0,SPI1_SOUT

         profile->adc_interface = calloc(1, sizeof(MCU_GPIO_ADC_Interface));
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = calloc(1, sizeof(MCU_GPIO_PWM_Interface));

         profile->adc_interface->adc_channel = MCU_ADC0;
         profile->adc_interface->sample_group = 0;

         profile->digital_interface->port = MCU_GPIO_PORT_PTD;
         profile->digital_interface->mask = GPIO_PTD_IO_12_MASK;

         profile->pwm_interface->pwm_channel = MCU_PWM_OUT_4;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE | CHANNEL_TYPE_WAVEFORM | CHANNEL_TYPE_PULSE;

         break;
      }

      default: {
         break;
      }

   }

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
