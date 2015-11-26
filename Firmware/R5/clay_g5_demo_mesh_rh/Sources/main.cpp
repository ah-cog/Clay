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
#include <cmath>
#include <cstdint>

#ifndef MESH_H_
#include "Mesh.h"
#endif

#include "../RadioHead/RHRouter.h"

#ifndef SYSTEM_TICK_H_
#include "system_tick.h"
#endif

#ifndef LED_DRIVER_PCA9552_H_
#include "led_driver_pca9552.h"
#endif

#ifndef MPU_9250_DRIVER_H_
#include "mpu_9250_driver.h"
#endif

#define MESH_TX_MAX_TIME_MSEC   5
#define MESH_RX_MAX_TIME_MSEC   800
#define MESH_MODE_RX_TX         0
#define MESH_MODE_BROADCAST     1
#define MESH_MODE_RX_ONLY       2

static uint8_t transmit = 0;
static uint32_t mode_start_time = 0;
static uint8_t mesh_mode = 0;

static uint8_t hb_led_count = 0;

static uint32_t size = sizeof(mpu_values) - 2;
static mpu_values local_imu_data = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static mpu_values remote_imu_data = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static color_rgb colors[] = { { LED_MODE_OFF, LED_MODE_OFF, LED_MODE_OFF },        //off
        { LED_MODE_MED, LED_MODE_MED, LED_MODE_OFF },        //rg
        { LED_MODE_OFF, LED_MODE_MED, LED_MODE_MED },        //gb
        { LED_MODE_MED, LED_MODE_OFF, LED_MODE_MED },        //rb
        { LED_MODE_MED, LED_MODE_OFF, LED_MODE_OFF },        //r
        };

///
void update_imu_leds(const mpu_values * remote_imu_data, color_rgb colors[]);
void upcount_hb_leds();
void update_mesh_mode(uint8_t * data, uint8_t len);
void mesh_update_imu_leds(uint8_t * data, uint8_t len);
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

    mesh_init(update_mesh_mode, mesh_update_imu_leds);
    upcount_hb_leds();

    uint32_t tx_start;
    uint32_t tx_time;

    //mesh diagnostic LEDs.
    //TX
    //rgb 4 is whether the packet is being sent to 1 or 2
    //rgb 5 is green/blue when successful, red otherwise

    //RX
    //rgb 8 is blue when no message received, green when message received
    //rgb 9 is blue when last received message was address broadcast, green when it was application message.
    //rgb 10 is green when the NRF driver is receiving a message in the 'available' method.
    //rgb 11 is green when last node search message was direct, blue when indirect, and is only updated when this board was the target of the search
    //rgb 12 is whether the received node search message was for this node or for another node. green means for this node, blue means another    

    int target_address = 2;

    for (;;)
    {
        mesh_process_commands();

        uint8_t source;
        if ((power_on_time_msec - mode_start_time) > MESH_RX_MAX_TIME_MSEC)
        {
            transmit = 1;
            mode_start_time = 0;
        }
        if (transmit)
        {
            get_mpu_readings(&local_imu_data);

//            uint8_t tx_buf[sizeof(local_imu_data) + 2];
//            tx_buf[0] = MESH_CMD_UPDATE_IMU_DATA;
//
//            for (int i = 0; i < sizeof(local_imu_data); ++i)
//            {
//                tx_buf[i + 1] = local_imu_data.bytes[i];
//            }

//            tx_buf[sizeof(local_imu_data) + 1] = MESH_CMD_TERMINATION;

//            if (mesh_tx_command(tx_buf, sizeof(local_imu_data) + 2, get_next_node(0xFF))
//            if (mesh_tx(local_imu_data.bytes, sizeof(local_imu_data) - 2, get_next_node(0xFF))           
            if (get_first_node())
            {
                tx_start = power_on_time_msec;
                if (TRANSMIT && mesh_tx(local_imu_data.bytes, sizeof(local_imu_data) - 2, target_address) == RH_ROUTER_ERROR_NO_ROUTE)
                {
                    set_led_output(RGB_5, colors + 2);
                }
                else
                {
                    set_led_output(RGB_5, colors + 4);
                }
                tx_time = power_on_time_msec - tx_start;

#if TRANSMIT
                if (target_address == 2)
                {
                    set_led_output(RGB_4, colors + 4);
                    target_address = 1;
                }
                else
                {
                    set_led_output(RGB_4, colors + 2);
                    target_address = 2;
                }
#endif
            }
            transmit = 0;
            mode_start_time = power_on_time_msec;

        }

        if (tick_1msec)
        {
            tick_1msec = FALSE;
        }

        if (tick_250msec)
        {
            tick_250msec = FALSE;
        }

        if (tick_500msec)
        {
            tick_500msec = FALSE;
//                mesh_discover_nodes();
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
    for (;;
            )
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

    if (std::abs(remote_imu_data->values.y_mag)
            >= std::abs(remote_imu_data->values.x_mag))
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
//    LED1_PutVal(LED1_DeviceData, !(hb_led_count & 0x02));
    LED2_PutVal(LED2_DeviceData, !(hb_led_count & 0x01));
    hb_led_count = (hb_led_count + 1) % 4;
}

void update_mesh_mode(uint8_t * data, uint8_t len)
{
    if (len < 2) return;

    mesh_mode = data[1];
}

void mesh_update_imu_leds(uint8_t * data, uint8_t len)
{
    if (len < sizeof(mpu_values) + 1) return;
    update_imu_leds((mpu_values*) (data + 1), colors);
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
