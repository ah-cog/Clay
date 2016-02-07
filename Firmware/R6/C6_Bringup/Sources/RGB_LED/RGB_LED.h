/*
 * RGB_LED.h
 *
 *  Created on: Jan 26, 2016
 *      Author: thebh
 */

#ifndef SOURCES_RGB_LED_RGB_LED_H_
#define SOURCES_RGB_LED_RGB_LED_H_

#include "PE_Types.h"

//TODO: update for new RGB driver
typedef enum {
	LED_MODE_MAX,       //full on
	LED_MODE_OFF,       //high-z
	LED_MODE_MED,       //pwm0
	LED_MODE_LOW        //pwm1
} LED_Mode;

//// RGB color type. LED drivers support 16 bit color.
//typedef struct {
//	LED_Mode R;
//	LED_Mode G;
//	LED_Mode B;
//} Color_RGB;

typedef struct {
	uint32_t R;
	uint32_t G;
	uint32_t B;
} RGB_Color;

typedef enum {
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

extern void RGB_LED_Enable();
extern void RGB_LED_Start();
extern void RGB_LED_Stop();
extern void RGB_LED_Pause();

extern void RGB_LED_SetColor(RGB_LED led, RGB_Color *output_color);

#endif /* SOURCES_RGB_LED_RGB_LED_H_ */
