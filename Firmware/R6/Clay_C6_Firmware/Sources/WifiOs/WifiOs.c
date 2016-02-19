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

#define OUT_BUFFER_LENGTH           100
#define IN_BUFFER_LENGTH            100
#define INTERRUPT_RX_TIMEOUT_MS     100
#define INTERRUPT_TX_TIMEOUT_MS     1000

ESP8266_UART_Device deviceData;
bool WifiInterruptReceived;
bool WifiSetProgramMode;

static uint32_t pendingTransmitByteCount;
static uint32_t pendingReceiveByteCount;

static uint8_t outBuffer[OUT_BUFFER_LENGTH] = "test message, yo\r\n";
static uint8_t inBuffer[IN_BUFFER_LENGTH];

static WIFI_STATE CurrentState;
static uint32_t interruptRxTime;
static uint32_t txStartTime;

static LDD_TDeviceData * WIFI_GPIO0_DeviceDataPtr;

bool Wifi_Enable()
{
   bool rval = FALSE;

   WIFI_GPIO0_DeviceDataPtr = WIFI_GPIO0_Init(WIFI_GPIO0_DeviceDataPtr);

   // Initialize the ESP8266 device data structure
   deviceData.handle = ESP8266_Serial_Init(&deviceData);
   deviceData.isSent = FALSE;
   deviceData.rxChar = '\0';
   deviceData.rxPutFct = Ring_Buffer_Put;        // ESP8266_RxBuf_Put;

   // Initialize a buffer for storing incoming data from the ESP8266
   Ring_Buffer_Init();        // ESP8266_RxBuf_Init ();

   // Read any pending data to "clear the line"
   while (ESP8266_Serial_ReceiveBlock(deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof(deviceData.rxChar)) != ERR_OK)
   {

   }

   Wifi_Set_Operating_Mode();

   WifiInterruptReceived = FALSE;
   WifiSetProgramMode = FALSE;

   pendingTransmitByteCount = 0;
   interruptRxTime = 0;

   CurrentState = IDLE;

   rval = TRUE;

   return rval;
}

void Wifi_State_Step()
{

   //TODO: if a transmission was waiting, we'll lose it here. Look at pendingbytecount? Maybe we don't care?
   //      This may just be test code, actually. The button handler in events.c is setting WifiSetProgramMode
   if (CurrentState != TRANSMISSION_WAITING && CurrentState != PROGRAMMING && WifiSetProgramMode)
   {
      Wifi_Set_Programming_Mode();
      WifiSetProgramMode = FALSE;
   }

   switch (CurrentState)
   {
      case PROGRAMMING:
      {
         //wait for the toggle again.
         if (WifiSetProgramMode)
         {
            Wifi_Set_Operating_Mode();
            WifiSetProgramMode = FALSE;
         }
         break;
      }

      case IDLE:
      {
         //TODO: look for ternaries
         //waiting for an interrupt, no tranmission pending
         if (WifiInterruptReceived)
         {
            //TODO: update the state in interrupt handler?
            //TODO: continue into next case?
            CurrentState = RECEIVE_INTERRUPT;
            WifiInterruptReceived = FALSE;
            interruptRxTime = Millis();
            WIFI_GPIO2_PutVal(NULL, 0);

            Ring_Buffer_Init();
         }

         break;
      }

      case RECEIVE_INTERRUPT:
      {
         if (WIFI_GPIO0_GetPortValue(NULL) & WIFI_GPIO0_GPIO0_MASK || Millis() - interruptRxTime > INTERRUPT_RX_TIMEOUT_MS)
         {
            pendingReceiveByteCount = Ring_Buffer_NofElements();
            int bufIdx = 0;
            while (!Ring_Buffer_Get(inBuffer + bufIdx++))
               ;
            WIFI_GPIO2_PutVal(NULL, 1);
            CurrentState = IDLE;
         }
         break;
      }

      case START_TRANSMISSION:
      {
         //signal to the WiFi that we're ready to send something
         WIFI_GPIO2_PutVal(NULL, 0);
         CurrentState = TRANSMISSION_WAITING;
         txStartTime = Millis();
         break;
      }

      case TRANSMISSION_WAITING:
      {
         //waiting for WiFi to OK transmission.
         //send when we get the interrupt
         if (WifiInterruptReceived || Millis() - txStartTime > INTERRUPT_TX_TIMEOUT_MS)
         {

            if (WifiInterruptReceived)
            {
               ESP8266_Serial_SendBlock(deviceData.handle, outBuffer, pendingTransmitByteCount);
               WifiInterruptReceived = FALSE;
               CurrentState = TRANSMISSION_SENT;
            }
            else
            {
               CurrentState = IDLE;
            }
            WIFI_GPIO2_PutVal(NULL, 1);
         }

         break;
      }

      case TRANSMISSION_SENT:
      {
         //transmission has been sent. back to idle for now, I guess
         CurrentState = IDLE;
         break;
      }

      default:
      {
         //this should never happen. let's pretend it didn't.
         CurrentState = IDLE;
         break;
      }
   }
}

void Wifi_Set_Programming_Mode()
{
   CurrentState = PROGRAMMING;

   WIFI_GPIO0_SetPortEventCondition(NULL, WIFI_GPIO0_GPIO0_MASK, LDD_GPIO_DISABLED);
   WIFI_GPIO0_SetPortOutputDirection(NULL, WIFI_GPIO0_GPIO0_MASK, WIFI_GPIO0_GPIO0_MASK);
   Wait(1);
   WIFI_GPIO0_SetPortValue(NULL, ~WIFI_GPIO0_GPIO0_MASK);
   WIFI_GPIO2_PutVal(NULL, 1);
   Wifi_Do_Reset();
}

void Wifi_Set_Operating_Mode()
{
   CurrentState = IDLE;

   WIFI_GPIO0_SetPortInputDirection(NULL, WIFI_GPIO0_GPIO0_MASK);
   WIFI_GPIO0_SetPortEventCondition(NULL, WIFI_GPIO0_GPIO0_MASK, LDD_GPIO_FALLING);
   Wait(1);
   WIFI_GPIO2_PutVal(NULL, 1);
   Wifi_Do_Reset();
}

void Wifi_Do_Reset()
{
   WIFI_RESET_PutVal(NULL, 0);
   Wait(2);
   WIFI_RESET_PutVal(NULL, 1);
   Wait(2);
}

void Wifi_Send(void * data, uint32_t length)
{
   CurrentState = START_TRANSMISSION;
   pendingTransmitByteCount = length;
   memcpy(outBuffer, data, length < OUT_BUFFER_LENGTH ? length : OUT_BUFFER_LENGTH);
}

uint32_t Wifi_Receive(void * data)
{
   uint32_t rval = pendingReceiveByteCount > IN_BUFFER_LENGTH ? IN_BUFFER_LENGTH : pendingReceiveByteCount;

   if (rval)
   {
      memcpy(data, inBuffer, rval);
      pendingReceiveByteCount = 0;
   }

   return rval;     //TODO: we need a better way to get this shit.
}

WIFI_STATE Wifi_Get_State()
{
   return CurrentState;
}
