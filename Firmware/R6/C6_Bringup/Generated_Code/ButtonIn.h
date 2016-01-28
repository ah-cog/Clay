/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : ButtonIn.h
**     Project     : C6_Bringup
**     Processor   : MK64FN1M0VLL12
**     Component   : GPIO_LDD
**     Version     : Component 01.128, Driver 01.08, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-01-27, 21:56, # CodeGen: 11
**     Abstract    :
**         The HAL GPIO component will provide a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL GPIO API will be simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : ButtonIn
**          Port                                           : PTB
**          Port width                                     : 32 bits
**          Mask of allocated pins                         : 0x200
**          Interrupt service/event                        : Enabled
**            Interrupt                                    : INT_PORTB
**            Interrupt priority                           : medium priority
**          Bit fields                                     : 1
**            Bit field                                    : 
**              Field name                                 : Button
**              Pins                                       : 1
**                Pin                                      : 
**                  Pin                                    : PTB9/SPI1_PCS1/UART3_CTS_b/FB_AD20
**                  Initial pin direction                  : Input
**                  Initial pin event                      : Falling edge
**                  Lock initialization function           : no
**          Initialization                                 : 
**            Auto initialization                          : yes
**            Event mask                                   : 
**              OnPortEvent                                : Enabled
**     Contents    :
**         Init            - LDD_TDeviceData* ButtonIn_Init(LDD_TUserData *UserDataPtr);
**         SetFieldValue   - void ButtonIn_SetFieldValue(LDD_TDeviceData *DeviceDataPtr,...
**         GetFieldValue   - ButtonIn_TFieldValue ButtonIn_GetFieldValue(LDD_TDeviceData *DeviceDataPtr,...
**         ClearFieldBits  - void ButtonIn_ClearFieldBits(LDD_TDeviceData *DeviceDataPtr,...
**         SetFieldBits    - void ButtonIn_SetFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField...
**         ToggleFieldBits - void ButtonIn_ToggleFieldBits(LDD_TDeviceData *DeviceDataPtr,...
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file ButtonIn.h
** @version 01.08
** @brief
**         The HAL GPIO component will provide a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL GPIO API will be simpler and more
**         portable to various microprocessors.
*/         
/*!
**  @addtogroup ButtonIn_module ButtonIn module documentation
**  @{
*/         

#ifndef __ButtonIn_H
#define __ButtonIn_H

/* MODULE ButtonIn. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "IO_Map.h"
#include "GPIO_PDD.h"
#include "PORT_PDD.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 


/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define ButtonIn_PRPH_BASE_ADDRESS  0x400FF040U
  
/*! Device data structure pointer used when auto initialization property is enabled. This constant can be passed as a first parameter to all component's methods. */
#define ButtonIn_DeviceData  ((LDD_TDeviceData *)PE_LDD_GetDeviceStructure(PE_LDD_COMPONENT_ButtonIn_ID))

/* Methods configuration constants - generated for all enabled component's methods */
#define ButtonIn_Init_METHOD_ENABLED   /*!< Init method of the component ButtonIn is enabled (generated) */
#define ButtonIn_SetFieldValue_METHOD_ENABLED /*!< SetFieldValue method of the component ButtonIn is enabled (generated) */
#define ButtonIn_GetFieldValue_METHOD_ENABLED /*!< GetFieldValue method of the component ButtonIn is enabled (generated) */
#define ButtonIn_ClearFieldBits_METHOD_ENABLED /*!< ClearFieldBits method of the component ButtonIn is enabled (generated) */
#define ButtonIn_SetFieldBits_METHOD_ENABLED /*!< SetFieldBits method of the component ButtonIn is enabled (generated) */
#define ButtonIn_ToggleFieldBits_METHOD_ENABLED /*!< ToggleFieldBits method of the component ButtonIn is enabled (generated) */

/* Events configuration constants - generated for all enabled component's events */
#define ButtonIn_OnPortEvent_EVENT_ENABLED /*!< OnPortEvent event of the component ButtonIn is enabled (generated) */

/* Definition of bit field constants */
#define Button ((LDD_GPIO_TBitField)0)

/* Definition of implementation constants */
#define ButtonIn_ALLOCATED_PINS_MASK 0x0200U /*!< Mask of all allocated pins from the port */
#define ButtonIn_MODULE_BASE_ADDRESS PTB_BASE_PTR /*!< Name of macro used as the base address */
#define ButtonIn_PORTCONTROL_BASE_ADDRESS PORTB_BASE_PTR /*!< Name of macro used as the base address */
#define ButtonIn_AVAILABLE_EVENTS_MASK LDD_GPIO_ON_PORT_EVENT /*!< Mask of all available events */
#define ButtonIn_FIELD_0_PIN_0 LDD_GPIO_PIN_9 /*!< Constant for the pin in the field used in the method ConnectPin */
#define ButtonIn_Button_START_BIT 9u   /*!< Index of the starting bit of the bit field (0 represents LSB) */
#define ButtonIn_Button_MASK 0x0200u   /*!< Mask of the bits allocated by the bit field (within the port) */
/* Representation of unaligned data value of the port.
   Unsigned integer of proper width depending on the size of the GPIO port allocated.
   Typically the value of n-th bit represents the data for the n-th pin within the port.
   Such value is not abstracted from the physical position of the bits within the port. */
typedef uint32_t ButtonIn_TPortValue;

/* Representation of right-aligned data value of the bit field.
   Typically the value of n-th bit represents the data of the n-th bit within the bit field (not within the port).
   There are used only so many lowest bits, as it is denoted by the width of the bit field.
   Such value is abstracted from the physical position of the bit field pins within the port.
   Equals to the type <compId>_TPortValue. */
typedef ButtonIn_TPortValue ButtonIn_TFieldValue;



/*
** ===================================================================
**     Method      :  ButtonIn_Init (component GPIO_LDD)
*/
/*!
**     @brief
**         This method initializes the associated peripheral(s) and the
**         component internal variables. The method is called
**         automatically as a part of the application initialization
**         code.
**     @param
**         UserDataPtr     - Pointer to the RTOS device
**                           structure. This pointer will be passed to
**                           all events as parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* ButtonIn_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  ButtonIn_SetFieldValue (component GPIO_LDD)
*/
/*!
**     @brief
**         This method sets the output data value of the specified bit
**         field.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to write. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @param
**         Value           - Aligned data value to writting to the
**                           specified bit field. The bit 0 corresponds
**                           with the pin which has index 0 within the
**                           given bit field, the bit 1 corresponds with
**                           the pin which has index 1 within the given
**                           bit field, etc.
*/
/* ===================================================================*/
void ButtonIn_SetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, ButtonIn_TFieldValue Value);

/*
** ===================================================================
**     Method      :  ButtonIn_GetFieldValue (component GPIO_LDD)
*/
/*!
**     @brief
**         This method returns the current input data of the specified
**         field.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to reading. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @return
**                         - Aligned current port input value masked for
**                           allocated pins of the field. The bit 0
**                           corresponds with the pin which has index 0
**                           within the given bit field, the bit 1
**                           corresponds with the pin which has index 1
**                           within the given bit field, etc.
*/
/* ===================================================================*/
ButtonIn_TFieldValue ButtonIn_GetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field);

/*
** ===================================================================
**     Method      :  ButtonIn_ClearFieldBits (component GPIO_LDD)
*/
/*!
**     @brief
**         This method drives the specified bits of the specified bit
**         field to the inactive level.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to write. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @param
**         Mask            - Aligned mask of bits to setting the
**                           inactive level. Each field pin has
**                           corresponding bit in the mask. Bit value 0
**                           means not selected bit, bit value 1 means
**                           selected bit. The bit 0 corresponds with
**                           the pin which has index 0 within the given
**                           bit field, the bit 1 corresponds with the
**                           pin which has index 1 within the given bit
**                           field, etc.
*/
/* ===================================================================*/
void ButtonIn_ClearFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, ButtonIn_TFieldValue Mask);

/*
** ===================================================================
**     Method      :  ButtonIn_SetFieldBits (component GPIO_LDD)
*/
/*!
**     @brief
**         This method drives the specified bits of the specified bit
**         field to the active level.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to write. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @param
**         Mask            - Aligned mask of bits to setting the
**                           active level. Each field pin has
**                           corresponding bit in the mask. Bit value 0
**                           means not selected bit, bit value 1 means
**                           selected bit. The bit 0 corresponds with
**                           the pin which has index 0 within the given
**                           bit field, the bit 1 corresponds with the
**                           pin which has index 1 within the given bit
**                           field, etc.
*/
/* ===================================================================*/
void ButtonIn_SetFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, ButtonIn_TFieldValue Mask);

/*
** ===================================================================
**     Method      :  ButtonIn_ToggleFieldBits (component GPIO_LDD)
*/
/*!
**     @brief
**         This method inverts the specified bits of the specified bit
**         field to other level.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to write. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @param
**         Mask            - Aligned mask of bits to inverting the
**                           current level. Each field pin has
**                           corresponding bit in the mask. Bit value 0
**                           means not selected bit, bit value 1 means
**                           selected bit. The bit 0 corresponds with
**                           the pin which has index 0 within the given
**                           bit field, the bit 1 corresponds with the
**                           pin which has index 1 within the given bit
**                           field, etc.
*/
/* ===================================================================*/
void ButtonIn_ToggleFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, ButtonIn_TFieldValue Mask);

/*
** ===================================================================
**     Method      :  ButtonIn_Interrupt (component GPIO_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
/* {Default RTOS Adapter} ISR function prototype */
PE_ISR(ButtonIn_Interrupt);

/* END ButtonIn. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif
/* ifndef __ButtonIn_H */
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
