/* ###################################################################
 **     Filename    : Events.c
 **     Project     : clay_g5_demo_gpio
 **     Processor   : MK2LED_DRIVER_0DX256VLH7
 **     Component   : Events
 **     Version     : Driver LED_DRIVER_01.LED_DRIVER_0LED_DRIVER_0
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2LED_DRIVER_015-LED_DRIVER_09-1LED_DRIVER_0, 15:LED_DRIVER_03, # CodeGen: LED_DRIVER_0
 **     Abstract    :
 **         This is user's event module.
 **         Put your event handler code here.
 **     Settings    :
 **     Contents    :
 **         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
 **
 ** ###################################################################*/
/*!
 ** @file Events.c
 ** @version LED_DRIVER_01.LED_DRIVER_0LED_DRIVER_0
 ** @brief
 **         This is user's event module.
 **         Put your event handler code here.
 */
/*!
 **  @addtogroup Events_module Events module documentation
 **  @{
 */
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 

/* User includes (#include below this line is not maintained by Processor Expert) */
#ifndef SYSTEM_TICK_H_
#include "system_tick.h"
#endif

/*
 ** ===================================================================
 **     Event       :  Cpu_OnNMIINT (module Events)
 **
 **     Component   :  Cpu [MK2LED_DRIVER_0DX256LL7]
 */
/*!
 **     @brief
 **         This event is called when the Non maskable interrupt had
 **         occurred. This event is automatically enabled when the [NMI
 **         interrupt] property is set to 'Enabled'.
 */
/* ===================================================================*/
void Cpu_OnNMIINT(void) {
	/* Write your code here ... */
}


/*
 ** ===================================================================
 **     Event       :  I2C0_OnMasterBlockSent (module Events)
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
void I2C0_OnMasterBlockSent(LDD_TUserData *UserDataPtr) {
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  I2C0_OnMasterBlockReceived (module Events)
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
void I2C0_OnMasterBlockReceived(LDD_TUserData *UserDataPtr) {
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  tick_1ms_timer_OnInterrupt (module Events)
 **
 **     Component   :  tick_1ms_timer [TimerInt_LDD]
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
void tick_1ms_timer_OnInterrupt(LDD_TUserData *UserDataPtr) {
	/* Write your code here ... */
	tick();
}

/*
** ===================================================================
**     Event       :  I2C0_OnMasterByteReceived (module Events)
**
**     Component   :  I2C0 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when I2C is in master mode and finishes
**         the reception of the byte successfully. This event is not
**         available for the SLAVE mode and if MasterReceiveBlock is
**         disabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C0_OnMasterByteReceived(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
    I2C0_SendAcknowledge(I2C0_DeviceData,LDD_I2C_ACK_BYTE);
}

/*
** ===================================================================
**     Event       :  RF1_OnInterrupt (module Events)
**
**     Component   :  RF1 [nRF24L01]
**     Description :
**         Called in case of an interrupt from the transcevier
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RF1_OnInterrupt(void)
{
  /* write your code here */
}

/* END Events */

#ifdef __cplusplus
} /* extern "C" */
#endif 

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
