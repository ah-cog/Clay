#include "Application.h"

void Application(void)
{
    uint8_t status = 0;

    Initialize_Unit_UUID();

    status = Enable_Clock();
    status = Start_Clock();

    Initialize_Bootloader();

    //if (!Verify_Firmware () || (/*!Has_Latest_Firmware()*/ SharedData.ApplicationUpdateAvailable && Has_User_Requested_Update ())) {
    if (0&&!Verify_Firmware() || (SharedData.ApplicationUpdateAvailable && Has_User_Requested_Update()))
    {

        Set_WiFi_Network(SSID_DEFAULT, PASSWORD_DEFAULT);
        status = Enable_ESP8266();

        //    Wait (500);
        if ((status = Enable_WiFi(internetProfile.wifi_ssid, internetProfile.wifi_password)) == TRUE)
        {

            // Check if an application update is available. If so, write that value to the shared flash memory.
            //    	if (!Has_Latest_Firmware ()) {
            //    		SharedData.ApplicationUpdateAvailable = TRUE;
            //    	}

            // Updates the current firmware if the current application doesn't verify or if the user has approved a pending update.
            // TODO: Initialize the "application key" // Has_User_Requested_Update ();
            //    	if (!Verify_Firmware() || Has_User_Requested_Update ())
//			if (!Verify_Firmware() || (/*!Has_Latest_Firmware()*/ SharedData.ApplicationUpdateAvailable = TRUE && Has_User_Requested_Update ()))
            // if (!Verify_Firmware() || (!Has_Latest_Firmware() && Has_User_Requested_Update ()) && Has_User_Forced_Update ())
//			{
            if ((status = Update_Firmware()) == TRUE)
            {
                // TODO: Post successful download operations (i.e., update shared variables, store checksum, jump to program).
            }

//			} else {

            // The firmware is already up to date or it hasn't yet been requested by the user.
            // So reset the flag indicating a new firmware update is available.
            //			SharedData.ApplicationUpdateAvailable = FALSE;
            //			SharedData.UpdateApplication = FALSE;

//			}

        }
        else
        {

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
