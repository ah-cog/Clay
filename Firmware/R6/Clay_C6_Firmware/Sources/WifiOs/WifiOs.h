/*
 * WifiOs.h
 *
 *  Created on: Feb 18, 2016
 *      Author: thebh
 */

#ifndef SOURCES_WIFIOS_WIFIOS_H_
#define SOURCES_WIFIOS_WIFIOS_H_

#include "PE_Types.h"
//#include "Message.h"
#include "Messenger.h"

typedef enum
{
   Enable,
   Programming,
   Idle,
   Receive_Message,
   Deserialize_Received_Message,
   Serialize_Transmission,
   Start_Transmission,
   Transmission_Wait,
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

extern bool Wifi_Send(Message * message);
//extern bool Wifi_Receive(Message * message);
extern Message* Wifi_Receive ();

#endif /* SOURCES_WIFIOS_WIFIOS_H_ */
