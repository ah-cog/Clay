////Includes //////////////////////////////////////////////////////
#include "WiFi.h"
#include "Application.h"
#include "Clock.h"
#include "Power_Manager.h"
#include "Button.h"

#include "program_flash.h"
#include "Multibyte_Ring_Buffer.h"
#include "Wifi_Message_Serialization.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////

////Local Prototypes///////////////////////////////////////////////
void Flash_Test();
void Wifi_Test();

////Global implementations ////////////////////m////////////////////

void Application(void) {

   //Init power manager to hold PowerOn line high so that our supply doesn't shut off.
   Power_Manager_Enable();
   //enable button so the user can shut us down.
   Button_Enable();

   Button_Register_Press_Response(Wifi_Set_Programming_Mode);
   Button_Register_Hold_Response(500, Wifi_Set_Operating_Mode);

   uint32_t enable_wifi_start_time_ms;
   Message * temp_message_ptr;

   uint8_t status = Enable_Clock();
   status = Start_Clock();

   Initialize_Unit_UUID();

   Initialize_Bootloader();

//   Multibyte_Ring_Buffer_Test();
//   Wifi_Test();
//   Flash_Test();

   wifi_connected = FALSE;
   local_address_received = FALSE;

   //if (!Verify_Firmware () || (/*!Has_Latest_Firmware()*/ SharedData.ApplicationUpdateAvailable && Has_User_Requested_Update ())) {
   if (!Verify_Firmware() || (SharedData.ApplicationUpdateAvailable && Has_User_Requested_Update())) {
//   if (0) {

      status = Enable_WiFi(SSID_DEFAULT, PASSWORD_DEFAULT);
      enable_wifi_start_time_ms = Millis();
      while ((Millis() - enable_wifi_start_time_ms) < 5000) {
         //see if we can catch the WiFi's messages during connection
         Monitor_Periodic_Events();
      }

#if 0
      Wifi_Set_Programming_Mode();

      while (Wifi_Get_State() == Programming)
      ;
#endif

      //take all the messages out of the queue, see if we got the two we care about: connection status and
      while (Has_Messages(&incomingWiFiMessageQueue)) {
         temp_message_ptr = Wifi_Receive();

         if (temp_message_ptr != NULL) {
            if (!wifi_connected) {
               wifi_connected = Parse_Wifi_Connection_Message(temp_message_ptr);
            }

            if (!local_address_received) {
               local_address_received = Parse_Wifi_Connection_Message(temp_message_ptr);
            }

            Delete_Message(temp_message_ptr);
         }
      }

      while (!wifi_connected) {
         wifi_connected = Get_WiFi_Connection_Status();
         Wait(1000);
      }

      while (!local_address_received) {
         local_address_received = Get_Local_Address();
         Wait(1000);
      }

      enable_wifi_start_time_ms = Millis();

      while (Has_Messages(&incomingWiFiMessageQueue) || (Millis() - enable_wifi_start_time_ms) < 2000) {
         Message * m;
         Monitor_Periodic_Events();
         m = Wifi_Receive();
         if (m != NULL) {
            Delete_Message(m);
         }
      }

      //TODO: do init stuff for wifi peripherals so we can preserve our connection?
      if (wifi_connected && local_address_received) {

         // Check if an application update is available. If so, write that value to the shared flash memory.
         if (!Has_Latest_Firmware()) {
            SharedData.ApplicationUpdateAvailable = TRUE;
         }

         // Update the current firmware if the current application doesn't verify or if the user has approved a pending update.
         if ((status = Update_Firmware()) == TRUE) {
            // TODO: Post successful download operations (i.e., update shared variables, store checksum, jump to program).
         }
      } else {
         // Error: Could not connect to Wi-Fi.

      }
   }

// Disable all interrupts before jumping to the application.
   Disable_Interrupts();

// TODO: Reset the "application key" to indicate the bootloader.
// Reset the "application key".
   SharedData.ApplicationKey = BOOTLOADER_KEY_VALUE;

// Jump to main application firmware
   Jump_To_Application();

   for (;;)
      ;
}

