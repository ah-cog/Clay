/*
 * Clock.h
 *
 * Created on: Sep 10, 2015
 * Authors: Ben Hefner, Michael Gubbels
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "PE_Types.h"

#include "Drivers/MPU9250.h"
#include "Drivers/PCA9552.h"
#include "Drivers/ESP8266.h"
#include "Messenger.h"

extern uint32_t power_on_time_msec;
extern bool tick_1msec;
extern bool tick_250msec;
extern bool tick_500msec;
extern bool tick_3000msec;

extern int8_t Enable_Clock ();

extern int8_t Start_Clock ();

extern void Tick ();

extern void Wait (uint32_t milliseconds);

extern uint32_t Millis ();

extern void Monitor_Periodic_Events ();

// extern void Stop_Clock ();

// TODO: Disable_Clock ()

#endif /* CLOCK_H_ */
