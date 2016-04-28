////Includes //////////////////////////////////////////////////////
#include "WiFi.h"
#include "Application.h"
#include "Clock.h"
#include "Power_Manager.h"
#include "Button.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////

void Application(void) {

   //Init power manager to hold PowerOn line high so that our supply doesn't shut off.
   Power_Manager_Enable();
   //enable button so the user can shut us down.
   Button_Enable();

   uint32_t enable_wifi_start_time_ms;
   Message * temp_message_ptr;

   uint8_t status = Enable_Clock();
   status = Start_Clock();

   Initialize_Unit_UUID();

   Initialize_Bootloader();

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
      }

      while (!local_address_received) {
         local_address_received = Get_Local_Address();
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

