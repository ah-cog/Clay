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

#define CHANNEL_COUNT 12

#define CHANNEL_ENABLED  1
#define CHANNEL_DISABLED 0

#define CHANNEL_DIRECTION_OUTPUT 0
#define CHANNEL_DIRECTION_INPUT  1

#define CHANNEL_MODE_TOGGLE   1
#define CHANNEL_MODE_WAVEFORM 2
#define CHANNEL_MODE_PULSE    3

#define CHANNEL_VALUE_TOGGLE_ON  1
#define CHANNEL_VALUE_TOGGLE_OFF 0

typedef struct {
	uint8_t number;
	uint8_t enabled; // Specifies whether or not the channel being used.
	uint8_t direction; // input or output
	uint8_t mode; // (output) digital, pwm, (input) digital, analog, pwm
	uint16_t value; // The raw value of the channel.
	// TODO: logical value
	// TODO: continuous value
	
	// TODO: Expected value. Set this to monitor the channel and look for a value. This will be used to set the LED state (maybe green or red, depending on correct or incorrect)
	
	// TODO: UUID for port. Used to record data and use it to submit data and request data.
	
	// TODO: UUID for transform.
} Channel;

extern Channel updateChannelProfile[];
extern Channel channelProfile[];

uint8_t Initialize_Channels ();
uint8_t Update_Channels ();
uint8_t Apply_Channels ();

uint8_t Enable_Channel (uint8_t number, uint8_t enabled);

uint8_t Enable_Channels ();
//uint8_t Enable_Channel (uint8_t number);
void Set_Channel (uint8_t number, uint8_t direction, uint8_t mode);
void Set_Channel_Value (uint8_t number, uint8_t state); // i.e., set discrete state of the channel (on or off)
//void Set_Channel_Signal (); // i.e., analog signal to generate on the channel
uint8_t Get_Channel_Value (uint8_t number); // i.e., get discrete input state
//void Get_Channel_Signal (); // i.e., read the analog signal on the channel
// void Disable_Channels ();

#endif /* GPIO_H_ */
