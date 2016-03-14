#ifndef WIFI_H
#define WIFI_H

#define SSID_DEFAULT "hefnet"
#define PASSWORD_DEFAULT "h3fn3r_is_better_than_me"

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

extern bool Enable_WiFi();
extern void Wifi_State_Step();
extern void Wifi_Set_Programming_Mode();
extern void Wifi_Set_Operating_Mode();
extern void Wifi_Do_Reset(bool StateMachineWaitForConnect);
extern Wifi_States Wifi_Get_State();

extern bool Wifi_Send(Message * message);
extern Message* Wifi_Receive ();

#endif
