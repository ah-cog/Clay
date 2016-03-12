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
//#include "Message.h"
#include "Messenger.h"

void Wifi_Test()
{
   Wifi_Enable();

   Message *message = NULL;

   for (;;) {
	  // Step state machine
      Wifi_State_Step ();

      // Monitor communication message queues.
      if (Has_Messages (&incomingMessageQueue) == TRUE) {
    	  message = Wifi_Receive ();
    	  if (message != NULL) {
    		  Wifi_Send (message);
    	  }
      }
   }
}

