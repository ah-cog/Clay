/* ###################################################################
**     Filename    : Events_ESP8266.h
**     Project     : C6_Bringup
**     Processor   : MK64FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-02-06, 19:20, # CodeGen: 43
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         ESP8266_Serial_OnBlockReceived - void ESP8266_Serial_OnBlockReceived(LDD_TUserData *UserDataPtr);
**         ESP8266_Serial_OnBlockSent     - void ESP8266_Serial_OnBlockSent(LDD_TUserData *UserDataPtr);
**
** ###################################################################*/
/*!
** @file Events_ESP8266.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_ESP8266_module Events_ESP8266 module documentation
**  @{
*/         

#ifndef __Events_ESP8266_H
#define __Events_ESP8266_H
/* MODULE Events_ESP8266 */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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
#include "WIFI_RESET.h"
#include "WIFI_CHIP_EN.h"
#include "WIFI_XPD_DCDC.h"
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

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  ESP8266_Serial_OnBlockReceived (module Events_ESP8266)
**
**     Component   :  ESP8266_Serial [Serial_LDD]
*/
/*!
**     @brief
**         This event is called when the requested number of data is
**         moved to the input buffer.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void ESP8266_Serial_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  ESP8266_Serial_OnBlockSent (module Events_ESP8266)
**
**     Component   :  ESP8266_Serial [Serial_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void ESP8266_Serial_OnBlockSent(LDD_TUserData *UserDataPtr);


/* END Events_ESP8266 */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_ESP8266_H*/
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
