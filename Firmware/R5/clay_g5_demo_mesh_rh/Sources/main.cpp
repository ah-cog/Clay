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
#include "SM1.h"
#include "MESH_IRQ.h"
#include "MESH_CE.h"
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

#define MESH_RX_TIMEOUT_MS  1

#if 1
#define THIS_NODE_ADDR 1u
#define REMOTE_NODE_ADDR 2u
#else
#define THIS_NODE_ADDR 2u
#define REMOTE_NODE_ADDR 1u
#endif

#ifndef SYSTEM_TICK_H_
#include "system_tick.h"
#endif

#ifndef LED_DRIVER_PCA9552_H_
#include "led_driver_pca9552.h"
#endif

#ifndef MPU_9250_DRIVER_H_
#include "mpu_9250_driver.h"
#endif

#ifndef RadioHead_h
#include "..\RadioHead\RadioHead.h"
#endif

#ifndef RHMesh_h
#include "../RadioHead/RHMesh.h"
#endif

#ifndef RH_NRF24_h
#include "../RadioHead/RH_NRF24.h"
#endif

#ifndef RHGenericDriver_h
#include "../RadioHead/RHGenericDriver.h"
#endif

#ifndef _wirish_h
#include "../RadioHead/wirish.h"
#endif

#ifndef _HardwareSPI_h
#include "../RadioHead/HardwareSPI.h"
#endif

#ifndef RHGenericSPI_h
#include "../RadioHead/RHGenericSPI.h"
#endif

#ifndef RHHardwareSPI_h
#include "../RadioHead/RHHardwareSPI.h"
#endif

static uint8_t hb_led_count = 0;

static uint8_t size = sizeof(mpu_values);
static mpu_values local_imu_data = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static mpu_values remote_imu_data = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static color_rgb colors[] = { { LED_MODE_OFF, LED_MODE_OFF, LED_MODE_OFF },        //off
        { LED_MODE_MED, LED_MODE_MED, LED_MODE_OFF },        //rg
        { LED_MODE_OFF, LED_MODE_MED, LED_MODE_MED },        //gb
        { LED_MODE_MED, LED_MODE_OFF, LED_MODE_MED }         //rb
};

///
void update_imu_leds(const mpu_values* remote_imu_data, color_rgb colors[]);
void upcount_hb_leds();
///

/*lint -save  -e97LED_DRIVER_0 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
    /* Write your local variable definition here */

    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init();
    /*** End of Processor Expert internal initialization.                    ***/

    init_tick();
    upcount_hb_leds();

    delay_n_msec(100);
    upcount_hb_leds();

    init_led_drivers();
    upcount_hb_leds();

    mpu_9250_init();
    upcount_hb_leds();

    RH_NRF24 meshRadio(MESH_CE_PIN_INDEX, MESH_SELECT_PIN_INDEX);
    upcount_hb_leds();

    RHMesh meshManager(meshRadio);
    upcount_hb_leds();

    meshManager.init();
    upcount_hb_leds();

    meshManager.setThisAddress(THIS_NODE_ADDR);
    upcount_hb_leds();

    for (;;)
    {
        if (tick_1msec)
        {
            tick_1msec = FALSE;

            if (meshManager.recvfromAck((uint8_t*) &remote_imu_data, &size))
            {
                update_imu_leds(&remote_imu_data, colors);
            }

            get_mpu_readings(&local_imu_data);
            meshManager.sendtoWait((uint8_t*) &local_imu_data, sizeof(mpu_values), REMOTE_NODE_ADDR, 0);

        }

        if (tick_250msec)
        {
            tick_250msec = FALSE;
        }

        if (tick_500msec)
        {
            tick_500msec = FALSE;
            upcount_hb_leds();
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

void update_imu_leds(const mpu_values* remote_imu_data, color_rgb colors[])
{
    if (remote_imu_data->values.x_accel < 50)
    {
        set_led_output(RGB_12, colors + 1);        //-x
        set_led_output(RGB_4, colors + 0);        //+x
    }
    else if (remote_imu_data->values.x_accel > 50)
    {
        set_led_output(RGB_12, colors + 0);        //-x
        set_led_output(RGB_4, colors + 1);        //+x
    }

    if (remote_imu_data->values.y_accel < 50)
    {
        set_led_output(RGB_1, colors + 1);        //-y
        set_led_output(RGB_9, colors + 0);        //+y
    }
    else if (remote_imu_data->values.y_accel > 50)
    {
        set_led_output(RGB_1, colors + 0);        //-y
        set_led_output(RGB_9, colors + 1);        //+y
    }

    if (remote_imu_data->values.z_accel > 0)        //+z
    {
        set_led_output(RGB_10, colors + 1);
        set_led_output(RGB_7, colors + 1);
        set_led_output(RGB_6, colors + 1);
        set_led_output(RGB_3, colors + 1);
    }
    else if (remote_imu_data->values.z_accel < 0)        //-z
    {
        set_led_output(RGB_10, colors + 3);
        set_led_output(RGB_7, colors + 3);
        set_led_output(RGB_6, colors + 3);
        set_led_output(RGB_3, colors + 3);
    }

    if (abs(remote_imu_data->values.y_mag)
            >= abs(remote_imu_data->values.x_mag))
    {
        if (remote_imu_data->values.y_mag > 0)
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
        if (remote_imu_data->values.x_mag > 0)
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

void upcount_hb_leds()
{
    LED1_PutVal(LED1_DeviceData, !(hb_led_count & 0x02));
    LED2_PutVal(LED2_DeviceData, !(hb_led_count & 0x01));
    hb_led_count = (hb_led_count + 1) % 4;
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
