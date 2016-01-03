#ifndef LEDS_H
#define LEDS_H

#include "PE_Types.h"
#include "PE_LDD.h"

#include "../Clock.h"

#define LED1 1
#define LED2 2

#define ON_CHANNEL 1
#define OFF_CHANNEL 0

extern int8_t Enable_LEDs ();
extern void Set_LED_State (uint8_t number, uint8_t state); // i.e., set discrete state of the channel (on or off)
extern uint8_t Get_LED_State (uint8_t number); // i.e., get discrete input state

extern int8_t Perform_Status_LED_Effect ();

#endif /* LEDS_H */
