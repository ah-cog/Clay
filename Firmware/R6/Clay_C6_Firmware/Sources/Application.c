#include <Message.h>
#include "Application.h"

//#include "meshTest.h"
#include "Bootloader.h"
//#include "Mesh.h"
#include "RGB_LED.h"
#include "GPIO.h"
#include "Clock.h"
#include "MPU9250.h"
#include "LEDs.h"
#include "Events.h"
//#include "RGBDemo.h"
#include "ADC0.h"

#include "Buzzer.h"
#include "PowerOn.h"
#include "Button.h"

#include "Power_Manager.h"

static bool led_1_state;
static bool led_2_state;
Message *outMessage = NULL;
int status;
char buffer2[128] = { 0 };

#define VBAT_ADC_SLOPE          7.97094E-5
#define VBAT_ADC_OFFSET         3.20144E-2
static double vBat;

char * ssid = "hefnet";
char * password = "h3fn3r_is_better_than_me";

//char * ssid = "Clay";
//char * password = "redgreenblue";

static uint16_t buzzerRatio = 6500;
static uint16_t buzzerPeriod_us = 240;
static uint16_t buzzerDuty_us = 120;
uint32_t Button_Press_Time;
uint32_t adcRead = 0;
LDD_TDeviceDataPtr ADC0_DeviceData;

void Monitor_Periodic_Events();
void Remote_Button_Pressed(uint8_t * data, uint8_t len);
void Send_Mesh_Test_Message();

void Initialize() {

   vBat = 0;
   Button_Press_Time = Millis();
   uint8_t status = 0;

   // Initialize Clay

//   Button_Register_Press_Response(Wifi_Set_Programming_Mode);
//   Button_Register_Press_Response(Send_Mesh_Test_Message);
//   Button_Register_Release_Response(Send_Mesh_Test_Message);

   Initialize_Unit_UUID();

   timeline = Create_Timeline("timeline-uuid");

   Enable_Actions();

   // Initialize bootloader.
   //todo: check this somewhere where it makes sense, get user consent, and then jump to the bootloader.
//	bool is_update_available = FALSE;
//	Initialize_Bootloader (); // TODO: Make this work!

   if ((status = Button_Enable()) != TRUE) {
      // Failure
   }

   if ((status = Power_Manager_Enable()) != TRUE) {
      // Failure
   }

   // Clock.
   if ((status = Enable_Clock()) != TRUE) {
      // Failure
   }

   if ((status = Start_Clock()) != TRUE) {
      // Failure
   }

   Power_Manager_Check_Startup();

   // Status LEDs.

   if ((status = LED_Enable()) != TRUE) {
      // Failure
   }

   Perform_Status_LED_Effect();

   //TODO: troubleshoot MPU start with invensense drivers.
   if ((status = Start_MPU9250()) != TRUE) {
      // Failure
   }

   Initialize_Color_Palette();

   if ((Initialize_Channel_Lights()) != TRUE) {
      // Failure
   }

   if ((status = Start_Light_Behavior()) != TRUE) {
      // Failure
   }

   if ((status = RGB_LED_Enable()) != TRUE) {
      // Failure
   }

   if ((status = Initialize_Channels()) != TRUE) {
      // Failure
   }

   //HACK -- need this to get the RGB, IMU, and GPIO to play nice.
   Apply_Channels();

   if ((status = Channel_Enable_All()) != TRUE) {
      // Failure
   }

   if ((status = Perform_Channel_Light_Effect(TRUE)) != TRUE) {
      // Failure
   }

   if ((status == Buzzer_Enable()) != TRUE) {
      // Failure
   }

   // Message queue.
   if ((status = Initialize_Message_Queue(&incomingMessageQueue)) != TRUE) {
      // Failure
   }

   if ((status = Initialize_Message_Queue(&outgoingMessageQueue)) != TRUE) {
      // Failure
   }

   if ((status = Enable_WiFi(ssid, password)) != TRUE) {     // if ((status = Enable_WiFi(SSID_DEFAULT, PASSWORD_DEFAULT)) != TRUE) {
      // Failure
   }

   //TODO: move power monitor code into a library.
   // Initialize Power Monitor
   ADC0_DeviceData = ADC0_Init(NULL);

   // Initialize Power Monitor
   ADC0_StartCalibration(ADC0_DeviceData);
   while (!ADC0_GetMeasurementCompleteStatus(ADC0_DeviceData))
      ;
   LDD_TError adcCalOk = ADC0_GetCalibrationResultStatus(ADC0_DeviceData);

   if ((status = Enable_Interactive_Assembly()) != TRUE) {
      // Failure
   }
}

// TODO: Move these into Device_Status.h
int8_t has_connection_to_wifi = FALSE;
int8_t has_received_internet_address = FALSE;
int8_t has_generated_discovery_broadcast_address = FALSE;
int8_t has_enabled_broadcast = FALSE;
char broadcast_address[32];

