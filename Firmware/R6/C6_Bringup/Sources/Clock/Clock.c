/*
 * Clock.cpp
 *
 *  Created on: Jan 26, 2016
 *      Author: thebh
 */
////includes
#include "PE_Types.h"

////global vars
bool tick_50us;
bool tick_1ms;
bool tick_50ms;
bool tick_250ms;

////local vars
uint32_t PowerOnTime_ms;
uint8_t tick_count;

////local function prototypes

////global function implementations
uint32_t Millis()
{
	return PowerOnTime_ms;
}

void Wait(uint32_t wait_ms)
{
	uint32_t Start = PowerOnTime_ms;
	while ((PowerOnTime_ms - Start) <= wait_ms)
		;
}

void Clock_Enable()
{
}

void Clock_Start()
{
	PowerOnTime_ms = 0;
	tick_count = 0;
}

void Clock_Stop()
{
	//todo: disable/deinit
}

void Clock_Pause()
{
	//todo: disable
}

void Resume()
{
	//todo: re-enable
	//reset tick?
}

void Tick()
{

	tick_50us = TRUE;

	if (++tick_count >= 20)
	{
		tick_count = 0;
		tick_1ms = TRUE;
		++PowerOnTime_ms;

		tick_50ms = !(PowerOnTime_ms % 50);
		tick_250ms = !(PowerOnTime_ms % 250);
	}


}

////local function implementations
