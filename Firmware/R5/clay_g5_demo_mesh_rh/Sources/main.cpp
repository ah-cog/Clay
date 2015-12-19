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

#include "RHRouter.h"

#ifndef SYSTEM_TICK_H_
#include "system_tick.h"
#endif

#ifndef LED_DRIVER_PCA9552_H_
#include "led_driver_pca9552.h"
#endif

#ifndef MPU_9250_DRIVER_H_
#include "mpu_9250_driver.h"
#endif

#ifndef MESH_STATISTICS_H_
#include "mesh_stastistics.h"
#endif

#if(ADDRESS_3 || ADDRESS_2 || ADDRESS_1)
#define TRANSMIT                1
#else
#define TRANSMIT                0
#endif

#define LED_TIME_SEGMENT_COUNT      40
#define LED_MINIMUM_ON_COUNT        (LED_TIME_SEGMENT_COUNT / 10)
#define LED_UPDATE_PERIOD_MS        (1000 / LED_TIME_SEGMENT_COUNT)

typedef struct
{
    uint8_t x_on;
    uint8_t x_sign;
    uint8_t y_on;
    uint8_t y_sign;
    uint8_t z_on;
    uint8_t z_sign;
} led_time_segment_values;

static led_time_segment_values LED_IMU_Levels[LED_TIME_SEGMENT_COUNT];
static uint32_t LED_time_segment = 0;

static uint32_t mode_start_time = 0;
static uint8_t mesh_mode = 0;

static uint8_t hb_led_count = 0;

uint8_t last_tx_return_value;

static uint32_t size = sizeof(mpu_values) - 2;
static mpu_values local_imu_data = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static mpu_values remote_imu_data = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static color_rgb colors[] = { { LED_MODE_OFF, LED_MODE_OFF, LED_MODE_OFF },        //off 0
        { LED_MODE_MED, LED_MODE_MED, LED_MODE_OFF },        //rg 1
        { LED_MODE_OFF, LED_MODE_MED, LED_MODE_MED },        //gb 2
        { LED_MODE_MED, LED_MODE_OFF, LED_MODE_MED },        //rb 3
        { LED_MODE_MED, LED_MODE_OFF, LED_MODE_OFF },        //r 4 
        { LED_MODE_OFF, LED_MODE_MED, LED_MODE_OFF },        //g 5 
        { LED_MODE_OFF, LED_MODE_OFF, LED_MODE_MED },        //b 6
        };

