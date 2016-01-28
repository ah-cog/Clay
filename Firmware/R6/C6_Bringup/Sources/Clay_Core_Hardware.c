/*
 * Clay_Core_Hardware.c
 *
 *  Created on: Jan 26
 2016
 *      Author: thebh
 */
#include "Clay_Core_Hardware.h"
#include "Clock.h"
#include "LED1.h"
#include "LED2.h"
#include "RGB_LED.h"
#include "BuzzerOut.h"
#include "Events.h"
////defines

////typedefs

////global vars

////local vars
static bool LED1_State;
static bool LED2_State;
static bool BuzzerOutState;
static uint32_t TickCount; //todo: expose this

////local function prototypes

////global function implementations
extern void Clay_Core_Init()
{
	LED1_State = FALSE;
	LED2_State = TRUE;
	BuzzerOutState = TRUE;
	Clock_Start();
	RGB_LED_Enable();
}

void Clay_Core_Update()
{
	if (tick_50us)
	{
		tick_50us = FALSE;

		switch (SelectedFreq)
		{
		case f_110Hz:
		{
			if (TickCount >= 182)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_220Hz:
		{
			if (TickCount >= 91)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_440Hz:
		{
			if (TickCount >= 45)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_880Hz:
		{
			if (TickCount >= 22)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_1760Hz:
		{
			if (TickCount >= 11)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_3520Hz:
		{
			if (TickCount >= 6)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_7040Hz:
		{
			if (TickCount >= 3)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_Off:
		default:
		{
			break;
		}
		}

		++TickCount;
		BuzzerOut_PutVal(NULL, BuzzerOutState);
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
