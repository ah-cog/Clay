/*
 * GPIO.h
 *
 *  Created on: Sep 17, 2015
 *      Author: mokogobo
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "PE_Types.h"
#include "PE_LDD.h"

#define OUTPUT_CHANNEL 0
#define INPUT_CHANNEL 1

#define ON_CHANNEL 1
#define OFF_CHANNEL 0

uint8_t Enable_Channels ();
//uint8_t Enable_Channel (uint8_t number);
void Set_Channel (uint8_t number, uint8_t direction, uint8_t mode);
void Set_Channel_State (uint8_t number, uint8_t state); // i.e., set discrete state of the channel (on or off)
//void Set_Channel_Signal (); // i.e., analog signal to generate on the channel
uint8_t Get_Channel_State (uint8_t number); // i.e., get discrete input state
//void Get_Channel_Signal (); // i.e., read the analog signal on the channel
// void Disable_Channels ();

#endif /* GPIO_H_ */