void Discovery_Broadcast_Presence() {

   // TODO: Check if have IP address. Only broadcast if have IP address.

   // Queue device discovery broadcast
   char *uuid = Get_Unit_UUID();
   sprintf(buffer2, "announce device %s", uuid);
   Message *broadcastMessage = Create_Message(buffer2);
   Set_Message_Type(broadcastMessage, "udp");
   Set_Message_Source(broadcastMessage, broadcast_address);
   Set_Message_Destination(broadcastMessage, broadcast_address);
   Queue_Message(&outgoingMessageQueue, broadcastMessage);
}

int8_t message_status = FALSE;
uint8_t lock_timeline = FALSE;
uint8_t pause_timeline = FALSE;

void Application(void) {
   Message *message = NULL;
   int i;

//	Message *signalMessage;
//	signalMessage = Create_Message("start event 89d87141-01f7-4812-a358-3892cf2f5a70");
//	Set_Message_Type(signalMessage, "tcp");
//	Set_Message_Source(signalMessage, "192.168.1.6:1002");
//	Set_Message_Destination(signalMessage, "192.168.1.3:1002");
//	Queue_Message(&incomingWiFiMessageQueue, signalMessage);
//
//	signalMessage = Create_Message("set event 89d87141-01f7-4812-a358-3892cf2f5a70 action bdb49750-9ead-466e-96a0-3aa88e7d246c");
//	Set_Message_Type(signalMessage, "tcp");
//	Set_Message_Source(signalMessage, "192.168.1.6:1002");
//	Set_Message_Destination(signalMessage, "192.168.1.3:1002");
//	Queue_Message(&incomingWiFiMessageQueue, signalMessage);
//
//	signalMessage = Create_Message("set event 89d87141-01f7-4812-a358-3892cf2f5a70 state \"TITL TOTH TITL TOTH TITL TOTH TITL TOTH TITL TOTH TITL TOTH\"");
//	Set_Message_Type(signalMessage, "tcp");
//	Set_Message_Source(signalMessage, "192.168.1.6:1002");
//	Set_Message_Destination(signalMessage, "192.168.1.3:1002");
//	Queue_Message(&incomingWiFiMessageQueue, signalMessage);

   for (;;) {

      // Call periodically to parse received messages and to enable the radio to receive
//      Mesh_Process_Commands();

      // TODO: Try processing the IMMEDIATE outgoing messages in the outgoing queue here! This will allow responding to incoming messages as soon as possible, using the queue.

      // Step state machine
      Wifi_State_Step();

      // Monitor incoming message queues and transfer them to the system's incoming queue for processing.
      if (Has_Messages(&incomingWiFiMessageQueue)) {
         message = Dequeue_Message(&incomingWiFiMessageQueue);

         message_status = Process_Incoming_Message(message);

         // If message status is TRUE, message was deleted. If FALSE, then it was not deleted, so queue it into the main system queue... each of those messages is processed one by one, once per iteration through the timeline...
         if (message_status == TRUE) {
            Delete_Message(message);
         } else if (message_status == FALSE) {     // FALSE means that the message was not a basic message, so the timeline has to run before dequeueing...
            // TODO: Process events on the timeline with the message, before dequeueing...
            Queue_Message(&incomingMessageQueue, message);
         }
      }

      // Process the next incoming message on the system queue
      if (lock_timeline == FALSE) {
         if (Has_Messages(&incomingMessageQueue)) {
            message = Peek_Message(&incomingMessageQueue);
            lock_timeline = TRUE;
         }
      }

      // Perform action.
      if ((*timeline).current_event != NULL) {
         if (Process_Event(((*timeline).current_event)) != NULL) {

            // NOTE: Action was performed successfully.

            // TODO: When repeating actions, don't clobber previous changes, just ensure the state is set.
         }

         // Go to the next action on the timeline
         if ((*((*timeline).current_event)).next != NULL) {
            (*timeline).current_event = (*((*timeline).current_event)).next;     // Go to the next action.
         } else {

            // TODO: Remove message from the queue (if it was not a basic message)
            if (lock_timeline == TRUE) {
               if (Has_Messages(&incomingMessageQueue)) {
                  Dequeue_Message(&incomingMessageQueue);
                  Delete_Message(message);
                  lock_timeline = FALSE;
               }
            }

            (*timeline).current_event = (*timeline).first_event;     // Go to the start of the loop.
         }

      } else {

         /*
          // Reset the channel states...
          Reset_Channels();
          Apply_Channels();

          // ...the channel light states...
          Reset_Channel_Lights();
          Apply_Channel_Lights();

          // ...and the device states.
          // TODO: Reset any other device states.
          */
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

//      // Perform action.
//      if ((*timeline).current_event != NULL) {
//         if (Process_Event(((*timeline).current_event)) != NULL) {
//
//            // NOTE: Action was performed successfully.
//
//            // TODO: When repeating actions, don't clobber previous changes, just ensure the state is set.
//
//            // Go to the next action on the timeline
//            if ((*((*timeline).current_event)).next != NULL) {
//            	(*timeline).current_event = (*((*timeline).current_event)).next;     // Go to the next action.
//            } else {
//            	// TODO: Remove message from the queue (if it was not a basic message)
//            	(*timeline).current_event = (*timeline).first_event;     // Go to the start of the loop.
//            }
//         }
//      } else {
//
//         /*
//          // Reset the channel states...
//          Reset_Channels();
//          Apply_Channels();
//
//          // ...the channel light states...
//          Reset_Channel_Lights();
//          Apply_Channel_Lights();
//
//          // ...and the device states.
//          // TODO: Reset any other device states.
//          */
//      }

      // Forward messages on the outgoing system queue to the component-specific outgoing message queue.
      if (Has_Messages(&outgoingMessageQueue) == TRUE) {
         message = Dequeue_Message(&outgoingMessageQueue);

         if (strncmp((*message).type, "device", strlen("device")) == 0) {
            // Device
            Queue_Message(&incomingMessageQueue, message);
         } else if ((strncmp((*message).type, "udp", strlen("udp")) == 0)
                    || (strncmp((*message).type, "tcp", strlen("tcp")) == 0)) {
            // Wi-Fi (UDP or TCP). Propagate to Wi-Fi message queue (or other queue, if exists)
            Queue_Message(&outgoingWiFiMessageQueue, message);
         }
      }

      // TODO: Monitor_Orientation ();

      // TODO: Monitor_Action (); // TODO: In this function, Consider_Action (), Engage_Action (), Perform_Action ().

      // Check and perform "scheduled" periodic events
      Monitor_Periodic_Events();
   }
}

//bool io_state;
void Monitor_Periodic_Events() {

   // TODO: Convert these to a dynamic list of timers with custom timeouts to check periodically?

   if (tick_1ms) {
      tick_1ms = FALSE;

      //TODO: these would be good as tasks
      Buzzer_Stop_Check();
      Imu_Get_Data();
      Button_Periodic_Call();

      // TODO: Put this in a callback timer...
      if (button_mode_timeout > 0) {
         button_mode_timeout--;

         // Check if the button mode timer expired
         if (button_mode_timeout == 0) {
            Request_Reset_Button();
         }
      }

      // TODO: Perform any periodic actions (1 ms).
   }

   if (tick_250ms) {
      tick_250ms = FALSE;

      // TODO: Perform any periodic actions (250 ms).
   }

   if (tick_500ms) {
      tick_500ms = FALSE;

      LED2_PutVal(NULL, led_2_state);
      LED1_PutVal(NULL, led_2_state);
      led_2_state = !led_2_state;

      // TODO: Perform any periodic actions (500 ms).
   }

   if (tick_1000ms) {
      tick_1000ms = FALSE;

      // TODO: Perform any periodic action (1000 ms).
   }

   if (tick_3000ms) {
      tick_3000ms = FALSE;

      // Request Wi-Fi status
      if (!has_connection_to_wifi) {
         WiFi_Request_Get_Connection_Status();
      }

      // Once connected, get Internet address.
      if (has_connection_to_wifi && !has_received_internet_address) {
         WiFi_Request_Get_Internet_Address();
      }

      // Once retreived address, generate broadcast address.
      if (has_received_internet_address && !has_generated_discovery_broadcast_address) {
         // TODO: Generate broadcast address based on received address
      }

      // Once discovery broadcast address is generated and discovery is enabled, send discovery broadcast.
      if (has_generated_discovery_broadcast_address && has_enabled_broadcast) {
         Discovery_Broadcast_Presence();
      }

      // TODO: Perform any periodic actions (3000 ms).
   }
}

void Remote_Button_Pressed(uint8_t * data, uint8_t len) {
   if (len != 2) return;

   RGB_Color c;
   srand(Millis());

   if (data[1]) {
      c.R = 10 + rand() % 130;
      c.G = 10 + rand() % 130;
      c.B = 10 + rand() % 130;
   } else {
      c.R = 0;
      c.G = 0;
      c.B = 0;
   }

   for (int i = data[1] ? 0 : (RGB_MAX - 1); data[1] ? i < RGB_MAX : i >= 0; i += data[1] ? 1 : -1) {
      RGB_LED_SetColor((RGB_LED) i, &c);
      Wait(2);
   }
}

//void Send_Mesh_Test_Message() {
//
//   uint8_t data[2] = { MESH_CMD_BUTTON_PRESSED, Button_Get_Status() };
////   Mesh_Tx(data, 2, 1);
//   Mesh_Tx(data, 2, 2);
//}
