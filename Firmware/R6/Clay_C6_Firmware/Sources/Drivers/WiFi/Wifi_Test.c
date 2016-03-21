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

void Wifi_Test() {
   Enable_WiFi();

   Message *message = NULL;
   uint32_t lastMessageSendTime = 0;
   uint32_t messageSendPeriod = 6000;

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
   //   Set_Access_Point();

//   char addrStr[] = "UDP,192.168.1.1:1000";
//   char testMsg[] = "SETAP hefnetm,dips00BOYNEdo$!&";

   char addrStr[] = "CMD,\x12";
   char testMsg[] = "SETAP hefnet,h3fn3r_is_better_than_me";

   message = Create_Message(testMsg);
   Set_Message_Destination(message, addrStr);
#endif

//echo and repeated send. include one of the blocks above.
#if 0
   for (;;) {

      // Step state machine
      Wifi_State_Step();

      if (Wifi_Get_State() != Programming
            && !Has_Messages(&outgoingMessageQueue)
            && Millis() - lastMessageSendTime > messageSendPeriod) {
         message = Create_Message(testMsg);
         Set_Message_Destination(message, addrStr);
         Wifi_Send(message);
         lastMessageSendTime = Millis();
      }
   }

#endif
#if 1
   char addrStr[] = "CMD,\x12";
   char testMsg[] = "SETAP hefnet,h3fn3r_is_better_than_me";

   Wait(5000);

   message = Create_Message(testMsg);
   Set_Message_Destination(message, addrStr);
   Wifi_Send(message);

   for (;;) {

      // Step state machine
      Wifi_State_Step();

      //Monitor communication message queues.
      if (Has_Messages(&incomingMessageQueue) == TRUE) {
         message = Wifi_Receive();
         if (message != NULL) {
            Wifi_Send(message);
         }
      }
   }
#endif

//serialization tests.
#if 0
   char testCmdContent[] = "AP";
   char testTcpStr[] = "TCP,10.0.0.2:56012!";
   char testUdpStr[] = "UDP,10.0.0.2:56012!";
   char testCmdStr[] = "CMD";

   struct sockaddr_in testTcpStruct;
   struct sockaddr_in testUdpStruct;
   struct sockaddr_in testCmdStruct;

   Message_Type tcpType;
   Message_Type udpType;
   Message_Type cmdType;

   Message * tcpMsg = Create_Message(testCmdContent);
   Set_Message_Destination(tcpMsg, testTcpStr);

   Message * udpMsg = Create_Message(testCmdContent);
   Set_Message_Destination(udpMsg, testUdpStr);

   Message * cmdMsg = Create_Message(testCmdContent);
   Set_Message_Destination(cmdMsg, testCmdStr);

   for (;;)
   {
      Deserialize_Address(testTcpStr, strlen(testTcpStr), &testTcpStruct, &tcpType);
      Deserialize_Address(testUdpStr, strlen(testUdpStr), &testUdpStruct, &udpType);
      Deserialize_Address(testCmdStr, strlen(testCmdStr), &testCmdStruct, &cmdType);

      Wait(100);
   }
#endif
}

