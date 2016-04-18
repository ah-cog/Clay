#include <Message.h>
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

#include "PE_Types.h"
#include "Events.h"
#include "WiFi.h"
#include "WIFI_GPIO0.h"
#include "WIFI_GPIO2.h"
#include "WIFI_CHIP_EN.h"
#include "WIFI_RESET.h"
#include "Ring_Buffer.h"
#include "Clock.h"
#include "Message_Info.h"
#include "Multibyte_Ring_Buffer.h"

Multibyte_Ring_Buffer wifi_multibyte_ring;

Message *incomingWiFiMessageQueue = NULL;
Message *outgoingWiFiMessageQueue = NULL;

#define WIFI_SERIAL_OUT_BUFFER_LENGTH           1024
#define WIFI_SERIAL_IN_BUFFER_LENGTH            1024
#define INTERRUPT_RX_TIMEOUT_MS     3000
#define INTERRUPT_TX_TIMEOUT_MS     1000

ESP8266_UART_Device deviceData;
volatile bool WifiInterruptReceived;
volatile bool WifiSetProgramMode;
bool Wifi_Message_Available;

static bool received_message_start;

static uint32_t pendingTransmitByteCount;
static uint32_t bytes_received;

static uint8_t serial_tx_buffer[WIFI_SERIAL_OUT_BUFFER_LENGTH] = "test message, yo\r\n";
static uint8_t serial_rx_buffer[WIFI_SERIAL_IN_BUFFER_LENGTH];

static Wifi_States State;
static uint32_t interruptRxTime;
static uint32_t txStartTime;
static uint32_t programStartTime;

static uint8_t * temp_content;
static uint8_t * temp_type;
static uint8_t * temp_source_address;
static uint8_t * temp_dest_address;
static uint8_t * message_end_ptr;
static uint8_t * message_start_ptr;

static const char * message_start = "\f";
static const char * message_field_delimiter = "\t";
static const char * message_end = "\n";

static LDD_TDeviceData * WIFI_GPIO0_DeviceDataPtr;
static uint8_t PowerOn_Interrupt_Count;

bool Enable_WiFi(const char *ssid, const char *password) {
   bool rval = FALSE;

   Wifi_Message_Available = FALSE;

   // Initialize the ESP8266 device data structure
   deviceData.handle = ESP8266_Serial_Init(&deviceData);
   deviceData.isSent = FALSE;
   deviceData.rxChar = '\0';
   deviceData.rxPutFct = Ring_Buffer_Put;        // ESP8266_RxBuf_Put;

   // Read any pending data to "clear the line"
   while (ESP8266_Serial_ReceiveBlock(deviceData.handle, wifi_serial_interrupt_rx_buf, wifi_rx_interrupt_count) != ERR_OK) {

   }

   State = Idle;

   Initialize_Message_Queue(&incomingWiFiMessageQueue);
   Initialize_Message_Queue(&outgoingWiFiMessageQueue);

   WIFI_CHIP_EN_PutVal(NULL, 1);
   Wifi_Set_Operating_Mode();

   Wait(2000);

   WiFi_Request_Connect(ssid, password);

   Multibyte_Ring_Buffer_Init(&wifi_multibyte_ring, WIFI_SERIAL_IN_BUFFER_LENGTH);

   WifiInterruptReceived = FALSE;
   WifiSetProgramMode = FALSE;

   pendingTransmitByteCount = 0;
   interruptRxTime = 0;

   rval = TRUE;

   return rval;
}

