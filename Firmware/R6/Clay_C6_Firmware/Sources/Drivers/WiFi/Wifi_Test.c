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
   uint32_t messageSendPeriod = 100;

   bool repeat_send = FALSE;
   bool request_connect = FALSE;
   bool get_ip = FALSE;

   char * ssid = "hefnet";
   char * password = "h3fn3r_is_better_than_me";

   char type_str[] = "udp";
   char dest_addr[] = "192.168.1.255:4446";
   char source_addr[] = "192.168.1.16:4445";
   char message_content[] = "broadcast message broadcast message broadcast message broadcast message broadcast message broadcast message e";

   for (;;) {

      // Step state machine
      Wifi_State_Step();
      Button_Periodic_Call();

#if 1
      //echo received messages
      if (Has_Messages(&incomingWiFiMessageQueue) == TRUE) {
         message = Wifi_Receive();
         if (message != NULL && strcmp(message->type, "INFO")) {
            char * temp = message->destination;
            message->destination = message->source;
            message->source = temp;

            Wifi_Send(message);
         }
      }
#endif

#define TEST_COMMAND_REPEAT 0
#if TEST_COMMAND_REPEAT
      if(Has_Messages(&incomingWiFiMessageQueue))
      {
         message = Wifi_Receive();
         Wait(1);
      }
#endif

      //repeatedly send a message
      if (repeat_send
          && Wifi_Get_State() != Programming
          && !Has_Messages(&outgoingWiFiMessageQueue)
          && Millis() - lastMessageSendTime > messageSendPeriod) {

#if TEST_COMMAND_REPEAT
         WiFi_Request_Get_Internet_Address();
#else
         message = Create_Message(message_content);
         Set_Message_Type(message, type_str);
         Set_Message_Source(message, source_addr);
         Set_Message_Destination(message, dest_addr);

         Wifi_Send(message);
#endif

         lastMessageSendTime = Millis();
      }

      if (request_connect) {
         request_connect = FALSE;
         WiFi_Request_Connect(ssid, password);
      }

      if (get_ip) {
         get_ip = FALSE;
         WiFi_Request_Get_Internet_Address();
      }
   }

}

