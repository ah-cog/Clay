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
#define GPIO_ADC_SLOPE          4.98344E-5F
#define GPIO_ADC_OFFSET         0.0F

//these are here to preserve the indexing when ptb4 and 6 are assigned to PWM and ADC
#ifndef GPIO_PTB_IO_4_MASK
#define GPIO_PTB_IO_4_MASK 0
#endif

#ifndef GPIO_PTB_IO_6_MASK
#define GPIO_PTB_IO_6_MASK 0
#endif

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
   IO_PTB,
   IO_PTC,
   IO_PTD,
   IO_PTE,
   IO_MAX
} IO_PORT;

typedef struct
{
   IO_PORT port;
   uint32_t mask;
   LDD_GPIO_TBitField field;
} Channel_Map;

////Globals   /////////////////////////////////////////////////////
Channel updated_channel_profile[CHANNEL_COUNT];
Channel channel_profile[CHANNEL_COUNT];

////Local vars/////////////////////////////////////////////////////
static Channel_Map channel_map[PORT_MAX] = { { IO_PTE, GPIO_PTE_IO_1_MASK },            //PTE1
                                             { IO_PTE, GPIO_PTE_IO_2_MASK },            //PTE2
                                             { IO_PTE, GPIO_PTE_IO_3_MASK },            //PTE3
                                             { IO_PTB, GPIO_PTB_IO_4_MASK },            //PTB18
                                             { IO_PTB, GPIO_PTB_IO_5_MASK },            //PTB19
                                             { IO_PTB, GPIO_PTB_IO_6_MASK },            //PTB0
                                             { IO_PTB, GPIO_PTB_IO_7_MASK },            //PTB21
                                             { IO_PTB, GPIO_PTB_IO_8_MASK },            //PTB22
                                             { IO_PTB, GPIO_PTB_IO_9_MASK },            //PTB23
                                             { IO_PTC, GPIO_PTC_IO_10_MASK },           //PTC16
                                             { IO_PTC, GPIO_PTC_IO_11_MASK },           //PTC17
                                             { IO_PTD, GPIO_PTD_IO_12_MASK } };         //PTD6

static LDD_TDeviceData * PTB_data;
static LDD_TDeviceData * PTC_data;
static LDD_TDeviceData * PTD_data;
static LDD_TDeviceData * PTE_data;

static LDD_TDeviceData * ADC1_data;
static LDD_TDeviceData * PWM_OUT_1_data;

////Local Prototypes///////////////////////////////////////////////
static bool Enable_Digital(PORT_NUMBER number);
static bool Enable_Analog(PORT_NUMBER number);
static bool Enable_PWM(PORT_NUMBER number);

static int32_t Read_Digital(PORT_NUMBER number);
static int32_t Read_Analog(PORT_NUMBER number);

static int32_t Write_Digital(PORT_NUMBER number, int32_t data);
static int32_t Write_PWM(PORT_NUMBER number, int32_t data);

////Global implementations ////////////////////////////////////////
bool Port_Enable_All() {

   bool rval = FALSE;

   for (int i = 0; i < PORT_MAX; ++i) {
      Port_Enable((PORT_NUMBER) i);
   }

   return rval;
}

void Port_Disable_All() {
}

bool Port_Enable(PORT_NUMBER number) {

   bool rval = FALSE;

   switch (channel_profile[number].mode) {

      case PORT_TYPE_DIGITAL: {

         rval = Enable_Digital(number);
         break;
      }

      case PORT_TYPE_ANALOG: {

         rval = Enable_Analog(number);
         break;
      }

      case PORT_TYPE_PWM: {

         rval = Enable_PWM(number);
         break;
      }

      case PORT_TYPE_MAX: {
         rval = FALSE;
         break;
      }

      default: {
         break;
      }
   }

   return rval;
}

void Port_Disable(PORT_NUMBER number) {
}

bool Port_Set_Type(PORT_NUMBER number, uint8_t type) {

   bool rval = FALSE;

   channel_profile[number].mode = type;

   //TODO: reinit as new type or disable -- we need to make sure the hardware is consistent with channel_profile

   return rval;
}

PORT_TYPE Port_Get_Type(PORT_NUMBER number) {

   return channel_profile[number].mode;

}

