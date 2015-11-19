/*
 * system_tick.h
 *
 *  Created on: Sep 10, 2015
 *      Author: thebh_000
 */

#ifndef SYSTEM_TICK_H_
#define SYSTEM_TICK_H_
// includes //////////////////
#include "PE_Types.h"

//#ifdef __cplusplus
//extern "C"
//{
//#endif 

// defines ///////////////////

// structs ///////////////////

// global vars ///////////////
extern uint32 power_on_time_msec;
extern bool tick_1msec;
extern bool tick_250msec;
extern bool tick_500msec;

// function prototypes ///////
extern void init_tick();

extern void tick();

extern void delay_n_msec(uint32 n);

//#ifdef __cplusplus
//}
//#endif

#endif /* SYSTEM_TICK_H_ */