//static Message *message = NULL;
//static Message * outgoing_message = NULL;
//static uint32_t lastMessageSendTime = 0;
//static uint32_t messageSendPeriod = 1000;
//
//static bool echo = FALSE;
//static bool repeat_send = FALSE;
//
//static bool request_connect = FALSE;
//static bool get_ip = FALSE;
//
//static bool send_text_content = TRUE;
//static bool send_http_message = TRUE;
//
//#define MAX_SERIALIZED_LENGTH  1024
//static char serialized_message[MAX_SERIALIZED_LENGTH];
//static char type_str[] = "tcp";
//static char dest_addr[] = "192.168.1.3:3000";
//static char source_addr[] = "192.168.1.21:3000";
//
//static char text_content_type[] = "text";
//static char text_message_content[] = "GET /clay/firmware/?startByte=%d&byteCount=256 HTTP/1.1";
//static uint32_t text_message_length;
//
//static uint32_t bootloader_index = 0;
//static char http_type_str[] = "http";
//static const char http_dest_addr_format[] = "107.170.180.158:3000/clay/firmware/?startByte=%d&byteCount=512";
////static const char http_dest_addr_format[] = "192.168.1.3:3000/clay/firmware/?startByte=%d&byteCount=256";
//static char http_dest_addr[100];
//static char http_source_addr[] = "192.168.1.5:3000";
//
//static char http_text_content_type[] = "text";
//static char http_text_message_content[] = "none";
//static uint32_t http_text_message_length;
//
//static char bin_content_type[] = "bin";
//#define BIN_MESSAGE_LENGTH  256
//static char bin_message_content[BIN_MESSAGE_LENGTH];
//static int message_index = 0;
//
//static char * ssid = "hefnet";
//static char * password = "h3fn3r_is_better_than_me";
//
//static char * ssid_m = "Clay";
//static char * password_m = "redgreenblue";
//
//bool use_mobile = false;
//
//////Local implementations /////////////////////////////////////////
//void Wifi_Test() {
//   text_message_length = strlen(text_message_content);
//
//   http_text_message_length = strlen(http_text_message_content);
//
//   Enable_WiFi(ssid, password);
//
//   for (int i = 0; i < BIN_MESSAGE_LENGTH; ++i) {
//      bin_message_content[i] = i;
//   }
//
//   for (;;) {
//
//      Monitor_Periodic_Events();
//
//      if (!echo && Has_Messages(&incomingWiFiMessageQueue)) {
//         Message * temp = Wifi_Receive();
//         Delete_Message(temp);
//      }
//
//      //repeatedly send a message
//      if (repeat_send
//          && Wifi_Get_State() != Programming
//          && !Has_Messages(&outgoingWiFiMessageQueue)
//          && Millis() - lastMessageSendTime > messageSendPeriod) {
//
//         outgoing_message = Create_Message();
//
//         if (send_http_message) {
//
//            Set_Message_Type(outgoing_message, http_type_str);
//            Set_Message_Source(outgoing_message, http_source_addr);
//
//            sprintf(http_dest_addr, http_dest_addr_format, bootloader_index * 256);
//            Set_Message_Destination(outgoing_message, http_dest_addr);
//
//         } else {
//            Set_Message_Type(outgoing_message, type_str);
//            Set_Message_Source(outgoing_message, source_addr);
//            Set_Message_Destination(outgoing_message, dest_addr);
//         }
//
//         if (send_text_content) {
//            if (send_http_message) {
//               Set_Message_Content(outgoing_message, http_text_message_content, http_text_message_length);
//               Set_Message_Content_Type(outgoing_message, text_content_type);
//            } else {
//               Set_Message_Content(outgoing_message, text_message_content, text_message_length);
//               Set_Message_Content_Type(outgoing_message, text_content_type);
//            }
//         } else {
//            Set_Message_Content(outgoing_message, bin_message_content, BIN_MESSAGE_LENGTH);
//            Set_Message_Content_Type(outgoing_message, bin_content_type);
//         }
//
//         Wifi_Send(outgoing_message);
//
//         lastMessageSendTime = Millis();
//      } else if (Wifi_Get_State() == Programming) {
//         repeat_send = FALSE;
//      }
//
//      if (echo && Has_Messages(&incomingWiFiMessageQueue) == TRUE) {
//         message = Wifi_Receive();
//         if (message != NULL && strcmp(message->message_type, "status")) {
//
//            char * temp = message->destination;
//            message->destination = message->source;
//            message->source = temp;
//
//            Wifi_Send(message);
//         }
//      }
//
//      if (request_connect) {
//         request_connect = FALSE;
//         if (use_mobile) {
//            WiFi_Request_Connect(ssid_m, password_m);
//         } else {
//            WiFi_Request_Connect(ssid, password);
//         }
//      }
//
//      if (get_ip) {
//         get_ip = FALSE;
//         WiFi_Request_Get_Internet_Address();
//      }
//   }
//}

//void Flash_Test() {
//
//   uint8_t not_actual_firmware[] = "aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu ";
//   uint32_t firmware_write_index = 0;
//   uint32_t firmware_block_size = strlen(not_actual_firmware) + 1;
//
//   uint16_t checksum = 0x50;
//   uint32_t size = 0x0770;
//   uint32_t version = 0x0880;
//
//   uint16_t checksum_read;
//   uint32_t size_read;
//   uint32_t version_read;
//
//   for (;;) {
//      Erase_Program_Flash();
//      Wait(10);
//
//      Write_Program_Version(++version);
//      Wait(10);
//
//      Write_Program_Checksum((++checksum));
//      Wait(10);
//
//      Write_Program_Size(++size);
//      Wait(10);
//
//      while (firmware_write_index * firmware_block_size < APP_END_ADDR) {
//         Write_Firmware_Bytes((firmware_write_index * firmware_block_size) + APP_START_ADDR,
//                              not_actual_firmware,
//                              firmware_block_size);
//         ++firmware_write_index;
//      }
//
//      firmware_write_index = 0;
//
//      checksum_read = Read_Program_Checksum();
//      size_read = Read_Program_Size();
//      version_read = Read_Program_Version();
//   }
//
//}
