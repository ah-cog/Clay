/*
 * WifiOs.c
 *
 *  Created on: Feb 18, 2016
 *      Author: thebh
 */

#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#include "PE_Types.h"
#include "WifiOs.h"
#include "WIFI_GPIO0.h"
#include "WIFI_GPIO2.h"
#include "WIFI_CHIP_EN.h"
#include "WIFI_RESET.h"
#include "ESP8266_Serial.h"
#include "Ring_Buffer.h"
#include "Clock.h"

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

static LDD_TDeviceData * WIFI_GPIO0_DeviceDataPtr;
static uint8_t PowerOn_Interrupt_Count;

bool Wifi_Enable()
{
   bool rval = FALSE;

   Wifi_Message_Available = FALSE;

   // Initialize the ESP8266 device data structure
   deviceData.handle = ESP8266_Serial_Init(&deviceData);
   deviceData.isSent = FALSE;
   deviceData.rxChar = '\0';
   deviceData.rxPutFct = Ring_Buffer_Put;        // ESP8266_RxBuf_Put;

   // Read any pending data to "clear the line"
   while (ESP8266_Serial_ReceiveBlock(deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof(deviceData.rxChar)) != ERR_OK)
   {

   }

   State = Idle;

   WIFI_CHIP_EN_PutVal(NULL, 1);
   Wifi_Set_Operating_Mode();

   WifiInterruptReceived = FALSE;
   WifiSetProgramMode = FALSE;

   pendingTransmitByteCount = 0;
   interruptRxTime = 0;

   rval = TRUE;

   return rval;
}

void Wifi_State_Step()
{

   //TODO: if a transmission was waiting, we'll lose it here. Look at pendingbytecount? Maybe we don't care?
   //      This may just be test code, actually. The button handler in events.c is setting WifiSetProgramMode
   if (State != Transmission_Waiting && State != Programming && WifiSetProgramMode)
   {
      Wifi_Set_Programming_Mode();
      WifiSetProgramMode = FALSE;
   }

   switch (State)
   {
      case Enable:
      {
         if (WifiInterruptReceived)
         {
            WifiInterruptReceived = FALSE;
            ++PowerOn_Interrupt_Count;
            if (PowerOn_Interrupt_Count >= 2)
            {
               State = Idle;
            }
         }
      }
      case Programming:
      {
         //wait for the toggle again.
         if (WifiSetProgramMode || ((Millis() - programStartTime > 5000) && WifiInterruptReceived))
         {
            Wifi_Set_Operating_Mode();
            WifiSetProgramMode = FALSE;
         }
         WifiInterruptReceived = FALSE;
         break;
      }

      case Idle:
      {
         //TODO: Monitor outgoing message queue for messages too.
         //waiting for an interrupt, no tranmission pending
         if (WifiInterruptReceived)
         {
            State = Receiving_Message;

            WifiInterruptReceived = FALSE;

            Newline_Count = 0;
            Pending_Receive_Byte_Count = 0;

            interruptRxTime = Millis();

            while (ESP8266_Serial_ReceiveBlock(deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof(deviceData.rxChar))
                   == ERR_OK)
            {

            }
            Ring_Buffer_Init();

            WIFI_GPIO2_PutVal(NULL, 0);
         }

         break;
      }

      case Receiving_Message:
      {
         if (Ring_Buffer_Has_Data())
         {
            Ring_Buffer_Get(inBuffer + Pending_Receive_Byte_Count);

            if (inBuffer[Pending_Receive_Byte_Count++] == '!')
            {
               WIFI_GPIO2_PutVal(NULL, 1);
               Wifi_Message_Available = TRUE;
               State = Idle;
            }
         }
         else if ((Millis() - interruptRxTime) > INTERRUPT_RX_TIMEOUT_MS)
         {
            WIFI_GPIO2_PutVal(NULL, 1);
            State = Idle;
         }

         break;
      }

      case Deserializing_Received_Message:
      {
         //TODO: deserialize. Set Buffer_Index to 0
         State = Idle;
         break;
      }

      case Serialize_Transmission:
      {
         //TODO: serialize
         State = Start_Transmission;
         break;
      }

      case Start_Transmission:
      {
         //signal to the WiFi that we're ready to send something
         WIFI_GPIO2_PutVal(NULL, 0);
         State = Transmission_Waiting;
         txStartTime = Millis();
         break;
      }

      case Transmission_Waiting:
      {
         //waiting for WiFi to OK transmission.
         //send when we get the interrupt
         if (WifiInterruptReceived)
         {
            WifiInterruptReceived = FALSE;
            deviceData.isSent = FALSE;
            ESP8266_Serial_SendBlock(deviceData.handle, outBuffer, pendingTransmitByteCount);
            State = Transmission_Sent;
         }
         else if (Millis() - txStartTime > INTERRUPT_TX_TIMEOUT_MS)
         {
            WIFI_GPIO2_PutVal(NULL, 1);
            State = Idle;
         }

         break;
      }

      case Transmission_Sent:
      {
         //transmission has been sent. back to idle for now, I guess
         if (deviceData.isSent)
         {
            WIFI_GPIO2_PutVal(NULL, 1);
            State = Idle;
         }
         break;
      }

      default:
      {
         //this should never happen. let's pretend it didn't.
         State = Idle;
         break;
      }
   }
}

void Wifi_Set_Programming_Mode()
{
   State = Programming;
   WifiInterruptReceived = TRUE;
   programStartTime = Millis();
   Wait(1);
   WIFI_GPIO0_PutVal(NULL, 0);
   WIFI_GPIO2_PutVal(NULL, 1);
   Wifi_Do_Reset(FALSE);
}

///this may not be needed. The ESP seems to come out of programming mode automatically.
void Wifi_Set_Operating_Mode()
{
   State = Idle;
   WIFI_GPIO0_PutVal(NULL, 1);
   Wait(1);
   WIFI_GPIO2_PutVal(NULL, 1);
   Wifi_Do_Reset(TRUE);
}

void Wifi_Do_Reset(bool StateMachineWaitForConnect)
{
   WIFI_RESET_PutVal(NULL, 0);
   Wait(1);
   WIFI_RESET_PutVal(NULL, 1);
   Wait(100);

   if (0 && StateMachineWaitForConnect)
   {
      PowerOn_Interrupt_Count = 0;
      WifiInterruptReceived = FALSE;
      State = Enable;
   }
}

void Wifi_Send(void * data, uint32_t length)
{
   if (State != Idle)
   {
      return;
   }
   //TODO: NQ the message. The state machine will pick it up in idle.
   pendingTransmitByteCount = length;
   memcpy(outBuffer, data, (length <= OUT_BUFFER_LENGTH) ? length : OUT_BUFFER_LENGTH);
   State = Serialize_Transmission;
}

uint32_t Wifi_Receive(void * data)
{
   if (!Wifi_Message_Available)
      return 0;

   uint32_t rval = Pending_Receive_Byte_Count > IN_BUFFER_LENGTH ? IN_BUFFER_LENGTH : Pending_Receive_Byte_Count;

   if (rval)
   {
      memcpy(data, inBuffer, rval);
      Pending_Receive_Byte_Count = 0;
   }

   Wifi_Message_Available = FALSE;

   return rval;
}

Wifi_States Wifi_Get_State()
{
   return State;
}
