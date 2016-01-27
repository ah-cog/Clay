/*
 * Clay_Core_Hardware.c
 *
 *  Created on: Jan 26, 2016
 *      Author: thebh
 */
#include "Clock.h"
#include "LED1.h"
#include "LED2.h"
#include "RGB_LED.h"

////global vars

////local vars
static bool LED1_State;
static bool LED2_State;

////local function prototypes

////global function implementations
extern void Clay_Core_Init()
{
	LED1_State = FALSE;
	LED2_State = TRUE;
	Clock_Start();
	RGB_LED_Enable();
}

void Clay_Core_Update()
{
	if (tick_50us)
	{
		tick_50us = FALSE;
	}
	if (tick_1ms)
	{
		tick_1ms = FALSE;
	}
	if (tick_50ms)
	{
		tick_50ms = FALSE;
	}
	if (tick_250ms)
	{
		tick_250ms = FALSE;

		LED1_PutVal(NULL, LED1_State);
		LED2_PutVal(NULL, LED2_State);
		LED1_State = !LED1_State;
		LED2_State = !LED2_State;
	}
}

////local function implementations
