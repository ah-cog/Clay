////Includes //////////////////////////////////////////////////////
#include "WiFi.h"
#include "Application.h"
#include "Clock.h"
#include "Power_Manager.h"
#include "Button.h"

#include "program_flash.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////

////Local Prototypes///////////////////////////////////////////////
void Flash_Test();

////Global implementations ////////////////////////////////////////

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