void Wifi_State_Step() {

   //TODO: if a transmission was waiting, we'll lose it here. Look at pendingbytecount? Maybe we don't care?
   //      This may just be test code, actually. The button handler in events.c is setting WifiSetProgramMode
   if (State != Programming && WifiSetProgramMode) {
      Wifi_Set_Programming_Mode();
      WifiSetProgramMode = FALSE;
   }

   switch (State) {
      case Enable: {
         if (WifiInterruptReceived) {
            WifiInterruptReceived = FALSE;
            ++PowerOn_Interrupt_Count;
            if (PowerOn_Interrupt_Count >= 2) {
               State = Idle;
            }
         }
      }
      case Programming: {
         //wait for the toggle again.
         if (WifiSetProgramMode || ((Millis() - programStartTime > 5000) && WifiInterruptReceived)) {
            Wifi_Set_Operating_Mode();
            WifiSetProgramMode = FALSE;
         }
         WifiInterruptReceived = FALSE;
         break;
      }

      case Idle: {
         //waiting for an interrupt, no tranmission pending

         if (Multibyte_Ring_Buffer_Get_Bytes_Before_Char(&wifi_multibyte_ring, message_end[0]) > 0) {
            State = Receive_Message;
         } else if (Has_Messages(&outgoingWiFiMessageQueue) == TRUE) {

            State = Serialize_Transmission;

         } else if (WifiInterruptReceived) {

            State = Receive_Message;

            WifiInterruptReceived = FALSE;
            received_message_start = FALSE;

            interruptRxTime = Millis();
         }

         break;
      }

      case Receive_Message: {

//         if (Multibyte_Ring_Buffer_Dequeue_Until_Char(&wifi_multibyte_ring,
//                                                               serial_rx_buffer,
//                                                               WIFI_SERIAL_IN_BUFFER_LENGTH,
//                                                               message_start[0])     //throw away data up until the start of a message

         while (Multibyte_Ring_Buffer_Dequeue_Until_Char(&wifi_multibyte_ring, serial_rx_buffer,
         WIFI_SERIAL_IN_BUFFER_LENGTH,
                                                         message_end[0])) {

            temp_type = strtok(serial_rx_buffer, message_start);     //throw out the start character
            temp_type = strtok(NULL, message_field_delimiter);
            temp_source_address = strtok(NULL, message_field_delimiter);
            temp_dest_address = strtok(NULL, message_field_delimiter);
            temp_content = strtok(NULL, message_end);

            if (temp_content != NULL && temp_type != NULL && temp_source_address != NULL && temp_dest_address != NULL) {

               // Create message object
               Message *message = Create_Message(temp_content);
               Set_Message_Type(message, temp_type);
               Set_Message_Source(message, temp_source_address);
               Set_Message_Destination(message, temp_dest_address);

               // Queue the message
               Queue_Message(&incomingWiFiMessageQueue, message);

               if (Multibyte_Ring_Buffer_Get_Count(&wifi_multibyte_ring) < 10) {
                  interruptRxTime = Millis();
                  State = Idle;
               }
            }
         }

         if ((Millis() - interruptRxTime) > INTERRUPT_RX_TIMEOUT_MS) {
            State = Idle;
         }

         break;
      }

      case Serialize_Transmission: {
         Message *message = Dequeue_Message(&outgoingWiFiMessageQueue);

         //	(*message).source = (char *) malloc (strlen (type) + 1 + strlen (address) + 1); // i.e., <channel>,<address>!
         //	strcpy ((*message).source, address);

         //	sprintf ((*message).source, "%s,%s%c", type, address, ADDRESS_TERMINATOR);

         //HACK: Padding added because it seems to lessen the likelihood that we miss a \n
         snprintf(serial_tx_buffer,
                  WIFI_SERIAL_OUT_BUFFER_LENGTH,
                  "  %s%s%s%s%s%s%s%s%s  ",
                  message_start,
                  message->type,
                  message_field_delimiter,
                  message->source,
                  message_field_delimiter,
                  message->destination,
                  message_field_delimiter,
                  message->content,
                  message_end);

         pendingTransmitByteCount = strlen(serial_tx_buffer);
         Delete_Message(message);

         State = Start_Transmission;
         break;
      }

      case Start_Transmission: {

         WIFI_GPIO2_PutVal(NULL, 0);
         Wait(1);
         WIFI_GPIO2_PutVal(NULL, 1);

         deviceData.isSent = FALSE;
         ESP8266_Serial_SendBlock(deviceData.handle, serial_tx_buffer, pendingTransmitByteCount);
         State = Transmission_Sent;

         break;
      }

      case Transmission_Sent: {
         //transmission has been sent. back to idle for now, I guess
         if (deviceData.isSent) {
            State = Idle;
         }
         break;
      }

      default: {
         //this should never happen. let's pretend it didn't.
         State = Idle;
         break;
      }
   }
}

void Wifi_Set_Programming_Mode() {
   State = Programming;
   WifiInterruptReceived = TRUE;
   programStartTime = Millis();
   Wait(1);
   WIFI_GPIO0_PutVal(NULL, 0);
   WIFI_GPIO2_PutVal(NULL, 1);
   Wifi_Do_Reset(FALSE);
}

///this may not be needed. The ESP seems to come out of programming mode automatically.
void Wifi_Set_Operating_Mode() {
   State = Idle;
   WIFI_GPIO0_PutVal(NULL, 1);
   Wait(1);
   WIFI_GPIO2_PutVal(NULL, 1);
   Wifi_Do_Reset(TRUE);
}

void Wifi_Do_Reset(bool StateMachineWaitForConnect) {
   WIFI_RESET_PutVal(NULL, 0);
   Wait(1);
   WIFI_RESET_PutVal(NULL, 1);
   Wait(100);

   if (0 && StateMachineWaitForConnect) {
      PowerOn_Interrupt_Count = 0;
      WifiInterruptReceived = FALSE;
      State = Enable;
   }
}

bool Wifi_Send(Message *message) {
   Queue_Message(&outgoingWiFiMessageQueue, message);
   return TRUE;
}

Message* Wifi_Receive() {
   Message *message = NULL;
   if (Has_Messages(&incomingWiFiMessageQueue) == TRUE) {
      message = Dequeue_Message(&incomingWiFiMessageQueue);
      return message;
   }
   return NULL;
}

