/*
 * Clock.h
 *
 *  Created on: Jan 26, 2016
 *      Author: thebh
 */

#ifndef SOURCES_CLOCK_H_
#define SOURCES_CLOCK_H_

#include "PE_Types.h"

extern bool tick_50us;
extern bool tick_1ms;
extern bool tick_50ms;
extern bool tick_250ms;
extern bool tick_500ms;

//todo: configurable ticks

extern uint32_t Millis();
extern void Wait(uint32_t wait_ms);
extern void Clock_Enable();
extern void Clock_Start();
extern void Clock_Stop();
extern void Clock_Pause();

extern void Tick();

#endif /* SOURCES_CLOCK_H_ */
