/** ###################################################################
**      Filename    : Vectors_Config.h
**      Processor   : MK64FN1M0VLL12
**      Version     : 1.00
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
** @file Vectors_Config.h                                                  
** @version 01.00
*/         
/*!
**  @addtogroup Vectors_Config_module Vectors_Config module documentation
**  @{
*/         

#ifndef __Vectors_Config_H
#define __Vectors_Config_H

/* MODULE Vectors_Config.h */
  
#include "Cpu.h"
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
#include "Events.h"
#include "Events_ESP8266.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PEX_VECTOR_TABLE                                   0x01U     /* Vector table is managed by PEx */ 

/* Vector                 Address                                  No.  Pri  Name                           Description */
#define VECTOR_SP_MAIN    &__SP_INIT                            /* 0x00 -    ivINT_Initial_Stack_Pointer    used by PE */
#define VECTOR_1          (tIsrFunc)&__thumb_startup            /* 0x01 -    ivINT_Initial_Program_Counter  used by PE */
#define VECTOR_2          (tIsrFunc)&Cpu_INT_NMIInterrupt       /* 0x02 -2   ivINT_NMI                      used by PE */
#define VECTOR_3          (tIsrFunc)&Unhandled_ivINT_Hard_Fault /* 0x03 -1   ivINT_Hard_Fault               unused by PE */
#define VECTOR_4          (tIsrFunc)&Unhandled_ivINT_Mem_Manage_Fault /* 0x04 - ivINT_Mem_Manage_Fault      unused by PE */
#define VECTOR_5          (tIsrFunc)&Unhandled_ivINT_Bus_Fault  /* 0x05 -    ivINT_Bus_Fault                unused by PE */
#define VECTOR_6          (tIsrFunc)&Unhandled_ivINT_Usage_Fault /* 0x06 -   ivINT_Usage_Fault              unused by PE */
#define VECTOR_7          (tIsrFunc)&Unhandled_ivINT_Reserved7  /* 0x07 -    ivINT_Reserved7                unused by PE */
#define VECTOR_8          (tIsrFunc)&Unhandled_ivINT_Reserved8  /* 0x08 -    ivINT_Reserved8                unused by PE */
#define VECTOR_9          (tIsrFunc)&Unhandled_ivINT_Reserved9  /* 0x09 -    ivINT_Reserved9                unused by PE */
#define VECTOR_10         (tIsrFunc)&Unhandled_ivINT_Reserved10 /* 0x0A -    ivINT_Reserved10               unused by PE */
#define VECTOR_11         (tIsrFunc)&Unhandled_ivINT_SVCall     /* 0x0B -    ivINT_SVCall                   unused by PE */
#define VECTOR_12         (tIsrFunc)&Unhandled_ivINT_DebugMonitor /* 0x0C -  ivINT_DebugMonitor             unused by PE */
#define VECTOR_13         (tIsrFunc)&Unhandled_ivINT_Reserved13 /* 0x0D -    ivINT_Reserved13               unused by PE */
#define VECTOR_14         (tIsrFunc)&Unhandled_ivINT_PendableSrvReq /* 0x0E - ivINT_PendableSrvReq          unused by PE */
#define VECTOR_15         (tIsrFunc)&Unhandled_ivINT_SysTick    /* 0x0F -    ivINT_SysTick                  unused by PE */
#define VECTOR_16         (tIsrFunc)&Unhandled_ivINT_DMA0       /* 0x10 -    ivINT_DMA0                     unused by PE */
#define VECTOR_17         (tIsrFunc)&Unhandled_ivINT_DMA1       /* 0x11 -    ivINT_DMA1                     unused by PE */
#define VECTOR_18         (tIsrFunc)&Unhandled_ivINT_DMA2       /* 0x12 -    ivINT_DMA2                     unused by PE */
#define VECTOR_19         (tIsrFunc)&Unhandled_ivINT_DMA3       /* 0x13 -    ivINT_DMA3                     unused by PE */
#define VECTOR_20         (tIsrFunc)&Unhandled_ivINT_DMA4       /* 0x14 -    ivINT_DMA4                     unused by PE */
#define VECTOR_21         (tIsrFunc)&Unhandled_ivINT_DMA5       /* 0x15 -    ivINT_DMA5                     unused by PE */
#define VECTOR_22         (tIsrFunc)&Unhandled_ivINT_DMA6       /* 0x16 -    ivINT_DMA6                     unused by PE */
#define VECTOR_23         (tIsrFunc)&Unhandled_ivINT_DMA7       /* 0x17 -    ivINT_DMA7                     unused by PE */
#define VECTOR_24         (tIsrFunc)&Unhandled_ivINT_DMA8       /* 0x18 -    ivINT_DMA8                     unused by PE */
#define VECTOR_25         (tIsrFunc)&Unhandled_ivINT_DMA9       /* 0x19 -    ivINT_DMA9                     unused by PE */
#define VECTOR_26         (tIsrFunc)&Unhandled_ivINT_DMA10      /* 0x1A -    ivINT_DMA10                    unused by PE */
#define VECTOR_27         (tIsrFunc)&Unhandled_ivINT_DMA11      /* 0x1B -    ivINT_DMA11                    unused by PE */
#define VECTOR_28         (tIsrFunc)&Unhandled_ivINT_DMA12      /* 0x1C -    ivINT_DMA12                    unused by PE */
#define VECTOR_29         (tIsrFunc)&Unhandled_ivINT_DMA13      /* 0x1D -    ivINT_DMA13                    unused by PE */
#define VECTOR_30         (tIsrFunc)&Unhandled_ivINT_DMA14      /* 0x1E -    ivINT_DMA14                    unused by PE */
#define VECTOR_31         (tIsrFunc)&Unhandled_ivINT_DMA15      /* 0x1F -    ivINT_DMA15                    unused by PE */
#define VECTOR_32         (tIsrFunc)&Unhandled_ivINT_DMA_Error  /* 0x20 -    ivINT_DMA_Error                unused by PE */
#define VECTOR_33         (tIsrFunc)&Unhandled_ivINT_MCM        /* 0x21 -    ivINT_MCM                      unused by PE */
#define VECTOR_34         (tIsrFunc)&Unhandled_ivINT_FTFE       /* 0x22 -    ivINT_FTFE                     unused by PE */
#define VECTOR_35         (tIsrFunc)&Unhandled_ivINT_Read_Collision /* 0x23 - ivINT_Read_Collision          unused by PE */
#define VECTOR_36         (tIsrFunc)&Unhandled_ivINT_LVD_LVW    /* 0x24 -    ivINT_LVD_LVW                  unused by PE */
#define VECTOR_37         (tIsrFunc)&Unhandled_ivINT_LLWU       /* 0x25 -    ivINT_LLWU                     unused by PE */
#define VECTOR_38         (tIsrFunc)&Unhandled_ivINT_WDOG_EWM   /* 0x26 -    ivINT_WDOG_EWM                 unused by PE */
#define VECTOR_39         (tIsrFunc)&Unhandled_ivINT_RNG        /* 0x27 -    ivINT_RNG                      unused by PE */
#define VECTOR_40         (tIsrFunc)&Unhandled_ivINT_I2C0       /* 0x28 -    ivINT_I2C0                     unused by PE */
#define VECTOR_41         (tIsrFunc)&Unhandled_ivINT_I2C1       /* 0x29 -    ivINT_I2C1                     unused by PE */
#define VECTOR_42         (tIsrFunc)&MESH_SPI_Interrupt         /* 0x2A 96   ivINT_SPI0                     used by PE */
#define VECTOR_43         (tIsrFunc)&Unhandled_ivINT_SPI1       /* 0x2B -    ivINT_SPI1                     unused by PE */
#define VECTOR_44         (tIsrFunc)&Unhandled_ivINT_I2S0_Tx    /* 0x2C -    ivINT_I2S0_Tx                  unused by PE */
#define VECTOR_45         (tIsrFunc)&Unhandled_ivINT_I2S0_Rx    /* 0x2D -    ivINT_I2S0_Rx                  unused by PE */
#define VECTOR_46         (tIsrFunc)&Unhandled_ivINT_UART0_LON  /* 0x2E -    ivINT_UART0_LON                unused by PE */
#define VECTOR_47         (tIsrFunc)&ESP8266_Serial_Interrupt   /* 0x2F 112  ivINT_UART0_RX_TX              used by PE */
#define VECTOR_48         (tIsrFunc)&ESP8266_Serial_Interrupt   /* 0x30 112  ivINT_UART0_ERR                used by PE */
#define VECTOR_49         (tIsrFunc)&Unhandled_ivINT_UART1_RX_TX /* 0x31 -   ivINT_UART1_RX_TX              unused by PE */
#define VECTOR_50         (tIsrFunc)&Unhandled_ivINT_UART1_ERR  /* 0x32 -    ivINT_UART1_ERR                unused by PE */
#define VECTOR_51         (tIsrFunc)&Unhandled_ivINT_UART2_RX_TX /* 0x33 -   ivINT_UART2_RX_TX              unused by PE */
#define VECTOR_52         (tIsrFunc)&Unhandled_ivINT_UART2_ERR  /* 0x34 -    ivINT_UART2_ERR                unused by PE */
#define VECTOR_53         (tIsrFunc)&Unhandled_ivINT_UART3_RX_TX /* 0x35 -   ivINT_UART3_RX_TX              unused by PE */
#define VECTOR_54         (tIsrFunc)&Unhandled_ivINT_UART3_ERR  /* 0x36 -    ivINT_UART3_ERR                unused by PE */
#define VECTOR_55         (tIsrFunc)&Unhandled_ivINT_ADC0       /* 0x37 -    ivINT_ADC0                     unused by PE */
#define VECTOR_56         (tIsrFunc)&Unhandled_ivINT_CMP0       /* 0x38 -    ivINT_CMP0                     unused by PE */
#define VECTOR_57         (tIsrFunc)&Unhandled_ivINT_CMP1       /* 0x39 -    ivINT_CMP1                     unused by PE */
#define VECTOR_58         (tIsrFunc)&TU1_Interrupt              /* 0x3A 112  ivINT_FTM0                     used by PE */
#define VECTOR_59         (tIsrFunc)&Unhandled_ivINT_FTM1       /* 0x3B -    ivINT_FTM1                     unused by PE */
#define VECTOR_60         (tIsrFunc)&Unhandled_ivINT_FTM2       /* 0x3C -    ivINT_FTM2                     unused by PE */
#define VECTOR_61         (tIsrFunc)&Unhandled_ivINT_CMT        /* 0x3D -    ivINT_CMT                      unused by PE */
#define VECTOR_62         (tIsrFunc)&Unhandled_ivINT_RTC        /* 0x3E -    ivINT_RTC                      unused by PE */
#define VECTOR_63         (tIsrFunc)&Unhandled_ivINT_RTC_Seconds /* 0x3F -   ivINT_RTC_Seconds              unused by PE */
#define VECTOR_64         (tIsrFunc)&Unhandled_ivINT_PIT0       /* 0x40 -    ivINT_PIT0                     unused by PE */
#define VECTOR_65         (tIsrFunc)&Unhandled_ivINT_PIT1       /* 0x41 -    ivINT_PIT1                     unused by PE */
#define VECTOR_66         (tIsrFunc)&Unhandled_ivINT_PIT2       /* 0x42 -    ivINT_PIT2                     unused by PE */
#define VECTOR_67         (tIsrFunc)&Unhandled_ivINT_PIT3       /* 0x43 -    ivINT_PIT3                     unused by PE */
#define VECTOR_68         (tIsrFunc)&Unhandled_ivINT_PDB0       /* 0x44 -    ivINT_PDB0                     unused by PE */
#define VECTOR_69         (tIsrFunc)&Unhandled_ivINT_USB0       /* 0x45 -    ivINT_USB0                     unused by PE */
#define VECTOR_70         (tIsrFunc)&Unhandled_ivINT_USBDCD     /* 0x46 -    ivINT_USBDCD                   unused by PE */
#define VECTOR_71         (tIsrFunc)&Unhandled_ivINT_Reserved71 /* 0x47 -    ivINT_Reserved71               unused by PE */
#define VECTOR_72         (tIsrFunc)&Unhandled_ivINT_DAC0       /* 0x48 -    ivINT_DAC0                     unused by PE */
#define VECTOR_73         (tIsrFunc)&Unhandled_ivINT_MCG        /* 0x49 -    ivINT_MCG                      unused by PE */
#define VECTOR_74         (tIsrFunc)&Unhandled_ivINT_LPTMR0     /* 0x4A -    ivINT_LPTMR0                   unused by PE */
#define VECTOR_75         (tIsrFunc)&Unhandled_ivINT_PORTA      /* 0x4B -    ivINT_PORTA                    unused by PE */
#define VECTOR_76         (tIsrFunc)&ButtonIn_Interrupt         /* 0x4C 112  ivINT_PORTB                    used by PE */
#define VECTOR_77         (tIsrFunc)&PTC_IRQ_Interrupt          /* 0x4D 112  ivINT_PORTC                    used by PE */
#define VECTOR_78         (tIsrFunc)&Unhandled_ivINT_PORTD      /* 0x4E -    ivINT_PORTD                    unused by PE */
#define VECTOR_79         (tIsrFunc)&Unhandled_ivINT_PORTE      /* 0x4F -    ivINT_PORTE                    unused by PE */
#define VECTOR_80         (tIsrFunc)&Unhandled_ivINT_SWI        /* 0x50 -    ivINT_SWI                      unused by PE */
#define VECTOR_81         (tIsrFunc)&Unhandled_ivINT_SPI2       /* 0x51 -    ivINT_SPI2                     unused by PE */
#define VECTOR_82         (tIsrFunc)&Unhandled_ivINT_UART4_RX_TX /* 0x52 -   ivINT_UART4_RX_TX              unused by PE */
#define VECTOR_83         (tIsrFunc)&Unhandled_ivINT_UART4_ERR  /* 0x53 -    ivINT_UART4_ERR                unused by PE */
#define VECTOR_84         (tIsrFunc)&Unhandled_ivINT_UART5_RX_TX /* 0x54 -   ivINT_UART5_RX_TX              unused by PE */
#define VECTOR_85         (tIsrFunc)&Unhandled_ivINT_UART5_ERR  /* 0x55 -    ivINT_UART5_ERR                unused by PE */
#define VECTOR_86         (tIsrFunc)&Unhandled_ivINT_CMP2       /* 0x56 -    ivINT_CMP2                     unused by PE */
#define VECTOR_87         (tIsrFunc)&Unhandled_ivINT_FTM3       /* 0x57 -    ivINT_FTM3                     unused by PE */
#define VECTOR_88         (tIsrFunc)&Unhandled_ivINT_Reserved88 /* 0x58 -    ivINT_Reserved88               unused by PE */
#define VECTOR_89         (tIsrFunc)&Unhandled_ivINT_ADC1       /* 0x59 -    ivINT_ADC1                     unused by PE */
#define VECTOR_90         (tIsrFunc)&I2C2_Interrupt             /* 0x5A 112  ivINT_I2C2                     used by PE */
#define VECTOR_91         (tIsrFunc)&Unhandled_ivINT_CAN0_ORed_Message_buffer /* 0x5B - ivINT_CAN0_ORed_Message_buffer unused by PE */
#define VECTOR_92         (tIsrFunc)&Unhandled_ivINT_CAN0_Bus_Off /* 0x5C -  ivINT_CAN0_Bus_Off             unused by PE */
#define VECTOR_93         (tIsrFunc)&Unhandled_ivINT_CAN0_Error /* 0x5D -    ivINT_CAN0_Error               unused by PE */
#define VECTOR_94         (tIsrFunc)&Unhandled_ivINT_CAN0_Tx_Warning /* 0x5E - ivINT_CAN0_Tx_Warning        unused by PE */
#define VECTOR_95         (tIsrFunc)&Unhandled_ivINT_CAN0_Rx_Warning /* 0x5F - ivINT_CAN0_Rx_Warning        unused by PE */
#define VECTOR_96         (tIsrFunc)&Unhandled_ivINT_CAN0_Wake_Up /* 0x60 -  ivINT_CAN0_Wake_Up             unused by PE */
#define VECTOR_97         (tIsrFunc)&Unhandled_ivINT_SDHC       /* 0x61 -    ivINT_SDHC                     unused by PE */
#define VECTOR_98         (tIsrFunc)&Unhandled_ivINT_ENET_1588_Timer /* 0x62 - ivINT_ENET_1588_Timer        unused by PE */
#define VECTOR_99         (tIsrFunc)&Unhandled_ivINT_ENET_Transmit /* 0x63 - ivINT_ENET_Transmit            unused by PE */
#define VECTOR_100        (tIsrFunc)&Unhandled_ivINT_ENET_Receive /* 0x64 -  ivINT_ENET_Receive             unused by PE */
#define VECTOR_101        (tIsrFunc)&Unhandled_ivINT_ENET_Error /* 0x65 -    ivINT_ENET_Error               unused by PE */
  
#ifdef __cplusplus
}
#endif

/* END Vectors_Config.h */

#endif /* __Vectors_Config_H */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file is a part of Processor Expert static initialization
**     library for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
