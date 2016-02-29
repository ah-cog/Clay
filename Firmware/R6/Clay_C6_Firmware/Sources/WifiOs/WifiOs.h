/*
 * WifiOs.h
 *
 *  Created on: Feb 18, 2016
 *      Author: thebh
 */

#ifndef SOURCES_WIFIOS_WIFIOS_H_
#define SOURCES_WIFIOS_WIFIOS_H_

#include "PE_Types.h"

typedef enum
{
   Enable,
   Programming,
   Idle,
   Receiving_Message,
   Deserializing_Received_Message,
   Serialize_Transmission,
   Start_Transmission,
   Transmission_Waiting,
   Transmission_Sent
} Wifi_States;

typedef struct
{
      LDD_TDeviceData *handle;
      volatile uint8_t isSent;
      uint8_t rxChar;
      uint8_t (*rxPutFct)(uint8_t);
} ESP8266_UART_Device;        // NOTE: This was named "UART_Desc" previously.

extern ESP8266_UART_Device deviceData;
extern volatile bool WifiInterruptReceived;
extern volatile bool WifiSetProgramMode;
extern bool Wifi_Message_Available;

extern bool Wifi_Enable();
extern void Wifi_State_Step();
extern void Wifi_Set_Programming_Mode();
extern void Wifi_Set_Operating_Mode();
extern void Wifi_Do_Reset(bool StateMachineWaitForConnect);
extern Wifi_States Wifi_Get_State();

extern void Wifi_Send(void * data, uint32_t length);
extern uint32_t Wifi_Receive(void * data);

#endif /* SOURCES_WIFIOS_WIFIOS_H_ */
