/*
 * Clock.h
 *
 *  Created on: Jan 26, 2016
 *      Author: thebh
 */

#ifndef SOURCES_CLOCK_H_
#define SOURCES_CLOCK_H_

#include "PE_Types.h"

extern bool enableBroadcastService;

extern bool tick_50us;
extern bool tick_1ms;
extern bool tick_50ms;
extern bool tick_250ms;
extern bool tick_500ms;
extern bool tick_3000ms;

//todo: configurable ticks

extern uint32_t Millis();
extern void Wait(uint32_t wait_ms);
extern bool Clock_Enable();
extern bool Clock_Start();
extern bool Clock_Stop();
extern bool Clock_Pause();

extern void Tick();

#endif /* SOURCES_CLOCK_H_ */
