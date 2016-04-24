#ifndef GPIO_H
#define GPIO_H

#include "PE_Types.h"
#include "PE_LDD.h"

////Includes //////////////////////////////////////////////////////
#include "PE_Types.h"

////Macros ////////////////////////////////////////////////////////
//#define CHANNEL_COUNT 12

#define CHANNEL_ENABLED  1
#define CHANNEL_DISABLED 0

//#define CHANNEL_DIRECTION_OUTPUT 0
//#define CHANNEL_DIRECTION_INPUT  1

//#define CHANNEL_MODE_TOGGLE   1
//#define CHANNEL_MODE_WAVEFORM 2
//#define CHANNEL_MODE_PULSE    3

#define CHANNEL_VALUE_TOGGLE_ON  1
#define CHANNEL_VALUE_TOGGLE_OFF 0

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
   CHANNEL_1 = 0,
   CHANNEL_2 = 1,
   CHANNEL_3 = 2,
   CHANNEL_4 = 3,
   CHANNEL_5 = 4,
   CHANNEL_6 = 5,
   CHANNEL_7 = 6,
   CHANNEL_8 = 7,
   CHANNEL_9 = 8,
   CHANNEL_10 = 9,
   CHANNEL_11 = 10,
   CHANNEL_12 = 11,
   CHANNEL_COUNT
} Channel_Number;

typedef enum
{
   CHANNEL_DIRECTION_OUTPUT = 0,     // i.e., source: Clay, destination: world
   CHANNEL_DIRECTION_INPUT = 1,     // i.e., source: world, destination: Clay
   CHANNEL_DIRECTION_COUNT
} Channel_Direction;

typedef enum
{
   CHANNEL_TYPE_TOGGLE = 1,
   CHANNEL_TYPE_WAVEFORM = 2,
   CHANNEL_TYPE_PULSE = 4,
   CHANNEL_TYPE_COUNT
} Channel_Type;

typedef enum
{
   MCU_GPIO_PORT_PTB,
   MCU_GPIO_PORT_PTC,
   MCU_GPIO_PORT_PTD,
   MCU_GPIO_PORT_PTE,
   MCU_GPIO_PORT_COUNT
} MCU_GPIO_Port;

typedef enum
{
   MCU_ADC0,
   MCU_ADC1,
   MCU_ADC_COUNT
} MCU_ADC_Channel;

typedef enum
{
   MCU_PWM_OUT_1,
   MCU_PWM_OUT_2,
   MCU_PWM_OUT_3,
   MCU_PWM_OUT_4,
   MCU_PULSE_COUNT
} MCU_PWM_Channel;

typedef struct
{
      MCU_GPIO_Port port;
      uint32_t mask;
} MCU_GPIO_Digital_Interface;

typedef struct
{
      MCU_ADC_Channel adc_channel;
      uint32_t sample_group;
} MCU_GPIO_ADC_Interface;

typedef struct
{
      MCU_PWM_Channel pwm_channel;
} MCU_GPIO_PWM_Interface;

typedef struct
{
      uint32_t supported_interfaces;
      MCU_GPIO_Digital_Interface * digital_interface;
      MCU_GPIO_ADC_Interface * adc_interface;
      MCU_GPIO_PWM_Interface * pwm_interface;
} MCU_GPIO_Profile;

typedef struct
{
      uint8_t enabled;     // Specifies whether or not the channel being used.

      Channel_Number number;
      Channel_Direction direction;     // input or output
      Channel_Type type;     // (output) digital, pwm, (input) digital, analog, pwm

      //HACK
      uint32_t toggle_value;
      uint32_t waveform_value;
      LDD_PPG_Tfloat pulse_period_s;
      uint16_t pulse_duty;
      //HACK

      MCU_GPIO_Profile mcu_hardware_profile;

      // TODO: Expected value. Set this to monitor the channel and look for a value. This will be used to set the LED state (maybe green or red, depending on correct or incorrect)
      // TODO: UUID for port. Used to record data and use it to submit data and request data.
      // TODO: UUID for transform.
} Channel;

////Globals   /////////////////////////////////////////////////////
extern Channel updated_channel_profile[CHANNEL_COUNT];
extern Channel channel_profile[CHANNEL_COUNT];

////Prototypes/////////////////////////////////////////////////////
extern bool Channel_Enable_All();
extern void Channel_Disable_All();

extern bool Channel_Enable(Channel_Number number);
extern void Channel_Disable(Channel_Number number);

extern bool Channel_Set_Type(Channel_Number number, Channel_Type type);
extern uint8_t Channel_Get_Type(Channel_Number number);

extern int32_t Channel_Set_Direction(Channel_Number number, Channel_Direction direction);
extern Channel_Direction Channel_Get_Direction(Channel_Number number);

extern int32_t Channel_Set_Data(Channel_Number number, int32_t data);
extern int32_t Channel_Get_Data(Channel_Number number);

extern void Channel_Periodic_Call();

int8_t Initialize_Channels();
int8_t Reset_Channels();
//int8_t Update_Channels ();

//int8_t Enable_Channels();
//int8_t Enable_Channel(uint8_t number, uint8_t enabled);
int8_t Apply_Channels();

#endif /* GPIO_H */
