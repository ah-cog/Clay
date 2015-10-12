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

#ifndef SYSTEM_TICK_H_
#include "system_tick.h"
#endif

#ifndef LED_DRIVER_PCA9552_H_
#include "led_driver_pca9552.h"
#endif

#ifndef MPU_9250_DRIVER_H_
#include "mpu_9250_driver.h"
#endif

#ifndef NRF24L01PLUS_H_
#include "nrf24L01plus.h"
#endif

/*lint -save  -e97LED_DRIVER_0 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
    /* Write your local variable definition here */
    bool led_state = FALSE;

    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init();
    /*** End of Processor Expert internal initialization.                    ***/

    /* Write your code here */

    init_tick();
    init_led_drivers();

    mpu_9250_init();

    mpu_values v = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    delay_n_msec(5);

    color_rgb
    colors[] =
            {
                    { LED_MODE_OFF, LED_MODE_OFF, LED_MODE_OFF },        //off
                    { LED_MODE_MED, LED_MODE_MED, LED_MODE_OFF },        //rg
                    { LED_MODE_OFF, LED_MODE_MED, LED_MODE_MED },        //gb
                    { LED_MODE_MED, LED_MODE_OFF, LED_MODE_MED }        //rb
            };


    for (;;)
    {
        if (tick_1msec)
        {
            tick_1msec = FALSE;

            if (!(power_on_time_msec % 30))
            {
                get_mpu_readings(&v);

                if (v.x_accel < 50)
                {
                    set_led_output(RGB_12, colors + 1);        //-x
                    set_led_output(RGB_4, colors + 0);        //+x
                }
                else if (v.x_accel > 50)
                {
                    set_led_output(RGB_12, colors + 0);        //-x
                    set_led_output(RGB_4, colors + 1);        //+x
                }

                if (v.y_accel < 50)
                {
                    set_led_output(RGB_1, colors + 1);        //-y
                    set_led_output(RGB_9, colors + 0);        //+y
                }
                else if (v.y_accel > 50)
                {
                    set_led_output(RGB_1, colors + 0);        //-y
                    set_led_output(RGB_9, colors + 1);        //+y
                }

                if (v.z_accel > 0)        //+z
                {
                    set_led_output(RGB_10, colors + 1);
                    set_led_output(RGB_7, colors + 1);
                    set_led_output(RGB_6, colors + 1);
                    set_led_output(RGB_3, colors + 1);
                }
                else if (v.z_accel < 0)        //-z
                {
                    set_led_output(RGB_10, colors + 3);
                    set_led_output(RGB_7, colors + 3);
                    set_led_output(RGB_6, colors + 3);
                    set_led_output(RGB_3, colors + 3);
                }

                if (abs(v.y_mag) >= abs(v.x_mag))
                {
                    if (v.y_mag > 0)
                    {
                        //strongest magnetic field towards y+
                        set_led_output(RGB_11, colors);              //y-
                        set_led_output(RGB_8, colors);              //x+
                        set_led_output(RGB_5, colors + 1);          //y+
                        set_led_output(RGB_2, colors);             //x-
                    }
                    else
                    {
                        //strongest magnetic field towards y-
                        set_led_output(RGB_11, colors + 1);          //y-
                        set_led_output(RGB_8, colors);              //x+
                        set_led_output(RGB_5, colors);              //y+
                        set_led_output(RGB_2, colors);             //x-
                    }
                }
                else
                {
                    if (v.x_mag > 0)
                    {
                        //strongest magnetic field towards x+
                        set_led_output(RGB_11, colors);              //y-
                        set_led_output(RGB_8, colors + 1);          //x+
                        set_led_output(RGB_5, colors);              //y+
                        set_led_output(RGB_2, colors);             //x-
                    }
                    else
                    {
                        //strongest magnetic field towards x-
                        set_led_output(RGB_11, colors);              //y-
                        set_led_output(RGB_8, colors);              //x+
                        set_led_output(RGB_5, colors);              //y+
                        set_led_output(RGB_2, colors + 1);         //x-
                    }
                }
            }
        }

        if (tick_250msec)
        {
            tick_250msec = FALSE;

        }

        if (tick_500msec)
        {
            tick_500msec = FALSE;

            //toggle LEDs
            LED1_PutVal(LED1_DeviceData, !led_state);
            LED2_PutVal(LED2_DeviceData, led_state);
            led_state = !led_state;
        }

    }

    /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

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
