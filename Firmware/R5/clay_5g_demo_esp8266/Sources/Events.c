/* ###################################################################
**     Filename    : Events.c
**     Project     : clay_5g_demo_esp8266
**     Processor   : MK20DX256VLH7
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-09-14, 14:01, # CodeGen: 0
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

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"
#include "Drivers/ESP8266.h"
#include "Clock.h"

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

	(void) ptr->rxPutFct (ptr->rxChar);
	(void) ESP8266_Serial_ReceiveBlock (ptr->handle, (LDD_TData *) &ptr->rxChar, sizeof (ptr->rxChar));
	
	if (Ring_Buffer_NofElements () > 500) {
		printf ("Ring_Buffer_NofElements: %d\r\n", Ring_Buffer_NofElements ());
	}
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
	
//	printf ("sent byte: %s\r\n", UserDataPtr);
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

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
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
