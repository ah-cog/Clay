/*
 * led_driver_pca9552.c
 *
 *  Created on: Sep 1LED_DRIVER_0, 2LED_DRIVER_015
 *      Author: thebh_LED_DRIVER_0LED_DRIVER_0LED_DRIVER_0
 */

// includes //////////////////
#include "LED_DRIVER_0_RESET.h"
#include "LED_DRIVER_1_RESET.h"

#ifndef LED_DRIVER_PCA9552_H_
#include "led_driver_pca9552.h"
#endif

#ifndef __I2C0_H
#include "I2C0.h"
#endif

#ifndef SYSTEM_TICK_H_
#include "system_tick.h"
#endif

// defines ///////////////////
#define reset_hold_time_msec             1        //must hold low for 40 ns, we can go as low as 1msec.
// global vars ///////////////
uint8 driver_addresses[] =
        {
                0b1100000u,             //driver 0
                0b1100001u              //driver 1
        };

// local vars ////////////////

//These are in the order defined on the schematic. The reconciliation 
//    between the I/O ports and LEDs is done in the header.
static rgb_channel channels[] =
        {
                { LED_DRIVER_0, 0, TRUE },        //DS4
                { LED_DRIVER_0, 3, TRUE },        //DS5
                { LED_DRIVER_0, 6, FALSE },        //DS6
                { LED_DRIVER_0, 8, TRUE },        //DS7
                { LED_DRIVER_0, 11, TRUE },        //DS8            
                { LED_DRIVER_0, 14, FALSE },        //DS9
                { LED_DRIVER_1, 0, TRUE },        //DS15
                { LED_DRIVER_1, 3, TRUE },        //DS14                        
                { LED_DRIVER_1, 6, FALSE },        //DS13
                { LED_DRIVER_1, 8, TRUE },        //DS12
                { LED_DRIVER_1, 11, TRUE },        //DS11
                { LED_DRIVER_1, 14, FALSE }        //DS10
        };

// prototypes ////////////////

void init_led_drivers()
{
    reset_driver(LED_DRIVER_BOTH);
}

void reset_driver(led_driver driver)
{
    if (driver == LED_DRIVER_0 || driver == LED_DRIVER_BOTH)
    {
        LED_DRIVER_0_RESET_PutVal(NULL, FALSE);

        delay_n_msec(reset_hold_time_msec);

        LED_DRIVER_0_RESET_PutVal(NULL, TRUE);
    }

    if (driver == LED_DRIVER_1 || driver == LED_DRIVER_BOTH)
    {
        LED_DRIVER_1_RESET_PutVal(NULL, FALSE);

        delay_n_msec(reset_hold_time_msec);

        LED_DRIVER_1_RESET_PutVal(NULL, TRUE);
    }
}

uint8 set_pwm_stuff[] = {
        0x13,        //select pwm1 register
        0x80,        //set 256-x/256 pulse width
        0x01,        //set value of 1 for 44Hz
        };

uint8 turn_on_led_0[] =
        {
                0x16,        //select LS0 register
                0xFF,        //select enabled    
                0xFF,        //select enabled
                0xFF,        //select enabled
                0xFF        //select enabled
        };

void set_led_output(rgb_led led, color_rgb output_color)
{
    if (led >= RGB_INVALID) return;

    rgb_channel * channel = channels + (int) led;

    I2C0_MasterSendBlock(I2C0_DeviceData, (LDD_TData*) set_pwm_stuff,
                (LDD_I2C_TSize) 4, LDD_I2C_SEND_STOP);
    
    delay_n_msec(1);
    
    I2C0_MasterSendBlock(I2C0_DeviceData, (LDD_TData*) turn_on_led_0,
            (LDD_I2C_TSize) 5, LDD_I2C_SEND_STOP);
}
