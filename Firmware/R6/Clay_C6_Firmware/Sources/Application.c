#include <Message.h>
#include "Application.h"

#include "Message_Processor.h"
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

#include "UDP_Discovery_temp.h"
#include "Interactive_Assembly.h"

#include "Power_Manager.h"

static bool led_1_state;
static bool led_2_state;
Message *outMessage = NULL;
int status;
char buffer2[128] = { 0 };

#define WIFI_CONNECT_TIMEOUT_ms     20000 //20 seconds should be plenty.
#define VBAT_ADC_SLOPE          7.97094E-5
#define VBAT_ADC_OFFSET         3.20144E-2
static double vBat;

char * ssid = "hefnet";
char * password = "h3fn3r_is_better_than_me";

//char * ssid = "Clay";
//char * password = "redgreenblue";

static bool request_status;
static bool performed_wifi_led_blast = FALSE;
static uint16_t buzzerRatio = 6500;
static uint16_t buzzerPeriod_us = 240;
static uint16_t buzzerDuty_us = 120;
uint32_t Button_Press_Time;
uint32_t adcRead = 0;
LDD_TDeviceDataPtr ADC0_DeviceData;

void Remote_Button_Pressed(uint8_t * data, uint8_t len);
void Send_Mesh_Test_Message();
static void Debug_Functions();

//BAMF
uint32_t wifi_reset_time = 0;

//this code is used when we receive a request message to blink the LEDs. BAMF
#define BLINK_INTERVAL_ms  50
#define BLINK_COUNT        3
int32_t blink_count;
uint32_t blink_time;
bool blunk;

//BAMF led blink
void Blink_Leds() {
   blunk = TRUE;
   blink_time = Millis();
   blink_count = BLINK_COUNT;
}

