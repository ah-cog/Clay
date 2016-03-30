/*
 * raw_imu.c
 *
 *  Created on: Dec 6, 2015
 *      Author: thebh_000
 */

#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
//#include "IMU_FSYNC.h"
#include "MPU9250.h"
#include "Clock.h"
#include "mpu_9250_driver.h"


// TODO: update IMU gpio driver
//#include "IMU_IRQ.h"

#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "eMPL_outputs.h"
#include "invensense.h"
#include "invensense_adv.h"
#include "data_builder.h"
#include "fusion_9axis.h"
#include "quaternion_supervisor.h"

// defines ////////////////////////////////////////////////////////////////////
#define MAX_HISTORY_COUNT       100 //MAX_HISTORY_COUNT * (1 / DEFAULT_MPU_HZ) = seconds worth of data stored in buffer 
#if MAX_HISTORY_COUNT > 0xFF
#error you need to increase the size of the index vars for the history buffers
#endif

#define DEFAULT_MPU_HZ          50
#define COMPASS_READ_MS         100                 
// global vars ////////////////////////////////////////////////////////////////
uint8_t data_ready = 0;

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

static struct platform_data_s gyro_pdata = { .orientation = { 1, -1, 0, 1, 0, 0, 0, 0, 1 } };

static struct platform_data_s compass_pdata = { .orientation = { 1, 0, 0, 0, -1, 0, 0, 0, -1 } };

// local function prototypes //////////////////////////////////////////////////
static void tap_cb(unsigned char direction, unsigned char count);
static void android_orient_cb(unsigned char orientation);
static void add_datapoint(quaternion * quat, mpu_values * mpu_raw);

//initalizes mpu and dmp. returns 1 if successful, 0 if not.
uint8_t Start_MPU9250() {
   raw_head = 0;
   raw_count = 0;
   raw_tail = 0;

   quat_head = 0;
   quat_count = 0;
   quat_tail = 0;

   // TODO: is the CS necessary here?
   //toggle these lines to ensure the bus is in an idle state.
   // TODO: update IMU gpio driver
//   IMU_FSYNC_PutVal(IMU_FSYNC_DeviceData, 1);
//   Wait(5);
//   IMU_FSYNC_PutVal(IMU_FSYNC_DeviceData, 0);

   ///initialize mpu driver from invensense. see arm project included in the library download zip for more info.
   int8_t status = !mpu_init(NULL);

   status = status && !inv_init_mpl();
   status = status && !inv_enable_quaternion();
   status = status && !inv_enable_9x_sensor_fusion();
   status = status && !inv_enable_fast_nomot();                 //enable quick calibration
   status = status && !inv_enable_gyro_tc();                    //enable temperature compensation
   status = status && !inv_enable_vector_compass_cal();         //enable compass calibration
   status = status && !inv_enable_magnetic_disturbance();        //enable compass calibration
   status = status && !inv_enable_eMPL_outputs();
   status = status && !inv_start_mpl();

   status = status && !mpu_set_int_level(1);
   status = status && !mpu_set_int_latched(0);

   status = status && !mpu_set_sensors(INV_XYZ_ACCEL | INV_XYZ_GYRO | INV_XYZ_COMPASS);
   status = status && !mpu_configure_fifo(INV_XYZ_ACCEL | INV_XYZ_GYRO);
   status = status && !mpu_set_sample_rate(DEFAULT_MPU_HZ);                 //hz
   status = status && !mpu_set_compass_sample_rate(1000 / COMPASS_READ_MS);          //msec

   status = status && !mpu_get_sample_rate(&gyro_rate);
   status = status && !mpu_get_gyro_fsr(&gyro_fsr);
   status = status && !mpu_get_accel_fsr(&accel_fsr);
   status = status && !mpu_get_compass_fsr(&compass_fsr);

   inv_set_gyro_sample_rate(1000000L / gyro_rate);         //(1 / 20hz) in usec
   inv_set_accel_sample_rate(1000000L / gyro_rate);        //(1 / 20hz) in usec
   inv_set_compass_sample_rate(10000);               //usec

   inv_set_gyro_orientation_and_scale(inv_orientation_matrix_to_scalar(gyro_pdata.orientation), (long) gyro_fsr << 15);
   inv_set_accel_orientation_and_scale(inv_orientation_matrix_to_scalar(gyro_pdata.orientation), (long) accel_fsr << 15);
   inv_set_compass_orientation_and_scale(inv_orientation_matrix_to_scalar(compass_pdata.orientation), (long) compass_fsr << 15);

   int32_t gyro_test[100];
   int32_t accel_test[100];
   status = status && mpu_run_self_test(gyro_test, accel_test) == 0x07;

   while (status) {
      ++fw_load_attempts;
      status = dmp_load_motion_driver_firmware();
      Wait(200);
   }

   if (!status)
      status = 1;     //pretty much all of the dmp/inv functions return 0 for success. We need to set this to 1 to avoid short-circuiting the next setup step.

   status = status && !dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_pdata.orientation));
   status = status && !dmp_register_tap_cb(tap_cb);
   status = status && !dmp_register_android_orient_cb(android_orient_cb);
   status = status && !dmp_enable_feature(
   DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL);
   status = status && !dmp_set_fifo_rate(DEFAULT_MPU_HZ);
   status = status && !dmp_set_interrupt_mode(DMP_INT_CONTINUOUS);

   status = status && !mpu_set_dmp_state(1);

   return status;
}

