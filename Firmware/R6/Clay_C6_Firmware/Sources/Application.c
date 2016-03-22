#include "Application.h"

//#include "meshTest.h"
#include "Bootloader.h"
#include "Mesh.h"
#include "RGB_LED.h"
#include "GPIO.h"
#include "Clock.h"
#include "MPU9250.h"
#include "LEDs.h"
#include "Events.h"
//#include "RGBDemo.h"
#include "Messenger.h"

#include "ADC0.h"

#include "Buzzer.h"
#include "PowerOn.h"
#include "ButtonIn.h"
//#include "PWM1.h"

static bool led_1_state;
static bool led_2_state;
Message *outMessage = NULL;
int status;
char buffer2[128] = { 0 };

#define VBAT_ADC_SLOPE          7.97094E-5
#define VBAT_ADC_OFFSET         3.20144E-2
static double vBat;

static uint16_t buzzerRatio = 6500;
static uint16_t buzzerPeriod_us = 240;
static uint16_t buzzerDuty_us = 120;
uint32_t Button_Press_Time;
uint32_t adcRead = 0;
LDD_TDeviceDataPtr ADC0_DeviceData;

void Monitor_Periodic_Events ();
void Remote_Button_Pressed (uint8_t * data, uint8_t len);
bool Read_Button_In ();

