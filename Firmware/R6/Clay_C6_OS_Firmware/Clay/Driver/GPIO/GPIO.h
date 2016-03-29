#ifndef GPIO_H
#define GPIO_H

////Includes //////////////////////////////////////////////////////
#include "stdint.h"
#include "stdbool.h"

////Macros ////////////////////////////////////////////////////////
#define CHANNEL_COUNT 12

#define CHANNEL_ENABLED  1
#define CHANNEL_DISABLED 0

#define CHANNEL_DIRECTION_OUTPUT 0
#define CHANNEL_DIRECTION_INPUT  1

#define CHANNEL_MODE_TOGGLE   1
#define CHANNEL_MODE_WAVEFORM 2
#define CHANNEL_MODE_PULSE    3

#define CHANNEL_VALUE_TOGGLE_ON  1
#define CHANNEL_VALUE_TOGGLE_OFF 0

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
   PORT_TYPE_DIGITAL,
   PORT_TYPE_ANALOG,
   PORT_TYPE_PWM,
   PORT_TYPE_MAX
} PORT_TYPE;

typedef enum
{
   PORT_DIR_IN,
   PORT_DIR_OUT,
   PORT_DIR_MAX
} PORT_DIRECTION;

typedef enum
{
   PORT_1,
   PORT_2,
   PORT_3,
   PORT_4,
   PORT_5,
   PORT_6,
   PORT_7,
   PORT_8,
   PORT_9,
   PORT_10,
   PORT_11,
   PORT_12,
   PORT_MAX
} PORT_NUMBER;

typedef struct
{
      uint8_t number;
      uint8_t enabled;     // Specifies whether or not the channel being used.
      uint8_t direction;     // input or output
      uint8_t mode;     // (output) digital, pwm, (input) digital, analog, pwm
      uint16_t value;     // The raw value of the channel.
      // TODO: logical value
      // TODO: continuous value

      // TODO: Expected value. Set this to monitor the channel and look for a value. This will be used to set the LED state (maybe green or red, depending on correct or incorrect)

      // TODO: UUID for port. Used to record data and use it to submit data and request data.

      // TODO: UUID for transform.
} Channel;

////Globals   /////////////////////////////////////////////////////
extern Channel updated_channel_profile[CHANNEL_COUNT];
extern Channel channel_profile[CHANNEL_COUNT];

////Prototypes/////////////////////////////////////////////////////
extern bool Port_Enable_All();
extern void Port_Disable_All();

extern bool Port_Enable(PORT_NUMBER number);
extern void Port_Disable(PORT_NUMBER number);

extern bool Port_Set_Type(PORT_NUMBER number, PORT_TYPE type);
extern PORT_TYPE Port_Get_Type(PORT_NUMBER number);

extern bool Port_Set_Direction(PORT_NUMBER number, PORT_DIRECTION direction);
extern PORT_DIRECTION Port_Get_Direction(PORT_NUMBER number);

extern void Port_Set_Data(PORT_NUMBER number, int32_t data);
extern uint32_t Port_Get_Data(PORT_NUMBER number);

//old functions
int8_t Initialize_Channels();
int8_t Reset_Channels();
//int8_t Update_Channels ();

int8_t Enable_Channels();
int8_t Enable_Channel(uint8_t number, uint8_t enabled);
int8_t Apply_Channels();

//uint8_t Enable_Channel (uint8_t number);
void Set_Channel(uint8_t number, uint8_t direction, uint8_t mode);
void Set_Channel_Value(uint8_t number, uint8_t state);     // i.e., set discrete state of the channel (on or off)
//void Set_Channel_Signal (); // i.e., analog signal to generate on the channel
int8_t Get_Channel_Value(uint8_t number);     // i.e., get discrete input state
//void Get_Channel_Signal (); // i.e., read the analog signal on the channel
// void Disable_Channels ();

#endif /* GPIO_H */
