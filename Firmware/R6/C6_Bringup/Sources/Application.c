#include "Application.h"
#include "meshTest.h"
#include "Bootloader.h"
#include "Mesh.h"
#include "RGB_LED.h"
#include "Clock.h"
#include "MPU9250.h"
#include "LEDs.h"
#include "Events.h"

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

static bool led_1_state;
static bool led_2_state;
Message *outMessage = NULL;
int status;

int8_t Start_Light_Behavior()
{
   //stubbed.
}

int8_t Perform_Channel_Light_Effect(uint8_t reverse)
{
   //stubbed
}

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

   if ((status = Clock_Enable()) != TRUE)
   {
      // Failure
   }

   if ((status = Clock_Start()) != TRUE)
   {
      // Failure
   }

   // Status LEDs.

   if ((status = LED_Enable()) != TRUE)
   {
      // Failure
   }

   Perform_Status_LED_Effect();

   if (!(status = Enable_Mesh()))
   {
      //failure
   }

   if (!(status = Start_Mesh()))
   {
      //failure
   }

   // Channels.

   if ((status = Enable_Channels()) != TRUE)
   {
      // Failure
   }

   if ((Initialize_Channels()) != TRUE)
   {
      // Failure
   }

   if ((status = RGB_LED_Enable()) != TRUE)
   {
      // Failure
   }

   int ledIndex = 0;
   int colorIndex = 0;
   RGB_Color currentColor = { 0, 0, 0 };

   uint8_t rTime = 30;
   uint8_t gTime = 30;
   uint8_t bTime = 30;

   uint8_t rMax = 0x90;
   uint8_t gMax = 0x97;
   uint8_t bMax = 0xAA;

   uint8_t rMin = 0x01;
   uint8_t gMin = 0x01;
   uint8_t bMin = 0x01;

   uint8_t rStep = 1;
   uint8_t gStep = 1;
   uint8_t bStep = 1;

   uint8_t r = rMax;
   uint8_t g = gMax;
   uint8_t b = bMax;

   bool rDescending = TRUE;
   bool gDescending = TRUE;
   bool bDescending = TRUE;

   bool LastState = LedOn;
   bool HbLedState = FALSE;
   bool BuzzerState = FALSE;

   for (int i = 0; i < RGB_MAX; ++i)
   {
      RGB_LED_SetState((RGB_LED) i, TRUE, LED_CURRENT_QUARTER);
   }

   for (;;)
   {
//      while (LastState == LedOn)
//         ;
//
//      LastState = LedOn;

      if (!(Millis() % 15))
      {
         currentColor.R = r;     // LedOn ? 0xFF : 0xAA;
         currentColor.G = g;     // LedOn ? 0xFF : 0xAA;
         currentColor.B = b;     // LedOn ? 0xFF : 0xAA;
//         currentColor.R = LedOn ? 0xFF : 0xAA;
//         currentColor.G = LedOn ? 0xFF : 0xAA;
//         currentColor.B = LedOn ? 0xFF : 0xAA;
//         currentColor.R = LedOn ? 0xFF : 0xAF;
//         currentColor.G = LedOn ? 0xFF : 0xAF;
//         currentColor.B = LedOn ? 0xFF : 0xAF;
         for (int i = 0; i < RGB_MAX; ++i)
//         for (;;)
         {
//            Wait(500);
//            ++currentColor.R;
//            ++currentColor.G;
//            ++currentColor.B;
//
//            for (int i = 0; i < RGB_MAX; ++i)
//            {
//               RGB_LED_SetColor((RGB_LED) i, &currentColor);
            RGB_LED_SetColor((RGB_LED) i, &currentColor);
//            Wait(1);
//            }
         }

         RGB_LED_SetColor((RGB_LED) ledIndex, &currentColor);

         LED1_PutVal(NULL, HbLedState);

         RGB_LED_UpdateOutput();
         ledIndex = (ledIndex + 1) % RGB_MAX;
      }

      if (!(Millis() % gTime))
      {
         if (rDescending)
         {
            if (LastState != LedOn || (r -= rStep) <= rMin)
            {
               rDescending = FALSE;
               if (!gDescending && !bDescending)
               {
                  LastState = LedOn;
               }
            }
         }
         else
         {
            if ((r += rStep) >= rMax)
            {
               rDescending = TRUE;
            }
         }
      }

      if (!(Millis() % gTime))
      {
         if (gDescending)
         {
            if (LastState != LedOn || (g -= gStep) <= gMin)
            {
               gDescending = FALSE;
               if (!rDescending && !bDescending)
               {
                  LastState = LedOn;
               }
            }
         }
         else
         {
            if ((g += gStep) >= gMax)
            {
               gDescending = TRUE;
            }
         }
      }

      if (!(Millis() % bTime))
      {
         if (bDescending)
         {
            if (LastState != LedOn || (b -= bStep) <= bMin)
            {
               bDescending = FALSE;
               if (!gDescending && !rDescending)
               {
                  LastState = LedOn;
               }
            }
         }
         else
         {
            if ((b += bStep) >= bMax)
            {
               bDescending = TRUE;
            }
         }
      }

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

//TODO: troubleshoot MPU start with invensense drivers.
   if (0 && (status = Start_MPU9250()) != TRUE)
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

   for (;;)
   {

//		Send_HTTP_Request ("192.168.1.105", 8080, "test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test,test");

// Check and process any incoming requests
//        Wait(10);        // Wait (100);
      Monitor_Network_Communications();
      MeshTestLoopStep();

//        mesh_process_commands();

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

void Monitor_Periodic_Events()
{

// TODO: Add dynamic list of timers with custom timeouts to check periodically.

   if (data_ready)
   {
      //        LED1_PutVal(NULL, led_1_state);
      //        led_1_state = !led_1_state;

      imu_periodic_callback();
   }

// LEDs
   if (tick_1ms)
   {
      tick_1ms = FALSE;

      // TODO: Perform any periodic actions (1 ms).

   }

   if (tick_250ms)
   {
      tick_250ms = FALSE;

      // TODO: Perform any periodic actions (1 ms).
   }

   if (tick_500ms)
   {
      tick_500ms = FALSE;

      LED2_PutVal(NULL, led_2_state);
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

   if (tick_3000ms)
   {
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
      outMessage = Create_Message(discoveryMessage);
      Queue_Outgoing_Message("255.255.255.255", outMessage);
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
