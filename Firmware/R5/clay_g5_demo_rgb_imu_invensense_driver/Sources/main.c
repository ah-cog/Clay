/* ###################################################################
 **     Filename    : main.c
 **     Project     : clay_g5_demo_gpio
 **     Processor   : MK2LED_DRIVER_0DX256VLH7
 **     Version     : Driver LED_DRIVER_01.LED_DRIVER_01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2LED_DRIVER_015-LED_DRIVER_09-1LED_DRIVER_0, 15:LED_DRIVER_03, # CodeGen: LED_DRIVER_0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "IO3.h"
#include "IO2.h"
#include "IO1.h"
#include "IO6.h"
#include "IO5.h"
#include "IO4.h"
#include "IO9.h"
#include "IO8.h"
#include "IO7.h"
#include "IO12.h"
#include "IO11.h"
#include "IO10.h"
#include "IO10.h"
#include "LED2.h"
#include "LED1.h"
#include "LED_DRIVER_0_RESET.h"
#include "LED_DRIVER_1_RESET.h"
#include "I2C0.h"
#include "IMU_FSYNC.h"
#include "IMU_CS.h"
#include "IMU_INT.h"
#include "tick_1ms_timer.h"
#include "TU1.h"

/* Including shared modules, which are used for whole project */
#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

#ifndef __PE_Error_H
#include "PE_Error.h"
#endif

#ifndef __PE_Const_H
#include "PE_Const.h"
#endif

#ifndef __IO_Map_H
#include "IO_Map.h"
#endif

/* User includes (#include below this line is not maintained by Processor Expert) */
#include <cstdlib>
#include "system_tick.h"
#include "led_driver_pca9552.h"
#include "mpu_9250_driver.h"

#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "eMPL_outputs.h"
#include "invensense.h"
#include "invensense_adv.h"
#include "data_builder.h"

#include "nrf24L01plus.h"

color_rgb colors[] =
        {
                { LED_MODE_OFF, LED_MODE_OFF, LED_MODE_OFF },        //off
                { LED_MODE_MED, LED_MODE_MED, LED_MODE_OFF },        //rg
                { LED_MODE_OFF, LED_MODE_MED, LED_MODE_MED },        //gb
                { LED_MODE_MED, LED_MODE_OFF, LED_MODE_MED }        //rb
        };

struct platform_data_s
{
    signed char orientation[9];
};

static struct platform_data_s gyro_pdata = {
        .orientation = { 1, 0, 0,
                0, 1, 0,
                0, 0, 1 }
};

static struct platform_data_s compass_pdata = {
        .orientation = { 0, 1, 0,
                1, 0, 0,
                0, 0, -1 }
};

static bool led_2_state = FALSE;
static bool led_1_state = FALSE;

static int32_t data[100] = { 0 };
static int8_t accuracy;
static inv_time_t timestamp;

static int16_t gyro[20];
static int16_t accel[20];
static int32_t quat[20];
static uint32_t sensor_timestamp;
static int16_t sensors;
static uint8_t more;

static uint16_t gyro_rate;
static uint16_t gyro_fsr;
static uint8_t accel_fsr;
static uint16_t compass_fsr;
static uint8_t fw_load_attempts = 0;

static mpu_values v = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static void update_imu_leds(const mpu_values* v);

static void tap_cb(unsigned char direction, unsigned char count);

/*lint -save  -e97LED_DRIVER_0 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
    /* Write your local variable definition here */

    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init();
    /*** End of Processor Expert internal initialization.                    ***/

    /* Write your code here */

    init_tick();

