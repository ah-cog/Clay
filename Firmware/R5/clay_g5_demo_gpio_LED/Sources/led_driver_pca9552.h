/*
 * led_driver_pca9552.h
 *
 *  Created on: Sep 10, 2015
 *      Author: thebh_000
 */

#ifndef LED_DRIVER_PCA9552_H_
#define LED_DRIVER_PCA9552_H_

// includes //////////////////

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

// defines ///////////////////

// structs ///////////////////

//LED drivers
typedef enum
{
    LED_DRIVER_0, LED_DRIVER_1, LED_DRIVER_BOTH
} led_driver;

//These are the LEDS as they are laid out on the board.
typedef enum
{
    RGB_1 = 10,//DS12
    RGB_2 = 11,//DS11
    RGB_3 = 12,//DS10
    RGB_4 = 7,//DS15
    RGB_5 = 8,//DS14
    RGB_6 = 9,//DS13
    RGB_7 = 6,//DS9
    RGB_8 = 5,//DS8
    RGB_9 = 4,//DS7
    RGB_10 = 3,//DS6
    RGB_11 = 2,//DS5
    RGB_12 = 1,//DS4
    RGB_INVALID = 13
} rgb_led;

//RGB Channel. Tells which driver the LED is driven by and the index of the green pin.
typedef struct
{
    led_driver driver_index;
    uint32 pin_base;
    bool has_red;
} rgb_channel;

//RGB color type. LED drivers support 16 bit color.
typedef struct
{
    uint16 R;
    uint16 G;    
    uint16 B;
} color_rgb;

// global vars ///////////////
extern uint8 driver_addresses[];

// function prototypes ///////
extern void init_led_drivers();

extern void reset_driver(led_driver Driver);

extern void set_led_output(rgb_led led, color_rgb output_color);

#endif /* LED_DRIVER_PCA9552_H_ */
