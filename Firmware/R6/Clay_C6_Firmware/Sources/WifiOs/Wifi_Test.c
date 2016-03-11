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
#include "Message.h"

void Wifi_Test()
{
   Wifi_Enable();

   Message m;
   int i = 0;
   bool SendAnyway = FALSE;

   for (;;)
   {
      Wifi_State_Step();

      if (SendAnyway || Wifi_Receive(&m))
      {
         Wifi_Send(&m);
      }

   }
}

