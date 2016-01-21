/* ###################################################################
 **     Filename    : Events.c
 **     Project     : Clay_5G_Firmware
 **     Processor   : MK20DX256VLH7
 **     Component   : Events
 **     Version     : Driver 01.00
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2015-09-16, 12:30, # CodeGen: 0
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
 ** @version 01.00
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
#include "Events_ESP8266.h"

#include "Application.h"
#include "Drivers/ESP8266.h"
#include "Clock.h"
#include "wirish.h"
#include "Mesh.h"
#include "Drivers/MPU9250.h"

#ifdef __cplusplus
extern "C"
{
#endif 

    /* User includes (#include below this line is not maintained by Processor Expert) */

    /*
     ** ===================================================================
     **     Event       :  Cpu_OnNMIINT (module Events)
     **
     **     Component   :  Cpu [MK20DX256LL7]
     */
    /*!
     **     @brief
     **         This event is called when the Non maskable interrupt had
     **         occurred. This event is automatically enabled when the [NMI
     **         interrupt] property is set to 'Enabled'.
     */
    /* ===================================================================*/
    void Cpu_OnNMIINT(void)
    {
        /* Write your code here ... */
    }

    /*
     ** ===================================================================
     **     Event       :  Timer_1ms_OnInterrupt (module Events)
     **
     **     Component   :  Timer_1ms [TimerInt_LDD]
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
    void Timer_1ms_OnInterrupt(LDD_TUserData *UserDataPtr)
    {
        Tick ();
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
    void I2C0_OnMasterBlockSent(LDD_TUserData *UserDataPtr)
    {
        /* Write your code here ... */
        i2c_tx_complete = TRUE;
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
    void I2C0_OnMasterBlockReceived(LDD_TUserData *UserDataPtr)
    {
        /* Write your code here ... */
        i2c_rx_complete = TRUE;
    }

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
    void MESH_IRQ_OnPortEvent(LDD_TUserData *UserDataPtr)
    {
        /* Write your code here ... */
        if (mesh_rx_enabled)
        {
            mesh_irq_handler();
        }
    }

    /*
     ** ===================================================================
     **     Event       :  SM1_OnBlockSent (module Events)
     **
     **     Component   :  SM1 [SPIMaster_LDD]
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
    void SM1_OnBlockSent(LDD_TUserData *UserDataPtr)
    {
        /* Write your code here ... */
    }

    /*
     ** ===================================================================
     **     Event       :  SM1_OnBlockReceived (module Events)
     **
     **     Component   :  SM1 [SPIMaster_LDD]
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
    void SM1_OnBlockReceived(LDD_TUserData *UserDataPtr)
    {
        /* Write your code here ... */
    }

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
void IMU_IRQ_OnPortEvent(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
    data_ready = 1;
}

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
void FLASH1_OnOperationComplete(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
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
 **     This file was created by Processor Expert 10.3 [05.09]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