bool Port_Set_Direction(PORT_NUMBER number, PORT_DIRECTION direction) {

   bool rval = FALSE;
   return rval;
}

PORT_DIRECTION Port_Get_Direction(PORT_NUMBER number) {

   PORT_DIRECTION rval = PORT_DIR_MAX;
   return rval;
}

int32_t Port_Set_Data(PORT_NUMBER number, int32_t data) {

   int32_t rval = -1;

   switch (channel_profile[number].mode) {

      case PORT_TYPE_DIGITAL: {

         rval = Write_Digital(number, data);
         break;
      }

      case PORT_TYPE_ANALOG: {

         //only ADC is available in the hardware right now.
         break;
      }

      case PORT_TYPE_PWM: {

         rval = Write_PWM(number, data);
         break;
      }

      case PORT_TYPE_MAX:
      default: {
         break;
      }
   }

   return rval;
}

int32_t Port_Get_Data(PORT_NUMBER number) {

   int32_t rval = -1;

   //TODO: return the output data when in output mode?

   switch (channel_profile[number].mode) {

      case PORT_TYPE_DIGITAL: {

         rval = Read_Digital(number);
         break;
      }

      case PORT_TYPE_ANALOG: {

         rval = Read_Analog(number);
         break;
      }

      case PORT_TYPE_PWM: {

         //TODO: hook up frequency read somewhere. Probably should call it a different pin type frequency_in or counter or something like that.
         break;
      }

      case PORT_TYPE_MAX:
      default: {
         break;
      }
   }

   return rval;
}

////Local implementations /////////////////////////////////////////
static bool Enable_Digital(PORT_NUMBER number) {
   bool rval = FALSE;

   return rval;
}

static bool Enable_Analog(PORT_NUMBER number) {

   if (number != PORT_6) return FALSE;

   bool rval = FALSE;

   ADC1_data = ADC1_Init(NULL);

   ADC1_StartCalibration(ADC1_data);

   while (!ADC1_GetMeasurementCompleteStatus(ADC1_data))
      ;

   LDD_TError adcCalOk = ADC1_GetCalibrationResultStatus(ADC1_data);

   return rval;
}

static bool Enable_PWM(PORT_NUMBER number) {

   if (number != PORT_4) return FALSE;

   bool rval = FALSE;

   LDD_TError err;

   PWM_OUT_1_data = PWM_OUT_1_Init(NULL);

   err = PWM_OUT_1_SetFrequencyHz(PWM_OUT_1_data, 0);
   PWM_OUT_1_SetRatio16(PWM_OUT_1_data, Scale_Percent_Uint16(0));

   return rval;
}

int32_t Read_Digital(PORT_NUMBER number) {

   if (number == PORT_6 || number == PORT_4) return -1;

   int32_t rval = -1;

   switch (channel_map[number].port) {
      case IO_PTB: {

         rval = (GPIO_PTB_GetPortValue(PTB_data) & channel_map[number].mask) ? 1 : 0;

         break;
      }

      case IO_PTC: {

         rval = (GPIO_PTC_GetPortValue(PTC_data) & channel_map[number].mask) ? 1 : 0;

         break;
      }

      case IO_PTD: {

         rval = (GPIO_PTC_GetPortValue(PTC_data) & channel_map[number].mask) ? 1 : 0;

         break;
      }

      case IO_PTE: {

         rval = (GPIO_PTC_GetPortValue(PTC_data) & channel_map[number].mask) ? 1 : 0;

         break;
      }

      case IO_MAX:
      default: {
         break;
      }
   }

   return rval;
}

int32_t Read_Analog(PORT_NUMBER number) {

   if (number != PORT_6) return -1;
   //TODO: get adc1 or adc0 and sample group from channel_map. For now, we just have PORT_6 to worry about.

   int32_t rval = -1;

   //select sample group. This in preconfigured in processor expert. port 6 is in sample group 0
   ADC1_SelectSampleGroup(ADC1_data, 0);

   //tell the ADC to start a measurement.
   ADC1_StartSingleMeasurement(ADC1_data);

   //Block while it measures. You could alternatively do this elsewhere. We may want to periodically read and cache the adc value for each active channel to avoid this
   while (!ADC1_GetMeasurementCompleteStatus(ADC1_data))
      ;

   //get the value
   ADC1_GetMeasuredValues(ADC1_data, &rval);

   //apply voltage slope and offset. Because we're returning an int32, this return value is in millivolts.
   rval = (((double) rval * GPIO_ADC_SLOPE) + GPIO_ADC_OFFSET);

   return rval;
}

