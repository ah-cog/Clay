/*
 * raw_imu.h
 *
 *  Created on: Dec 6, 2015
 *      Author: thebh_000
 */

#ifndef RAW_IMU_H_
#define RAW_IMU_H_

#include <stdlib.h>
#include <stdint.h>
#include "mpu_9250_driver.h"

struct platform_data_s
{
    signed char orientation[9];
};

typedef struct quaternion_vals
{
    int32_t w;
    int32_t x;
    int32_t y;
    int32_t z;
    uint32_t timestamp;
} quaternion_vals;

typedef union quaternion
{
    quaternion_vals quat;
    int32_t array[5];
} quaternion;

extern uint8_t clay_imu_init();
extern void tap_callback();
extern void periodic_callback();
extern const quaternion const * get_quaternion_history(uint8_t * count, uint8_t * head);
extern const mpu_values const * get_raw_history(uint8_t * count, uint8_t * head);

#endif /* RAW_IMU_H_ */
