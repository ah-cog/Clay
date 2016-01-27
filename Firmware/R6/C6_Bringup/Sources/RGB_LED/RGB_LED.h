/*
 * RGB_LED.h
 *
 *  Created on: Jan 26, 2016
 *      Author: thebh
 */

#ifndef SOURCES_RGB_LED_RGB_LED_H_
#define SOURCES_RGB_LED_RGB_LED_H_

#include "PE_Types.h"

typedef struct
{
	uint32_t R;
	uint32_t G;
	uint32_t B;
} RGB_Color;

typedef enum
{
	RGB1, RGB2, RGB3, RGB4, RGB5, RGB6, RGB7, RGB8, RGB9, RGB10, RGB11, RGB12, RGB_MAX
} RGB_LED_Index;

extern void RGB_LED_Enable();
extern void RGB_LED_Start();
extern void RGB_LED_Stop();
extern void RGB_LED_Pause();

extern void RGB_LED_SetColor(RGB_LED_Index LED, RGB_Color Color);

#endif /* SOURCES_RGB_LED_RGB_LED_H_ */
