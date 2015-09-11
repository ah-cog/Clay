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
#include "LED_DRIVER_0_RESET.h"
#include "LED_DRIVER_1_RESET.h"
#include "I2C0.h"
#include "tick_1ms_timer.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "system_tick.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e97LED_DRIVER_0 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	int i;
	bool led_state = FALSE;

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */

	init_tick();
	
	for (;;) {

		if(tick_1msec)
		{
			tick_1msec = FALSE;
			
		}
		if(tick_250msec)
		{
			tick_250msec = FALSE;
			
		}
		if(tick_500msec)
		{
			tick_500msec = FALSE;
			
			//toggle LEDs
			LED1_PutVal(NULL, !led_state);
			LED2_PutVal(NULL, led_state);
			led_state = !led_state;
		}
		
		
		/*
		IO1_PutVal(NULL, TRUE);
		IO2_PutVal(NULL, TRUE);
		IO3_PutVal(NULL, TRUE);
		IO4_PutVal(NULL, TRUE);
		IO5_PutVal(NULL, TRUE);
		IO6_PutVal(NULL, TRUE);
		IO7_PutVal(NULL, TRUE);
		IO8_PutVal(NULL, TRUE);
		IO9_PutVal(NULL, TRUE);
		IO10_PutVal(NULL, TRUE);
		IO11_PutVal(NULL, TRUE);
		IO12_PutVal(NULL, TRUE);
		LED1_PutVal(NULL, TRUE);
		LED2_PutVal(NULL, FALSE);

		for (i = 0; i < 1000000; i++) {
		}

		IO1_PutVal(NULL, FALSE);
		IO2_PutVal(NULL, FALSE);
		IO3_PutVal(NULL, FALSE);
		IO4_PutVal(NULL, FALSE);
		IO5_PutVal(NULL, FALSE);
		IO6_PutVal(NULL, FALSE);
		IO7_PutVal(NULL, FALSE);
		IO8_PutVal(NULL, FALSE);
		IO9_PutVal(NULL, FALSE);
		IO10_PutVal(NULL, FALSE);
		IO11_PutVal(NULL, FALSE);
		IO12_PutVal(NULL, FALSE);
		LED2_PutVal(NULL, TRUE);
		LED1_PutVal(NULL, FALSE);

		for (i = 0; i < 1000000; i++) {
		*/
		

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
