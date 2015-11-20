// ArduinoCompat/wirish.cpp
//
// Arduino-like API for STM32F4 Discovery and similar
// using STM32F4xx_DSP_StdPeriph_Lib_V1.3.0

#include "wirish.h"
#include <stdlib.h>

#include <system_tick.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include <MESH_CE.h>
#include <MESH_IRQ.h>
#include <MESH_CS.h>
#ifdef __cplusplus
}
#endif

//SerialUSBClass SerialUSB;

void (*mesh_irq_handler)(void);

#define NUM_IRQ_LINES (sizeof(irqlines) / sizeof(IRQLine))

// Functions we expect to find in the sketch
volatile unsigned long systick_count = 0;

void SysTickConfig()
{
    srand(power_on_time_msec);
    //tick implemented in system_tick.c
}

//TODO: Interrupt handlers for GPIOs
// These interrupt handlers have to be extern C else they dont get linked in to the interrupt vectors
void pinMode(uint8_t pin, WiringPinMode mode)
{
}

// This takes about 150ns on STM32F4 Discovery
void digitalWrite(uint8_t pin, uint8_t val)
{
    bool val_bool = (bool)val;
    if (pin == 0)
    {
        //irq is input only
        return;
    }
    else if (pin == MESH_CE_PIN_INDEX)
    {
        MESH_CE_PutVal(MESH_CE_DeviceData, val_bool);
    }
    else if (pin == MESH_SELECT_PIN_INDEX)
    {
        MESH_CS_PutVal(MESH_CS_DeviceData, val_bool);
    }
}

uint8_t digitalRead(uint8_t pin)
{
    if (pin > 1) return 0;

    uint8_t rval;

    if (pin == 1)
    {
        rval = MESH_CE_GetVal(MESH_CE_DeviceData );
    }

    return rval;
}

void attachInterrupt(uint8_t pin, void (*handler)(void), int mode)
{
    mesh_irq_handler = handler;
}

void delay(unsigned long ms)
{
    delay_n_msec(ms);
}

unsigned long millis()
{
    return power_on_time_msec;
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
void _init()
{
}
void _fini()
{
}
}
