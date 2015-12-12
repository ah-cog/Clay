/*
 * gesture.h
 *
 *  Created on: Dec 3, 2015
 *      Author: thebh_000
 */

#ifndef GESTURE_H_
#define GESTURE_H_

#include <stdint.h>
#include "mpu_9250_driver.h"

extern uint8_t parse_gesture(mpu_values * v, uint8_t count, uint8_t head, uint8_t sample_time_ms);
extern uint8_t train_gesture(mpu_values * v, uint8_t count, uint8_t head, uint8_t sample_time_ms, uint8_t gesture_id);

#endif /* GESTURE_H_ */
