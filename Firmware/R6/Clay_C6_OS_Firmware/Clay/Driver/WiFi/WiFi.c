#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "stdio.h"

#include "Message.h"

//#include "Events.h"
#include "WiFi.h"
//#include "WIFI_GPIO0.h"
//#include "WIFI_GPIO2.h"
//#include "WIFI_CHIP_EN.h"
//#include "WIFI_RESET.h"
#include "Ring_Buffer.h"
#include "Clock.h"
#include "Message_Info.h"

#define OUT_BUFFER_LENGTH           1024
#define IN_BUFFER_LENGTH            1024
#define INTERRUPT_RX_TIMEOUT_MS     1000
#define INTERRUPT_TX_TIMEOUT_MS     1000

ESP8266_UART_Device deviceData;
volatile bool WifiInterruptReceived;
volatile bool WifiSetProgramMode;
bool Wifi_Message_Available;

static uint32_t pendingTransmitByteCount;
static uint32_t Pending_Receive_Byte_Count;

static char outBuffer[OUT_BUFFER_LENGTH] = "test message, yo\r\n";
static char inBuffer[IN_BUFFER_LENGTH];

static Wifi_States State;
static uint32_t interruptRxTime;
static uint32_t txStartTime;
static uint32_t programStartTime;

static uint8_t Newline_Count;
static char * temp_content;
static char * temp_type;
static char * temp_source_address;
static char * temp_dest_address;
static char temp_address_string[50];

static const char * message_terminator = "\n";

// TODO: update serial driver
//static LDD_TDeviceData * WIFI_GPIO0_DeviceDataPtr;
static uint8_t PowerOn_Interrupt_Count;

bool Enable_WiFi(const char *ssid, const char *password) {
   bool rval = false;

   Wifi_Message_Available = false;

   // Initialize the ESP8266 device data structure
//   deviceData.handle = ESP8266_Serial_Init(&deviceData); // TODO: update serial driver
   deviceData.isSent = false;
   deviceData.rxChar = '\0';
   deviceData.rxPutFct = Ring_Buffer_Put;        // ESP8266_RxBuf_Put;

   // Read any pending data to "clear the line"

   // TODO: update serial driver
//   while (ESP8266_Serial_ReceiveBlock(deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof(deviceData.rxChar)) != 0) {
//
//   }

   State = Idle;

   // TODO: update WiFi GPIOs
//   WIFI_CHIP_EN_PutVal(NULL, 1);
   Wifi_Set_Operating_Mode();

   char addrStr[] = "\x12";
   char testMsg[] = "SETAP hefnet,h3fn3r_is_better_than_me";

   Wait(5000);

   Message * message = Create_Message(testMsg);
   Set_Message_Type(message, "CMD");
   Set_Message_Destination(message, addrStr);
   Wifi_Send(message);

   WifiInterruptReceived = false;
   WifiSetProgramMode = false;

//   Initialize_Message_Queue(&incomingMessageQueue);
//   Initialize_Message_Queue(&outgoingMessageQueue);

   pendingTransmitByteCount = 0;
   interruptRxTime = 0;

   rval = true;

   return rval;
}

