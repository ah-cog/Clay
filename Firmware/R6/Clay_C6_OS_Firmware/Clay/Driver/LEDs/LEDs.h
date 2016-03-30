#ifndef LEDS_H
#define LEDS_H

#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"

#include "Clock.h"

#define LED1 1
#define LED2 2

#define ON_CHANNEL 1
#define OFF_CHANNEL 0

extern int8_t LED_Enable();
extern void Set_LED_State(uint8_t number, uint8_t state);     // i.e., set discrete state of the channel (on or off)
extern uint8_t Get_LED_State(uint8_t number);     // i.e., get discrete input state

extern int8_t Perform_Status_LED_Effect();

#endif /* LEDS_H */