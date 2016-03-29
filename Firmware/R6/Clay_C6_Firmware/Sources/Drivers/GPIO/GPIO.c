////Includes //////////////////////////////////////////////////////
#include "GPIO.h"

#include "GPIO_PTB.h"
#include "GPIO_PTC.h"
#include "GPIO_PTD.h"
#include "GPIO_PTE.h"

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

////Local Prototypes///////////////////////////////////////////////
static bool Enable_Digital(PORT_NUMBER number);
static bool Enable_Analog(PORT_NUMBER number);
static bool Enable_PWM(PORT_NUMBER number);

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

bool Port_Set_Type(PORT_NUMBER number, PORT_TYPE type) {

   bool rval = FALSE;
   return rval;
}

PORT_TYPE Port_Get_Type(PORT_NUMBER number) {

   PORT_TYPE rval = PORT_TYPE_MAX;
   return rval;
}

bool Port_Set_Direction(PORT_NUMBER number, PORT_DIRECTION direction) {

   bool rval = FALSE;
   return rval;
}

PORT_DIRECTION Port_Get_Direction(PORT_NUMBER number) {

   PORT_DIRECTION rval = PORT_DIR_MAX;
   return rval;
}

void Port_Set_Data(PORT_NUMBER number, int32_t data) {

}

uint32_t Port_Get_Data(PORT_NUMBER number) {

   uint32_t rval = 0;
   return rval;
}

////Local implementations /////////////////////////////////////////
static bool Enable_Digital(PORT_NUMBER number) {
   bool rval = FALSE;

   return rval;
}

static bool Enable_Analog(PORT_NUMBER number) {
   bool rval = FALSE;
   return rval;
}

static bool Enable_PWM(PORT_NUMBER number) {
   bool rval = FALSE;

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

