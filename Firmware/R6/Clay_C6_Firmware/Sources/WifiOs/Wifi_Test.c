/*
 * wifi_test.c
 *
 *  Created on: Feb 18, 2016
 *      Author: thebh
 */
#include "PE_Types.h"
#include "WifiOs.h"

void Wifi_Test()
{
   Wifi_Enable();
   Wifi_Set_Operating_Mode();

   bool LoopWifiReset = TRUE;
   bool IntReceived = FALSE;

   uint32_t dataCount;
   uint8_t data[100];

   for (;;)
   {
      Wifi_State_Step();

      if(dataCount = Wifi_Receive(data))
      {
         Wifi_Send(data, dataCount);
      }
   }
}

