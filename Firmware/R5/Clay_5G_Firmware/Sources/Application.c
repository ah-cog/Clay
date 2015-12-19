#include "Application.h"

// Clay's print, debug, and error messages.
//#define ENABLE_DEBUG_OUTPUT TRUE
//#if ENABLE_DEBUG_OUTPUT == TRUE
//	#define print(fmt, ...) printf("print: " fmt, __VA_ARGS__);
//	#define status(fmt, ...) printf("status: " fmt);
//	#define debug(fmt, ...) printf("%s:%d: " fmt, __FILE__, __LINE__, __VA_ARGS__);
//	#define error(fmt, ...) printf("%s:%d: " fmt, __FILE__, __LINE__, __VA_ARGS__);
//#else
//	#define print(fmt, ...) ; // (void) 0;
//	#define status(fmt, ...) ;
//	#define debug(fmt, ...) ; // (void) 0;
//	#define error(fmt, ...) ; // (void) 0;
//#endif

void Application (void) {
	
	int i = 0;
	int n = 0;
	uint8_t status = 0;
	Message *message = NULL;
//	uint16_t messageCount = 0;
//	char buffer2[32] = { 0 };
	
	/* Start Clay */
	
//	printf ("Clay\r\n")/;
	
//	D(printf ("\r\n"));
	
//	D(printf ("Enabling clock. "));
	Enable_Clock ();
//	D(printf ("Done.\r\n")); // printf ("I'm keeping time. ");
	
//	D(printf ("Starting clock. "));
	Start_Clock ();
//	D(printf ("Done.\r\n"));
	
	Enable_LEDs ();

	Set_LED_State (LED1, ON_CHANNEL);
	Set_LED_State (LED2, OFF_CHANNEL);
	Wait (50);
	Set_LED_State (LED1, OFF_CHANNEL);
	Set_LED_State (LED2, ON_CHANNEL);
	Wait (50);
	Set_LED_State (LED1, ON_CHANNEL);
	Set_LED_State (LED2, OFF_CHANNEL);
	Wait (50);
	Set_LED_State (LED1, OFF_CHANNEL);
	Set_LED_State (LED2, ON_CHANNEL);
	Wait (50);
	Set_LED_State (LED1, OFF_CHANNEL);
	Set_LED_State (LED2, OFF_CHANNEL);
	
//	D(printf ("\r\n"));
	
//	D(printf ("Enabling LED controls. ")); // printf ("Starting lights. ");
	Enable_PCA9552();
	Wait (5);
//	D(printf ("Done.\r\n"));
	
//	D(printf ("Starting LEDs. "));
	Start_Light_Behavior (); // previously Start_Light_Feedback ()
//	D(printf ("Done.\r\n"));

	for (i = 1; i <= 12; i++) {
		Set_LED_Output ((RGB_LED) i,  &onColor);
		Wait (20);
		Set_LED_Output ((RGB_LED) i,  &offColor);
		Wait (20);
		Set_LED_Output ((RGB_LED) i,  &colorA);
		Wait (20);
		Set_LED_Output ((RGB_LED) i,  &offColor);
		Wait (20);
		Set_LED_Output ((RGB_LED) i,  &colorB);
		Wait (20);
		Set_LED_Output ((RGB_LED) i,  &offColor);
		Wait (20);
	}

	for (i = 1; i <= 12; i++) { Set_LED_Output ((RGB_LED) i,  &onColor); }
	Wait (20);
	for (i = 1; i <= 12; i++) { Set_LED_Output ((RGB_LED) i,  &offColor); }
	Wait (20);
	for (i = 1; i <= 12; i++) { Set_LED_Output ((RGB_LED) i,  &colorA); }
	Wait (20);
	for (i = 1; i <= 12; i++) { Set_LED_Output ((RGB_LED) i,  &offColor); }
	Wait (20);
	for (i = 1; i <= 12; i++) { Set_LED_Output ((RGB_LED) i,  &colorB); }
	Wait (20);
	for (i = 1; i <= 12; i++) { Set_LED_Output ((RGB_LED) i,  &offColor); }
	Wait (20);
	for (i = 1; i <= 12; i++) { Set_LED_Output ((RGB_LED) i,  &onColor); }
	Wait (20);
	for (i = 1; i <= 12; i++) { Set_LED_Output ((RGB_LED) i,  &offColor); }
	Wait (20);
	for (i = 1; i <= 12; i++) { Set_LED_Output ((RGB_LED) i,  &colorA); }
	Wait (50);
	for (i = 1; i <= 12; i++) { Set_LED_Output ((RGB_LED) i,  &offColor); }
	Wait (80);
	for (i = 1; i <= 12; i++) { Set_LED_Output ((RGB_LED) i,  &colorB); }
	Wait (100);
	for (i = 1; i <= 12; i++) { Set_LED_Output ((RGB_LED) i,  &offColor); }
	Wait (20);
	
//	D(printf ("\r\n"));
	
//	D(printf ("Enabling MPU-9250. "));
	mpu_9250_init ();
//	D(printf ("Done.\r\n"));

	// TODO: Start_Spatial_Sensing ()
	
//	D(printf ("\r\n"));
	
	// TODO: Enable_GPIO ()
	
//	D(printf ("Initializing message queue. "));
	if ((status = Initialize_Incoming_Message_Queue ()) == TRUE) {
//		D(printf ("Done.\r\n"));
	} else {
//		D(printf ("Failed.\r\n"));
	}
	
//	D(printf ("\r\n"));
	
//	D(printf ("Enabling ESP8266. "));
	Enable_ESP8266 ();
//	D(printf ("Done.\r\n"));
	
//	Wait (200);
	
	//	D(printf ("Setting Wi-Fi Network. "));
	//	Set_WiFi_Network (SSID_DEFAULT, PASSWORD_DEFAULT);
	//	D(printf ("Done.\r\n"));
	
	// TODO: Generate SSID according to regular expression and set up access point to facilitate discovery.
	
//	D(printf ("Enabling Wi-Fi. "));
	Enable_WiFi (SSID_DEFAULT, PASSWORD_DEFAULT);
//	D(printf ("Done.\r\n"));
	
//	D(printf ("Starting HTTP Server. "));
	Start_HTTP_Server (HTTP_SERVER_PORT);
//	D(printf ("Done.\r\n"));
	
	// TODO: Eanble_UDP_Communications
	
//	D(printf ("Starting UDP Server. "));
	Start_UDP_Server (MESSAGE_PORT);
//	D(printf ("Done.\r\n"));
	
	// TODO: Enable_UDP_Broadcast
	// TODO: Start_Discovery_Broadcast
	Generate_Discovery_Message ();
	
//	// Periodically send a datagram announcing the presence of this device.
//	// TODO: Only broadcast UDP message if an address has been received!
//	if (Has_Internet_Address () == TRUE) {
//		char *address = Get_Internet_Address ();
//		// TODO: Create and buffer the command to broadcast the unit's address.
//		n = sprintf (buffer2, "connect to %s", address); // Create message to send.
////			printf("buffer = %s\r\n", buffer2);
////		Broadcast_UDP_Message (buffer2, 4445);
//		// TODO: Queue a (periodic) UDP broadcast announcing the unit's presence on the network.
//	}
	
	for (;;) {
		
//		Send_HTTP_Request ("192.168.1.105", 8080, "test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test");
		
		// Periodically send a datagram announcing the presence of this device.
		// TODO: Only broadcast UDP message if an address has been received!
//		if (Has_Internet_Address () == TRUE) {
//			char *address = Get_Internet_Address ();
			// TODO: Create and buffer the command to broadcast the unit's address.
//			n = sprintf (buffer2, "connect to %s", address); // Create message to send.
//			printf("buffer = %s\r\n", buffer2);
//			Broadcast_UDP_Message (buffer2, 4445);
			// TODO: Queue a (periodic) UDP broadcast announcing the unit's presence on the network.
//		}
		
		// Check and process any incoming requests
		//Monitor_HTTP_Server ();
//		Wait (100);
		Wait (10);
		Monitor_Network_Communications ();
		
		// Monitor communication message queues.
		if (Has_Incoming_Message () == TRUE) {
			message = Dequeue_Incoming_Message ();
			status = Process_Incoming_Message (message);
//			if (status == TRUE) {
//				Delete_Message (message);
//			}
		}
		
		// Perform behavior
		if (currentBehaviorConstruct != NULL) {
			if (Perform_Behavior ((*currentBehaviorConstruct).behavior) != NULL) {
				// NOTE: Behavior was performed successfully.
				
				// Go to the next behavior
				// TODO: When repeating behaviors, don't clobber previous changes, just ensure the state is set.
				if ((*currentBehaviorConstruct).next != NULL) {
					currentBehaviorConstruct = (*currentBehaviorConstruct).next;
				} else {
					// Go to the start of the loop.
					currentBehaviorConstruct = loop;
				}
			}
		}
		
		// TODO: Monitor_Orientation ();
		
		// TODO: Monitor_Behavior (); // TODO: In this function, Consider_Behavior (), Engage_Behavior (), Perform_Behavior ().
		
		// Check and perform "scheduled" periodic events
		Monitor_Periodic_Events ();
	}
}
