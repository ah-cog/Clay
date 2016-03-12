#include "Application.h"
#include "meshTest.h"
#include "Bootloader.h"
#include "Mesh.h"
#include "RGB_LED.h"
#include "GPIO.h"
#include "Clock.h"
#include "MPU9250.h"
#include "LEDs.h"
#include "Events.h"
#include "RGBDemo.h"

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

#define DISABLE_WIFI //wifi disable. comment or remove to enable wifi.

static bool led_1_state;
static bool led_2_state;
Message *outMessage = NULL;
int status;

void Monitor_Periodic_Events ();
void Remote_Button_Pressed (uint8_t * data, uint8_t len);

int8_t Start_Light_Behavior () {
	//stubbed.
}

bool Perform_Channel_Light_Effect (bool reverse) {
	RGB_Color c = { 0, 0, 0 };

	for (c.R = 0; c.R <= 200; c.R += 70) {
		for (c.G = 0; c.G <= 200; c.G += 70) {
			for (c.B = 0; c.B <= 200; c.B += 70) {
				for (int i = reverse ? RGB_MAX : 0;
						reverse ? i > 0 : i < RGB_MAX; i +=
								(reverse ? -1 : 1)) {
					RGB_LED_SetColor ((RGB_LED) i, &c);
					Wait (1);
				}
			}
		}
	}

	c.R = 0;
	c.G = 0;
	c.B = 0;

	for (int i = 0; i < RGB_MAX; ++i) {
		RGB_LED_SetColor ((RGB_LED) i, &c);
	}

	return TRUE;
}

void Initialize () {

	uint8_t status = 0;

	// Initialize Clay

	Initialize_Unit_UUID ();

	// Initialize bootloader.
	//todo: check this somewhere where it makes sense, get user consent, and then jump to the bootloader.
//	bool is_update_available = FALSE;
	Initialize_Bootloader ();

	// Clock.
	if ((status = Clock_Enable ()) != TRUE) {
		// Failure
	}

	if ((status = Clock_Start ()) != TRUE) {
		// Failure
	}

	// Status LEDs.

	if ((status = LED_Enable ()) != TRUE) {
		// Failure
	}

	Perform_Status_LED_Effect ();

	if (!(status = Enable_Mesh ())) {
		//failure
	}

	if (!(status = Start_Mesh ())) {
		//failure
	}

	// Channels.

	if ((status = Enable_Channels ()) != TRUE) {
		// Failure
	}

	if ((Initialize_Channels ()) != TRUE) {
		// Failure
	}

	if ((status = RGB_LED_Enable ()) != TRUE) {
		// Failure
	}
	// RGBDemoLoop();

	if ((status = Start_Light_Behavior ()) != TRUE) {
		// Failure
	}

	if ((status = Perform_Channel_Light_Effect (TRUE)) != TRUE) {
		// Failure
	}

	if ((Initialize_Channel_Lights ()) != TRUE) {
		// Failure
	}

//TODO: troubleshoot MPU start with invensense drivers.
	if ((status = Start_MPU9250 ()) != TRUE) {
		// Failure
	}

// Message queue.
	if ((status = Initialize_Message_Queue (&incomingMessageQueue)) != TRUE) {
		// Failure
	}

	if ((status = Initialize_Message_Queue (&outgoingMessageQueue)) != TRUE) {
		// Failure
	}

	if ((status = Wifi_Enable ()) != TRUE) {
		// Failure
	}

#if 1
//#if !defined DISABLE_WIFI

//   // ESP8266, WiFi, HTTP, UDP.
//   if ((status = Enable_ESP8266()) != TRUE)
//   {
//      // Failure
//   }
//// TODO: Generate SSID for AP according to regular expression and set up access point to facilitate discovery.
//
//   if ((status = Enable_WiFi(SSID_DEFAULT, PASSWORD_DEFAULT)) != TRUE)
//   {
//      // Failure
//   }
//
//   if ((status = Start_HTTP_Server(HTTP_SERVER_PORT)) != TRUE)
//   {
//      // Failure
//   }
//
//   if ((Start_UDP_Server(MESSAGE_PORT)) != TRUE)
//   {
//      // Failure
//   }
//
//   if ((Start_Discovery_Broadcast()) != TRUE)
//   {
//      // Failure
//   }
#endif
}

