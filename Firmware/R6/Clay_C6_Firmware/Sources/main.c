/* ###################################################################
 **     Filename    : main.c
 **     Project     : C6_Bringup
 **     Processor   : MK64FN1M0VLL12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2016-01-26, 22:06, # CodeGen: 0
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
#include "Events_ESP8266.h"
#include "Pins1.h"
#include "LED1.h"
#include "LED2.h"
#include "TI1.h"
#include "TU1.h"
#include "I2C2.h"
#include "LED_SDB.h"
#include "BuzzerOut.h"
#include "BuzzerLine.h"
#include "ButtonIn.h"
#include "MESH_SPI.h"
#include "MESH_CE.h"
#include "MESH_CS.h"
#include "PTC_IRQ.h"
#include "ESP8266_Serial.h"
#include "WIFI_GPIO0.h"
#include "WIFI_GPIO2.h"
#include "WIFI_XPD_DCDC_INTERRUPT.h"
#include "WIFI_RESET.h"
#include "WIFI_CHIP_EN.h"
#include "IMU_FSYNC.h"
#include "FLASH1.h"
#include "IO_1.h"
#include "IO_2.h"
#include "IO_3.h"
#include "IO_4.h"
#include "IO_5.h"
#include "IO_6.h"
#include "IO_7.h"
#include "IO_8.h"
#include "IO_9.h"
#include "IO_10.h"
#include "IO_11.h"
#include "IO_12.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Clay_Core_Hardware.h"
#include "Application.h"
#include "Wifi_Test.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
   /* Write your local variable definition here */

   /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
   PE_low_level_init();
   /*** End of Processor Expert internal initialization.                    ***/

   Wifi_Test();
   Application();

   for (;;)
   {

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
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
