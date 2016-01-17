#include "Application.h"

void Application(void)
{
    uint8_t status = 0;

    Initialize_Unit_UUID ();

    status = Enable_Clock ();
    status = Start_Clock ();
    
    Set_WiFi_Network (SSID_DEFAULT, PASSWORD_DEFAULT);
    status = Enable_ESP8266 ();
    
    Wait (500);
    if ((status = Enable_WiFi (internetProfile.wifi_ssid, internetProfile.wifi_password)) == TRUE) {

		// Updates the current firmware if the current application doesn't verify or if the user has approved a pending update.
    	// TODO: Initialize the "application key" // Has_User_Requested_Update ();
		if (Verify_Firmware() == FALSE || (Has_Latest_Firmware() == FALSE && Has_User_Requested_Update ()))
		{
			if ((status = Update_Firmware ()) == TRUE) {
				// TODO: Post successful download operations (i.e., update shared variables, store checksum, jump to program).
			}
		}
		
    } else {
    	
    	// Error: Could not connect to Wi-Fi.
    	
    }

    // Disable all interrupts before jumping to the application.
    Disable_Interrupts ();

    // Jump to main application firmware
    Jump_To_Application ();

    for (;;);
}
