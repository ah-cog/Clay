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
	
	int n = 0;
	uint8_t status = 0;
	Message *message = NULL;
//	uint16_t messageCount = 0;
	char buffer2[32] = { 0 };
	
	/* Start Clay */
	
	D(printf ("Clay\r\n"));
	
	D(printf ("\r\n"));
	
	D(printf ("Enabling clock. "));
	Enable_Clock ();
	D(printf ("Done.\r\n")); // printf ("I'm keeping time. ");
	
	D(printf ("Starting clock. "));
	Start_Clock ();
	D(printf ("Done.\r\n"));
	
	D(printf ("\r\n"));
	
	D(printf ("Enabling LED controls. ")); // printf ("Starting lights. ");
	Enable_PCA9552();
	Wait (5);
	D(printf ("Done.\r\n"));
	
	D(printf ("Starting LEDs. "));
	Start_Light_Behavior (); // previously Start_Light_Feedback ()
	D(printf ("Done.\r\n"));
	
	D(printf ("\r\n"));
	
	D(printf ("Enabling MPU-9250. "));
	mpu_9250_init();
	D(printf ("Done.\r\n"));

	// TODO: Start_Spatial_Sensing ()
	
	D(printf ("\r\n"));
	
	// TODO: Enable_GPIO ()
	
	D(printf ("Initializing message queue. "));
	if ((status = Initialize_Message_Queue ()) == TRUE) {
		D(printf ("Done.\r\n"));
	} else {
		D(printf ("Failed.\r\n"));
	}

	/*
	if (status > 0) {
		printf ("Creating message. ");
		message = Create_Message ("one");
		printf ("Queueing message \"%s\". ", (*message).content);
		messageCount = Queue_Incoming_Message (message);
		printf ("Size: %d.\r\n", messageCount);
		
		if (incomingMessageQueue != NULL) {
			message = incomingMessageQueue;
			printf ("%s <-- ", (*message).content);
			while ((*message).previous != NULL) {
				message = (*message).previous;
				printf ("%s <-- ", (*message).content);
			}
			printf ("\r\n");
		} else {
			printf ("There aren't any incoming messages.\r\n");
		}
		
		printf ("Creating message. ");
		message = Create_Message ("two");
		printf ("Queueing message \"%s\". ", (*message).content);
		messageCount = Queue_Incoming_Message (message);
		printf ("Size: %d.\r\n", messageCount);
		
		if (incomingMessageQueue != NULL) {
			message = incomingMessageQueue;
			printf ("%s <-- ", (*message).content);
			while ((*message).previous != NULL) {
				message = (*message).previous;
				printf ("%s <-- ", (*message).content);
			}
			printf ("\r\n");
		} else {
			printf ("There aren't any incoming messages.\r\n");
		}
		
		printf ("Dequeuing message ");
		message = Dequeue_Incoming_Message ();
		printf ("\"%s\".", (*message).content);
//		printf ("Size: %d.\r\n", messageCount);
		printf ("Deleting message. ");
		Delete_Message (message); // status = Delete_Message (message);
		printf ("Done.\r\n");
		
		if (incomingMessageQueue != NULL) {
			message = incomingMessageQueue;
			printf ("%s <-- ", (*message).content);
			while ((*message).previous != NULL) {
				message = (*message).previous;
				printf ("%s <-- ", (*message).content);
			}
			printf ("\r\n");
		} else {
			printf ("There aren't any incoming messages.\r\n");
		}
		
		printf ("Creating message. ");
		message = Create_Message ("three");
		printf ("Queueing message \"%s\". ", (*message).content);
		messageCount = Queue_Incoming_Message (message);
		printf ("Size: %d.\r\n", messageCount);
		
		if (incomingMessageQueue != NULL) {
			message = incomingMessageQueue;
			printf ("%s <-- ", (*message).content);
			while ((*message).previous != NULL) {
				message = (*message).previous;
				printf ("%s <-- ", (*message).content);
			}
			printf ("\r\n");
		} else {
			printf ("There aren't any incoming messages.\r\n");
		}
		
		printf ("Creating message. ");
		message = Create_Message ("four");
		printf ("Queueing message \"%s\". ", (*message).content);
		messageCount = Queue_Incoming_Message (message);
		printf ("Size: %d.\r\n", messageCount);
		
		if (incomingMessageQueue != NULL) {
			message = incomingMessageQueue;
			printf ("%s <-- ", (*message).content);
			while ((*message).previous != NULL) {
				message = (*message).previous;
				printf ("%s <-- ", (*message).content);
			}
			printf ("\r\n");
		} else {
			printf ("There aren't any incoming messages.\r\n");
		}
		
		printf ("Creating message. ");
		message = Create_Message ("five");
		printf ("Queueing message \"%s\". ", (*message).content);
		messageCount = Queue_Incoming_Message (message);
		printf ("Size: %d.\r\n", messageCount);
		
		if (incomingMessageQueue != NULL) {
			message = incomingMessageQueue;
			printf ("%s <-- ", (*message).content);
			while ((*message).previous != NULL) {
				message = (*message).previous;
				printf ("%s <-- ", (*message).content);
			}
			printf ("\r\n");
		} else {
			printf ("There aren't any incoming messages.\r\n");
		}
		
		printf ("Dequeuing message ");
		message = Dequeue_Incoming_Message ();
		printf ("\"%s\".", (*message).content);
//		printf ("Size: %d.\r\n", messageCount);
		printf ("Deleting message. ");
		Delete_Message (message); // status = Delete_Message (message);
		printf ("Done.\r\n");
		
		if (incomingMessageQueue != NULL) {
			message = incomingMessageQueue;
			printf ("%s <-- ", (*message).content);
			while ((*message).previous != NULL) {
				message = (*message).previous;
				printf ("%s <-- ", (*message).content);
			}
			printf ("\r\n");
		} else {
			printf ("There aren't any incoming messages.\r\n");
		}
		
		printf ("Dequeuing message ");
		message = Dequeue_Incoming_Message ();
		printf ("\"%s\".", (*message).content);
//		printf ("Size: %d.\r\n", messageCount);
		printf ("Deleting message. ");
		Delete_Message (message); // status = Delete_Message (message);
		printf ("Done.\r\n");
		
		if (incomingMessageQueue != NULL) {
			message = incomingMessageQueue;
			printf ("%s <-- ", (*message).content);
			while ((*message).previous != NULL) {
				message = (*message).previous;
				printf ("%s <-- ", (*message).content);
			}
			printf ("\r\n");
		} else {
			printf ("There aren't any incoming messages.\r\n");
		}
		
		printf ("Dequeuing message ");
		message = Dequeue_Incoming_Message ();
		printf ("\"%s\".", (*message).content);
//		printf ("Size: %d.\r\n", messageCount);
		printf ("Deleting message. ");
		Delete_Message (message); // status = Delete_Message (message);
		printf ("Done.\r\n");
		
		if (incomingMessageQueue != NULL) {
			message = incomingMessageQueue;
			printf ("%s <-- ", (*message).content);
			while ((*message).previous != NULL) {
				message = (*message).previous;
				printf ("%s <-- ", (*message).content);
			}
			printf ("\r\n");
		} else {
			printf ("There aren't any incoming messages.\r\n");
		}
		
		printf ("Dequeuing message ");
		message = Dequeue_Incoming_Message ();
		printf ("\"%s\".", (*message).content);
//		printf ("Size: %d.\r\n", messageCount);
		printf ("Deleting message. ");
		Delete_Message (message); // status = Delete_Message (message);
		printf ("Done.\r\n");
		
		if (incomingMessageQueue != NULL) {
			message = incomingMessageQueue;
			printf ("%s <-- ", (*message).content);
			while ((*message).previous != NULL) {
				message = (*message).previous;
				printf ("%s <-- ", (*message).content);
			}
			printf ("\r\n");
		} else {
			printf ("There aren't any incoming messages.\r\n");
		}
	}
	*/
	
	D(printf ("\r\n"));
	
	D(printf ("Enabling ESP8266. "));
	Enable_ESP8266 ();
	D(printf ("Done.\r\n"));
	
	//	D(printf ("Setting Wi-Fi Network. "));
	//	Set_WiFi_Network (SSID_DEFAULT, PASSWORD_DEFAULT);
	//	D(printf ("Done.\r\n"));
	
	// TODO: Generate SSID according to regular expression and set up access point to facilitate discovery.
	
	D(printf ("Enabling Wi-Fi. "));
	Enable_WiFi (SSID_DEFAULT, PASSWORD_DEFAULT);
	D(printf ("Done.\r\n"));
	
	D(printf ("Starting HTTP Server. "));
	Start_HTTP_Server (HTTP_SERVER_PORT);
	D(printf ("Done.\r\n"));
	
	// TODO: Eanble_UDP_Communications
	
	D(printf ("Starting UDP Server. "));
	Start_UDP_Server (4445);
	D(printf ("Done.\r\n"));
	
	// TODO: Enable_UDP_Broadcast
	// TODO: Start_Discovery_Broadcast
	
	for (;;) {
		
		Send_HTTP_Request ("192.168.1.105", 8080, "test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test");
		
		// Periodically send a datagram announcing the presence of this device.
		// TODO: Only broadcast UDP message if an address has been received!
		if (Has_Internet_Address () == TRUE) {
			char *address = Get_Internet_Address ();
			// TODO: Create and buffer the command to broadcast the unit's address.
			n = sprintf (buffer2, "connect to %s", address); // Create message to send.
//			printf("buffer = %s\r\n", buffer2);
			Broadcast_UDP_Message (buffer2);
			// TODO: Queue a (periodic) UDP broadcast announcing the unit's presence on the network.
		}
		
		// Check and process any incoming requests
		//Monitor_HTTP_Server ();
		Monitor_Network_Communications ();
		
		// TODO: Monitor_Messages ();
		
		if (Has_Incoming_Message () == TRUE) {
			message = Dequeue_Incoming_Message ();
			status = Process_Message (message);
			if (status == TRUE) {
				Delete_Message (message);
			}
		}
		
		// TODO: Monitor_Orientation ();
		
		// TODO: Monitor_Behavior (); // TODO: In this function, Consider_Behavior (), Engage_Behavior (), Perform_Behavior ().
		
		// Check and perform "scheduled" periodic events
//		Monitor_Periodic_Events ();
	}
}
