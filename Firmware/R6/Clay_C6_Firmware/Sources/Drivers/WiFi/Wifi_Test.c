/*
 * wifi_test.c
 *
 *  Created on: Feb 18, 2016
 *      Author: thebh
 */
#include "PE_Types.h"
#include "WiFi.h"
#include "Clock.h"
#include "Ring_Buffer.h"
//#include "Message.h"
#include "Messenger.h"
#include "AddressSerialization.h"

void Wifi_Test()
{
   Enable_WiFi();

   Message *message = NULL;
   uint32_t lastMessageSendTime = 0;
   uint32_t messageSendPeriod = 10000;

#if 0
   struct sockaddr_in DestinationAddr;

   memset(&DestinationAddr, 0, sizeof(DestinationAddr));
   char testMessageStr[] = "testacool";
   char addrStr[] = "192.168.1.2";
   char serializedAddr[100];
   Message_Type mt;

   DestinationAddr.sin_family = AF_INET
   ;
   inet_aton(addrStr, &DestinationAddr.sin_addr.s_addr);
   DestinationAddr.sin_port = htons(4445);
   DestinationAddr.sin_len = sizeof(DestinationAddr);

   Serialize_Address(&DestinationAddr, serializedAddr, 100, MESSAGE_TYPE_UDP);
   memset(&DestinationAddr, 0, sizeof(DestinationAddr));
   Deserialize_Address(serializedAddr, 100, &DestinationAddr, &mt);
   memset(&serializedAddr, 0, 100);
   Serialize_Address(&DestinationAddr, serializedAddr, 100, MESSAGE_TYPE_UDP);

   message = Create_Message(testMessageStr);

   Set_Message_Destination(message, serializedAddr);
#endif

#if 0
   char addrStr[] = "UDP,255.255.255.255:4445!";
   char testMsg[] = "hey hey mama";

   message = Create_Message(testMsg);
   Set_Message_Destination(message, addrStr);
#endif

   for (;;)
   {
      // Step state machine
      Wifi_State_Step();

//      if (Wifi_Get_State() != Programming
//          && !Has_Messages(&outgoingMessageQueue)
//          && Millis() - lastMessageSendTime > messageSendPeriod)
//      {
//         Wifi_Send(message);
//         lastMessageSendTime = Millis();
//      }

//      // Monitor communication message queues.
      if (Has_Messages(&incomingMessageQueue) == TRUE)
      {
         message = Wifi_Receive();
         if (message != NULL)
         {
            Wifi_Send(message);
         }
      }
   }
}

