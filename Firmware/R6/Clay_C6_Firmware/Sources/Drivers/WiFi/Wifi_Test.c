/*
 * wifi_test.c
 *
 *  Created on: Feb 18, 2016
 *      Author: thebh
 */
#include <Message.h>
#include "PE_Types.h"
#include "WiFi.h"
#include "Clock.h"
#include "Ring_Buffer.h"
#include "Button.h"
#include "GPIO.h"
//#include "Message.h"

void Wifi_Test() {

   Enable_Channels();
   Button_Enable();
   Enable_WiFi();

   Button_Register_Press_Response(Wifi_Set_Programming_Mode);

   Message *message = NULL;
   uint32_t lastMessageSendTime = 0;
   uint32_t messageSendPeriod = 6000;

#if 0
   struct sockaddr_in DestinationAddr;

   memset(&DestinationAddr, 0, sizeof(DestinationAddr));
   char testMessageStr[] = "testacool";
   char addr_string[] = "192.168.1.2";
   char serializedAddr[100];
   Message_Type mt;

   DestinationAddr.sin_family = AF_INET
   ;
   inet_aton(addr_string, &DestinationAddr.sin_addr.s_addr);
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

   char addr_string[] = "CMD,\x12";
   char commands[] = "SETAP hefnet,h3fn3r_is_better_than_me";

   message = Create_Message(commands);
   Set_Message_Destination(message, addr_string);
#endif

//echo and repeated send. include one of the blocks above.
#if 0
   for (;;) {

      // Step state machine
      Wifi_State_Step();

      if (Wifi_Get_State() != Programming
            && !Has_Messages(&outgoingWiFiMessageQueue)
            && Millis() - lastMessageSendTime > messageSendPeriod) {
         message = Create_Message(commands);
         Set_Message_Destination(message, addr_string);
         Wifi_Send(message);
         lastMessageSendTime = Millis();
      }
   }

#endif

#if 0

   char addr_string[] = ":";
   char commands[] = "GET_IP";

   Wait(5000);

   int last_ip_get = 0;

   for (;;) {

      // Step state machine
      Wifi_State_Step();

      //Monitor communication message queues.
      if (Has_Messages(&incomingWiFiMessageQueue) == TRUE) {
         message = Wifi_Receive();
         if (message != NULL && strcmp(message->type, "INFO")) {
            char * temp = message->destination;
            message->destination = message->source;
            message->source = temp;

            Wifi_Send(message);
         }
      }

//      if (Millis() - last_ip_get > 5000) {
//         Message * get_ip_message = Create_Message(testMsg);
//         Set_Message_Type(get_ip_message, "CMD");
//         Set_Message_Destination(get_ip_message, addrStr);
//         Set_Message_Source(get_ip_message, addrStr);
//
//         Wifi_Send(get_ip_message);
//         last_ip_get = Millis();
//      }
   }
#endif

   //command tests
#if 1
   char addr_string[] = ":";
   char *commands[] = { "GET_IP", "GET_GATEWAY", "GET_SUBNET", "SETAP hefnetm, dips00BOYNEdo$!&", "", "", "", "", };
   int command_count = 4;
   int test_message_index = 0;
   int period_ms = 5000;

   int last_ip_get = 0;

   for (;;) {

      // Step state machine
      Wifi_State_Step();

      if (Millis() - lastMessageSendTime >= period_ms) {
         WiFi_Request_Connect("hefnetm", "dips00BOYNEdo$!&");
//         WiFi_Request_Get_Internet_Address();
         lastMessageSendTime = Millis();
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

