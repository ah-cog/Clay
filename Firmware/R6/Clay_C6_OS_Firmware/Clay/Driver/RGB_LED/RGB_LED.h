#ifndef RGB_LED_H
#define RGB_LED_H

#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "GPIO.h"

int8_t Start_Light_Behavior();
bool Perform_Channel_Light_Effect(bool reverse);

// TODO: #define several LED colors (RGB_Color){0xFF,0xFF,0xFF}

//these values are the values in the SL field of each channel control register
typedef enum
{
   LED_CURRENT_MAX,        //full max current
   LED_CURRENT_HALF,       //max current / 2
   LED_CURRENT_THIRD,      //max current / 3
   LED_CURRENT_QUARTER     //max current / 4
} LED_Mode;

typedef struct
{
      uint8_t R;
      uint8_t G;
      uint8_t B;
} RGB_Color;

typedef struct
{
      uint8_t number;
      uint8_t enabled;     // Specifies whether or not the channel being used.
      RGB_Color color;
} Channel_Light;

RGB_Color offColor;
RGB_Color onColor;

typedef enum
{
   RGB1,
   RGB2,
   RGB3,
   RGB4,
   RGB5,
   RGB6,
   RGB7,
   RGB8,
   RGB9,
   RGB10,
   RGB11,
   RGB12,
   RGB_MAX
} RGB_LED;

extern Channel_Light proposed_light_profiles[CHANNEL_COUNT];
extern Channel_Light channelLightProfiles[CHANNEL_COUNT];

extern bool RGB_LED_Enable();
extern bool RGB_LED_Start();
extern bool RGB_LED_Stop();
extern bool RGB_LED_Pause();

extern void RGB_LED_SetState(RGB_LED LED, bool On, LED_Mode CurrentMax);
extern void RGB_LED_SetColor(RGB_LED led, RGB_Color *output_color);
extern void RGB_LED_UpdateOutput();

extern void Set_Light_Color(Channel_Light *channel_light, uint8_t red, uint8_t green, uint8_t blue);

int8_t Initialize_Channel_Lights();
void Reset_Channel_Lights();
int8_t Apply_Channel_Lights();

int8_t Initialize_Color_Palette();

#endif /* SOURCES_RGB_LED_RGB_LED_H_ */
