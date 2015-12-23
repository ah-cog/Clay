/*
 * led_driver_pca9552.c
 *
 *  Created on: Sep 1LED_DRIVER_0, 2LED_DRIVER_015
 *      Author: thebh_LED_DRIVER_0LED_DRIVER_0LED_DRIVER_0
 */

#include "LED_DRIVER_0_RESET.h"
#include "LED_DRIVER_1_RESET.h"

#include "PCA9552.h"

#include "I2C0.h"
#include "Timer_1ms.h"

#include "clock.h"

#define PCA9552_RESET_HOLD_TIME_MSEC 1 // must hold low for 40 ns, we can go as low as 1msec.

typedef struct {
	
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

} LED_Bit_Field;

typedef union {
    LED_Bit_Field leds;
    uint8 i2c_message[5];
} Driver_LED_State;

typedef struct { // TODO: Is this the I2C message packet?
    uint8 address;
    Driver_LED_State led_state;
} LED_Driver_Info;

// global vars ///////////////
LED_Driver_Info driver_info[] = {
	//set addresses, address of LS0 with autoincrement, and init all LED states to off.
	{ PCA9552_PRIMARY_I2C_ADDRESS,   { 0x16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } },
	{ PCA9552_SECONDARY_I2C_ADDRESS, { 0x16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } }
};

// local vars ////////////////
static uint8 pwm_settings[] = {
	0x12,        //select pwm0 register, auto-increment
	0xC0,        //set 256-x/256 pulse width   PWM0 @ 50% duty cycle
	0x01,        //set value of 1 for 44Hz
	0xF0,        //set 256-x/256 pulse width   PWM1 @ 75% duty cycle (25% low)
	0x01         //set value of 1 for 44Hz
};

/**
 * These are in the order defined on the schematic. The reconciliation between the I/O ports and LEDs is done in the header.
 */
static RGB_Channel channels[] = {
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

Color_RGB onColor  = { LED_MODE_MAX, LED_MODE_OFF, LED_MODE_LOW };
Color_RGB colorA  = { LED_MODE_MED, LED_MODE_MED, LED_MODE_LOW };
Color_RGB colorB  = { LED_MODE_OFF, LED_MODE_MED, LED_MODE_MAX };
Color_RGB offColor = { LED_MODE_OFF, LED_MODE_OFF, LED_MODE_OFF };

/**
 * Enables both PCA9552 LED drivers.
 */
void Enable_PCA9552 () {
	
	int i;
	
    Reset_PCA9552 (LED_DRIVER_BOTH);

    for (i = 0; i < LED_DRIVER_COUNT; ++i) {
    	
        I2C0_SelectSlaveDevice (I2C0_DeviceData, LDD_I2C_ADDRTYPE_7BITS, driver_info[i].address);
        Wait (1);

        I2C0_MasterSendBlock (I2C0_DeviceData, (LDD_TData*) pwm_settings, (LDD_I2C_TSize) 5, LDD_I2C_SEND_STOP);
        Wait (1);
    }
}

void Reset_PCA9552 (LED_Driver driver) {
	
    if (driver == LED_DRIVER_0 || driver == LED_DRIVER_BOTH) {
    	
        LED_DRIVER_0_RESET_PutVal (NULL, FALSE);
        Wait (PCA9552_RESET_HOLD_TIME_MSEC);
        LED_DRIVER_0_RESET_PutVal (NULL, TRUE);
    }

    if (driver == LED_DRIVER_1 || driver == LED_DRIVER_BOTH) {
    	
        LED_DRIVER_1_RESET_PutVal (NULL, FALSE);
        Wait (PCA9552_RESET_HOLD_TIME_MSEC);
        LED_DRIVER_1_RESET_PutVal (NULL, TRUE);
    }
}

// TODO: Make the indexing (0 or 1) consistent with LEDs!
void Set_LED_Output (RGB_LED led, Color_RGB *output_color) {
	
    if (led >= RGB_INVALID) { return; }

    RGB_Channel *channel = channels + (int) (led - 1);

    Set_LED_Output_Mode (channel, output_color);

    // Select the PCA9552 LED driver corresponding to the specified LED.
    I2C0_SelectSlaveDevice (I2C0_DeviceData, LDD_I2C_ADDRTYPE_7BITS, driver_info[channel->driver_index].address);
    Wait (1);

    // Send control signals to set up the specified LED with the specified color or state.
    I2C0_MasterSendBlock (I2C0_DeviceData, (LDD_TData*) driver_info[channel->driver_index].led_state.i2c_message, (LDD_I2C_TSize) 5, LDD_I2C_SEND_STOP);
    Wait (1);
}

void Set_LED_Output_Mode (RGB_Channel* led, Color_RGB * output_color) {
	
    Driver_LED_State * driver_state = &(driver_info[led->driver_index].led_state);

    switch (led->led_index) {
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
    default: {
    	break;
    }
    }
}

int8_t Start_Light_Behavior () {
	
	// Start LEDs (and initialize their state)
	Set_LED_Output ((RGB_LED) 0,  &offColor);
	Set_LED_Output ((RGB_LED) 1,  &offColor);
	Set_LED_Output ((RGB_LED) 2,  &offColor);
	Set_LED_Output ((RGB_LED) 3,  &offColor);
	Set_LED_Output ((RGB_LED) 4,  &offColor);
	Set_LED_Output ((RGB_LED) 5,  &offColor);
	Set_LED_Output ((RGB_LED) 6,  &offColor);
	Set_LED_Output ((RGB_LED) 7,  &offColor);
	Set_LED_Output ((RGB_LED) 8,  &offColor);
	Set_LED_Output ((RGB_LED) 9,  &offColor);
	Set_LED_Output ((RGB_LED) 10, &offColor);
	Set_LED_Output ((RGB_LED) 11, &offColor);
}
