// ArduinoCompat/wirish.cpp
//
// Arduino-like API for STM32F4 Discovery and similar
// using STM32F4xx_DSP_StdPeriph_Lib_V1.3.0

#include "wirish.h"
#include <stdlib.h>

#include "mesh.h"

extern "C"
{
#include "Clock.h"
#include "MESH_CE.h"
#include "PTC_IRQ.h"
#include "MESH_CS.h"
}

// Functions we expect to find in the sketch
volatile unsigned long systick_count = 0;

void SysTickConfig()
{
	srand(Millis());
	//tick implemented in system_tick.c
}

// These interrupt handlers have to be extern C else they dont get linked in to the interrupt vectors
void pinMode(uint8_t pin, WiringPinMode mode)
{
}

// This takes about 150ns on STM32F4 Discovery
void digitalWrite(uint8_t pin, uint8_t val)
{
	bool val_bool = (bool) val;
	if (pin == MESH_IRQ_PIN_INDEX)
	{
		//irq is input only
		return;
	}
	else if (pin == MESH_CE_PIN_INDEX)
	{
		MESH_CE_PutVal(NULL, val_bool);
	}
	else if (pin == MESH_SELECT_PIN_INDEX)
	{
		MESH_CS_PutVal(NULL, val_bool);
	}
}

uint8_t digitalRead(uint8_t pin)
{
	if (pin > 1)
		return 0;

	uint8_t rval;

	if (pin == MESH_IRQ_PIN_INDEX)
	{
		rval = PTC_IRQ_GetFieldValue(NULL, MESH_IRQ);
	}
	else if (pin == MESH_CE_PIN_INDEX)
	{
		rval = MESH_CE_GetVal(NULL);
	}

	return rval;
}

void attachInterrupt(uint8_t pin, void (*handler)(void), int mode)
{
	//don't anything
}

void delay(unsigned long ms)
{
	Wait(ms);
}

unsigned long millis()
{
	return Millis();
}

void update_random_seed(int32_t seed)
{
	srand(seed);
}

long random(long from, long to)
{
	return from + (rand() % (to - from));
}

long random(long to)
{
	return random(0, to);
}

extern "C"
{
// These need to be in C land for correct linking
//void _init()
//{
//}
//void _fini()
//{
//}
}