int32_t Write_Digital(PORT_NUMBER number, int32_t data) {

   if (number == PORT_6 || number == PORT_4) return -1;

   int32_t rval = 0;

   switch (channel_map[number].port) {
      case IO_PTB: {

         if (data) {
            GPIO_PTB_SetPortBits(PTB_data, channel_map[number].mask);
         } else {
            GPIO_PTB_ClearPortBits(PTB_data, channel_map[number].mask);
         }

         break;
      }

      case IO_PTC: {

         if (data) {
            GPIO_PTC_SetPortBits(PTC_data, channel_map[number].mask);
         } else {
            GPIO_PTC_ClearPortBits(PTC_data, channel_map[number].mask);
         }

         break;
      }

      case IO_PTD: {

         if (data) {
            GPIO_PTD_SetPortBits(PTD_data, channel_map[number].mask);
         } else {
            GPIO_PTD_ClearPortBits(PTD_data, channel_map[number].mask);
         }

         break;
      }

      case IO_PTE: {

         if (data) {
            GPIO_PTE_SetPortBits(PTE_data, channel_map[number].mask);
         } else {
            GPIO_PTE_ClearPortBits(PTE_data, channel_map[number].mask);
         }

         break;
      }

      case IO_MAX:
      default: {
         break;
      }
   }

   return rval;
}

int32_t Write_PWM(PORT_NUMBER number, int32_t data) {

   if (number != PORT_4) return -1;

   int32_t rval = 0;

   if (data > 0) {

      //set the frequency
      PWM_OUT_1_SetFrequencyHz(PWM_OUT_1_data, data);

      //this is how we set the ratio. The ratio is set by a 16-bit value. We scale a percentage up to the full scale of that 16 bit value. example: 50% = 32768
      PWM_OUT_1_SetRatio16(PWM_OUT_1_data, Scale_Percent_Uint16(75));
   } else {

      //if we set the ratio to 0, the output will never change states.
      PWM_OUT_1_SetRatio16(PWM_OUT_1_data, 0);
   }

   return rval;
}

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int8_t Initialize_Channels() {
   int i;

   for (i = 0; i < CHANNEL_COUNT; i++) {
      // Initialize update channel profile
      updated_channel_profile[i].number = (i + 1);
      updated_channel_profile[i].enabled = FALSE;
      updated_channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      updated_channel_profile[i].mode = CHANNEL_MODE_TOGGLE;
      updated_channel_profile[i].value = CHANNEL_VALUE_TOGGLE_OFF;

      // Initialize channel profile
      channel_profile[i].number = (i + 1);
      channel_profile[i].enabled = FALSE;
      channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      channel_profile[i].mode = CHANNEL_MODE_TOGGLE;
      channel_profile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
   }

   return TRUE;
}

int8_t Reset_Channels() {
   int i;

   for (i = 0; i < CHANNEL_COUNT; i++) {

      // Initialize update channel profile
      updated_channel_profile[i].number = (i + 1);
      updated_channel_profile[i].enabled = FALSE;
      updated_channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      updated_channel_profile[i].mode = CHANNEL_MODE_TOGGLE;
      updated_channel_profile[i].value = CHANNEL_VALUE_TOGGLE_OFF;

//		// Initialize channel profile
//		channelProfile[i].number = (i + 1);
//		channelProfile[i].enabled = FALSE;
//		channelProfile[i].direction = CHANNEL_DIRECTION_OUTPUT;
//		channelProfile[i].mode = CHANNEL_MODE_TOGGLE;
//		channelProfile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
   }

   return TRUE;
}

