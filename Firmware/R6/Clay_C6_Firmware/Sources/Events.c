/* ###################################################################
 **     Filename    : Events.c
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
#include "Init_Config.h"
#include "PDD_Includes.h"

#include "Clock.h"
#include "Mesh.h"
#include "I2C.h"
#include "MPU9250.h"
#include "WiFi.h"

FREQ_OUT SelectedFreq = f_Off;
volatile bool ButtonPressed = FALSE;

#ifdef __cplusplus
extern "C"
{
#endif 

/* User includes (#include below this line is not maintained by Processor Expert) */

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
void TI1_OnInterrupt(LDD_TUserData *UserDataPtr)
{
   /* Write your code here ... */

   Tick();
}

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
void I2C2_OnMasterBlockSent(LDD_TUserData *UserDataPtr)
{
   /* Write your code here ... */
   i2c_tx_complete = TRUE;
}

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
void I2C2_OnMasterBlockReceived(LDD_TUserData *UserDataPtr)
{
   /* Write your code here ... */
   i2c_rx_complete = TRUE;
}

/*
 ** ===================================================================
 **     Event       :  ButtonIn_OnPortEvent (module Events)
 **
 **     Component   :  ButtonIn [GPIO_LDD]
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
void ButtonIn_OnPortEvent(LDD_TUserData *UserDataPtr)
{
   /* Write your code here ... */
   ButtonPressed = !ButtonPressed;
   WifiSetProgramMode = TRUE;

   if (ButtonPressed)
   {
      SelectedFreq = (SelectedFreq + 1) % (f_Off + 1);
   }
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
   if (MeshRxEnabled)
   {
      Mesh_Irq_Handler();
   }
}

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
void MESH_SPI_OnBlockSent(LDD_TUserData *UserDataPtr)
{
   /* Write your code here ... */
}

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
void MESH_SPI_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
   /* Write your code here ... */
}

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
void Cpu_OnNMI(void)
{
   /* Write your code here ... */
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
void WIFI_XPD_DCDC_INTERRUPT_OnPortEvent(LDD_TUserData *UserDataPtr)
{
   /* Write your code here ... */
   WifiInterruptReceived = TRUE;
}

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
void ESP8266_Serial_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
   ESP8266_UART_Device *ptr = (ESP8266_UART_Device*) UserDataPtr;

   (void) ESP8266_Serial_ReceiveBlock(ptr->handle, (LDD_TData *) &ptr->rxChar, sizeof(ptr->rxChar));
   (void) ptr->rxPutFct(ptr->rxChar);
}

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
void ESP8266_Serial_OnBlockSent(LDD_TUserData *UserDataPtr)
{
   ESP8266_UART_Device *ptr = (ESP8266_UART_Device*) UserDataPtr;
   ptr->isSent = TRUE;
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
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
