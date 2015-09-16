/*
 * led_driver_pca9552.c
 *
 *  Created on: Sep 1LED_DRIVER_0, 2LED_DRIVER_015
 *      Author: thebh_LED_DRIVER_0LED_DRIVER_0LED_DRIVER_0
 */

// includes //////////////////
#include "LED_DRIVER_0_RESET.h"
#include "LED_DRIVER_1_RESET.h"

#include "PCA9552.h"

#include "I2C0.h"

#include "Timer_1ms.h"

// defines ///////////////////
#define reset_hold_time_msec             1        //must hold low for 40 ns, we can go as low as 1msec.
// structs ///////////////////
typedef struct
{
    //register select. high nibble should be == 1 to enable autoincrementing.
    uint8 ls0_reg_address;

    //LS0
    uint8 led0_g :2;
    uint8 led0_r :2;
    uint8 led0_b :2;
    uint8 led1_g :2;

    //LS1
    uint8 led1_r :2;
    uint8 led1_b :2;
    uint8 led2_g :2;
    uint8 led2_b :2;

    //LS2
    uint8 led3_g :2;
    uint8 led3_r :2;
    uint8 led3_b :2;
    uint8 led4_g :2;

    //LS3
    uint8 led4_r :2;
    uint8 led4_b :2;
    uint8 led5_g :2;
    uint8 led5_b :2;

} led_bitfield;

typedef union
{
    led_bitfield leds;
    uint8 i2c_message[5];
} driver_led_state;

typedef struct
{
    uint8 address;
    driver_led_state led_state;
} led_driver_info;

// global vars ///////////////
led_driver_info driver_info[] =
        {
                //set addresses, address of LS0 with autoincrement, and init all LED states to off.
                { 0x60, { 0x16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } },
                { 0x61, { 0x16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } }
        };

// local vars ////////////////
static uint8 pwm_settings[] =
        {
                0x12,        //select pwm0 register, auto-increment
                0xC0,        //set 256-x/256 pulse width   PWM0 @ 50% duty cycle
                0x01,        //set value of 1 for 44Hz
                0xF0,        //set 256-x/256 pulse width   PWM1 @ 75% duty cycle (25% low)
                0x01         //set value of 1 for 44Hz
        };

//These are in the order defined on the schematic. The reconciliation 
//    between the I/O ports and LEDs is done in the header.
static rgb_channel channels[] =
        {
                { LED_DRIVER_1, LED_3 },        //DS12
                { LED_DRIVER_1, LED_4 },        //DS11
                { LED_DRIVER_1, LED_5 },        //DS10
                { LED_DRIVER_1, LED_0 },        //DS15
                { LED_DRIVER_1, LED_1 },        //DS14
                { LED_DRIVER_1, LED_2 },        //DS13
                { LED_DRIVER_0, LED_5 },        //DS9
                { LED_DRIVER_0, LED_4 },        //DS8
                { LED_DRIVER_0, LED_3 },        //DS7
                { LED_DRIVER_0, LED_2 },        //DS6
                { LED_DRIVER_0, LED_1 },        //DS5
                { LED_DRIVER_0, LED_0 },        //DS4
        };

// prototypes ////////////////
static void set_led_output_mode(rgb_channel * led, color_rgb * output_color);

// implementations ///////////

void init_led_drivers()
{
	int i;
	
    reset_driver(LED_DRIVER_BOTH);

    for (i = 0; i < LED_DRIVER_COUNT; ++i)
    {
        I2C0_SelectSlaveDevice(I2C0_DeviceData, LDD_I2C_ADDRTYPE_7BITS, driver_info[i].address);
        Wait (1);

        I2C0_MasterSendBlock(I2C0_DeviceData, (LDD_TData*) pwm_settings, (LDD_I2C_TSize) 5, LDD_I2C_SEND_STOP);
        Wait (1);
    }
}

void reset_driver(led_driver driver)
{
    if (driver == LED_DRIVER_0 || driver == LED_DRIVER_BOTH)
    {
        LED_DRIVER_0_RESET_PutVal(NULL, FALSE);

        Wait (reset_hold_time_msec);

        LED_DRIVER_0_RESET_PutVal(NULL, TRUE);
    }

    if (driver == LED_DRIVER_1 || driver == LED_DRIVER_BOTH)
    {
        LED_DRIVER_1_RESET_PutVal(NULL, FALSE);

        Wait (reset_hold_time_msec);

        LED_DRIVER_1_RESET_PutVal(NULL, TRUE);
    }
}

void set_led_output(rgb_led led, color_rgb *output_color)
{
    if (led >= RGB_INVALID) return;

    rgb_channel * channel = channels + (int) led;

    set_led_output_mode(channel, output_color);

    I2C0_SelectSlaveDevice(I2C0_DeviceData, LDD_I2C_ADDRTYPE_7BITS, driver_info[channel->driver_index].address);
    Wait (1);

    I2C0_MasterSendBlock(I2C0_DeviceData, (LDD_TData*) driver_info[channel->driver_index].led_state.i2c_message, (LDD_I2C_TSize) 5,
            LDD_I2C_SEND_STOP);
    Wait (1);
}

static void set_led_output_mode(rgb_channel* led, color_rgb * output_color)
{
    driver_led_state * driver_state = &(driver_info[led->driver_index].led_state);

    switch (led->led_index)
    {
    case LED_0:
        {
        driver_state->leds.led0_r = output_color->R & 0x3;
        driver_state->leds.led0_g = output_color->G & 0x3;
        driver_state->leds.led0_b = output_color->B & 0x3;
        break;
    }
    case LED_1:
        {
        driver_state->leds.led1_r = output_color->R & 0x3;
        driver_state->leds.led1_g = output_color->G & 0x3;
        driver_state->leds.led1_b = output_color->B & 0x3;
        break;
    }
    case LED_2:
        {
        driver_state->leds.led2_g = output_color->G & 0x3;
        driver_state->leds.led2_b = output_color->B & 0x3;
        break;
    }
    case LED_3:
        {
        driver_state->leds.led3_r = output_color->R & 0x3;
        driver_state->leds.led3_g = output_color->G & 0x3;
        driver_state->leds.led3_b = output_color->B & 0x3;
        break;
    }
    case LED_4:
        {
        driver_state->leds.led4_r = output_color->R & 0x3;
        driver_state->leds.led4_g = output_color->G & 0x3;
        driver_state->leds.led4_b = output_color->B & 0x3;
        break;
    }
    case LED_5:
        {
        driver_state->leds.led5_g = output_color->G & 0x3;
        driver_state->leds.led5_b = output_color->B & 0x3;
        break;
    }
    default:
        {
        break;
    }
    }
}