Wifi_States Wifi_Get_State() {
   return State;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//new API implemented below.
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

///macros

///typedefs

///local vars
#define GET_IP_CMD_STR                "get_ip"
#define GET_GATEWAY_CMD_STR           "get_gateway"
#define GET_SUBNET_CMD_STR            "get_subnet"
#define SET_AP_CMD_STR                "setap"
#define GET_WIFI_STATUS_CMD_STR       "get_status"

///local prototypes
static bool WiFi_Send_Command(char * command, char ** args, int arg_count);

///global implementations
bool WiFi_Enable() {
   bool rval = FALSE;

   Wifi_Message_Available = FALSE;

// Initialize the ESP8266 device data structure
   deviceData.handle = ESP8266_Serial_Init(&deviceData);
   deviceData.isSent = FALSE;
   deviceData.rxChar = '\0';
   deviceData.rxPutFct = Ring_Buffer_Put;        // ESP8266_RxBuf_Put;

// Read any pending data to "clear the line"
   while (ESP8266_Serial_ReceiveBlock(deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof(deviceData.rxChar)) != ERR_OK) {

   }

   State = Idle;

   WIFI_CHIP_EN_PutVal(NULL, 1);
   Wifi_Set_Operating_Mode();

//   char addrStr[] = "\x12";
//   char testMsg[64] = { '\0' };
//   sprintf(testMsg, "SETAP %s,%s", ssid, password);

//   Wait(5000);

//   Message * message = Create_Message(testMsg);
//   Set_Message_Type(message, "CMD");
//   Set_Message_Destination(message, addrStr);
//   Wifi_Send(message);

   WifiInterruptReceived = FALSE;
   WifiSetProgramMode = FALSE;

   Initialize_Message_Queue(&incomingWiFiMessageQueue);
   Initialize_Message_Queue(&outgoingWiFiMessageQueue);

   pendingTransmitByteCount = 0;
   interruptRxTime = 0;

   rval = TRUE;

   return rval;
}

bool WiFi_Disable() {
   bool rval = false;
   return rval;
}

// Requests the WiFi controller to connect to an access point with the specified SSID and password.
// The WiFi controller will send a response in a "status" Message.
bool WiFi_Request_Connect(char * ssid, char * password) {
   char* args[] = { ssid, password };
   return WiFi_Send_Command(SET_AP_CMD_STR, args, 2);
}

// Requests the WiFi controller to disconnect from the connected access point, if any.
// The WiFi controller will send a response in a "status" Message.
bool WiFi_Request_Disconnect() {
   bool rval = false;
   return rval;
}

// Requests connection status from WiFi controller. Connection status can be disconnected, connecting, connected, disconnecting, or unavailable.
// The WiFi controller will send a response in a "status" Message with one of the statuses in a string formatted like "disconnected", "connecting", "connected", "disconnecting", or "unavailable".
bool WiFi_Request_Get_Connection_Status() {
   return WiFi_Send_Command(GET_WIFI_STATUS_CMD_STR, NULL, 0);
}

// Requests the Internet (IP) address from the WiFi controller.
// The WiFi controller will send a response in a "status" Message with the address in a string formatted like "192.168.1.10".
bool WiFi_Request_Get_Internet_Address() {

   return WiFi_Send_Command(GET_IP_CMD_STR, NULL, 0);
}

// Requests the WiFi controller to send the message. The message contains the messaging protocol (udp, tcp, http, or https),
//  source address (IP string), destination address (IP string), and content (string).
bool WiFi_Request_Send_Message(Message * message) {
   bool rval = false;
   return rval;
}

// Requests the WiFi controller to enable an access point with the specified SSID and password.
// WiFi controller sends a response in a "status" Message with the AP connection status in a
//   string formatted like "ap enable success" or "ap enable failure" or "ap disable success".
bool WiFi_Request_Enable_Access_Point(char * ssid, char * password) {
   bool rval = false;
   return rval;
}

// Requests the WiFi controller to disable the access point, if enabled.
bool WiFi_Request_Disable_Access_Point() {
   bool rval = false;
   return rval;
}

bool WiFi_Request_Start_Discovery_Service() {
   bool rval = false;
   return rval;
}

//TODO: capture command return values in this layer

///local implementations
static bool WiFi_Send_Command(char * command, char ** args, int arg_count) {

   int buff_length = strlen(command) + 1;     //+1 for null.
   Message * message;
   char * send_buffer;

   for (int i = 0; i < arg_count; ++i) {
      buff_length += strlen(args[i]) + 1;     //+1 for comma;
   }

   send_buffer = calloc(buff_length, sizeof(char));

   sprintf(send_buffer, "%s ", command);

   for (int i = 0; i < arg_count; ++i) {

      strcat(send_buffer, args[i]);

      if (i < arg_count - 1) {
         strcat(send_buffer, arg_delimiter);
      }
   }

   message = Create_Message(send_buffer);
   Set_Message_Destination(message, "none");
   Set_Message_Source(message, "none");
   Set_Message_Type(message, "command");

   free(send_buffer);

   return Wifi_Send(message);
}