//int8_t Update_Channels () {
//	int i;
//	
//	// Copy the updated state into the internal state
//	// Save the current state in the cloud history
//	// Set the internal state as updated so it won't be updated again
//	
//	for (i = 0; i < CHANNEL_COUNT; i++) {
//
//		// Check if the enable state changed. Apply the corresponding transform.
//		if (updateChannelProfile[i].enabled != channelProfile[i].enabled) {
//			channelProfile[i] = updateChannelProfile[i];
//		}
//		
//		// Check if the direction change. Apply the corresponding transform.
//		if (updateChannelProfile[i].direction != channelProfile[i].direction) {
//			channelProfile[i].direction = updateChannelProfile[i];
//		}
//		
//		// Check if the mode change. Apply the corresponding transform.
//		if (updateChannelProfile[i].mode != channelProfile[i].mode) {
//			channelProfile[i].mode = updateChannelProfile[i].mode;
//		}
//		
//		// Check if the value change. Apply the corresponding transform.
//		if (updateChannelProfile[i].value != channelProfile[i].value) {
//			channelProfile[i].value = updateChannelProfile[i].value;
//		}
//		
//	}
//	
//	return TRUE;
//}

// TODO: Apply only changes! Compare current state to previous state or to actual hardware state. The former might be faster, but it's less "ground truth."
int8_t Apply_Channels() {
   int i;

   for (i = 0; i < CHANNEL_COUNT; i++) {

      // Check if the enable state changed. Apply the corresponding transform.
      if (updated_channel_profile[i].enabled != channel_profile[i].enabled) {

         // Update state.
         channel_profile[i].enabled = updated_channel_profile[i].enabled;

         if (channel_profile[i].enabled == TRUE) {

            // Apply state.
            Enable_Channel(channel_profile[i].number, channel_profile[i].enabled);

            // Check if the direction change. Apply the corresponding transform if it changed.
            if (updated_channel_profile[i].direction != channel_profile[i].direction) {

               // Update direction.
               channel_profile[i].direction = updated_channel_profile[i].direction;

               // Apply direction.
               Set_Channel(channel_profile[i].number, channel_profile[i].direction, channel_profile[i].mode);
            }

            // Check if the mode change. Apply the corresponding transform if it changed.
            if (updated_channel_profile[i].mode != channel_profile[i].mode) {

               // Update mode.
               channel_profile[i].mode = updated_channel_profile[i].mode;

               // Apply mode.
               Set_Channel(channel_profile[i].number, channel_profile[i].direction, channel_profile[i].mode);
            }

            // Check if the value change. Apply the corresponding transform if it changed.
            if (updated_channel_profile[i].value != channel_profile[i].value) {

               // Update value.
               channel_profile[i].value = updated_channel_profile[i].value;

               // Apply value.
               if (channel_profile[i].direction == CHANNEL_DIRECTION_INPUT) {
                  //					channelProfile[i].value = IO_1_GetVal (NULL);
                  //					channelProfile[i].value = (uint16_t) Get_Channel_Value (channelProfile[i].number);
               } else if (channel_profile[i].direction == CHANNEL_DIRECTION_OUTPUT) {
                  Set_Channel_Value(channel_profile[i].number, channel_profile[i].value);
               }
            }

         } else if (channel_profile[i].enabled == FALSE) {

            // Apply direction and mode.
            Set_Channel(channel_profile[i].number, CHANNEL_DIRECTION_OUTPUT, CHANNEL_MODE_TOGGLE);

            // Apply value.
            Set_Channel_Value(channel_profile[i].number, CHANNEL_VALUE_TOGGLE_OFF);

         }
      }
   }

   return TRUE;
}

// TODO: Remove this? Just use the above one that does per-channel enabling?
int8_t Enable_Channels() {
   PTB_data = GPIO_PTB_Init(NULL);
   PTC_data = GPIO_PTC_Init(NULL);
   PTD_data = GPIO_PTD_Init(NULL);
   PTE_data = GPIO_PTE_Init(NULL);

   return TRUE;
}

int8_t Enable_Channel(uint8_t number, uint8_t enabled) {

   channel_profile[(number - 1)].enabled = enabled;

   switch (channel_map[number].port) {
      case IO_PTB: {
         if (PTB_data == NULL) {
            PTB_data = GPIO_PTB_Init(NULL);
         }
         break;
      }

      case IO_PTC: {
         if (PTC_data == NULL) {
            PTC_data = GPIO_PTC_Init(NULL);
         }
         break;
      }

      case IO_PTD: {
         if (PTD_data == NULL) {
            PTD_data = GPIO_PTD_Init(NULL);
         }
         break;
      }

      case IO_PTE: {
         if (PTE_data == NULL) {
            PTE_data = GPIO_PTE_Init(NULL);
         }
         break;
      }

      case IO_MAX:
      default: {
         break;
      }
   }

   return TRUE;
}

