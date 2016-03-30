#ifndef CLOCK_H
#define CLOCK_H

#include "stdint.h"
#include "stdbool.h"

extern bool tick_50us;
extern bool tick_1ms;
extern bool tick_50ms;
extern bool tick_250ms;
extern bool tick_500ms;
extern bool tick_1000ms;
extern bool tick_3000ms;

// TODO: configurable ticks

extern uint32_t Millis();
extern void Wait(uint32_t wait_ms);
extern bool Enable_Clock();
extern bool Start_Clock();
extern bool Stop_Clock();
extern bool Pause_Clock();

extern void Tick();

#endif
