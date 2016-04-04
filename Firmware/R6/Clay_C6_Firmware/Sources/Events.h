/* ###################################################################
 **     Filename    : Events.h
 **     Project     : C6_Bringup
 **     Processor   : MK64FN1M0VLL12
 **     Component   : Events
 **     Version     : Driver 01.00
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2016-01-26, 22:06, # CodeGen: 0
 **     Abstract    :
 **         This is user's event module.
 **         Put your event handler code here.
 **     Contents    :
 **         Cpu_OnNMI - void Cpu_OnNMI(void);
 **
 ** ###################################################################*/
/*!
 ** @file Events.h
 ** @version 01.00
 ** @brief
 **         This is user's event module.
 **         Put your event handler code here.
 */
/*!
 **  @addtogroup Events_module Events module documentation
 **  @{
 */

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Pins1.h"
#include "LED1.h"
#include "LED2.h"
#include "TI1.h"
#include "TU1.h"
#include "I2C0.h"
#include "LED_SDB.h"
#include "ADC0.h"
#include "BUTTON_IN.h"
#include "MESH_SPI.h"
#include "MESH_CE.h"
#include "MESH_CS.h"
#include "MESH_IRQ.h"
#include "ESP8266_Serial.h"
#include "WIFI_GPIO0.h"
#include "WIFI_GPIO2.h"
#include "WIFI_XPD_DCDC_INTERRUPT.h"
#include "WIFI_RESET.h"
#include "WIFI_CHIP_EN.h"
#include "IMU_FSYNC.h"
#include "IMU_IRQ.h"
#include "FLASH1.h"
#include "BUZZER_PWM.h"
#include "GPIO_PTB.h"
#include "GPIO_PTD.h"
#include "GPIO_PTC.h"
#include "GPIO_PTE.h"
#include "ADC1.h"
#include "PWM_OUT_1.h"

#include "PowerOn.h"
#include "Buzzer.h"