void Wifi_State_Step() {

   // TODO: if a transmission was waiting, we'll lose it here. Look at pendingbytecount? Maybe we don't care?
   //      This may just be test code, actually. The button handler in events.c is setting WifiSetProgramMode
   if (State != Transmission_Wait && State != Programming && WifiSetProgramMode) {
      Wifi_Set_Programming_Mode();
      WifiSetProgramMode = false;
   }

   switch (State) {
      case Enable: {
         if (WifiInterruptReceived) {
            WifiInterruptReceived = false;
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
            WifiSetProgramMode = false;
         }
         WifiInterruptReceived = false;
         break;
      }

      case Idle: {
         //waiting for an interrupt, no tranmission pending
         if (WifiInterruptReceived) {
            State = Receive_Message;

            WifiInterruptReceived = false;

            Newline_Count = 0;
            Pending_Receive_Byte_Count = 0;

            interruptRxTime = Millis();

            // TODO: update serial driver
//            while (ESP8266_Serial_ReceiveBlock(deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof(deviceData.rxChar))
//                   == 0) {
//
//            }
            Ring_Buffer_Init();

            // TODO: update WIFI GPIO
//            WIFI_GPIO2_PutVal(NULL, 0);
         }
//         else if (Peek_Message(&outgoingMessageQueue) != NULL)
         else if (Has_Messages(&outgoingMessageQueue) == true) {
            State = Serialize_Transmission;
         }

         break;
      }

      case Receive_Message: {
         if (Ring_Buffer_Has_Data()) {
            Ring_Buffer_Get(inBuffer + Pending_Receive_Byte_Count);

            if (inBuffer[Pending_Receive_Byte_Count++] == address_terminator[0]) {
               // TODO: update WiFi GPIO
//               WIFI_GPIO2_PutVal(NULL, 1);
               WifiInterruptReceived = false;
               Wifi_Message_Available = true;
               State = Deserialize_Received_Message;
            }
         } else if ((Millis() - interruptRxTime) > INTERRUPT_RX_TIMEOUT_MS) {

            // TODO: update WiFi GPIO
//            WIFI_GPIO2_PutVal(NULL, 1);
            WifiInterruptReceived = false;
            State = Idle;
         }

         break;
      }

      case Deserialize_Received_Message: {
         temp_content = strtok(inBuffer, message_terminator);
         temp_type = strtok(NULL, type_delimiter);
         temp_source_address = strtok(NULL, address_delimiter);
         temp_dest_address = strtok(NULL, address_terminator);

         if (temp_content != NULL && temp_type != NULL && temp_source_address != NULL && temp_dest_address != NULL) {

            sprintf(temp_address_string, "%s", temp_source_address);

            // Create message object
            Message *message = Create_Message(temp_content);
            Set_Message_Type(message, temp_type);
            Set_Message_Source(message, temp_source_address);
            Set_Message_Destination(message, temp_dest_address);

            // Queue the message
            Queue_Message(&incomingMessageQueue, message);
         }

         State = Idle;
         break;
      }

      case Serialize_Transmission: {
         Message *message = Dequeue_Message(&outgoingMessageQueue);

         //	(*message).source = (char *) malloc (strlen (type) + 1 + strlen (address) + 1); // i.e., <channel>,<address>!
         //	strcpy ((*message).source, address);

         //	sprintf ((*message).source, "%s,%s%c", type, address, ADDRESS_TERMINATOR);

         snprintf(outBuffer,
         OUT_BUFFER_LENGTH,
                  "%s\n%s,%s;%s\x12\n", message->content, message->type, message->source, message->destination);

         pendingTransmitByteCount = strlen(outBuffer);
         Delete_Message(message);

         State = Start_Transmission;
         break;
      }

      case Start_Transmission: {
         //signal to the WiFi that we're ready to send something

         // TODO: update wifi gpio
//         WIFI_GPIO2_PutVal(NULL, 0);
         State = Transmission_Wait;
         txStartTime = Millis();
         break;
      }

      case Transmission_Wait: {
         //waiting for WiFi to OK transmission.
         //send when we get the interrupt
         if (WifiInterruptReceived) {
            WifiInterruptReceived = false;
            deviceData.isSent = false;
//            ESP8266_Serial_SendBlock(deviceData.handle, outBuffer, pendingTransmitByteCount); // TODO: update serial driver
            State = Transmission_Sent;
         } else if (Millis() - txStartTime > INTERRUPT_TX_TIMEOUT_MS) {
            // TODO: update wifi gpio
//            WIFI_GPIO2_PutVal(NULL, 1);
            State = Idle;
         }

         break;
      }

      case Transmission_Sent: {
         //transmission has been sent. back to idle for now, I guess
         if (deviceData.isSent) {
            // TODO: update wifi gpio
//            WIFI_GPIO2_PutVal(NULL, 1);
            WifiInterruptReceived = false;
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
   WifiInterruptReceived = true;
   programStartTime = Millis();
   Wait(1);
   // TODO: update WiFi GPIOs

//   WIFI_GPIO0_PutVal(NULL, 0);
//   WIFI_GPIO2_PutVal(NULL, 1);
   Wifi_Do_Reset(false);
}

///this may not be needed. The ESP seems to come out of programming mode automatically.
void Wifi_Set_Operating_Mode() {
   State = Idle;
   // TODO: update WiFi GPIOs
//   WIFI_GPIO0_PutVal(NULL, 1);
   Wait(1);
   // TODO: update WiFi GPIOs
//   WIFI_GPIO2_PutVal(NULL, 1);
   Wifi_Do_Reset(true);
}

void Wifi_Do_Reset(bool StateMachineWaitForConnect) {
   // TODO: update WiFi GPIOs
//   WIFI_RESET_PutVal(NULL, 0);
   Wait(1);
   // TODO: update WiFi GPIOs
//   WIFI_RESET_PutVal(NULL, 1);
   Wait(100);

   if (0 && StateMachineWaitForConnect) {
      PowerOn_Interrupt_Count = 0;
      WifiInterruptReceived = false;
      State = Enable;
   }
}

bool Wifi_Send(Message *message) {
   Queue_Message(&outgoingMessageQueue, message);
   return true;
}

Message* Wifi_Receive() {
   Message *message = NULL;
   if (Has_Messages(&incomingMessageQueue) == true) {
      message = Dequeue_Message(&incomingMessageQueue);
      return message;
   }
   return NULL;
}

Wifi_States Wifi_Get_State() {
   return State;
}