void Set_Channel(uint8_t number, uint8_t direction, uint8_t mode) {

   switch (channel_map[number].port) {
      case IO_PTB: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTB_SetPortInputDirection(PTB_data, channel_map[number].mask);
         } else {
            GPIO_PTB_SetPortOutputDirection(PTB_data, channel_map[number].mask, 0);
         }

         break;
      }

      case IO_PTC: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTC_SetPortInputDirection(PTC_data, channel_map[number].mask);
         } else {
            GPIO_PTC_SetPortOutputDirection(PTC_data, channel_map[number].mask, 0);
         }

         break;
      }

      case IO_PTD: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTD_SetPortInputDirection(PTD_data, channel_map[number].mask);
         } else {
            GPIO_PTD_SetPortOutputDirection(PTD_data, channel_map[number].mask, 0);
         }

         break;
      }

      case IO_PTE: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTE_SetPortInputDirection(PTE_data, channel_map[number].mask);
         } else {
            GPIO_PTE_SetPortOutputDirection(PTE_data, channel_map[number].mask, 0);
         }

         break;
      }

      case IO_MAX:
      default: {
         break;
      }
   }
}

void Set_Channel_Value(uint8_t number, uint8_t value) {     // i.e., set discrete state of the channel (on or off)

   switch (channel_map[number].port) {
      case IO_PTB: {

         if (value) {
            GPIO_PTB_SetPortBits(PTB_data, channel_map[number].mask);
         } else {
            GPIO_PTB_ClearPortBits(PTB_data, channel_map[number].mask);
         }

         break;
      }

      case IO_PTC: {

         if (value) {
            GPIO_PTC_SetPortBits(PTC_data, channel_map[number].mask);
         } else {
            GPIO_PTC_ClearPortBits(PTC_data, channel_map[number].mask);
         }

         break;
      }

      case IO_PTD: {

         if (value) {
            GPIO_PTD_SetPortBits(PTD_data, channel_map[number].mask);
         } else {
            GPIO_PTD_ClearPortBits(PTD_data, channel_map[number].mask);
         }

         break;
      }

      case IO_PTE: {

         if (value) {
            GPIO_PTE_SetPortBits(PTE_data, channel_map[number].mask);
         } else {
            GPIO_PTE_ClearPortBits(PTE_data, channel_map[number].mask);
         }

         break;
      }

      case IO_MAX:
      default: {
         break;
      }
   }

   uint8_t stateValue = 0;

   // TODO: Set the specified channel to be an output if it is not configured as such (and save state if it was an input so it can resume that behavior later).
}

int8_t Get_Channel_Value(uint8_t number) {     // i.e., Get discrete input state

   uint8_t value = 0xFF;

   switch (channel_map[number].port) {
      case IO_PTB: {

         value = (GPIO_PTB_GetPortValue(PTB_data) & channel_map[number].mask) ? TRUE : FALSE;

         break;
      }

      case IO_PTC: {

         value = (GPIO_PTC_GetPortValue(PTC_data) & channel_map[number].mask) ? TRUE : FALSE;

         break;
      }

      case IO_PTD: {

         value = (GPIO_PTC_GetPortValue(PTC_data) & channel_map[number].mask) ? TRUE : FALSE;

         break;
      }

      case IO_PTE: {

         value = (GPIO_PTC_GetPortValue(PTC_data) & channel_map[number].mask) ? TRUE : FALSE;

         break;
      }

      case IO_MAX:
      default: {
         break;
      }
   }

   return value;
}




///test code for PWM and ADC.
//Port_Set_Type(PORT_4, PORT_TYPE_PWM);
//Port_Set_Type(PORT_6, PORT_TYPE_ANALOG);
//
//Port_Enable(PORT_4);
//Port_Enable(PORT_6);
//
//int adc;
//int pwm_freq_hz = 1000;
//
//for (;;) {
//
//   adc = Port_Get_Data(PORT_6);
//   Port_Set_Data(PORT_4, pwm_freq_hz);
//
//   pwm_freq_hz = (pwm_freq_hz + 1000) % 10000;
//
//   Wait(1000);
//}