void tap_callback() {

}

void Imu_Get_Data() {
   if (!data_ready)
      return;

   mpu_values v;
   quaternion q;

   uint8_t status;
   uint32_t gyro_timestamp;
   uint32_t mag_timestamp;
   int16_t sensors;
   uint8_t more;

   status = dmp_read_fifo(v.values.gyro.array, v.values.accel.array, q.array, &gyro_timestamp, &sensors, &more);
   status = mpu_get_compass_reg(v.values.mag.array, &mag_timestamp);

   (void) status;        //shut up, warnings

   v.values.mag.val.timestamp = mag_timestamp;
   q.quat.timestamp = gyro_timestamp;

   add_datapoint(&q, &v);

   data_ready = more > 0;
}

const quaternion * get_quaternion_history(uint8_t* count, uint8_t * head) {
   // TODO: we'll need to know the size of the measurement array, otherwise we'll just walk off the end when we try to iterate.
   *count = quat_count;
   *head = quat_head;
   return quat_history;
}

const mpu_values * get_raw_history(uint8_t* count, uint8_t * head) {
   // TODO: we'll need to know the size of the measurement array, otherwise we'll just walk off the end when we try to iterate.
   *count = raw_count;
   *head = raw_head;
   return raw_history;
}

static void add_datapoint(quaternion * quat, mpu_values * mpu_raw) {
   quaternion * quat_dest = quat_history + quat_head;
   mpu_values * raw_dest = raw_history + raw_head;

   for (int i = 0; i < 4; ++i) {
      quat_dest->array[i] = quat->array[i];
   }
   quat_head = (quat_head + 1) % MAX_HISTORY_COUNT;
   if (quat_count == MAX_HISTORY_COUNT) {
      quat_tail = (quat_tail + 1 % MAX_HISTORY_COUNT);
   }
   else {
      ++quat_count;
   }

   for (int i = 0; i < 3; ++i) {
      raw_dest->values.accel.array[i] = mpu_raw->values.accel.array[i];
      raw_dest->values.gyro.array[i] = mpu_raw->values.gyro.array[i];
      raw_dest->values.mag.array[i] = mpu_raw->values.mag.array[i];
   }
   raw_head = (raw_head + 1) % MAX_HISTORY_COUNT;
   if (raw_count == MAX_HISTORY_COUNT) {
      raw_tail = (raw_tail + 1) % MAX_HISTORY_COUNT;
   }
   else {
      ++raw_count;
   }
}

static void tap_cb(unsigned char direction, unsigned char count) {
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

static void android_orient_cb(unsigned char orientation) {
   switch (orientation) {
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
