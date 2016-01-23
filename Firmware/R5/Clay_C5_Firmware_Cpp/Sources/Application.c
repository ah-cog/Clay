#include "Application.h"
#include "meshTest.h"
#include "Bootloader.h"

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

void Application(void)
{
    uint8_t status = 0;
    Message *message = NULL;

    // Initialize Clay

    Initialize_Unit_UUID();

    // Initialize bootloader.
    //todo: check this somewhere where it makes sense, get user consent, and then jump to the bootloader.
//	bool is_update_available = FALSE;
    Initialize_Bootloader();

    // Clock.

    if ((status = Enable_Clock()) != TRUE)
    {
        // Failure
    }

    if ((status = Start_Clock()) != TRUE)
    {
        // Failure
    }

    // Status LEDs.

    if ((status = Enable_LEDs()) != TRUE)
    {
        // Failure
    }

    Perform_Status_LED_Effect();

    // Channels.

    if ((status = Enable_Channels()) != TRUE)
    {
        // Failure
    }

    if ((Initialize_Channels()) != TRUE)
    {
        // Failure
    }

    if ((status = Enable_PCA9552()) != TRUE)
    {
        // Failure
    }

    if ((status = Start_Light_Behavior()) != TRUE)
    {
        // Failure
    }

    if ((status = Perform_Channel_Light_Effect(TRUE)) != TRUE)
    {
        // Failure
    }

    if ((Initialize_Channel_Lights()) != TRUE)
    {
        // Failure
    }

    if ((status = Start_MPU9250()) != TRUE)
    {
        // Failure
    }

    // Message queue.
    if ((status = Initialize_Message_Queue(&incomingMessageQueue)) != TRUE)
    {
        // Failure
    }

    if ((status = Initialize_Message_Queue(&outgoingMessageQueue)) != TRUE)
    {
        // Failure
    }

    // ESP8266, WiFi, HTTP, UDP.

    if ((status = Enable_ESP8266()) != TRUE)
    {
        // Failure
    }

    // TODO: Generate SSID for AP according to regular expression and set up access point to facilitate discovery.

//#if !defined DONT_DO_WIFI_STUFF
    if ((status = Enable_WiFi(SSID_DEFAULT, PASSWORD_DEFAULT)) != TRUE)
    {
        // Failure
    }

    if ((status = Start_HTTP_Server(HTTP_SERVER_PORT)) != TRUE)
    {
        // Failure 
    }

    if ((Start_UDP_Server(MESSAGE_PORT)) != TRUE)
    {
        // Failure
    }

    if ((Start_Discovery_Broadcast()) != TRUE)
    {
        // Failure
    }
//#endif
    
    MeshTestLoop();

    for (;;)
    {

//		Send_HTTP_Request ("192.168.1.105", 8080, "test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test");

// Check and process any incoming requests
        Wait(10);        // Wait (100);
        Monitor_Network_Communications();

        // TODO: Try processing the IMMEDIATE outgoing messages in the outgoing queue here! This will allow responding to incoming messages as soon as possible, using the queue.

        // Monitor communication message queues.
        if (Has_Messages(&incomingMessageQueue) == TRUE)
        {
            message = Dequeue_Message(&incomingMessageQueue);
            status = Process_Incoming_Message(message);
//			if (status == TRUE) {
//				Delete_Message (message);
//			}
        }

        // Send the next message on the outgoing message queue.
        if (Has_Messages(&outgoingMessageQueue) == TRUE)
        {
            Message *message = Dequeue_Message(&outgoingMessageQueue);
            if ((status = Process_Outgoing_Message(message)) == TRUE)
            {
                // Delete_Message (message);
            }
            Delete_Message(message);
        }

//        // Perform operating system operations.
//        //todo: check this somewhere where it makes sense, get user consent, and then jump to the bootloader.
//		is_update_available = Update_Available ();
//		//if (is_update_available) {
//		if (SharedData.UpdateApplication) {
//			
//			// TODO: Disable all interrupts!
//			
//			// Jump to the bootloader.
//			Jump_To_Bootloader_And_Update_Application ();
//		}

        // Perform behavior.
        if (currentBehaviorConstruct != NULL)
        {
            if (Perform_Behavior((*currentBehaviorConstruct).behavior) != NULL)
            {
                // NOTE: Behavior was performed successfully.

                // Go to the next behavior
                // TODO: When repeating behaviors, don't clobber previous changes, just ensure the state is set.
                if ((*currentBehaviorConstruct).next != NULL)
                {
                    currentBehaviorConstruct = (*currentBehaviorConstruct).next;
                }
                else
                {
                    // Go to the start of the loop.
                    currentBehaviorConstruct = loop;
                }
            }

        }
        else
        {

            // Reset the channel states...
            Reset_Channels();
            Apply_Channels();

            // ...the channel light states...
            Reset_Channel_Lights();
            Apply_Channel_Lights();

            // ...and the device states.
            // TODO: Reset any other device states.
        }

        // TODO: Monitor_Orientation ();

        // TODO: Monitor_Behavior (); // TODO: In this function, Consider_Behavior (), Engage_Behavior (), Perform_Behavior ().

        // Check and perform "scheduled" periodic events
        Monitor_Periodic_Events();
    }
}
