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

   Multibyte_Ring_Buffer_Test();
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
         temp_message_ptr = Dequeue_Message(&incomingWiFiMessageQueue);

         if (!wifi_connected) {
            wifi_connected = Parse_Wifi_Connection_Message(temp_message_ptr);
         }

         if (!local_address_received) {
            local_address_received = Parse_Wifi_Connection_Message(temp_message_ptr);
         }
      }

      while (!wifi_connected) {
         wifi_connected = Get_WiFi_Connection_Status();
         Wait(100);
      }

      while (!local_address_received) {
         local_address_received = Get_Local_Address();
         Wait(100);
      }

      enable_wifi_start_time_ms = Millis();

      while (Has_Messages(&incomingWiFiMessageQueue) || (Millis() - enable_wifi_start_time_ms) < 2000) {
         Message * m;
         Monitor_Periodic_Events();
         m = Dequeue_Message(&incomingWiFiMessageQueue);
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

////Local implementations /////////////////////////////////////////
void Wifi_Test() {

   char * ssid = "hefnet";
   char * password = "h3fn3r_is_better_than_me";

   char * ssid_m = "Clay";
   char * password_m = "redgreenblue";

   bool use_mobile = false;
//   char * ssid_m = "hefnetm";
//   char * password_m = "dips00BOYNEdo$!&";

   Power_Manager_Enable();
   Button_Enable();
   Enable_WiFi(ssid, password);

   Button_Register_Press_Response(Wifi_Set_Programming_Mode);
   Button_Register_Hold_Response(1000, Wifi_Set_Operating_Mode);

   Message *message = NULL;
   Message * outgoing_message = NULL;
   uint32_t lastMessageSendTime = 0;
   uint32_t messageSendPeriod = 1000;

   bool echo = FALSE;
   bool repeat_send = FALSE;
   bool request_connect = FALSE;
   bool get_ip = FALSE;
   bool send_text_content = TRUE;

   bool request_firmware_size = FALSE;

   const uint32_t max_serialized_length = 1024;
   char serialized_message[max_serialized_length];
   char type_str[] = "tcp";
   char dest_addr[] = "192.168.1.3:3000";
   char source_addr[] = "192.168.1.21:3000";

   char text_content_type[] = "text";
   char text_message_content[] = "this is my test message, yo. i can put all the \t's and \f's in it that i want and no one is going to give a hoot. how about that? good golly, this is some more text over here, and look what i brought along that's right its some tabs \t\t\t\t\t\t lots of tabs \t\t\t\t\t\t \t\a\bs those probably arent even all special charachters. i bet i get an error when i try to build! nope, it was a warning, and the only one that was a problem was \\s!";
   uint32_t text_message_length = strlen(text_message_content);

   char bin_content_type[] = "bin";
   uint32_t bin_message_length = 256;
   char bin_message_content[bin_message_length];
   int message_index = 0;

   for (int i = 0; i < bin_message_length; ++i) {
      bin_message_content[i] = i;
   }

   for (;;) {

      Monitor_Periodic_Events();

      //repeatedly send a message
      if (repeat_send
          && Wifi_Get_State() != Programming
          && !Has_Messages(&outgoingWiFiMessageQueue)
          && Millis() - lastMessageSendTime > messageSendPeriod) {

         outgoing_message = Create_Message();

         Set_Message_Type(outgoing_message, type_str);
         Set_Message_Source(outgoing_message, source_addr);
         Set_Message_Destination(outgoing_message, dest_addr);
         if (send_text_content) {
            Set_Message_Content(outgoing_message, text_message_content, text_message_length);
            Set_Message_Content_Type(outgoing_message, text_content_type);
         } else {
            Set_Message_Content(outgoing_message, bin_message_content, bin_message_length);
            Set_Message_Content_Type(outgoing_message, bin_content_type);
         }

         Serialize_Message_With_Message_Header(outgoing_message, serialized_message, max_serialized_length);

         Wifi_Send(outgoing_message);

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

void Flash_Test() {

   uint8_t not_actual_firmware[] = "aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu aoeu ";
   uint32_t firmware_write_index = 0;
   uint32_t firmware_block_size = strlen(not_actual_firmware) + 1;

   uint16_t checksum = 0x50;
   uint32_t size = 0x0770;
   uint32_t version = 0x0880;

   uint16_t checksum_read;
   uint32_t size_read;
   uint32_t version_read;

   for (;;) {
      Erase_Program_Flash();
      Wait(10);

      Write_Program_Version(++version);
      Wait(10);

      Write_Program_Checksum((++checksum));
      Wait(10);

      Write_Program_Size(++size);
      Wait(10);

      while (firmware_write_index * firmware_block_size < APP_END_ADDR) {
         Write_Firmware_Bytes((firmware_write_index * firmware_block_size) + APP_START_ADDR,
                              not_actual_firmware,
                              firmware_block_size);
         ++firmware_write_index;
      }

      firmware_write_index = 0;

      checksum_read = Read_Program_Checksum();
      size_read = Read_Program_Size();
      version_read = Read_Program_Version();
   }

}
