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
#define LED_DRIVER_COUNT            2

// structs ///////////////////

//LED drivers
typedef enum
{
    LED_0,
    LED_1,
    LED_2,        //no red
    LED_3,
    LED_4,
    LED_5         //no red
} led_driver_channel;

typedef enum
{
    LED_DRIVER_0,
    LED_DRIVER_1,
    LED_DRIVER_BOTH,
} led_driver;

typedef enum
{
    LED_MODE_MAX,       //full on
    LED_MODE_OFF,       //high-z
    LED_MODE_MED,       //pwm0
    LED_MODE_LOW        //pwm1
} led_mode;

//These are the LEDS as they are laid out on the board.
typedef enum
{
    RGB_1,        //DS12
    RGB_2,        //DS11
    RGB_3,        //DS10
    RGB_4,         //DS15
    RGB_5,         //DS14
    RGB_6,         //DS13
    RGB_7,         //DS9
    RGB_8,         //DS8
    RGB_9,         //DS7
    RGB_10,        //DS6
    RGB_11,        //DS5
    RGB_12,        //DS4
    RGB_INVALID
} rgb_led;

//RGB Channel. Tells which driver the LED is driven by and the index of the green pin.
typedef struct
{
    led_driver driver_index;
    led_driver_channel led_index;
} rgb_channel;

//RGB color type. LED drivers support 16 bit color.
typedef struct
{
    led_mode R;
    led_mode G;
    led_mode B;
} color_rgb;

// global vars ///////////////
extern uint8 driver_addresses[];

// function prototypes ///////
extern void init_led_drivers();

extern void reset_driver(led_driver Driver);

extern void set_led_output(rgb_led led, color_rgb * output_color);

#endif /* LED_DRIVER_PCA9552_H_ */
