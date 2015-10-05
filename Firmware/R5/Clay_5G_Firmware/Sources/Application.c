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
	
	uint8_t status = 0;
	Message *message = NULL;
//	uint16_t messageCount = 0;
	
	/* Start Clay */
	
	printf ("Clay\r\n");
	
	printf ("\r\n");
	
	printf ("Enabling clock. ");
	Enable_Clock ();
	printf ("Done.\r\n"); // printf ("I'm keeping time. ");
	
	printf ("Starting clock. ");
	Start_Clock ();
	printf ("Done.\r\n");
	
	printf ("\r\n");
	
	printf ("Enabling LED controls. "); // printf ("Starting lights. ");
	Enable_PCA9552();
	Wait (5);
	printf ("Done.\r\n");
	
	printf ("Starting LEDs. ");
	Start_Light_Behavior (); // previously Start_Light_Feedback ()
	printf ("Done.\r\n");
	
	printf ("\r\n");
	
	printf ("Enabling MPU-9250. ");
	mpu_9250_init();
	printf ("Done.\r\n");

	// TODO: Start_Spatial_Sensing ()
	
	printf ("\r\n");
	
	// TODO: Enable_GPIO ()
	
	printf ("Initializing message queue. ");
	if ((status = Initialize_Message_Queue ()) == TRUE) {
		printf ("Done.\r\n");
	} else {
		printf ("Failed.\r\n");
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
	
	printf ("\r\n");
	
	printf ("Enabling ESP8266. ");
	Enable_ESP8266 ();
	printf ("Done.\r\n");
	
	printf ("Starting HTTP Server. ");
	Start_HTTP_Server (HTTP_SERVER_PORT);
	printf ("Done.\r\n");
	
	printf ("Starting UDP Server. ");
	Start_UDP_Server (4445);
	printf ("Done.\r\n");
	
//	Broadcast_UDP_Message("hello");
	
	for (;;) {
		
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