#ifdef __cplusplus
extern "C"
{
#endif 

extern volatile bool ButtonPressed;

/*
 ** ===================================================================
 **     Event       :  TI1_OnInterrupt (module Events)
 **
 **     Component   :  TI1 [TimerInt_LDD]
 */
/*!
 **     @brief
 **         Called if periodic event occur. Component and OnInterrupt
 **         event must be enabled. See [SetEventMask] and [GetEventMask]
 **         methods. This event is available only if a [Interrupt
 **         service/event] is enabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. The pointer passed as
 **                           the parameter of Init method.
 */
/* ===================================================================*/
void TI1_OnInterrupt(LDD_TUserData *UserDataPtr);

/*
 ** ===================================================================
 **     Event       :  I2C2_OnMasterBlockSent (module Events)
 **
 **     Component   :  I2C0 [I2C_LDD]
 */
/*!
 **     @brief
 **         This event is called when I2C in master mode finishes the
 **         transmission of the data successfully. This event is not
 **         available for the SLAVE mode and if MasterSendBlock is
 **         disabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void I2C2_OnMasterBlockSent(LDD_TUserData *UserDataPtr);

/*
 ** ===================================================================
 **     Event       :  I2C2_OnMasterBlockReceived (module Events)
 **
 **     Component   :  I2C0 [I2C_LDD]
 */
/*!
 **     @brief
 **         This event is called when I2C is in master mode and finishes
 **         the reception of the data successfully. This event is not
 **         available for the SLAVE mode and if MasterReceiveBlock is
 **         disabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void I2C2_OnMasterBlockReceived(LDD_TUserData *UserDataPtr);

/*
 ** ===================================================================
 **     Event       :  BUTTON_IN_OnPortEvent (module Events)
 **
 **     Component   :  BUTTON_IN [GPIO_LDD]
 */
/*!
 **     @brief
 **         Called if defined event on any pin of the port occured.
 **         OnPortEvent event and GPIO interrupt must be enabled. See
 **         SetEventMask() and GetEventMask() methods. This event is
 **         enabled if [Interrupt service/event] is Enabled and disabled
 **         if [Interrupt service/event] is Disabled.
 **     @param
 **         UserDataPtr     - Pointer to RTOS device
 **                           data structure pointer.
 */
/* ===================================================================*/
void BUTTON_IN_OnPortEvent(LDD_TUserData *UserDataPtr);

/*
 ** ===================================================================
 **     Event       :  ESP8266_Serial_OnBlockReceived (module Events)
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
 **     Event       :  ESP8266_Serial_OnBlockSent (module Events)
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

/*
 ** ===================================================================
 **     Event       :  MESH_IRQ_OnPortEvent (module Events)
 **
 **     Component   :  MESH_IRQ [GPIO_LDD]
 */
/*!
 **     @brief
 **         Called if defined event on any pin of the port occured.
 **         OnPortEvent event and GPIO interrupt must be enabled. See
 **         SetEventMask() and GetEventMask() methods. This event is
 **         enabled if [Interrupt service/event] is Enabled and disabled
 **         if [Interrupt service/event] is Disabled.
 **     @param
 **         UserDataPtr     - Pointer to RTOS device
 **                           data structure pointer.
 */
/* ===================================================================*/
void MESH_IRQ_OnPortEvent(LDD_TUserData *UserDataPtr);

/*
 ** ===================================================================
 **     Event       :  MESH_SPI_OnBlockSent (module Events)
 **
 **     Component   :  MESH_SPI [SPIMaster_LDD]
 */
/*!
 **     @brief
 **         This event is called after the last character from the
 **         output buffer is moved to the transmitter. This event is
 **         available only if the SendBlock method is enabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. The pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void MESH_SPI_OnBlockSent(LDD_TUserData *UserDataPtr);

/*
 ** ===================================================================
 **     Event       :  MESH_SPI_OnBlockReceived (module Events)
 **
 **     Component   :  MESH_SPI [SPIMaster_LDD]
 */
/*!
 **     @brief
 **         This event is called when the requested number of data is
 **         moved to the input buffer. This method is available only if
 **         the ReceiveBlock method is enabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. The pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void MESH_SPI_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
 ** ===================================================================
 **     Event       :  Cpu_OnNMI (module Events)
 **
 **     Component   :  Cpu [MK64FN1M0LL12]
 */
/*!
 **     @brief
 **         This event is called when the Non maskable interrupt had
 **         occurred. This event is automatically enabled when the [NMI
 **         interrupt] property is set to 'Enabled'.
 */
/* ===================================================================*/
void Cpu_OnNMI(void);

/*
 ** ===================================================================
 **     Event       :  FLASH1_OnOperationComplete (module Events)
 **
 **     Component   :  FLASH1 [FLASH_LDD]
 */
/*!
 **     @brief
 **         Called at the end of the whole write / erase operation. if
 **         the event is enabled. See SetEventMask() and GetEventMask()
 **         methods.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void FLASH1_OnOperationComplete(LDD_TUserData *UserDataPtr);

/*
 ** ===================================================================
 **     Event       :  WIFI_GPIO0_OnPortEvent (module Events)
 **
 **     Component   :  WIFI_GPIO0 [GPIO_LDD]
 */
/*!
 **     @brief
 **         Called if defined event on any pin of the port occured.
 **         OnPortEvent event and GPIO interrupt must be enabled. See
 **         SetEventMask() and GetEventMask() methods. This event is
 **         enabled if [Interrupt service/event] is Enabled and disabled
 **         if [Interrupt service/event] is Disabled.
 **     @param
 **         UserDataPtr     - Pointer to RTOS device
 **                           data structure pointer.
 */
/* ===================================================================*/
void WIFI_GPIO0_OnPortEvent(LDD_TUserData *UserDataPtr);

/*
 ** ===================================================================
 **     Event       :  WIFI_XPD_DCDC_INTERRUPT_OnPortEvent (module Events)
 **
 **     Component   :  WIFI_XPD_DCDC_INTERRUPT [GPIO_LDD]
 */
/*!
 **     @brief
 **         Called if defined event on any pin of the port occured.
 **         OnPortEvent event and GPIO interrupt must be enabled. See
 **         SetEventMask() and GetEventMask() methods. This event is
 **         enabled if [Interrupt service/event] is Enabled and disabled
 **         if [Interrupt service/event] is Disabled.
 **     @param
 **         UserDataPtr     - Pointer to RTOS device
 **                           data structure pointer.
 */
/* ===================================================================*/
void WIFI_XPD_DCDC_INTERRUPT_OnPortEvent(LDD_TUserData *UserDataPtr);

/*
 ** ===================================================================
 **     Event       :  IMU_IRQ_OnPortEvent (module Events)
 **
 **     Component   :  IMU_IRQ [GPIO_LDD]
 */
/*!
 **     @brief
 **         Called if defined event on any pin of the port occured.
 **         OnPortEvent event and GPIO interrupt must be enabled. See
 **         SetEventMask() and GetEventMask() methods. This event is
 **         enabled if [Interrupt service/event] is Enabled and disabled
 **         if [Interrupt service/event] is Disabled.
 **     @param
 **         UserDataPtr     - Pointer to RTOS device
 **                           data structure pointer.
 */
/* ===================================================================*/
void IMU_IRQ_OnPortEvent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  GPIO_PTE_OnPortEvent (module Events)
**
**     Component   :  GPIO_PTE [GPIO_LDD]
*/
/*!
**     @brief
**         Called if defined event on any pin of the port occured.
**         OnPortEvent event and GPIO interrupt must be enabled. See
**         SetEventMask() and GetEventMask() methods. This event is
**         enabled if [Interrupt service/event] is Enabled and disabled
**         if [Interrupt service/event] is Disabled.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void GPIO_PTE_OnPortEvent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  GPIO_PTC_OnPortEvent (module Events)
**
**     Component   :  GPIO_PTC [GPIO_LDD]
*/
/*!
**     @brief
**         Called if defined event on any pin of the port occured.
**         OnPortEvent event and GPIO interrupt must be enabled. See
**         SetEventMask() and GetEventMask() methods. This event is
**         enabled if [Interrupt service/event] is Enabled and disabled
**         if [Interrupt service/event] is Disabled.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void GPIO_PTC_OnPortEvent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  GPIO_PTD_OnPortEvent (module Events)
**
**     Component   :  GPIO_PTD [GPIO_LDD]
*/
/*!
**     @brief
**         Called if defined event on any pin of the port occured.
**         OnPortEvent event and GPIO interrupt must be enabled. See
**         SetEventMask() and GetEventMask() methods. This event is
**         enabled if [Interrupt service/event] is Enabled and disabled
**         if [Interrupt service/event] is Disabled.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void GPIO_PTD_OnPortEvent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  GPIO_PTB_OnPortEvent (module Events)
**
**     Component   :  GPIO_PTB [GPIO_LDD]
*/
/*!
**     @brief
**         Called if defined event on any pin of the port occured.
**         OnPortEvent event and GPIO interrupt must be enabled. See
**         SetEventMask() and GetEventMask() methods. This event is
**         enabled if [Interrupt service/event] is Enabled and disabled
**         if [Interrupt service/event] is Disabled.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void GPIO_PTB_OnPortEvent(LDD_TUserData *UserDataPtr);

/* END Events */

#ifdef __cplusplus
} /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
