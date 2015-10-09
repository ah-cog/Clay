/*
 * system_tick.c
 *
 *  Created on: Sep 10, 2015
 *      Author: thebh_000
 */

// includes //////////////////
#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

// defines ///////////////////

// structs ///////////////////

// global vars ///////////////
uint32 power_on_time_msec;
bool tick_1msec;
bool tick_250msec;
bool tick_500msec;

// function prototypes ///////

//reset all of the flags to false and the power on time to 0.
void init_tick()
{
    power_on_time_msec = 0;
    tick_1msec = FALSE;
    tick_250msec = FALSE;
    tick_500msec = FALSE;
}

//call this every 1msec to increment the power on time and set the flags.
void tick()
{
    ++power_on_time_msec;
    tick_1msec = TRUE;

    if (!(power_on_time_msec % 250))
    {
        tick_250msec = TRUE;
    }

    if (!(power_on_time_msec % 500))
    {
        tick_500msec = TRUE;
    }
}

///will block for n milliseconds
extern void delay_n_msec(uint32 n)
{
    int start = power_on_time_msec;
    while (power_on_time_msec - start < n)
        ;
}
