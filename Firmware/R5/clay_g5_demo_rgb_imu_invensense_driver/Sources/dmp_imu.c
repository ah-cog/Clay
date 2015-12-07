/*
 * raw_imu.c
 *
 *  Created on: Dec 6, 2015
 *      Author: thebh_000
 */

#include <stdlib.h>
#include <stdint.h>
#include "IMU_CS.h"
#include "IMU_FSYNC.h"
#include "PE_Types.h"
#include "dmp_imu.h"
#include "system_tick.h"
#include "mpu_9250_driver.h"

#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "eMPL_outputs.h"
#include "invensense.h"
#include "invensense_adv.h"
#include "data_builder.h"

// defines ////////////////////////////////////////////////////////////////////
#define MAX_HISTORY_COUNT       100 //.5 seconds worth @ 200hz update rate
#if MAX_HISTORY_COUNT > 0xFF
#error you need to increase the size of the index vars for the history buffers
#endif

#define DEFAULT_MPU_HZ          20
#define COMPASS_READ_MS         100                 
// global vars ////////////////////////////////////////////////////////////////

// local vars /////////////////////////////////////////////////////////////////
static quaternion quat_history[MAX_HISTORY_COUNT];
static uint8_t quat_count;
static uint8_t quat_head;
static uint8_t quat_tail;

static mpu_values raw_history[MAX_HISTORY_COUNT];
static uint8_t raw_count;
static uint8_t raw_head;
static uint8_t raw_tail;

static uint16_t gyro_rate;
static uint16_t gyro_fsr;
static uint8_t accel_fsr;
static uint16_t compass_fsr;
static uint8_t fw_load_attempts = 0;

static struct platform_data_s gyro_pdata = {
        .orientation = { 1, -1, 0,
                1, 0, 0,
                0, 0, 1 }
};

static struct platform_data_s compass_pdata = {
        .orientation = { 1, 0, 0,
                0, -1, 0,
                0, 0, -1 }
};

// local function prototypes //////////////////////////////////////////////////
static void tap_cb(unsigned char direction, unsigned char count);
static void android_orient_cb(unsigned char orientation);
static void add_datapoint(quaternion * quat, mpu_values * mpu_raw);

uint8_t clay_imu_init()
{
    raw_head = 0;
    raw_count = 0;
    raw_tail = 0;

    quat_head = 0;
    quat_count = 0;
    quat_tail = 0;

    //toggle these lines to ensure the bus is in an idle state.
    IMU_CS_PutVal(IMU_CS_DeviceData, 0);
    IMU_FSYNC_PutVal(IMU_FSYNC_DeviceData, 1);
    delay_n_msec(5);
    IMU_CS_PutVal(IMU_CS_DeviceData, 1);
    IMU_FSYNC_PutVal(IMU_FSYNC_DeviceData, 0);

    ///initialize mpu driver from invensense. see arm project included in the library download zip for more info.
    int8_t derp = mpu_init(NULL);

    derp = inv_init_mpl();
    derp = inv_enable_quaternion();
    derp = inv_enable_9x_sensor_fusion();
    derp = inv_enable_fast_nomot();                 //enable quick calibration
    derp = inv_enable_gyro_tc();                    //enable temperature compensation
    derp = inv_enable_vector_compass_cal();         //enable compass calibration
    derp = inv_enable_magnetic_disturbance();        //enable compass calibration
    derp = inv_enable_eMPL_outputs();
    derp = inv_start_mpl();

    derp = mpu_set_int_level(1);
    derp = mpu_set_int_latched(0);

    derp = mpu_set_sensors(INV_XYZ_ACCEL | INV_XYZ_GYRO | INV_XYZ_COMPASS);
    derp = mpu_configure_fifo(INV_XYZ_ACCEL | INV_XYZ_GYRO);
    derp = mpu_set_sample_rate(DEFAULT_MPU_HZ);                 //hz
    derp = mpu_set_compass_sample_rate(1000 / COMPASS_READ_MS);          //msec

    derp = mpu_get_sample_rate(&gyro_rate);
    derp = mpu_get_gyro_fsr(&gyro_fsr);
    derp = mpu_get_accel_fsr(&accel_fsr);
    derp = mpu_get_compass_fsr(&compass_fsr);

    inv_set_gyro_sample_rate(1000000L / gyro_rate);         //(1 / 20hz) in usec
    inv_set_accel_sample_rate(1000000L / gyro_rate);        //(1 / 20hz) in usec
    inv_set_compass_sample_rate(10000);               //usec

    inv_set_gyro_orientation_and_scale(
            inv_orientation_matrix_to_scalar(gyro_pdata.orientation),
            (long) gyro_fsr << 15);
    inv_set_accel_orientation_and_scale(
            inv_orientation_matrix_to_scalar(gyro_pdata.orientation),
            (long) accel_fsr << 15);
    inv_set_compass_orientation_and_scale(
            inv_orientation_matrix_to_scalar(compass_pdata.orientation),
            (long) compass_fsr << 15);

    int32 gyro_test[100];
    int32 accel_test[100];
    derp = mpu_run_self_test(gyro_test, accel_test);

    derp = 1;
    while (derp)
    {
        ++fw_load_attempts;
        derp = dmp_load_motion_driver_firmware();
        delay_n_msec(200);
    }
    derp = dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_pdata.orientation));
    derp = dmp_register_tap_cb(tap_cb);
    derp = dmp_register_android_orient_cb(android_orient_cb);
    derp = dmp_enable_feature(
            DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO
            | DMP_FEATURE_GYRO_CAL);
    derp = dmp_set_fifo_rate(DEFAULT_MPU_HZ);
    derp = dmp_set_interrupt_mode(DMP_INT_CONTINUOUS);

    derp = mpu_set_dmp_state(1);
}

