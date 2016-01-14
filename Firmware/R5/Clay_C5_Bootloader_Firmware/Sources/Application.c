#include "Application.h"

void Application(void)
{

    int i = 0;
    int n = 0;
    uint8_t status = 0;

    Initialize_Unit_UUID();

    status = Enable_Clock();
    status = Start_Clock();

//	Wait (1000); // Wait for ESP8266 to turn on.
    status = Enable_ESP8266();
    Wait(500);
    status = Enable_WiFi(SSID_DEFAULT, PASSWORD_DEFAULT);
//	Start_HTTP_Server (HTTP_SERVER_PORT);

// Updates the current firmware if the current application doesn't verify or if the user has approved a pending update.
    if (Verify_Firmware() == FALSE || (Has_Latest_Firmware() == FALSE && UserApprovedUpdate()))
    {
        Update_Firmware();
    }

    // Disable interrupts
    NVICICER0 = 0xFFFFFFFF;
    NVICICER1 = 0xFFFFFFFF;
    NVICICER2 = 0xFFFFFFFF;
    NVICICER3 = 0xFFFFFFFF;

    // Jump to application
    Jump_To_Application();

    // TODO: Jump to the updated program memory.

    for (;;)
        ;

//	for (;;) {
//		
////		Send_HTTP_Request ("192.168.1.105", 8080, "test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test");
//		
//		// Periodically send a datagram announcing the presence of this device.
//		// TODO: Only broadcast UDP message if an address has been received!
////		if (Has_Internet_Address () == TRUE) {
////			char *address = Get_Internet_Address ();
//			// TODO: Create and buffer the command to broadcast the unit's address.
////			n = sprintf (buffer2, "connect to %s", address); // Create message to send.
////			printf("buffer = %s\r\n", buffer2);
////			Broadcast_UDP_Message (buffer2, 4445);
//			// TODO: Queue a (periodic) UDP broadcast announcing the unit's presence on the network.
////		}
//		
//		// Check and process any incoming requests
//		//Monitor_HTTP_Server ();
////		Wait (100);
//		Wait (10);
//		Monitor_Network_Communications ();
//		
//		// TODO: Try processing the IMMEDIATE outgoing messages in the outgoing queue here! This will allow responding to incoming messages as soon as possible, using the queue.
//		
//		// Monitor communication message queues.
//		if (Has_Messages (&incomingMessageQueue) == TRUE) {
//			message = Dequeue_Message (&incomingMessageQueue);
//			status = Process_Incoming_Message (message);
////			if (status == TRUE) {
////				Delete_Message (message);
////			}
//		}
//		
//		// Send the next message on the outgoing message queue.
//		if (Has_Messages (&outgoingMessageQueue) == TRUE) {
//			Message *message = Dequeue_Message (&outgoingMessageQueue);
//			if ((status = Process_Outgoing_Message (message)) == TRUE) {
//				// Delete_Message (message);
//			}
//			Delete_Message (message);
//		}
//		
//		// Perform behavior
//		if (currentBehaviorConstruct != NULL) {
//			if (Perform_Behavior ((*currentBehaviorConstruct).behavior) != NULL) {
//				// NOTE: Behavior was performed successfully.
//				
//				// Go to the next behavior
//				// TODO: When repeating behaviors, don't clobber previous changes, just ensure the state is set.
//				if ((*currentBehaviorConstruct).next != NULL) {
//					currentBehaviorConstruct = (*currentBehaviorConstruct).next;
//				} else {
//					// Go to the start of the loop.
//					currentBehaviorConstruct = loop;
//				}
//			}
//		}
//		
//		// TODO: Monitor_Orientation ();
//		
//		// TODO: Monitor_Behavior (); // TODO: In this function, Consider_Behavior (), Engage_Behavior (), Perform_Behavior ().
//		
//		// Check and perform "scheduled" periodic events
//		Monitor_Periodic_Events ();
//	}
}
