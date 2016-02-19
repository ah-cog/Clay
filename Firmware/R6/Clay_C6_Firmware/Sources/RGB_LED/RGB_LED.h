/*
 * RGB_LED.h
 *
 *  Created on: Jan 26, 2016
 *      Author: thebh
 */

#ifndef SOURCES_RGB_LED_RGB_LED_H_
#define SOURCES_RGB_LED_RGB_LED_H_

#include "PE_Types.h"

//todo: #define several LED colors (RGB_Color){0xFF,0xFF,0xFF}

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

extern bool RGB_LED_Enable();
extern bool RGB_LED_Start();
extern bool RGB_LED_Stop();
extern bool RGB_LED_Pause();

extern void RGB_LED_SetState(RGB_LED LED, bool On, LED_Mode CurrentMax);
extern void RGB_LED_SetColor(RGB_LED led, RGB_Color *output_color);
extern void RGB_LED_UpdateOutput();

#endif /* SOURCES_RGB_LED_RGB_LED_H_ */