void tap_callback()
{

}

void periodic_callback()
{
    mpu_values v;
    quaternion q;

    uint8_t status;
    uint32_t gyro_timestamp;
    uint32_t mag_timestamp;
    int16_t sensors;
    uint8_t more;

    status = dmp_read_fifo(v.gyro.array, v.accel.array, q.array, &gyro_timestamp, &sensors, &more);
    status = mpu_get_compass_reg(v.mag.array, &mag_timestamp);

    v.gyro.val.timestamp = gyro_timestamp;
    v.accel.val.timestamp = gyro_timestamp;
    v.mag.val.timestamp = mag_timestamp;
    q.quat.timestamp = gyro_timestamp;

    add_datapoint(&q, &v);

    data_ready = more > 0;
}

const quaternion const * get_quaternion_history(uint8_t* count)
{
    *count = quat_count;
    return quat_history;
}

const mpu_values const * get_raw_history(uint8_t* count)
{
    *count = raw_count;
    return raw_history;
}

static void add_datapoint(quaternion * quat, mpu_values * mpu_raw)
{
    quaternion * quat_dest = quat_history + quat_head;
    mpu_values * raw_dest = raw_history + raw_head;

    for (int i = 0; i < 4; ++i)
    {
        quat_dest->array[i] = quat->array[i];
    }
    quat_head = (quat_head + 1) % MAX_HISTORY_COUNT;
    quat_count = (quat_count == MAX_HISTORY_COUNT ? MAX_HISTORY_COUNT : (quat_count + 1));

    for (int i = 0; i < 3; ++i)
    {
        raw_dest->accel.array[i] = mpu_raw->accel.array[i];
        raw_dest->gyro.array[i] = mpu_raw->gyro.array[i];
        raw_dest->mag.array[i] = mpu_raw->mag.array[i];
    }
    raw_head = (raw_head + 1) % MAX_HISTORY_COUNT;
    raw_count = (raw_count == MAX_HISTORY_COUNT ? MAX_HISTORY_COUNT : (raw_count + 1));
}

static void tap_cb(unsigned char direction, unsigned char count)
{
//    data_ready = 0;
//
//    set_led_output(RGB_1, colors);
//    set_led_output(RGB_10, colors);
//    set_led_output(RGB_5, colors);
//    set_led_output(RGB_2, colors);
//    set_led_output(RGB_8, colors);
//    set_led_output(RGB_7, colors);
//    set_led_output(RGB_3, colors);
//
//    switch (direction)
//    {
//        case TAP_X_UP:
//            set_led_output(RGB_5, colors + 1);
//            break;
//        case TAP_X_DOWN:
//            set_led_output(RGB_10, colors + 1);
//            break;
//        case TAP_Y_UP:
//            set_led_output(RGB_8, colors + 1);
//            break;
//        case TAP_Y_DOWN:
//            set_led_output(RGB_2, colors + 1);
//            break;
//        case TAP_Z_UP:
//            set_led_output(RGB_7, colors + 2);
//            break;
//        case TAP_Z_DOWN:
//            set_led_output(RGB_3, colors + 2);
//            break;
//        default:
//            return;
//    }
//    return;
}

static void android_orient_cb(unsigned char orientation)
{
    switch (orientation)
    {
        case ANDROID_ORIENT_PORTRAIT:
            break;
        case ANDROID_ORIENT_LANDSCAPE:
            break;
        case ANDROID_ORIENT_REVERSE_PORTRAIT:
            break;
        case ANDROID_ORIENT_REVERSE_LANDSCAPE:
            break;
        default:
            return;
    }
}