void Application (void) {
	Message *message = NULL;

//	bool LastButtonStateUpdated = ButtonPressed;
//	Mesh_Register_Callback(MESH_CMD_BUTTON_PRESSED, Remote_Button_Pressed);
//
//	//add software ack to mesh layer
//	//add speaker output
//	//
//
//   //Behavior test loop: Button press on module sends message to other module. Other module receives message and changes LED output.
//   for (;;)
//   {
//      //call ticks for heartbeat
//      Monitor_Periodic_Events();
//      Mesh_Process_Commands();
//      if (ButtonPressed != LastButtonStateUpdated)
//      {
//         LastButtonStateUpdated = ButtonPressed;
//         uint8_t msgbuf[] = { MESH_CMD_BUTTON_PRESSED, 1 };
//
//         if (!ButtonPressed)
//         {
//            msgbuf[1] = 0;
//         }
//
//         Mesh_Tx_With_Retry(msgbuf, 2, RemoteAddress);
////         Mesh_Tx(msgbuf,2,RemoteAddress);
//      }
//
//      //incoming button press messages are handled by interrupt.
//   }

	//TODO: never reached because of test loop above
	for (;;) {

//		Send_HTTP_Request ("192.168.1.105", 8080, "test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test");

// Check and process any incoming requests
//        Wait(10);        // Wait (100);
//      Monitor_Network_Communications(); // Replace this!
//      MeshTestLoopStep();

//        mesh_process_commands();

		// TODO: Try processing the IMMEDIATE outgoing messages in the outgoing queue here! This will allow responding to incoming messages as soon as possible, using the queue.

		// Step state machine
		Wifi_State_Step ();

		// Monitor communication message queues.
		if (Has_Messages (&incomingMessageQueue) == TRUE) {
			message = Wifi_Receive ();
			status = Process_Incoming_Message (message);
			if (message != NULL) {
				Set_ESP8266_Address(message, "255.255.255.255");
				Wifi_Send (message);
			}
		}

//		// Monitor communication message queues.
//		if (Has_Messages (&incomingMessageQueue) == TRUE) {
//			message = Dequeue_Message (&incomingMessageQueue);
//			status = Process_Incoming_Message (message);
////			if (status == TRUE) {
////				Delete_Message (message);
////			}
//		}
		// Send the next message on the outgoing message queue.
		if (Has_Messages (&outgoingMessageQueue) == TRUE) {
			Message *message = Dequeue_Message (&outgoingMessageQueue);
			if ((status = Process_Outgoing_Message (message)) == TRUE) {
				// Delete_Message (message);
			}
//			Delete_Message (message);
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

		} else {

			// Reset the channel states...
			Reset_Channels ();
			Apply_Channels ();

			// ...the channel light states...
			Reset_Channel_Lights ();
			Apply_Channel_Lights ();

			// ...and the device states.
			// TODO: Reset any other device states.
		}

		// TODO: Monitor_Orientation ();

		// TODO: Monitor_Behavior (); // TODO: In this function, Consider_Behavior (), Engage_Behavior (), Perform_Behavior ().

		// Check and perform "scheduled" periodic events
		Monitor_Periodic_Events ();
	}
}

void Monitor_Periodic_Events () {

// TODO: Add dynamic list of timers with custom timeouts to check periodically.

	if (data_ready) {
		//        LED1_PutVal(NULL, led_1_state);
		//        led_1_state = !led_1_state;

		imu_periodic_callback ();
	}

// LEDs
	if (tick_1ms) {
		tick_1ms = FALSE;

		// TODO: Perform any periodic actions (1 ms).

	}

	if (tick_250ms) {
		tick_250ms = FALSE;

		// TODO: Perform any periodic actions (1 ms).
	}

	if (tick_500ms) {
		tick_500ms = FALSE;

		LED2_PutVal (NULL, led_2_state);
		LED1_PutVal (NULL, led_2_state);
		led_2_state = !led_2_state;

		// TODO: Perform any periodic actions (1 ms).

		/*
		 //toggle LEDs
		 LED1_PutVal(LED1_DeviceData, !led_state);
		 LED2_PutVal(LED2_DeviceData, led_state);
		 led_state = !led_state;

		 Color_RGB * derp = colors + color_index;

		 Set_LED_Output((RGB_LED) led_index, derp);

		 if (++led_index % RGB_INVALID == 0)
		 {
		 led_index = 0;
		 color_index = (color_index + 1) % 3;
		 }
		 */
	}

	//TODO: commented this out while working on button press/remote LED app.
	if (0 && tick_3000ms) {
		tick_3000ms = FALSE;

		// Periodically send a datagram announcing the presence of this device.
		// TODO: Only broadcast UDP message if an address has been received!
		//		if (Has_Internet_Address () == TRUE) {
		//			char *address = Get_Internet_Address ();
		//			// TODO: Create and buffer the command to broadcast the unit's address.
		//			n = sprintf (buffer2, "connect to %s", address); // Create message to send.
		//	//			printf("buffer = %s\r\n", buffer2);
		//	//		Broadcast_UDP_Message (buffer2, 4445);
		//			// TODO: Queue a (periodic) UDP broadcast announcing the unit's presence on the network.
		//		}

		// TODO: Do this elsewhere! Broadcast_UDP_Message (discoveryMessage, DISCOVERY_BROADCAST_PORT);
		//		Broadcast_UDP_Message (discoveryMessage, DISCOVERY_BROADCAST_PORT);
		//		message = Create_Message (discoveryMessage);
		//		Queue_Outgoing_Message ("255.255.255.255", message);

		//#if !defined DONT_DO_WIFI_STUFF
		outMessage = Create_Message (discoveryMessage);
		Queue_Outgoing_Message ("255.255.255.255", outMessage);
		//#endif
		//		Queue_Message (&outgoingMessageQueue, outMessage);
		//		Delete_Message (outMessage);

		/*
		 // Send the next message on the outgoing message queue.
		 if (Has_Messages (&outgoingMessageQueue) == TRUE) {
		 Message *message = Dequeue_Message (&outgoingMessageQueue);
		 if ((status = Process_Outgoing_Message (message)) == TRUE) {
		 // Delete_Message (message);
		 }
		 Delete_Message (message);
		 }
		 */

		//		Wait (200);
		//		if (Has_Behaviors() == TRUE) {
		//			Broadcast_UDP_Message ("got turn light 1 on", DISCOVERY_BROADCAST_PORT);
		//		}
		//		Wait (200);
	}
}

void Remote_Button_Pressed (uint8_t * data, uint8_t len) {
	if (len != 2)
		return;

	RGB_Color c;
	srand (Millis ());

	if (data[1]) {
		c.R = 10 + rand () % 130;
		c.G = 10 + rand () % 130;
		c.B = 10 + rand () % 130;
	} else {
		c.R = 0;
		c.G = 0;
		c.B = 0;
	}

	for (int i = data[1] ? 0 : (RGB_MAX - 1); data[1] ? i < RGB_MAX : i >= 0;
			i += data[1] ? 1 : -1) {
		RGB_LED_SetColor ((RGB_LED) i, &c);
		Wait (2);
	}
}
