/*
 * mpu_9250_driver.c
 *
 *  Created on: Sep 14, 2015
 *      Author: thebh_000
 */

// includes //////////////////
#ifndef MPU_9250_DRIVER_H_
#include "mpu_9250_driver.h"
#endif

#ifndef __I2C0_H
#include "I2C0.h"
#endif

#ifndef SYSTEM_TICK_H_
#include "system_tick.h"
#endif

// defines ///////////////////

// structs ///////////////////

// global vars ///////////////

// local vars ////////////////

// prototypes ////////////////

// implementations ///////////
extern void mpu_9250_init()
{
    I2C0_SelectSlaveDevice(I2C0_DeviceData, LDD_I2C_ADDRTYPE_7BITS, MPU9250_ADDRESS);
    
    //
}

extern void get_mpu_readings(mpu_values * data)
{
}