///
static void update_imu_leds(const mpu_values * remote_imu_data, color_rgb colors[]);
static void upcount_hb_leds();
static void update_mesh_mode(uint8_t * data, uint8_t len);
static void mesh_update_imu_leds(uint8_t * data, uint8_t len);
static void update_3LED_imu();
static void complete_experiment_and_send();
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

    init_led_drivers();
    upcount_hb_leds();

    mpu_9250_init();
    upcount_hb_leds();

    mesh_init(update_mesh_mode, mesh_update_imu_leds);
    upcount_hb_leds();

    uint32_t tx_start;
    uint32_t tx_time;

    //mesh diagnostic LEDs.
    // TX
    //     rgb 4 is green when last tx was successful, red if not.
    //     rgb 5 shows last address sent to. red when last sent to address 1, green when last sent to 2, blue when last sent to 3
    // RX
    //     led 1 is toggled when an IMU update message is received
    //     rgb 1 is red when address 1 sent the last message, green when address 2, blue when address 3
    //     rgb 7 is green when the NRF driver is receiving a message in the 'available' method.
    //     rgb 8 is blue when no message received, green when message received
    //     rgb 9 is blue when last received message was address broadcast, green when it was application message.    
    //     rgb 11 is green when last node search message was direct, blue when indirect, and is only updated when this board was the target of the search
    //     rgb 12 is whether the received node search message was for this node or for another node. green means for this node, blue means another

    int target_address = 2;

    //used to make sure these variables get initialized. they'll never be accessed otherwise.

    start_time = power_on_time_msec;
    setup_next_experiment();

    for (;;)
    {
        //todo: collect until time is up or number of samples is reached.

        if ((experiment_data.settings.message_transmission_count
                && transmissions_sent_for_this_experiment >= experiment_data.settings.message_transmission_count)
                || (experiment_data.settings.experiment_duration_ms
                        && (power_on_time_msec - start_time) >= experiment_data.settings.experiment_duration_ms))
        {
            send_data_and_setup_next_experiment();
        }

        mesh_process_commands();

#if TRANSMIT
        if ((power_on_time_msec - mode_start_time)
                > (experiment_data.settings.mesh_tx_period_max_ms ?
                        random(experiment_data.settings.mesh_tx_period_min_ms, experiment_data.settings.mesh_tx_period_max_ms) :
                        experiment_data.settings.mesh_tx_period_min_ms))
        {
            mode_start_time = power_on_time_msec;

            //update the target address
#if ADDRESS_3 || ADDRESS_1              //address 3 or address 1 will send to 2 occasionally
            if (target_address == 2)
            #elif ADDRESS_2             //address 2 will send to address 1 (so will address 3, but that's covered in the 'else' below)
            if (target_address == 1)
#endif
            {
#if ADDRESS_3                           //address 3 needs to switch up and send to 2 instead of 1 at this point.
                target_address = 1;
#if ENABLE_DIAGNOSTIC_LED
                set_led_output(RGB_5, colors + 4);
#endif
#elif ADDRESS_2 || ADDRESS_1            //on module with address 2 at this point, we're sending to 1. on module with address 1, we're sending to 2. in either case, we need to send to 3 on the next iteration.
                target_address = 3;
#if ENABLE_DIAGNOSTIC_LED
                set_led_output(RGB_5, colors + 6);
#endif
#endif
            }
            else
            {
#if ADDRESS_3 || ADDRESS_1              //on module with address 3, we last sent to 1, on module with address 1, we last sent to 3. in both cases, the next address we need to send to is address 2
                target_address = 2;
#if ENABLE_DIAGNOSTIC_LED
                set_led_output(RGB_5, colors + 5);
#endif
#elif ADDRESS_2                         //on module with address 2, we last sent to 3, so we need to send to 1 next.
                target_address = 1;
#if ENABLE_DIAGNOSTIC_LED
                set_led_output(RGB_5, colors + 4);
#endif
#endif
            }

            //read the mpu and prepare the command to be sent
            get_mpu_readings(&local_imu_data);

            uint8_t tx_buf[sizeof(local_imu_data) - 2];
            tx_buf[0] = MESH_CMD_UPDATE_IMU_DATA;

            for (uint32_t i = 0; i < sizeof(local_imu_data) - 4; ++i)
            {
                tx_buf[i + 1] = local_imu_data.bytes[i];
            }

            tx_buf[sizeof(local_imu_data) + 1] = MESH_CMD_TERMINATION;

            //send the message
            tx_start = power_on_time_msec;
            last_tx_return_value = mesh_tx(tx_buf, sizeof(local_imu_data) - 2, target_address);
            tx_time = power_on_time_msec - tx_start;

            //update return value accumulators
            switch (last_tx_return_value)
            {
                case RH_ROUTER_ERROR_NONE:
                    {
#if ENABLE_DIAGNOSTIC_LED
                    set_led_output(RGB_4, colors + 5);
#endif
                    experiment_data.transmit_time_success_total_ms += tx_time;
                    ++experiment_data.ERROR_NONE_count;
                    break;
                }
                case RH_ROUTER_ERROR_INVALID_LENGTH:
                    {
                    ++experiment_data.ERROR_INVALID_LENGTH_count;
                    break;
                }
                case RH_ROUTER_ERROR_NO_ROUTE:
                    {
                    ++experiment_data.ERROR_NO_ROUTE_count;
                    break;
                }
                case RH_ROUTER_ERROR_TIMEOUT:
                    {
                    ++experiment_data.ERROR_TIMEOUT_count;
                    break;
                }
                case RH_ROUTER_ERROR_NO_REPLY:
                    {
                    ++experiment_data.ERROR_NO_REPLY_count;
                    break;
                }
                case RH_ROUTER_ERROR_UNABLE_TO_DELIVER:
                    {
                    ++experiment_data.ERROR_UNABLE_TO_DELIVER_count;
                    break;
                }
                default:
                    {
                    break;
                }
            }

            //increment transmit counter
            ++experiment_data.tx_messages_sent[target_address - 1];
            ++transmissions_sent_for_this_experiment;

            //increment fail counter if necessary
            if (last_tx_return_value > 0)
            {
#if ENABLE_DIAGNOSTIC_LED
                set_led_output(RGB_4, colors + 4);
#endif

                ++(experiment_data.tx_messages_failed[target_address - 1]);
                experiment_data.transmit_time_fail_total_ms += tx_time;
            }

            mode_start_time = power_on_time_msec;
        }
#endif

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

static void update_imu_leds(const mpu_values* remote_imu_data, color_rgb colors[])
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

static void upcount_hb_leds()
{
//    LED1_PutVal(LED1_DeviceData, !(hb_led_count & 0x02));
    LED2_PutVal(LED2_DeviceData, !(hb_led_count & 0x01));
    hb_led_count = (hb_led_count + 1) % 4;
}

static void update_mesh_mode(uint8_t * data, uint8_t len)
{
    if (len < 2) return;

    mesh_mode = data[1];
}

uint8_t derp = 0;

static void mesh_update_imu_leds(uint8_t * data, uint8_t len)
{
    LED1_PutVal(LED1_DeviceData, derp);
    derp = !derp;

    if (data != NULL) return;
    mpu_values * imu_data = &local_imu_data;

    if (imu_data->values.x_accel == 0 && imu_data->values.y_accel == 0 && imu_data->values.z_accel == 0) return;
//    if (len < 6) return;

//    mpu_values * imu_data = (mpu_values*) (data + 1);
    uint32_t x_on_periods = LED_MINIMUM_ON_COUNT + (abs(imu_data->values.x_accel) / 16000.0) * LED_TIME_SEGMENT_COUNT;
    uint32_t y_on_periods = LED_MINIMUM_ON_COUNT + (abs(imu_data->values.y_accel) / 16000.0) * LED_TIME_SEGMENT_COUNT;
    uint32_t z_on_periods = LED_MINIMUM_ON_COUNT + (abs(imu_data->values.z_accel) / 16000.0) * LED_TIME_SEGMENT_COUNT;

    for (int i = 0; i < LED_TIME_SEGMENT_COUNT; ++i)
    {
        LED_IMU_Levels[i].x_on = (i % x_on_periods ? 0 : 1);
        LED_IMU_Levels[i].y_on = (i % y_on_periods ? 0 : 1);
        LED_IMU_Levels[i].z_on = (i % z_on_periods ? 0 : 1);

        if (imu_data->values.x_accel > 0)
        {
            LED_IMU_Levels[i].x_sign = 1;
        }
        else
        {
            LED_IMU_Levels[i].x_sign = 0;
        }

        if (imu_data->values.y_accel > 0)
        {
            LED_IMU_Levels[i].y_sign = 1;
        }
        else
        {
            LED_IMU_Levels[i].y_sign = 0;
        }

        if (imu_data->values.z_accel > 0)
        {
            LED_IMU_Levels[i].z_sign = 1;
        }
        else
        {
            LED_IMU_Levels[i].z_sign = 0;
        }
    }

}

static void update_3LED_imu()
{
    led_time_segment_values v = LED_IMU_Levels[LED_time_segment];
    LED_time_segment = (LED_time_segment + 1) % LED_TIME_SEGMENT_COUNT;
    if (v.x_on)
    {
        if (1 || v.x_sign)
        {
            set_led_output(RGB_4, colors + 4);        //x+
        }
        else
        {
            set_led_output(RGB_4, colors + 5);        //x-
        }
    }
    else
    {
        set_led_output(RGB_4, colors);
    }

    if (v.y_on)
    {
        if (1 || v.y_sign)
        {
            set_led_output(RGB_5, colors + 4);        //y
        }
        else
        {
            set_led_output(RGB_5, colors + 6);        //y
        }
    }
    else
    {
        set_led_output(RGB_5, colors);
    }

    if (v.z_on)
    {
        if (1 || v.z_sign)
        {
            set_led_output(RGB_6, colors + 5);        //z
        }
        else
        {
            set_led_output(RGB_6, colors + 6);        //z
        }
    }
    else
    {
        set_led_output(RGB_6, colors);
    }
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
