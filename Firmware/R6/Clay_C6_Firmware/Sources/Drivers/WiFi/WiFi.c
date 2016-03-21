#include "stdint.h"
#include "stdlib.h"
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
#include "AddressSerialization.h"
#include "Messenger.h"

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

static uint8_t outBuffer[OUT_BUFFER_LENGTH] = "test message, yo\r\n";
static uint8_t inBuffer[IN_BUFFER_LENGTH];

static Wifi_States State;
static uint32_t interruptRxTime;
static uint32_t txStartTime;
static uint32_t programStartTime;

static uint8_t Newline_Count;
static uint8_t * Temp_Content;
static uint8_t * Temp_Address;

static const uint8_t Newline = '\n';

//static Message Temp_Message;
//static Message * Temp_Message_ptr;

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
   while (ESP8266_Serial_ReceiveBlock(deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof(deviceData.rxChar)) != ERR_OK) {

   }

   State = Idle;

   WIFI_CHIP_EN_PutVal(NULL, 1);
   Wifi_Set_Operating_Mode();

   WifiInterruptReceived = FALSE;
   WifiSetProgramMode = FALSE;

//   Initialize_Message_Queue(&incomingMessageQueue);
//   Initialize_Message_Queue(&outgoingMessageQueue);

   pendingTransmitByteCount = 0;
   interruptRxTime = 0;

   rval = TRUE;

   return rval;
}

void Wifi_State_Step() {

   //TODO: if a transmission was waiting, we'll lose it here. Look at pendingbytecount? Maybe we don't care?
   //      This may just be test code, actually. The button handler in events.c is setting WifiSetProgramMode
   if (State != Transmission_Wait && State != Programming && WifiSetProgramMode) {
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
         //TODO: Monitor outgoing message queue for messages too.
         //waiting for an interrupt, no tranmission pending
         if (WifiInterruptReceived) {
            State = Receive_Message;

            WifiInterruptReceived = FALSE;

            Newline_Count = 0;
            Pending_Receive_Byte_Count = 0;

            interruptRxTime = Millis();

            while (ESP8266_Serial_ReceiveBlock(deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof(deviceData.rxChar))
                   == ERR_OK) {

            }
            Ring_Buffer_Init();

            WIFI_GPIO2_PutVal(NULL, 0);
         }
//         else if (Peek_Message(&outgoingMessageQueue) != NULL)
         else if (Has_Messages(&outgoingMessageQueue) == TRUE) {
            State = Serialize_Transmission;
         }

         break;
      }

      case Receive_Message: {
         if (Ring_Buffer_Has_Data()) {
            Ring_Buffer_Get(inBuffer + Pending_Receive_Byte_Count);

            if (inBuffer[Pending_Receive_Byte_Count++] == AddressTerminator) {
               WIFI_GPIO2_PutVal(NULL, 1);
               WifiInterruptReceived = FALSE;
               Wifi_Message_Available = TRUE;
               State = Deserialize_Received_Message;
            }
         }
         else if ((Millis() - interruptRxTime) > INTERRUPT_RX_TIMEOUT_MS) {
            WIFI_GPIO2_PutVal(NULL, 1);
            WifiInterruptReceived = FALSE;
            State = Idle;
         }

         break;
      }

      case Deserialize_Received_Message: {
         Temp_Content = strtok(inBuffer, &Newline);

         Temp_Address = strtok(NULL, &Newline);

         if (Temp_Address != NULL && Temp_Content != NULL) {

            // Create message object
            Message *message = Create_Message(Temp_Content);
            Set_Message_Source(message, Temp_Address);
            Set_Message_Destination(message, Temp_Address);

            // Queue the message
            //Initialize_Message (&Temp_Message, Temp_Address, Temp_Address, Temp_Content);
            //Queue_Message (&incomingMessageQueue, &Temp_Message);
            Queue_Message(&incomingMessageQueue, message);
         }

         State = Idle;
         break;
      }

      case Serialize_Transmission: {
//		Temp_Message_ptr = Dequeue_Message (&outgoingMessageQueue);
//		snprintf (outBuffer, OUT_BUFFER_LENGTH, "%s\n",
//				Temp_Message_ptr->content);
//		strcat (outBuffer, Temp_Message_ptr->destination);
//		pendingTransmitByteCount = strlen (outBuffer);

         Message *message = Dequeue_Message(&outgoingMessageQueue);
         snprintf(outBuffer, OUT_BUFFER_LENGTH, "%s\n", message->content);
         strcat(outBuffer, message->destination);
         pendingTransmitByteCount = strlen(outBuffer);
         Delete_Message(message);

         State = Start_Transmission;
         break;
      }

      case Start_Transmission: {
         //signal to the WiFi that we're ready to send something
         WIFI_GPIO2_PutVal(NULL, 0);
         State = Transmission_Wait;
         txStartTime = Millis();
         break;
      }

      case Transmission_Wait: {
         //waiting for WiFi to OK transmission.
         //send when we get the interrupt
         if (WifiInterruptReceived) {
            WifiInterruptReceived = FALSE;
            deviceData.isSent = FALSE;
            ESP8266_Serial_SendBlock(deviceData.handle, outBuffer, pendingTransmitByteCount);
            State = Transmission_Sent;
         }
         else if (Millis() - txStartTime > INTERRUPT_TX_TIMEOUT_MS) {
            WIFI_GPIO2_PutVal(NULL, 1);
            State = Idle;
         }

         break;
      }

      case Transmission_Sent: {
         //transmission has been sent. back to idle for now, I guess
         if (deviceData.isSent) {
            WIFI_GPIO2_PutVal(NULL, 1);
            WifiInterruptReceived = FALSE;
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
//	if (Queue_Full (&outgoingMessageQueue)) {
//		return FALSE;
//	}

   Queue_Message(&outgoingMessageQueue, message);
   return TRUE;
}

Message* Wifi_Receive() {
   Message *message = NULL;
   if (Has_Messages(&incomingMessageQueue) == TRUE) {
      message = Dequeue_Message(&incomingMessageQueue);
      return message;
   }
   return NULL;
}

Wifi_States Wifi_Get_State() {
   return State;
}
