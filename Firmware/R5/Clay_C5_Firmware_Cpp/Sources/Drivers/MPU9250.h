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

extern uint8_t data_ready;

extern uint8_t Enable_MPU9250();
extern uint8_t Start_MPU9250();
extern uint8_t Stop_MPU9250();
extern uint8_t Pause_MPU9250();
extern uint8_t Resume_MPU9250();
extern void tap_callback();
extern void imu_periodic_callback();
extern const quaternion * get_quaternion_history(uint8_t * count, uint8_t * head);
extern const mpu_values * get_raw_history(uint8_t * count, uint8_t * head);

#endif /* RAW_IMU_H_ */
