/*
 * led_driver_pca9552.h
 *
 *  Created on: Sep 10, 2015
 *      Author: thebh_000
 */

#ifndef LED_DRIVER_PCA9552_H_
#define LED_DRIVER_PCA9552_H_

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

#define LED_DRIVER_COUNT 2

#define PCA9552_PRIMARY_I2C_ADDRESS 0x60
#define PCA9552_SECONDARY_I2C_ADDRESS 0x61

// LED drivers
typedef enum {
    LED_0,
    LED_1,
    LED_2,        //no red
    LED_3,
    LED_4,
    LED_5         //no red
} LED_Driver_Channel;

typedef enum {
    LED_DRIVER_0,
    LED_DRIVER_1,
    LED_DRIVER_BOTH,
} LED_Driver;

typedef enum {
    LED_MODE_MAX,       //full on
    LED_MODE_OFF,       //high-z
    LED_MODE_MED,       //pwm0
    LED_MODE_LOW        //pwm1
} LED_Mode;

// These are the LEDS as they are laid out on the board.
typedef enum {
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
} RGB_LED;

// RGB Channel. Tells which driver the LED is driven by and the index of the green pin.
typedef struct {
    LED_Driver driver_index; // The PCA9552 device (no. 1 or no. 2).
    LED_Driver_Channel led_index; // The index of an LED of the LED of interest associated with the specified PCA9552 device.
} RGB_Channel;

// RGB color type. LED drivers support 16 bit color.
typedef struct {
    LED_Mode R;
    LED_Mode G;
    LED_Mode B;
} Color_RGB;

extern Color_RGB onColor;
extern Color_RGB offColor;
extern Color_RGB colorA;
extern Color_RGB colorB;

extern uint8 driver_addresses[];

extern void Enable_PCA9552 ();
extern void Reset_PCA9552 (LED_Driver Driver);
extern void Set_LED_Output (RGB_LED led, Color_RGB * output_color);
extern void Set_LED_Output_Mode (RGB_Channel * led, Color_RGB * output_color);

extern int8_t Start_Light_Behavior ();

#endif /* LED_DRIVER_PCA9552_H_ */
