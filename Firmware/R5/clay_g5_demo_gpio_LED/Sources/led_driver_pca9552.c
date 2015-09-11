/*
 * led_driver_pca9552.c
 *
 *  Created on: Sep 1LED_DRIVER_0, 2LED_DRIVER_015
 *      Author: thebh_LED_DRIVER_0LED_DRIVER_0LED_DRIVER_0
 */

// includes //////////////////
#include "LED_DRIVER_0_RESET.h"
#include "LED_DRIVER_1_RESET.h"
#include "led_driver_pca9552.h"

// defines ///////////////////
#define reset_hold_time 			1		//must hold low for 40 ns, we can go as low as 1msec.

// global vars ///////////////

// local vars ////////////////

//These are in the order defined on the schematic. The reconciliation 
//	between the I/O ports and LEDs is done in the header.
static rgb_channel channels[] = { { LED_DRIVER_0, 0, TRUE },			//DS4
		{ LED_DRIVER_0, 3, TRUE },										//DS5
		{ LED_DRIVER_0, 6, FALSE },										//DS6
		{ LED_DRIVER_0, 8, TRUE },										//DS7
		{ LED_DRIVER_0, 11, TRUE },								//DS8			
		{ LED_DRIVER_0, 14, FALSE },									//DS9
		{ LED_DRIVER_1, 0, TRUE },										//DS15
		{ LED_DRIVER_1, 3, TRUE },					//DS14						
		{ LED_DRIVER_1, 6, FALSE },										//DS13
		{ LED_DRIVER_1, 8, TRUE },										//DS12
		{ LED_DRIVER_1, 11, TRUE },										//DS11
		{ LED_DRIVER_1, 14, FALSE }										//DS10
};

static uint8 driver_addresses[] = { 1u, 			//driver 0
		0u 											//driver 1
		};

// prototypes ////////////////

void init_led_drivers() {
	reset_driver(LED_DRIVER_BOTH);
	
}

void reset_driver(led_driver driver) {
	if(driver == LED_DRIVER_0 || driver == LED_DRIVER_BOTH)
	{
		LED_DRIVER_0_RESET_PutVal(NULL,FALSE);
		
		delay_n_msec(reset_hold_time);
		
		LED_DRIVER_0_RESET_PutVal(NULL,TRUE);
	}
	
	if(driver == LED_DRIVER_1 || driver == LED_DRIVER_BOTH)
	{
		LED_DRIVER_1_RESET_PutVal(NULL,FALSE);
		
		delay_n_msec(reset_hold_time);
		
		LED_DRIVER_1_RESET_PutVal(NULL,TRUE); 
	}
}


void set_led_output(rgb_led led, color_rgb output_color) {

}