void Initialize() {

   vBat = 0;
   Button_Press_Time = Millis();
   uint8_t status = 0;

// Initialize Clay

   Debug_Functions();

   Initialize_Unit_UUID();

   Enable_Observable_Interface();     // Enable Clay's observable interface service

   timeline = Create_Timeline("timeline-uuid");

   Enable_Actions();

// Initialize bootloader.
   Initialize_Bootloader();

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

// Message queue.
   if ((status = Initialize_Message_Queue(&incomingMessageQueue)) != TRUE) {
      // Failure
   }

   if ((status = Initialize_Message_Queue(&outgoingMessageQueue)) != TRUE) {
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

//TODO: troubleshoot MPU start with invensense drivers.
//   if ((status = Start_MPU9250()) != TRUE) {
//      // Failure
//   }

   if ((status = Enable_WiFi(ssid, password)) != TRUE) {     // if ((status = Enable_WiFi(SSID_DEFAULT, PASSWORD_DEFAULT)) != TRUE) {
      // Failure
   }

// Status LEDs.

   if ((status = LED_Enable()) != TRUE) {
      // Failure
   }

   Perform_Status_LED_Effect();

   Initialize_Color_Palette();

   if ((Initialize_Channel_Lights()) != TRUE) {
      // Failure
   }

//HACK: buy some time for the ESP to come online. dazzle teh user with fancy lights
   Perform_Status_LED_Effect();

   if ((status = Start_Light_Behavior()) != TRUE) {
      // Failure
   }

//HACK: buy some time for the ESP to come online. dazzle teh user with fancy lights
   Perform_Status_LED_Effect();
   Channel_Light_Startup_Step();

   if ((status = RGB_LED_Enable()) != TRUE) {
      // Failure
   }
   Channel_Light_Startup_Step();

//   if ((status = Perform_Channel_Light_Effect(TRUE)) != TRUE) {
//      // Failure
//   }
   Channel_Light_Startup_Step();

   if ((status == Buzzer_Enable()) != TRUE) {
      // Failure
   }
   Channel_Light_Startup_Step();

//TODO: move power monitor code into a library.
// Initialize Power Monitor
   ADC0_DeviceData = ADC0_Init(NULL);
   Channel_Light_Startup_Step();

// Initialize Power Monitor
   ADC0_StartCalibration(ADC0_DeviceData);
   while (!ADC0_GetMeasurementCompleteStatus(ADC0_DeviceData)) {
      Channel_Light_Startup_Step();
      Wait(10);
   }
   LDD_TError adcCalOk = ADC0_GetCalibrationResultStatus(ADC0_DeviceData);
   Channel_Light_Startup_Step();

//HACK HACK HACK HACK HACK OH NO !!1 ELEVENS
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//   if ((status = Enable_Interactive_Assembly()) != TRUE) {
//      // Failure
//   }
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF
//TODO: DISABLED FOR BAMF

}

// Device profile
// TODO: Create a structure for the device profile
Observable_Interface *observable_interface = NULL;
char internet_address[32] = { 0 };

void Enable_Observable_Interface() {
// <HACK>
// TODO: Consider giving each device a unique interface UUID and expose it.
   char *device_uuid = Get_Unit_UUID();
// </HACK>
   observable_interface = Create_Observable_Interface(device_uuid);     // e.g., "set interface <uuid> provider <uuid> observable <uuid> content <content>"
}

// TODO: Move these into Device_Status.h
int8_t has_connection_to_wifi = FALSE;
int8_t has_received_internet_address = FALSE;
int8_t has_generated_discovery_broadcast_address = FALSE;
int8_t has_enabled_broadcast = FALSE;
char broadcast_address[32];
char local_address[32];

void Discovery_Broadcast_Presence() {

// TODO: Check if have IP address. Only broadcast if have IP address.

// Queue device discovery broadcast
   char *uuid = Get_Unit_UUID();
   sprintf(buffer2, "announce device %s", uuid);
   Message *broadcastMessage = Create_Message();
   Set_Message_Type(broadcastMessage, "udp");
   Set_Message_Source(broadcastMessage, broadcast_address);
   Set_Message_Destination(broadcastMessage, broadcast_address);
   Set_Message_Content(broadcastMessage, buffer2, strlen(buffer2));
   Set_Message_Content_Type(broadcastMessage, "text");

   Queue_Message(&outgoingMessageQueue, broadcastMessage);
}

void Wait_For_Wifi_Startup() {

   Message * message = NULL;
   bool message_status = FALSE;
//wait until we've finished the startup light show.
   while (!performed_wifi_led_blast) {

      // Monitor incoming message queues and transfer them to the system's incoming queue for processing.
      if (Has_Messages(&incomingWiFiMessageQueue)) {
         message = Wifi_Receive();

         message_status = Process_Incoming_Message(message);

         // If message status is TRUE, message was deleted. If FALSE, then it was not deleted, so queue it into the main system queue... each of those messages is processed one by one, once per iteration through the timeline...
         if (message_status == TRUE) {
            Delete_Message(message);
         } else if (message_status == FALSE) {     // FALSE means that the message was not a basic message, so the timeline has to run before dequeueing...
            Queue_Message(&incomingMessageQueue, message);
            message = NULL;     //queue has the reference to this message now.
         }
      }

      Monitor_Periodic_Events();
   }
}

int8_t message_status = FALSE;
uint8_t lock_timeline = FALSE;
uint8_t pause_timeline = FALSE;

//#define SKIP_FIRMWARE_CHECKSUM

void Application(void) {
   Message *message = NULL;
   int i;

#if !defined SKIP_FIRMWARE_CHECKSUM
   if (Update_Available()) {
      Disable_Interrupts();
      Jump_To_Bootloader_And_Update_Application();
   }
#else
#warning BOOTLOADER CHECK IS DISABLED!!!!
#endif

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
         message = Wifi_Receive();

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
         message_status = Process_Event(((*timeline).current_event));

         if (message_status != FALSE) {

            // NOTE: Action was performed successfully.

            // TODO: When repeating actions, don't clobber previous changes, just ensure the state is set.
         }

         if (message_status != 2) {
            // Go to the next action on the timeline
            if ((*((*timeline).current_event)).next != NULL) {
               (*timeline).current_event = (*((*timeline).current_event)).next;     // Go to the next action.
            } else {

               // TODO: Remove message from the queue (if it was not a basic message)
               if (lock_timeline == TRUE) {
                  if (Has_Messages(&incomingMessageQueue)) {
                     message = Dequeue_Message(&incomingMessageQueue);
                     Delete_Message(message);
                     lock_timeline = FALSE;
                  }
               }

               (*timeline).current_event = (*timeline).first_event;     // Go to the start of the loop.
            }
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

         if (strncmp((*message).message_type, "device", strlen("device")) == 0) {
            // Device
            Queue_Message(&incomingMessageQueue, message);
         } else if ((strncmp((*message).message_type, "udp", strlen("udp")) == 0)
                    || (strncmp((*message).message_type, "tcp", strlen("tcp")) == 0)) {
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

   if (blink_count > 0 && (Millis() - blink_time) > BLINK_INTERVAL_ms) {
      interactive_assembly_using_lights = true;
      for (int i = 0; i < CHANNEL_COUNT; ++i) {
         if (blunk) {
            Set_Light_Color(&proposed_light_profiles[i], 0, 0, 150);
         } else {
            Set_Light_Color(&proposed_light_profiles[i], 0, 0, 0);
         }
      }

      if (!blunk) {
         --blink_count;
      }

      // Apply the new light states
      Apply_Channels();
      Apply_Channel_Lights();
      blink_time = Millis();
      blunk = !blunk;

      interactive_assembly_using_lights = blink_count > 0;
   }

   if (tick_1ms) {
      tick_1ms = FALSE;

      //TODO: these would be good as tasks

      Buzzer_Stop_Check();

      Imu_Get_Data();

      Button_Periodic_Call();

      Channel_Periodic_Call();

      Interactive_Assembly_Periodic_Call();

      Wifi_State_Step();

      // TODO: Perform any periodic actions (1 ms).
   }

//HACK: added 10ms tick and the code in it for BAMF day 2
   if (tick_10ms) {
      tick_10ms = FALSE;
      if (has_connection_to_wifi && !performed_wifi_led_blast) {
         performed_wifi_led_blast = Channel_Light_Blast_Step();
         if (performed_wifi_led_blast) {
            Channel_Light_Program_Reset();
         }
      }
   }

//HACK: added 50ms tick and the code in it for BAMF day 2
   if (tick_50ms) {
      tick_50ms = FALSE;

      if (!has_connection_to_wifi) {
         if ((Millis() - wifi_reset_time) > WIFI_CONNECT_TIMEOUT_ms) {
            wifi_reset_time = Millis();
            Enable_WiFi(ssid, password);
            Channel_Light_Program_Reset();
         }
         Channel_Light_Startup_Step();
      }
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
         //6 second period.
         if (request_status) {
            request_status = false;
            WiFi_Request_Get_Connection_Status();
         } else {
            request_status = true;
         }
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
         Discovery_Broadcast_Presence_4446();
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

#define WIFI_DEBUG_BUTTONS

static void Debug_Functions() {

#if defined TEST_BLINK
#warning DEBUG BUTTONS ENABLED!!!!
   Button_Register_Press_Response(Blink_Leds);
#endif

#if defined TEST_SOFTWARE_RESET
#warning DEBUG BUTTONS ENABLED!!!!
   Button_Register_Hold_Response(5000, Software_Reset);
#endif

#if defined TEST_MESH_MESSAGES
#warning DEBUG BUTTONS ENABLED!!!!
   Button_Register_Press_Response(Send_Mesh_Test_Message);
   Button_Register_Release_Response(Send_Mesh_Test_Message);
#endif

#if defined WIFI_DEBUG_BUTTONS
#warning DEBUG BUTTONS ENABLED!!!!
   Button_Register_Press_Response(Wifi_Set_Programming_Mode);
   Button_Register_Hold_Response(500, Wifi_Set_Operating_Mode);
#endif

#if defined WIFI_TEST
#warning WIFI TEST ENABLED!!!!
   Wifi_Test();
#elif defined MULTIBYTE_TEST
#warning MULTIBYTE RING BUFFER TEST ENABLED!!!!
   Multibyte_Ring_Buffer_Test();
#endif
}


//void Check_Queue_Pointers() {
//
//   if (incomingMessageQueue == NULL) return;
//
//   Message * lastMessage = incomingMessageQueue;     // Get the front of the queue.
//
//   if ((lastMessage) > 0x2002FFF0) {
//      PE_DEBUGHALT();
//   }
//
//   if ((lastMessage->previous) > 0x2002FFF0) {
//      PE_DEBUGHALT();
//   }
//
//   while ((*lastMessage).previous != NULL) {
//
//      if ((lastMessage) > 0x2002FFF0) {
//         PE_DEBUGHALT();
//      }
//
//      if ((lastMessage->previous) > 0x2002FFF0) {
//         PE_DEBUGHALT();
//      }
//      lastMessage = (*lastMessage).previous;
//
//      if ((lastMessage) > 0x2002FFF0) {
//         PE_DEBUGHALT();
//      }
//
//      if ((lastMessage->previous) > 0x2002FFF0) {
//         PE_DEBUGHALT();
//      }
//   }
//}
