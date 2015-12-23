/* ###################################################################
**     Filename    : main.c
**     Project     : clay_g5_demo_gpio
**     Processor   : MK20DX256VLH7
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-09-10, 15:03, # CodeGen: 0
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
#include "LED2.h"
#include "LED1.h"
#include "LED_DRIVER_0_RESET.h"
#include "LED_DRIVER_1_RESET.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  int i;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
//  (void) IO1_Init (NULL);
//  (void) IO2_Init (NULL);
//  (void) IO3_Init (NULL);
//  (void) IO4_Init (NULL);
//  (void) IO5_Init (NULL);
//  (void) IO6_Init (NULL);
//  (void) IO7_Init (NULL);
//  (void) IO8_Init (NULL);
//  (void) IO9_Init (NULL);
//  (void) IO10_Init (NULL);
//  (void) IO11_Init (NULL);
//  (void) IO12_Init (NULL);
  for(;;) {
	  
	  // Turn LED0 on and LED1 off.
	  IO1_PutVal (NULL, TRUE);
	  IO2_PutVal (NULL, TRUE);
	  IO3_PutVal (NULL, TRUE);
	  IO4_PutVal (NULL, TRUE);
	  IO5_PutVal (NULL, TRUE);
	  IO6_PutVal (NULL, TRUE);
	  IO7_PutVal (NULL, TRUE);
	  IO8_PutVal (NULL, TRUE);
	  IO9_PutVal (NULL, TRUE);
	  IO10_PutVal (NULL, TRUE);
	  IO11_PutVal (NULL, TRUE);
	  IO12_PutVal (NULL, TRUE);
	  LED1_PutVal(NULL, TRUE);
	  LED2_PutVal(NULL, FALSE);
	  
//	  for (i = 0; i < 1000000; i++) {}
//	  for (i = 0; i < 1000000; i++) {}
//	  for (i = 0; i < 1000000; i++) {}
	  for (i = 0; i < 1000000; i++) {}
	  
	  // Alternate the state of the LEDs. Turn LED0 off and LED1 on.
	  IO1_PutVal (NULL, FALSE);
	  IO2_PutVal (NULL, FALSE);
	  IO3_PutVal (NULL, FALSE);
	  IO4_PutVal (NULL, FALSE);
	  IO5_PutVal (NULL, FALSE);
	  IO6_PutVal (NULL, FALSE);
	  IO7_PutVal (NULL, FALSE);
	  IO8_PutVal (NULL, FALSE);
	  IO9_PutVal (NULL, FALSE);
	  IO10_PutVal (NULL, FALSE);
	  IO11_PutVal (NULL, FALSE);
	  IO12_PutVal (NULL, FALSE);
	  LED2_PutVal(NULL, TRUE);
	  LED1_PutVal(NULL, FALSE);
//	  for (i = 0; i < 1000000; i++) {}
//	  for (i = 0; i < 1000000; i++) {}
//	  for (i = 0; i < 1000000; i++) {}
	  for (i = 0; i < 1000000; i++) {}
	  
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
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
