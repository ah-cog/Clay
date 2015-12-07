/*
 * gesture.c
 *
 *  Created on: Dec 3, 2015
 *      Author: thebh_000
 */

#include <stdint.h>
#include "gesture.h"

#define GESTURE_COUNT       5
#define MAX_GESTURE_STEPS   100

typedef enum gesture_type
{
    gesture_accel = 1,
    gesture_gyro = 2,
    gesture_mag = 4
} gesture_type;

typedef enum
{
    no_change,
    increase_x,
    decrease_x,
    increase_y,
    decrease_y,
    increase_z,
    decrease_z
} axis_diff;

typedef struct gesture_step
{
    axis_diff accel_diff;
    uint16_t accel_threshold;
    axis_diff gyro_diff;
    uint16_t gyro_threshold;
    axis_diff mag_diff;
    uint16_t mag_threshold;
} gesture_step;

//gestures are defined as a series of deltas in accelerometer, gyro, and magnetometer data.
//the first step in a gesture is detected based on the first delta from some baseline.
typedef struct gesture
{
    gesture_step gesture_steps[MAX_GESTURE_STEPS];
    uint8_t gesture_step_duration_msec_min;
    uint8_t gesture_step_duration_msec_max;
    uint8_t gesture_step_count;
    uint8_t gesture_id;
    uint8_t trained;
    gesture_type type;
} gesture;

static gesture gesture_collection[GESTURE_COUNT];

static uint8_t detect_gesture(gesture * gest, mpu_values * v, uint8_t count, uint8_t head, uint8_t sample_time_ms);
static bool check_diff(axis_diff diff, _3axis * avg, _3axis * input, uint8_t i);

uint8_t parse_gesture(mpu_values * v, uint8_t count, uint8_t head, uint8_t sample_time_ms)
{
    if (count > MAX_GESTURE_STEPS) return 0;

    uint8_t gesture_id = 0;

    for (int i = 0; i < GESTURE_COUNT; ++i)
    {
        if (gesture_collection[i].trained)
        {
            gesture_id = detect_gesture(gesture_collection + i, v, count, head, sample_time_ms);
            if (gesture_id < GESTURE_COUNT) break;   //default return is 0xFF
        }
    }

    return gesture_id;
}

uint8_t train_gesture(mpu_values * v, uint8_t count, uint8_t head, uint8_t sample_time_ms, uint8_t gesture_id)
{
    if (gesture_id > GESTURE_COUNT) return 0;

    gesture * target_gesture = gesture_collection + gesture_id;
    uint8_t rval = 0;

    return rval;
}

static uint8_t detect_gesture(gesture * gest, mpu_values * v, uint8_t count, uint8_t head, uint8_t sample_time_ms)
{
    uint8_t rval = 0;
    uint8_t next_gesture_step = 0;
    bool accel_condition_met;
    bool gyro_condition_met;
    bool mag_condition_met;
    bool wrong_delta_found;

    mpu_values rolling_average;

    if (gest->type & gesture_accel)
    {
        rolling_average.accel.val.x = v[head].accel.val.x;
        rolling_average.accel.val.y = v[head].accel.val.y;
        rolling_average.accel.val.z = v[head].accel.val.z;
    }

    if (gest->type & gesture_gyro)
    {
        rolling_average.gyro.val.x = v[head].gyro.val.x;
        rolling_average.gyro.val.y = v[head].gyro.val.y;
        rolling_average.gyro.val.z = v[head].gyro.val.z;
    }

    if (gest->type & gesture_mag)
    {
        rolling_average.mag.val.x = v[head].mag.val.x;
        rolling_average.mag.val.y = v[head].mag.val.y;
        rolling_average.mag.val.z = v[head].mag.val.z;
    }

    for (uint8_t i = 0; i < count; ++i)
    {
        //look for first delta to exist.

        if (gest->type & gesture_accel)
        {
            check_diff(gest->gesture_steps[next_gesture_step].accel_diff, &rolling_average.accel, &(v[(head + i) % count].accel), i);
        }
        else
        {
            accel_condition_met = TRUE;
        }

        if (gest->type & gesture_gyro)
        {
            check_diff(gest->gesture_steps[next_gesture_step].gyro_diff, &rolling_average.gyro, &(v[(head + i) % count].gyro), i);
        }
        else
        {
            gyro_condition_met = TRUE;
        }

        if (gest->type & gesture_mag)
        {
            check_diff(gest->gesture_steps[next_gesture_step].mag_diff, &rolling_average.mag, &(v[(head + i) % count].mag), i);
        }
        else
        {
            mag_condition_met = TRUE;
        }

        if (accel_condition_met && gyro_condition_met && mag_condition_met)
        {

            if (next_gesture_step == gest->gesture_step_count)
            {
                rval = 1;        //we got all the way to the last gesture and succeeded every step.
                break;
            }
            else if (!((i * sample_time_ms) < gest->gesture_step_duration_msec_min))
            {
                //too soon. we weren't expecting this change yet.
                rval = 0;
                break;
            }
            else
            {
                //next step.
                ++next_gesture_step;
                accel_condition_met = FALSE;
                gyro_condition_met = FALSE;
                mag_condition_met = FALSE;
            }
        }
        else if (i * sample_time_ms > gest->gesture_step_duration_msec_max)
        {
            //the next delta wasn't found in the data
            break;
        }
        else if (wrong_delta_found)
        {
            //bail out. this isn't our gesture
            break;
        }

    }

    return rval;
}

static bool check_diff(axis_diff diff, _3axis * avg, _3axis * input, uint8_t i)
{

    bool rval = FALSE;
    
    //find largest delta
    //check it against the required delta

    switch (diff)
    {
        case increase_x:
            {
            break;
        }
        case decrease_x:
            {
            break;
        }
        case increase_y:
            {
            break;
        }
        case decrease_y:
            {
            break;
        }
        case increase_z:
            {
            break;
        }
        case decrease_z:
            {
            break;
        }
        case no_change:
            default:
            {
            break;
        }
    }

    avg->val.x = (input->val.x + ((avg->val.x) * (i - 1))) / i;
    avg->val.y = (input->val.y + ((avg->val.y) * (i - 1))) / i;
    avg->val.z = (input->val.z + ((avg->val.z) * (i - 1))) / i;

    return rval;
}