void Initialize () {

	vBat = 0;
	Button_Press_Time = Millis ();
	uint8_t status = 0;

	// Initialize Clay

	Initialize_Unit_UUID ();

	timeline = Create_Timeline ("timeline-uuid");

	// Initialize bootloader.
	//todo: check this somewhere where it makes sense, get user consent, and then jump to the bootloader.
//	bool is_update_available = FALSE;
//	Initialize_Bootloader (); // TODO: Make this work!

	// Clock.
	if ((status = Enable_Clock ()) != TRUE) {
		// Failure
	}

	if ((status = Start_Clock ()) != TRUE) {
		// Failure
	}

	// Status LEDs.

	if ((status = LED_Enable ()) != TRUE) {
		// Failure
	}
	Perform_Status_LED_Effect ();

	if ((status = Enable_Mesh ()) != TRUE) {
		// Failure
	}

	if ((status = Start_Mesh ()) != TRUE) {
		// Failure
	}

	// Channels.

	if ((status = Enable_Channels ()) != TRUE) {
		// Failure
	}

	if ((status = Initialize_Channels ()) != TRUE) {
		// Failure
	}

	Initialize_Color_Palette ();

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

	if ((status = Enable_WiFi (SSID_DEFAULT, PASSWORD_DEFAULT)) != TRUE) {
		// Failure
	}

	ADC0_DeviceData = ADC0_Init (NULL);

	ADC0_StartCalibration (ADC0_DeviceData);
	while (!ADC0_GetMeasurementCompleteStatus (ADC0_DeviceData))
		;
	LDD_TError adcCalOk = ADC0_GetCalibrationResultStatus (ADC0_DeviceData);

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

	//add software ack to mesh layer
	//add speaker output

//   //Action test loop: Button press on module sends message to other module. Other module receives message and changes LED output.
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

	// TODO: Include "\n" at end of string? Or is this buried in the library?

	/*
	 Message *testMessage = NULL;

	 // cache action <action-uuid> <state>
	 testMessage = Create_Message ("cache action 34d87141-01f7-4812-a358-3892cf2f5a3c");
	 Set_Message_Source (testMessage, "UDP,192.168.1.255:4445!");
	 Set_Message_Destination (testMessage, "UDP,192.168.1.255:4445!");
	 Queue_Message (&incomingMessageQueue, testMessage);

	 // start event <event-uuid>
	 testMessage = Create_Message ("start event 89d87141-01f7-4812-a358-3892cf2f5a66");
	 Set_Message_Source (testMessage, "UDP,192.168.1.255:4445!");
	 Set_Message_Destination (testMessage, "UDP,192.168.1.255:4445!");
	 Queue_Message (&incomingMessageQueue, testMessage);

	 // start event <event-uuid>
	 testMessage = Create_Message ("set event 89d87141-01f7-4812-a358-3892cf2f5a66 action 34d87141-01f7-4812-a358-3892cf2f5a3c");
	 Set_Message_Source (testMessage, "UDP,192.168.1.255:4445!");
	 Set_Message_Destination (testMessage, "UDP,192.168.1.255:4445!");
	 Queue_Message (&incomingMessageQueue, testMessage);

	 // start event <event-uuid>
	 testMessage = Create_Message ("set event 89d87141-01f7-4812-a358-3892cf2f5a66 state \"light T T T T T T T T T T T T\"");
	 Set_Message_Source (testMessage, "UDP,192.168.1.255:4445!");
	 Set_Message_Destination (testMessage, "UDP,192.168.1.255:4445!");
	 Queue_Message (&incomingMessageQueue, testMessage);
	 */

	for (;;) {

// Check and process any incoming requests
//      MeshTestLoopStep();

//        mesh_process_commands();

		// TODO: Try processing the IMMEDIATE outgoing messages in the outgoing queue here! This will allow responding to incoming messages as soon as possible, using the queue.

		// Step state machine
		Wifi_State_Step ();
		Wifi_State_Step ();
		Wifi_State_Step ();

//		message = Create_Message ("discovery");
//		Set_Message_Source (message, "192.168.1.255");
//		Set_Message_Destination (message, "192.168.1.255:4445");
////			Wifi_Send(&outgoingMessageQueue, message);
//		Queue_Message(&outgoingMessageQueue, message);
//
//		continue;

		// TODO: Check for Wi-Fi messages on the Wi-Fi queue, and put them onto the system incoming queue.
		// Monitor communication message queues.
		if (Has_Messages (&incomingMessageQueue) == TRUE) {
			message = Wifi_Receive ();
			status = Process_Incoming_Message (message);
			if (message != NULL) {

			}
			//			Set_Message_Type (message, "TCP");
			//			Set_Message_Destination (message, "10.0.0.5:8000");
			//			Wifi_Send (message);
		}

		// Step state machine
		Wifi_State_Step ();
		Wifi_State_Step ();
		Wifi_State_Step ();

//		// Monitor communication message queues.
//		if (Has_Messages (&incomingMessageQueue) == TRUE) {
//			message = Dequeue_Message (&incomingMessageQueue);
//			status = Process_Incoming_Message (message);
////			if (status == TRUE) {
////				Delete_Message (message);
////			}
//		}

//		// Send the next message on the outgoing message queue.
//		if (Has_Messages (&outgoingMessageQueue) == TRUE) {
//			Message *message = Dequeue_Message (&outgoingMessageQueue);
//			if ((status = Process_Outgoing_Message (message)) == TRUE) {
//				// Delete_Message (message);
//			}
////			Delete_Message (message);
//		}

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

		// Perform action.
		if ((*timeline).current_event != NULL) {
			if (Perform_Action (((*timeline).current_event)) != NULL) {

				// NOTE: Action was performed successfully.

				// TODO: When repeating actions, don't clobber previous changes, just ensure the state is set.

				// Go to the next action
				if ((*((*timeline).current_event)).next != NULL) {
					// Go to the next action.
					(*timeline).current_event = (*((*timeline).current_event)).next;
				} else {
					// Go to the start of the loop.
					(*timeline).current_event = (*timeline).first_event;
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

		// Step state machine
//		Wifi_State_Step ();
//		Wifi_State_Step ();
//		Wifi_State_Step ();

		// TODO: Monitor_Orientation ();

		// TODO: Monitor_Action (); // TODO: In this function, Consider_Action (), Engage_Action (), Perform_Action ().

		// Check and perform "scheduled" periodic events
		Monitor_Periodic_Events ();

		// Step state machine
		Wifi_State_Step ();
		Wifi_State_Step ();
		Wifi_State_Step ();
	}
}

void Monitor_Periodic_Events () {

	// TODO: Convert these to a dynamic list of timers with custom timeouts to check periodically?

	if (data_ready) {
		//        LED1_PutVal(NULL, led_1_state);
		//        led_1_state = !led_1_state;

		imu_periodic_callback ();
	}

	if (tick_1ms) {
		tick_1ms = FALSE;

		// TODO: Perform any periodic actions (1 ms).
	}

	if (tick_250ms) {
		tick_250ms = FALSE;

		// TODO: Perform any periodic actions (250 ms).
	}

	if (tick_500ms) {
		tick_500ms = FALSE;

		LED2_PutVal (NULL, led_2_state);
		LED1_PutVal (NULL, led_2_state);
		led_2_state = !led_2_state;

      //monitor the input voltage line. We need to shut down on low battery ~3.2v. See schematic for resistor divider and input scaling.
      if ((vBat != 0 && vBat < 3.2) || Button_Press_Time > 0 && (Millis() - Button_Press_Time) > 1500) {

         //TODO: We may need a watchdog or high priority timer interrupt, or task, that checks to see if the user is holding down the button. Perhaps we just make it a high priority double-edge
         //IDEA: start flashing LEDs to signal to the user that they are about to shut
         //      the module down. If the user releases the button, continue operation
         //      as usual. Otherwise:

         //TODO: stop doing things, shut down gracefully,  and then:

         //TODO: Make it apparent that Clay is ready to turn off. Stop flashing things. The power LED will remain on.
         //We wait for the user to release the button so that they don't immediately turn the module back on again.

         LED2_PutVal(NULL, FALSE);
         LED1_PutVal(NULL, FALSE);
         while (Read_Button_In()) {
            Wait(1);
         }

         //Pull the PowerOn line low. The Vreg enable button will drop below 0 and
         PowerOn_PutVal(NULL, 0);
         for (;;)
            ;
      }
      else if (Button_Press_Time == 0 && Read_Button_In()) {
         Button_Press_Time = Millis();
      }
      else if (Button_Press_Time > 0 && !Read_Button_In()) {
         Button_Press_Time = 0;
      }

      // TODO: Perform any periodic actions (500 ms).
   }

	if (tick_1000ms) {
		tick_1000ms = FALSE;

		// TODO: Perform any periodic action (1000 ms).
	}

	if (tick_3000ms) {
		tick_3000ms = FALSE;

		char *uuid = Get_Unit_UUID ();
		sprintf (buffer2, "announce device %s", uuid);
		Message *broadcastMessage = Create_Message (buffer2);
		Set_Message_Type (broadcastMessage, "UDP");
		Set_Message_Source (broadcastMessage, "10.0.0.255:4445");
		Set_Message_Destination (broadcastMessage, "10.0.0.255:4445");
		Queue_Message (&outgoingMessageQueue, broadcastMessage);
//		Wifi_Send (broadcastMessage);

		// TODO: Perform any periodic actions (3000 ms).
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

bool Read_Button_In () {
	bool rval = ButtonIn_GetPortValue (NULL) & ButtonIn_Button_Field_MASK;

	return rval;
}
