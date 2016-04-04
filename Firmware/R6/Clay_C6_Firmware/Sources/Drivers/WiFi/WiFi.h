#ifndef WIFI_H
#define WIFI_H

#define SSID_DEFAULT "hefnet"
#define PASSWORD_DEFAULT "h3fn3r_is_better_than_me"

#define DEFAULT_WIFI_HOTSPOT_SSID "Clay"
#define DEFAULT_WIFI_HOTSPOT_PASSWORD "Clay"

#include "PE_Types.h"

#include "Message.h"
#include "Message_Queue.h"

extern Message *incomingWiFiMessageQueue;
extern Message *outgoingWiFiMessageQueue;

typedef enum
{
   Enable,
   Programming,
   Idle,
   Receive_Message,
   Deserialize_Received_Message,
   Serialize_Transmission,
   Start_Transmission,
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
;
extern void Wifi_State_Step();
;
extern void Wifi_Set_Programming_Mode();
;
extern void Wifi_Set_Operating_Mode();
;
extern void Wifi_Do_Reset(bool StateMachineWaitForConnect);
extern Wifi_States Wifi_Get_State();

extern bool Wifi_Send(Message * message);
extern Message* Wifi_Receive();

// TODO: Implement these functions using "command" and "info" protocols.
//extern void Request_Internet_Address ();; // e.g., K64 creates and sends request (i.e., "control") message to the ESP. In response, the ESP stores the IP address in an "status" message and sends it to the K64. Upon receipt, the K64 will store the IP address locally in it's WiFi_Profile structure.
//extern char* Get_Internet_Address ();; // e.g., Returns the IP address stored on the K64 in string format "192.168.1.10".
//extern char* Request_Access_Point (char *ssid, char *password); // e.g., K64 creates and sends "control" message to the ESP containing the SSID and password. In response, the ESP stores the SSID and password, attempts to connect, and once connected, sends to the K64 a (1) "status" message stating "connected to <ssid>" and a second (2) "status" message stating "set internet address to <internet-address>".
//extern char* Get_WiFi_SSID ();;

//New API is below

extern bool WiFi_Enable();
extern bool WiFi_Disable();

// Requests the WiFi controller to connect to an access point with the specified SSID and password.
// The WiFi controller will send a response in a "status" Message.
extern bool WiFi_Request_Connect(char * ssid, char * password);

// Requests the WiFi controller to disconnect from the connected access point, if any.
// The WiFi controller will send a response in a "status" Message.
extern bool WiFi_Request_Disconnect();

// Requests connection status from WiFi controller. Connection status can be disconnected, connecting, connected, disconnecting, or unavailable.
// The WiFi controller will send a response in a "status" Message with one of the statuses in a string formatted like "disconnected", "connecting", "connected", "disconnecting", or "unavailable".
extern bool WiFi_Request_Get_Connection_Status();

// Requests the Internet (IP) address from the WiFi controller.
// The WiFi controller will send a response in a "status" Message with the address in a string formatted like "192.168.1.10".
extern bool WiFi_Request_Get_Internet_Address();

// Requests the WiFi controller to send the message. The message contains the messaging protocol (UDP, TCP, HTTP, or HTTPS),
//  source address (IP string), destination address (IP string), and content (string).
extern bool WiFi_Request_Send_Message(Message * message);

// Requests the WiFi controller to enable an access point with the specified SSID and password.
// WiFi controller sends a response in a "status" Message with the AP connection status in a
//   string formatted like "ap enable success" or "ap enable failure" or "ap disable success".
extern bool WiFi_Request_Enable_Access_Point(char * ssid, char * password);

// Requests the WiFi controller to disable the access point, if enabled.
extern bool WiFi_Request_Disable_Access_Point();

extern bool WiFi_Request_Start_Discovery_Service();

#endif
