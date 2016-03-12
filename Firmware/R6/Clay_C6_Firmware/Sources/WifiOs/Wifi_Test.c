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

//   Message m;
   Message *message = NULL;

   for (;;)
   {
      Wifi_State_Step();

      // Monitor communication message queues.
      if (Has_Messages (&incomingMessageQueue) == TRUE)
      {
//         message = Dequeue_Message (&incomingMessageQueue);
//         status = Process_Incoming_Message (message);
//			if (status == TRUE) {
//				Delete_Message (message);
//			}
//         Delete_Message(message);

    	  message = Wifi_Receive ();
    	  if (message != NULL) {
    		  Wifi_Send (message);
    	  }
      }



//      if (Wifi_Receive(&m))
//      {
//         Wifi_Send(&m);
//      }

   }
}

