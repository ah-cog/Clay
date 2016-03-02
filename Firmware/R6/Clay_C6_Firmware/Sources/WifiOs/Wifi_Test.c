/*
 * wifi_test.c
 *
 *  Created on: Feb 18, 2016
 *      Author: thebh
 */
#include "PE_Types.h"
#include "WifiOs.h"
#include "Clock.h"
#include "Ring_Buffer.h"

void Wifi_Test()
{
   Wifi_Enable();

   bool LoopWifiReset = TRUE;
   bool IntReceived = FALSE;

   uint32_t dataCount;

//   uint8_t data[] = "don't ald tormp wongs\n3232235778,2,16,61838,0,0,0,0,0,0,0,0\n";
//   uint8_t data[] = "don't ald tormp wongs\n3232235778,2,16,61838,0,0,0,0,0,0,0,0!";
   uint8_t data[1024];


   uint32_t lastSend;
   uint32_t sendTime = 10;
   bool derp = FALSE;

   for (;;)
   {
      Wifi_State_Step();

      if (derp)
      {
         if (Wifi_Get_State() != Programming && ((Millis() - lastSend) > sendTime))
         {
//            ESP8266_Serial_SendBlock(deviceData.handle, data, 60);
            Wifi_Send(data, 60);
            lastSend = Millis();
         }
      }
      else
      {

         if (dataCount = Wifi_Receive(data))
         {
            Wifi_Send(data, dataCount);
            sendTime = Millis();
         }
      }
   }
}