//    mpu_9250_init();

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
    derp = mpu_set_sample_rate(20);                 //hz
    derp = mpu_set_compass_sample_rate(10);          //msec

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

    derp = 1;
    while (derp)
    {
        ++fw_load_attempts;
        derp = dmp_load_motion_driver_firmware();
        delay_n_msec(200);
    }
    derp = dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_pdata.orientation));
    derp = dmp_register_tap_cb(tap_cb);

    derp = dmp_enable_feature(
            DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL);
    derp = dmp_set_fifo_rate(20);
    derp = dmp_set_interrupt_mode(DMP_INT_CONTINUOUS);
    derp = mpu_set_dmp_state(1);

    (void) accuracy;
    (void) data;
    (void) timestamp;
    (void) v;
    (void) derp;
    update_imu_leds(NULL);

    init_led_drivers();

    delay_n_msec(5);

    if ((fw_load_attempts) > 11)
    {
        set_led_output(RGB_12, colors + 1);
    }
    else if ((fw_load_attempts) > 10)
    {
        set_led_output(RGB_11, colors + 1);
    }
    else if ((fw_load_attempts) > 9)
    {
        set_led_output(RGB_10, colors + 1);
    }
    else if ((fw_load_attempts) > 8)
    {
        set_led_output(RGB_9, colors + 1);
    }
    else if ((fw_load_attempts) > 7)
    {
        set_led_output(RGB_8, colors + 1);
    }
    else if ((fw_load_attempts) > 6)
    {
        set_led_output(RGB_7, colors + 1);
    }
    else if ((fw_load_attempts) > 5)
    {
        set_led_output(RGB_6, colors + 1);
    }
    else if ((fw_load_attempts) > 4)
    {
        set_led_output(RGB_5, colors + 1);
    }
    else if ((fw_load_attempts) > 3)
    {
        set_led_output(RGB_4, colors + 1);
    }
    else if ((fw_load_attempts) > 2)
    {
        set_led_output(RGB_3, colors + 1);
    }
    else if ((fw_load_attempts) > 1)
    {
        set_led_output(RGB_2, colors + 1);
    }
    else
    {
        set_led_output(RGB_1, colors + 1);
    }

    for (;;)
    {

        if (data_ready)
        {
            LED1_PutVal(LED1_DeviceData, led_1_state);
            led_1_state = !led_1_state;

//            int16_t intStatus;
//            derp = mpu_get_int_status(&intStatus);

            derp = dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more);
            data_ready = more > 0;
        }

        if (tick_1msec)
        {
            tick_1msec = FALSE;

            if (!(power_on_time_msec % 30))
            {
//                get_mpu_readings(&v);
//                update_imu_leds(&v);
            }
        }

        if (tick_250msec)
        {
            tick_250msec = FALSE;
//            inv_get_6axis_quaternion(&data);
        }

        if (tick_500msec)
        {
            tick_500msec = FALSE;

            //toggle LEDs
            LED2_PutVal(LED2_DeviceData, led_2_state);
            led_2_state = !led_2_state;
        }

    }

    /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
    /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
    PEX_RTOS_START(); /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
    /*** End of RTOS startup code.  ***/
    /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
    for (;;)
    {
    }
    /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

static void update_imu_leds(const mpu_values* v)
{
    if (!v) return;

    if (v->x_accel < 50)
    {
        set_led_output(RGB_12, colors + 1);        //-x
        set_led_output(RGB_4, colors + 0);        //+x
    }
    else
    if (v->x_accel > 50)
    {
        set_led_output(RGB_12, colors + 0);        //-x
        set_led_output(RGB_4, colors + 1);        //+x
    }

    if (v->y_accel < 50)
    {
        set_led_output(RGB_1, colors + 1);        //-y
        set_led_output(RGB_9, colors + 0);        //+y
    }
    else
    if (v->y_accel > 50)
    {
        set_led_output(RGB_1, colors + 0);        //-y
        set_led_output(RGB_9, colors + 1);        //+y
    }

    if (v->z_accel > 0)        //+z
    {
        set_led_output(RGB_10, colors + 1);
        set_led_output(RGB_7, colors + 1);
        set_led_output(RGB_6, colors + 1);
        set_led_output(RGB_3, colors + 1);
    }
    else
    if (v->z_accel < 0)        //-z
    {
        set_led_output(RGB_10, colors + 3);
        set_led_output(RGB_7, colors + 3);
        set_led_output(RGB_6, colors + 3);
        set_led_output(RGB_3, colors + 3);
    }

    if (abs(v->y_mag) >= abs(v->x_mag))
    {
        if (v->y_mag > 0)
        {
            //strongest magnetic field towards y+
            set_led_output(RGB_11, colors);        //y-
            set_led_output(RGB_8, colors);        //x+
            set_led_output(RGB_5, colors + 1);        //y+
            set_led_output(RGB_2, colors);        //x-
        }
        else
        {
            //strongest magnetic field towards y-
            set_led_output(RGB_11, colors + 1);        //y-
            set_led_output(RGB_8, colors);        //x+
            set_led_output(RGB_5, colors);        //y+
            set_led_output(RGB_2, colors);        //x-
        }
    }
    else
    {
        if (v->x_mag > 0)
        {
            //strongest magnetic field towards x+
            set_led_output(RGB_11, colors);        //y-
            set_led_output(RGB_8, colors + 1);        //x+
            set_led_output(RGB_5, colors);        //y+
            set_led_output(RGB_2, colors);        //x-
        }
        else
        {
            //strongest magnetic field towards x-
            set_led_output(RGB_11, colors);        //y-
            set_led_output(RGB_8, colors);        //x+
            set_led_output(RGB_5, colors);        //y+
            set_led_output(RGB_2, colors + 1);        //x-
        }
    }
}

static void tap_cb(unsigned char direction, unsigned char count)
{
    data_ready = 0;
    switch (direction)
    {
        case TAP_X_UP:
            break;
        case TAP_X_DOWN:
            break;
        case TAP_Y_UP:
            break;
        case TAP_Y_DOWN:
            break;
        case TAP_Z_UP:
            break;
        case TAP_Z_DOWN:
            break;
        default:
            return;
    }
    return;
}

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 1LED_DRIVER_0.3 [LED_DRIVER_05.LED_DRIVER_09]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
