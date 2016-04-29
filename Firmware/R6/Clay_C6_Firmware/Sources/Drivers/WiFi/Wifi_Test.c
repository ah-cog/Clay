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
#include "Power_Manager.h"

void Wifi_Test() {

   char * ssid = "hefnet";
   char * password = "h3fn3r_is_better_than_me";

   char * ssid_m = "Clay";
   char * password_m = "redgreenblue";

   bool use_mobile = false;
//   char * ssid_m = "hefnetm";
//   char * password_m = "dips00BOYNEdo$!&";

   Power_Manager_Enable();
   Initialize_Channels();
   Channel_Enable_All();
   Button_Enable();
   Enable_WiFi(ssid, password);

   Button_Register_Press_Response(Wifi_Set_Programming_Mode);
   Button_Register_Hold_Response(1000, Wifi_Set_Operating_Mode);

   Message *message = NULL;
   Message * outgoing_message = NULL;
   uint32_t lastMessageSendTime = 0;
   uint32_t messageSendPeriod = 1000;

   bool echo = TRUE;
   bool repeat_send = FALSE;
   bool request_connect = FALSE;
   bool get_ip = FALSE;

   char type_str[] = "http";
   char dest_addr[] = "107.170.180.158:3000/clay/firmware/size";
//   char dest_addr[] = "192.168.1.3:3000/clay/firmware/size";
   char source_addr[] = "192.168.1.21:3000";
//   char message_content_template[] = "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm%d";
//   char message_content[256];
   char message_content[] = "none";
   int message_index = 0;

   for (;;) {

      // Step state machine
      Wifi_State_Step();
      Button_Periodic_Call();

#if 0
      //echo received messages
      if (echo && Has_Messages(&incomingWiFiMessageQueue) == TRUE) {
         message = Wifi_Receive();
         if (message != NULL && strcmp(message->type, "status")) {

//            sprintf(message_content, message_content_template, ++message_index);
//
//            outgoing_message = Create_Message(message_content);
//            Set_Message_Type(outgoing_message, type_str);
//            Set_Message_Source(outgoing_message, source_addr);
//            Set_Message_Destination(outgoing_message, dest_addr);

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

         outgoing_message = Create_Message(message_content);
         Set_Message_Type(outgoing_message, type_str);
         Set_Message_Source(outgoing_message, source_addr);
         Set_Message_Destination(outgoing_message, dest_addr);

         Wifi_Send(outgoing_message);
#endif

         lastMessageSendTime = Millis();
      } else if (Wifi_Get_State() == Programming) {
         repeat_send = FALSE;
      }

      if (request_connect) {
         request_connect = FALSE;
         if (use_mobile) {
            WiFi_Request_Connect(ssid_m, password_m);
         } else {
            WiFi_Request_Connect(ssid, password);
         }
      }

      if (get_ip) {
         get_ip = FALSE;
         WiFi_Request_Get_Internet_Address();
      }
   }

}

///setap test code.
//   char * ssid = "hefnet";
//   char * password = "h3fn3r_is_better_than_me";
//
//   //   char * ssid_m = "Clay";
//   //   char * password_m = "redgreenblue";
//
//   char * ssid_m = "hefnetm";
//   char * password_m = "dips00BOYNEdo$!&";
//
//   bool use_mobile = false;
//   bool request_connect = false;
//
//   if (request_connect) {
//      request_connect = FALSE;
//      if (use_mobile) {
//         WiFi_Request_Connect(ssid_m, password_m);
//      } else {
//         WiFi_Request_Connect(ssid, password);
//      }
//   }
