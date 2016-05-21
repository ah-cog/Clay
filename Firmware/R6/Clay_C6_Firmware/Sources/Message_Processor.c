#include "Application.h"
#include "Message_Processor.h"
#include "Trigger.h"
#include "Action.h"
#include "Event.h"
#include "Timeline.h"
#include "Power_Manager.h"

#include "Interactive_Assembly.h"
#include "UDP_Discovery_temp.h"

#define FIRST_PARAMETER   0
#define SECOND_PARAMETER  1
#define THIRD_PARAMETER   2
#define FOURTH_PARAMETER  3
#define FIFTH_PARAMETER   4
#define SIXTH_PARAMETER   5
#define SEVENTH_PARAMETER 6
#define EIGHTH_PARAMETER  7
#define NINTH_PARAMETER   8
#define TENTH_PARAMETER   9

char uuid_buffer[DEFAULT_UUID_LENGTH] = { 0 };
char uuid_buffer2[512] = { 0 };     // char uuid_buffer2[DEFAULT_UUID_LENGTH] = { 0 };
char state_buffer[MAXIMUM_GRAMMAR_SYMBOL_LENGTH] = { 0 };

static uint8_t Message_Content_Parameter_Equals(Message *message, int token_index, const char *pattern);
static int8_t Process_Cache_Action(Message *message);
static int8_t Process_Start_Event(Message *message);
static int8_t Process_Stop_Event(Message *message);
static int8_t Process_Set_Event_Action(Message *message);
static int8_t Process_Set_Event_State(Message *message);
static int8_t Process_Set_Event_Trigger(Message *message);
static int8_t Process_Get_Event_State(Message * message);
static int8_t Process_Set_Event_Context(Message *message);
static int8_t Process_Set_Event_Length(Message *message);
static int8_t Receive_Interactive_Assembly_Message(Message *message);
static int8_t Process_Set_Observable_Content(Message *message);
static int8_t Hack_Process_Start_Propagator(Message *message);

int8_t Process_Incoming_Message(Message *message) {

   int8_t status = NULL;
   int8_t result = NULL;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };
   int token_count = 0;

   if (message == NULL) {
      return FALSE;
   }

   token_count = Get_Token_Count((*message).content);

// Reset the buffer
   memset(uuid_buffer2, '\0', DEFAULT_UUID_LENGTH);

// <HACK>
// TODO: Handle messages from ESP8266:
// TODO: - INFO,CONNECTED
// TODO: - INFO,192.168.1.1 (for example)
// TODO: - INFO,DISCONNECTED
   if (strncmp((*message).type, "status", strlen("status")) == 0) {

      // <HACK>
      // </HACK>
      if (has_connection_to_wifi == FALSE) {
         if (Message_Content_Parameter_Equals(message, FIRST_PARAMETER, "wifi")) {
            if (Message_Content_Parameter_Equals(message, SECOND_PARAMETER, "connected")) {
               has_connection_to_wifi = TRUE;

//					Delete_Message (message);
               return TRUE;
            }
         }
      } else if (Message_Content_Parameter_Equals(message, SECOND_PARAMETER, "disconnected")) {
         has_connection_to_wifi = FALSE;
         has_received_internet_address = FALSE;
         has_generated_discovery_broadcast_address = FALSE;
         has_enabled_broadcast = FALSE;
//         Delete_Message(message);
         return TRUE;
      }

      if (has_connection_to_wifi == TRUE && has_received_internet_address == FALSE) {
         if (Message_Content_Parameter_Equals(message, FIRST_PARAMETER, "wifi")) {
            if (Message_Content_Parameter_Equals(message, SECOND_PARAMETER, "address")) {
               has_received_internet_address = TRUE;

               // Extract address
               // e.g., "wifi address 192.168.43.6"

               // Find the beginning of the fourth octet
               char *internet_address = NULL;
               internet_address = (*message).content;     // Start at the beginning of the message content (first token)...
               internet_address = strchr(internet_address, ' ') + 1;     // ...then jump to "address" (second token)...
               internet_address = strchr(internet_address, ' ') + 1;     // ...then jump to start of first address octet (third token)...

               strncpy(local_address, internet_address, strlen(internet_address));

               char *fourth_octet = strchr(internet_address, '.') + 1;     // ...then the second...
               fourth_octet = strchr(fourth_octet, '.') + 1;     // ...then the third...
               fourth_octet = strchr(fourth_octet, '.') + 1;     // ...then the fourth.

               // e.g., "192.168.43.255:4445"

               // i.e., Copy "192.168.43." into broadcast_address
               strncpy(broadcast_address, internet_address, (fourth_octet - internet_address));
               strncpy(broadcast_address_module, internet_address, (fourth_octet - internet_address));

               broadcast_address[fourth_octet - internet_address] = '\0';
               strcat(broadcast_address, "255:4445");

               broadcast_address_module[fourth_octet - internet_address] = '\0';
               strcat(broadcast_address_module, "255:4446");

               has_generated_discovery_broadcast_address = TRUE;
            }
         }
      }

      if (has_connection_to_wifi == TRUE
          && has_received_internet_address == TRUE
          && has_generated_discovery_broadcast_address == TRUE
          && has_enabled_broadcast == FALSE) {
         has_enabled_broadcast = TRUE;

//			Delete_Message (message);
         return TRUE;
      }
   }
// </HACK>

   if (Check_For_Discovery_Message(message)) {
      return TRUE;
   }

   if (Receive_Interactive_Assembly_Message(message)) {
      return TRUE;
   }

// "get channel state"
// "get observables" -> "(<id>, <key>), (<id>, <key>), (<id>, <key>), ..."
// "propagate observable <source-observable> <source-observable> observable <destination-observable> <destination-key>"
// "set channel <number> observable <key> source [to] channel <number> observable <key>"
// "propagate channel <number> observable <key> [to] channel <number> observable <key>"

   if (Message_Content_Parameter_Equals(message, FIRST_PARAMETER, "cache")) {
      if (Message_Content_Parameter_Equals(message, SECOND_PARAMETER, "action")) {
         return Process_Cache_Action(message);
      }
   } else if (Message_Content_Parameter_Equals(message, FIRST_PARAMETER, "start")) {
      if (Message_Content_Parameter_Equals(message, SECOND_PARAMETER, "event")) {
         return Process_Start_Event(message);
      }
   } else if (Message_Content_Parameter_Equals(message, FIRST_PARAMETER, "stop")) {
      if (Message_Content_Parameter_Equals(message, SECOND_PARAMETER, "event")) {
         return Process_Stop_Event(message);
      }
   } else if (Message_Content_Parameter_Equals(message, FIRST_PARAMETER, "set")) {
      if (Message_Content_Parameter_Equals(message, SECOND_PARAMETER, "event")) {
         if (Message_Content_Parameter_Equals(message, FOURTH_PARAMETER, "action")) {
            return Process_Set_Event_Action(message);
         } else if (Message_Content_Parameter_Equals(message, FOURTH_PARAMETER, "state")) {     // JUST DATA GOES HERE
            return Process_Set_Event_State(message);
         } else if (Message_Content_Parameter_Equals(message, FOURTH_PARAMETER, "trigger")) {     // Rename to "CUE"
            return Process_Set_Event_Trigger(message);
         } else if (Message_Content_Parameter_Equals(message, FOURTH_PARAMETER, "context")) {     // PUT CHANNEL CONFIG STUFF HERE! (& send before state)
            return Process_Set_Event_Context(message);
         } else if (Message_Content_Parameter_Equals(message, FOURTH_PARAMETER, "duration")) {
            return Process_Set_Event_Length(message);
         }
      } else if (Message_Content_Parameter_Equals(message, SECOND_PARAMETER, "provider")) {
         // e.g., "set provider <uuid> observable <key> type <type> content <content>"
         if (Message_Content_Parameter_Equals(message, FOURTH_PARAMETER, "observable")) {
            if (Message_Content_Parameter_Equals(message, SIXTH_PARAMETER, "type")) {
               if (Message_Content_Parameter_Equals(message, EIGHTH_PARAMETER, "content")) {
                  return Process_Set_Observable_Content(message);
               }
            }
         }
      }
   } else if (Message_Content_Parameter_Equals(message, FIRST_PARAMETER, "get")) {
      if (Message_Content_Parameter_Equals(message, SECOND_PARAMETER, "channel")) {
         if (Message_Content_Parameter_Equals(message, FOURTH_PARAMETER, "state")) {
            return Process_Get_Event_State(message);
         }
      }
   } else if (Message_Content_Parameter_Equals(message, FIRST_PARAMETER, "propagate")) {
      // e.g., propagate 3,'waveform_sample_value' to 002effff-ffff-ffff-4e45-3158200a0015,4,'pulse_duty_cycle'
      return Hack_Process_Start_Propagator(message);
   } else if (Message_Content_Parameter_Equals(message, FIRST_PARAMETER, "request")) {
      if (Message_Content_Parameter_Equals(message, SECOND_PARAMETER, "blink")) {
Blink_Leds();
         return TRUE;
      } else if (Message_Content_Parameter_Equals(message, SECOND_PARAMETER, "reset")) {
         Power_Manager_Software_Reset();
         return TRUE; //not really needed, we'll never come back from the reset...
      }
      return Hack_Process_Start_Propagator(message);
   } else {
      // TODO: Don't delete the message until after executing the entire timeline of events.
      // TODO: (cont'd) Do if any message trigger dependencies are present on events in the timeline.
      // TODO: (cont'd) Can delete message if no triggers depend on it.
      // TODO: (cont'd) Perform_Timeline for Timeline, without changing its state, for each message. Process all timeline messages until custom message is recognized, then run the timeline with each custom message, one by one, until all processed.
      //Delete_Message (message);
      return FALSE;
   }

// TODO: Store message UUID for use in message acknowledgment protocol. If it has been received, then don't apply it again, just send the acknowledgment packet.

//	return FALSE;
}

int8_t Process_Outgoing_Message(Message *message) {

   int8_t result = NULL;

   if (message != NULL) {

      // Send message over Wi-Fi
      result = Wifi_Send(message);

      result = TRUE;

   }

   return result;
}

static uint8_t Message_Content_Parameter_Equals(Message *message, int token_index, const char *pattern) {
   int8_t status = NULL;
   int8_t result = NULL;
   char *message_content = (*message).content;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };
   if ((status = Get_Token(message_content, token, token_index)) != NULL) {
      if (strncmp(token, pattern, strlen(pattern)) == 0) {
         return TRUE;
      }
   }
   return FALSE;
}

static int8_t Process_Cache_Action(Message *message) {

   int8_t status = NULL;
   int8_t result = NULL;

   char *message_content = NULL;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };
   message_content = (*message).content;

// Get UUID (parameter index 2) and command (parenthesized string index 3)
   Get_Token(message_content, uuid_buffer, THIRD_PARAMETER);
//	Get_Token (message_content, state_buffer, FOURTH_PARAMETER);

// Send message to sender to acknowledge receipt
   Send_Acknowledgment(token, message_content);

// Delete the message
//	Delete_Message (message);

// Check if the action is already in the cache. If nay, cache it!
// TODO: Get available memory and only create the action if there's enough memory. Otherwise, move something out of memory to make room for it (and stream the moved thing back in when it's needed).
   if (Has_Cached_Action_By_UUID(uuid_buffer) == FALSE) {
      Action *action = Create_Action(uuid_buffer);     // Create the action then cache it
      result = Cache_Action(action);     // Add the action to the local cache!
   } else {
      result = TRUE;     // The action construct already exists in the cache. There's no need to create it!
   }

   return result;
}

static int8_t Process_Start_Event(Message *message) {

   int8_t status = NULL;
   int8_t result = NULL;

   int token_count = 0;

   char *message_content = (*message).content;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

   token_count = Get_Token_Count(message_content);

   if (token_count == 3) {

      // i.e., "start event <uuid>"

      // Get UUID (parameter index 2)
      status = Get_Token(message_content, uuid_buffer, 2);

      // Send message to sender to acknowledge receipt
      Send_Acknowledgment(token, message_content);

      // Delete the message
//		Delete_Message (message);

      // Check if the action is already in the cache. If nay, cache it!
      // TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
      //						if (Has_Cached_Action_By_UUID (uuid_buffer) == TRUE) {
      //							Event *event = Get_Cached_Action_By_UUID (uuid_buffer);
      Event *event = Create_Event(uuid_buffer, NULL, NULL);
      if (event != NULL) {
         Add_Event(timeline, event);
         result = TRUE;
      } else {
         result = FALSE;
      }

   } else if (token_count > 3) {

      // i.e., "start event <event-uuid> before event <event-uuid>"

//	} else if (Message_Content_Parameter_Equals (message, FIRST_PARAMETER, "start")) {
//			if (Message_Content_Parameter_Equals (message, SECOND_PARAMETER, "event")) {
//				return Process_Start_Event (message);
//			}
//		}

      // Extract parameters
      status = Get_Token(message_content, uuid_buffer, 2);     // Get UUID of action being added (parameter index 2)
      status = Get_Token(message_content, uuid_buffer2, 5);     // Get UUID of action already on the loop (parameter index 4)

      // Send message to sender to acknowledge receipt
      Send_Acknowledgment(token, message_content);

      // Delete the message
      Delete_Message(message);

      // Check if the action is already in the cache. If nay, cache it!
      // TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
      //						if (Has_Cached_Action_By_UUID (uuid_buffer) == TRUE && Has_Cached_Action_By_UUID (uuid_buffer2) == TRUE ) {

      Event *event = Create_Event(uuid_buffer, NULL, NULL);
      Event *next_event = Get_Event_By_UUID(timeline, uuid_buffer2);
//		uint16_t event_index = atoi (uuid_buffer2);
      if (event != NULL) {
         //result = Insert_Event (timeline, event, event_index);
         result = Add_Before_Event(timeline, event, next_event);
      } else {
         result = FALSE;
      }
   }
   return result;
}

static int8_t Process_Stop_Event(Message *message) {

   int8_t status = NULL;
   int8_t result = NULL;

   int token_count = 0;

   char *message_content = (*message).content;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

// stop event <event-uuid> [on <timeline-uuid>]
//      ^
//	if (strncmp (token, "event", strlen ("event")) == 0) {

// Get UUID (parameter index 2)
   status = Get_Token(message_content, uuid_buffer, 2);

// Send message to sender to acknowledge receipt
   Send_Acknowledgment(token, message_content);

// Delete the message
//		Delete_Message (message);

// Check if the action is already in the cache. If nay, cache it!
// TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
// Parse the message content and perform the corresponding action operation
   if (Has_Event_By_UUID(timeline, uuid_buffer) == TRUE) {
      Event *event = Get_Event_By_UUID(timeline, uuid_buffer);
      if (event != NULL) {
         Remove_Event(timeline, event);     // Add the action to the local cache!
         Delete_Event(event);
         result = TRUE;
      }
   } else {
      // TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
      result = FALSE;
   }
//	}
   return result;
}

static int8_t Process_Set_Event_Action(Message *message) {

   int8_t status = NULL;
   int8_t result = NULL;

   int token_count = 0;

   char *message_content = (*message).content;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

// i.e., "set event <event-uuid> action <action-uuid>"

// Extract parameters
   status = Get_Token(message_content, uuid_buffer, 2);     // Get UUID of action being added (parameter index 2)
   status = Get_Token(message_content, uuid_buffer2, 4);     // Get UUID of action already on the loop (parameter index 4)

// Send message to sender to acknowledge receipt
   Send_Acknowledgment(token, message_content);

// Delete the message
//	Delete_Message (message);

// Check if the action is already in the cache. If nay, cache it!
// TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
   if (Has_Event_By_UUID(timeline, uuid_buffer) == TRUE && Has_Cached_Action_By_UUID(uuid_buffer2) == TRUE) {

      // Get the event with the UUID and assign the action with the UUID.
      Event *event = Get_Event_By_UUID(timeline, uuid_buffer);
      Action *action = Get_Cached_Action_By_UUID(uuid_buffer2);
      if (event != NULL && action != NULL) {
         (*event).action = action;
         result = TRUE;

//         // <HACK>
//         if (strncmp(uuid_buffer2, "99ff8f6d-a0e7-4b6e-8033-ee3e0dc9a78e", strlen("99ff8f6d-a0e7-4b6e-8033-ee3e0dc9a78e")) == 0) {
//        	 (*event).repeat_period = 1000;
//         } else if (strncmp(uuid_buffer2, "56d0cf7d-ede6-4529-921c-ae9307d1afbc", strlen("56d0cf7d-ede6-4529-921c-ae9307d1afbc")) == 0) {
//        	 (*event).repeat_period = 1000;
//         }
//         // </HACK>
      } else {
         // TODO: If action or nextAction are NULL, stream them in over the Internet.
      }
   } else {
      // TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
      result = FALSE;
   }

   return result;
}

static int8_t Process_Set_Event_State(Message *message) {

   int8_t status = NULL;
   int8_t result = NULL;

   int token_count = 0;

   char *message_content = (*message).content;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

// i.e., "set event <event-uuid> action <action-uuid>"

// Extract parameters
   status = Get_Token(message_content, uuid_buffer, 2);     // Get UUID of action (parameter index 2)
   status = Get_Token(message_content, uuid_buffer2, 4);     // Get state of action (parameter index 4)

// Send message to sender to acknowledge receipt
   Send_Acknowledgment(token, message_content);

// Delete the message
//	Delete_Message (message);

// Check if the action is already in the cache. If nay, cache it!
// TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
   if (Has_Event_By_UUID(timeline, uuid_buffer) == TRUE) {

      // Get the event with the UUID and assign the action with the UUID.
      Event *event = Get_Event_By_UUID(timeline, uuid_buffer);
      //	Action *action = Get_Cached_Action_By_UUID (uuid_buffer2);
      if (event != NULL) {
         Set_Event_State(event, uuid_buffer2);
         result = TRUE;
      } else {
         // TODO: If action or nextAction are NULL, stream them in over the Internet.
      }
   } else {
      // TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
      result = FALSE;
   }

   return result;
}

static int8_t Process_Set_Observable_Content(Message *message) {

   int8_t status = NULL;
   int8_t result = NULL;

   int token_count = 0;

   char *message_content = (*message).content;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

   char content_buffer[32] = { 0 };
   char observable_buffer[32] = { 0 };
   char type_buffer[32] = { 0 };

   // i.e., "start device <uuid> provider <uuid> observable <key> content <content> type <type>" (maybe "enable" rather than "start")
   //       (or) "set device <uuid> provider <uuid> observable <key> content <content> type <type>" (maybe "enable" rather than "start")
   //
   // This is created on the sender by a propagator that has a destination observable with a device UUID not matching the sender's. For example:
   //
   // e.g., "set [device <uuid>] provider "00000000-0000-0000-0000-000000000004" observable "pulse_duty_cycle" content "scaled_output" [type "int32"]
   //
   // Don't need the type when just sending data. The received data is assumed to be encoded as a string and is cast to the type of the
   // destination observable. This type is determined by calling one function such as atoi, strtof, strtod, etc. based on the data type
   // stored in (*destinatino_observable).content_type.

   // TODO: Make function for generating (temporary) UUIDs from system tick bytes then generate string from that.
   // TODO: Make function for quickly making events on the timeline programmatically. Use it for writing interactive assembly code.

   // TODO: Create message to create signal event that configures channel (3) as input on the "local" device.
   // TODO: Create message to create propgator on "local" device that propagates input channel (3) on "local" device to output (4) on "remote" device
   // TODO: Create message to create signal event that configures channel (4) as output on the "remote" device.

   // Extract parameters
   // e.g., "set provider <uuid> observable <key> type <type> content <content>"
   status = Get_Token(message_content, uuid_buffer, 2);     // Get device UUID (parameter index 2)
   status = Get_Token(message_content, observable_buffer, 4);     // Get provider UUID (parameter index 4)
   status = Get_Token(message_content, type_buffer, 6);     // Get state of action (parameter index 6)
   status = Get_Token(message_content, content_buffer, 8);     // Get state of action (parameter index 8)
   //status = Get_Token (message_content, type_buffer, 10);     // Get state of action (parameter index 10)

   // Send message to sender to acknowledge receipt
   Send_Acknowledgment(token, message_content);

   // Delete the message
//	Delete_Message (message);

   /*
    // Create observable provider for the "remote" observable and add it to the interface
    Observable_Set *observable_provider = Create_Observable_Set (uuid_buffer);
    //Set_Observable_Provider_Device_UUID (observable_provider, uuid_buffer);
    Add_Observable_Provider (observable_interface, observable_provider);
    */

   // Create observable and add it to the observable associated provider
   int32_t observable_type = atoi(type_buffer);

   char content_char = 0;
   int16_t content_int16 = 0;
   int32_t content_int32 = 0;
   float content_float = 0;
   double content_double = 0;

   // Get observable provider by UUID
   Observable_Set *observable_provider = Get_Observable_Provider_By_UUID(observable_interface, uuid_buffer);

   // <HACK>
   if (observable_provider == NULL) {
      return TRUE;
   }
   // </HACK>

   // Get observable
   Observable *observable = Get_Observable(observable_provider, observable_buffer);

   // Set the data type
   if (observable_type == CONTENT_TYPE_CHAR) {
      content_char = (char) content_buffer[0];
      Set_Observable_Content(observable, (*observable).content_type, &content_char);
   } else if (observable_type == CONTENT_TYPE_INT16) {
      content_int16 = (int16_t) atoi(content_buffer);
      Set_Observable_Content(observable, (*observable).content_type, &content_int16);
   } else if (observable_type == CONTENT_TYPE_INT32) {
      content_int32 = (int32_t) atoi(content_buffer);
      Set_Observable_Content(observable, (*observable).content_type, &content_int32);
   } else if (observable_type == CONTENT_TYPE_FLOAT) {
      content_float = strtof(content_buffer, NULL);
      Set_Observable_Content(observable, (*observable).content_type, &content_float);
   } else if (observable_type == CONTENT_TYPE_DOUBLE) {
      content_double = strtod(content_buffer, NULL);
      Set_Observable_Content(observable, (*observable).content_type, &content_double);
   }

   /*
    // Set the data type
    if (observable_type == CONTENT_TYPE_CHAR) {
    content_char = (char) content_buffer[0];
    observable = Create_Observable (observable_buffer, observable_type, &content_char);
    } else if (observable_type == CONTENT_TYPE_INT16) {
    content_int16 = (int16_t) atoi (content_buffer);
    observable = Create_Observable (observable_buffer, observable_type, &content_int16);
    } else if (observable_type == CONTENT_TYPE_INT32) {
    content_int32 = (int32_t) atoi (content_buffer);
    observable = Create_Observable (observable_buffer, observable_type, &content_int32);
    } else if (observable_type == CONTENT_TYPE_FLOAT) {
    content_float = strtof (content_buffer, NULL);
    observable = Create_Observable (observable_buffer, observable_type, &content_float);
    } else if (observable_type == CONTENT_TYPE_DOUBLE) {
    content_double = strtod (content_buffer, NULL);
    observable = Create_Observable (observable_buffer, observable_type, &content_double);
    }
    */

   // Add observable to the "remote" provider (already in the "local" interface)
//   Observable *observable = Create_Observable (observable_buffer, observable_type, &content_int32);
//   Observable_Set *observable_set = updated_channel_profile[i].observable_set;
   /*
    Add_Observable (observable_provider, observable);
    */

//   Observable_Set *source_observable_provider = channel_profile[source_channel_index].observable_set;
//   Observable_Set *destination_observable_provider = channel_profile[i].observable_set;
//
//   if (!Has_Propagator (Get_Observable (source_observable_provider, source_observable_key), // Get_Observable (source_observable_set, "waveform_sample_value"),
//		   source_observable_key,
//		   Get_Observable (destination_observable_provider, destination_observable_key),
//		   destination_observable_key)) {
//
//	   Propagator *propagator = Create_Propagator (
//			   Get_Observable (source_observable_provider, source_observable_key), // Get_Observable (source_observable_set, "waveform_sample_value"),
//			   source_observable_key,
//			   Get_Observable (destination_observable_provider, destination_observable_key),
//			   destination_observable_key);
//	   Add_Propagator (
//			   Get_Observable (source_observable_provider, source_observable_key),
//			   propagator);
//   }
//
//   Set_Observable_Content ((*propagator).destination, (*((*propagator).destination)).content_type, &scaled_content);
//   // Set_Observable_Content ((*propagator).destination, (*((*propagator).source)).content_type, (*((*propagator).source)).content);
//
//   // Check if the action is already in the cache. If nay, cache it!
//   // TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
//   if (Has_Event_By_UUID(timeline, uuid_buffer) == TRUE) {
//
//	   // Get the event with the UUID and assign the action with the UUID.
//	   Event *event = Get_Event_By_UUID(timeline, uuid_buffer);
//	   //	Action *action = Get_Cached_Action_By_UUID (uuid_buffer2);
//	   if (event != NULL) {
//		   Set_Event_Context(event, uuid_buffer2);
//		   result = TRUE;
//	   } else {
//		   // TODO: If action or nextAction are NULL, stream them in over the Internet.
//	   }
//   } else {
//	   // TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
//	   result = FALSE;
//   }
   return result;
}

static int8_t Hack_Process_Start_Propagator(Message *message) {

   int8_t status = NULL;
   int8_t result = NULL;

   int token_count = 0;

   char *message_content = (*message).content;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

   char content_buffer[32] = { 0 };
   char observable_buffer[32] = { 0 };
   char type_buffer[32] = { 0 };

   // e.g., propagate 3,'waveform_sample_value' to 002effff-ffff-ffff-4e45-3158200a0015,4,'pulse_duty_cycle'

   // e.g., propagate 3 waveform_sample_value to 002effff-ffff-ffff-4e45-3158200a0015 4 pulse_duty_cycle

   // e.g., propagate 00000000-0000-0000-0000-000000000003 toggle_value to 002fffff-ffff-ffff-4e45-3158200a0015 00000000-0000-0000-0000-000000000004 pulse_duty_cycle

   // Extract parameters
//   status = Get_Token (message_content, uuid_buffer, 2);     // Get device UUID (parameter index 2)
//   status = Get_Token (message_content, observable_buffer, 4);     // Get provider UUID (parameter index 4)
//   status = Get_Token (message_content, type_buffer, 6);     // Get state of action (parameter index 6)
//   status = Get_Token (message_content, content_buffer, 8);     // Get state of action (parameter index 8)
//   //status = Get_Token (message_content, type_buffer, 10);     // Get state of action (parameter index 10)

   char *source_provider_uuid = NULL;
   char *source_observable_key = NULL;
   char *destination_device_uuid = NULL;
   char *destination_provider_uuid = NULL;
   char *destination_observable_key = NULL;

   source_provider_uuid = strtok(message_content, " ");     // <HACK />
   source_provider_uuid = strtok(NULL, " ");
   source_observable_key = strtok(NULL, " ");
   destination_device_uuid = strtok(NULL, " ");     // <HACK />
   destination_device_uuid = strtok(NULL, " ");
   destination_provider_uuid = strtok(NULL, " ");
   destination_observable_key = strtok(NULL, " ");

   // Send message to sender to acknowledge receipt
   Send_Acknowledgment(token, message_content);

   // Delete the message
//	Delete_Message (message);

   /*
    // Create observable provider for the "remote" observable and add it to the interface
    Observable_Set *observable_provider = Create_Observable_Set (uuid_buffer);
    //Set_Observable_Provider_Device_UUID (observable_provider, uuid_buffer);
    Add_Observable_Provider (observable_interface, observable_provider);
    */

   // Create observable and add it to the observable associated provider
//   int32_t observable_type = atoi (type_buffer);
//   char content_char = 0;
//   int16_t content_int16 = 0;
//   int32_t content_int32 = 0;
//   float content_float = 0;
//   double content_double = 0;
   // Get observable provider by UUID
   Observable_Set *observable_provider = Get_Observable_Provider_By_UUID(observable_interface, source_provider_uuid);

   // <HACK>
   if (observable_provider == NULL) {
      return TRUE;
   }
   // </HACK>

   // Get observable
   Observable *source_observable = Get_Observable(observable_provider, source_observable_key);

   // <HACK>
   // Create destination observable (for propagator)
   int32_t content_int32 = 0;
   Observable *destination_observable = Create_Observable(destination_observable_key, CONTENT_TYPE_INT32, &content_int32);
   Set_Observable_Provider_UUID(destination_observable, destination_provider_uuid);
   Set_Observable_Device_UUID(destination_observable, destination_device_uuid);
   // TODO: Observable_Set *observable_set = updated_channel_profile[i].observable_set;
   // </HACK>

   // Add observable to the "remote" provider (already in the "local" interface)
//   Observable *observable = Create_Observable (observable_buffer, observable_type, &content_int32);
//   Observable_Set *observable_set = updated_channel_profile[i].observable_set;
   /*
    Add_Observable (observable_provider, observable);
    */

//   Observable_Set *source_observable_provider = channel_profile[source_channel_index].observable_set;
//   Observable_Set *destination_observable_provider = channel_profile[i].observable_set;
//
   if (!Has_Propagator(source_observable,     // Get_Observable (source_observable_set, "waveform_sample_value"),
                       (*source_observable).key,
                       destination_observable,
                       (*destination_observable).key)) {

      Propagator *propagator = Create_Propagator(source_observable,     // Get_Observable (source_observable_provider, source_observable_key), // Get_Observable (source_observable_set, "waveform_sample_value"),
                                                 (*source_observable).key,
                                                 destination_observable,
                                                 (*destination_observable).key);
      Add_Propagator(source_observable,     // Get_Observable (source_observable_provider, source_observable_key),
                     propagator);
   }
//
//   Set_Observable_Content ((*propagator).destination, (*((*propagator).destination)).content_type, &scaled_content);
//   // Set_Observable_Content ((*propagator).destination, (*((*propagator).source)).content_type, (*((*propagator).source)).content);
//
//   // Check if the action is already in the cache. If nay, cache it!
//   // TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
//   if (Has_Event_By_UUID(timeline, uuid_buffer) == TRUE) {
//
//	   // Get the event with the UUID and assign the action with the UUID.
//	   Event *event = Get_Event_By_UUID(timeline, uuid_buffer);
//	   //	Action *action = Get_Cached_Action_By_UUID (uuid_buffer2);
//	   if (event != NULL) {
//		   Set_Event_Context(event, uuid_buffer2);
//		   result = TRUE;
//	   } else {
//		   // TODO: If action or nextAction are NULL, stream them in over the Internet.
//	   }
//   } else {
//	   // TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
//	   result = FALSE;
//   }

   return result;
}

static int8_t Process_Set_Event_Context(Message *message) {

   int8_t status = NULL;
   int8_t result = NULL;

   int token_count = 0;

   char *message_content = (*message).content;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

// i.e., "set event <event-uuid> action <action-uuid>"

// Extract parameters
   status = Get_Token(message_content, uuid_buffer, 2);     // Get UUID of action (parameter index 2)
   status = Get_Token(message_content, uuid_buffer2, 4);     // Get state of action (parameter index 4)

// Send message to sender to acknowledge receipt
   Send_Acknowledgment(token, message_content);

// Delete the message
//	Delete_Message (message);

// Check if the action is already in the cache. If nay, cache it!
// TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
   if (Has_Event_By_UUID(timeline, uuid_buffer) == TRUE) {

      // Get the event with the UUID and assign the action with the UUID.
      Event *event = Get_Event_By_UUID(timeline, uuid_buffer);
      //	Action *action = Get_Cached_Action_By_UUID (uuid_buffer2);
      if (event != NULL) {
         Set_Event_Context(event, uuid_buffer2);
         result = TRUE;
      } else {
         // TODO: If action or nextAction are NULL, stream them in over the Internet.
      }
   } else {
      // TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
      result = FALSE;
   }

   return result;
}

static int8_t Process_Set_Event_Trigger(Message *message) {

   int8_t status = NULL;
   int8_t result = NULL;

   int token_count = 0;

   char *message_content = (*message).content;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

// i.e., "set event <event-uuid> trigger \"<message-content>\""
// TODO: "set event <event-uuid> trigger <trigger-uuid>"

// Extract parameters
   status = Get_Token(message_content, uuid_buffer, 2);     // Get UUID of event (parameter index 2)
   status = Get_Token(message_content, uuid_buffer2, 4);     // Get state of action (parameter index 4)

// Send message to sender to acknowledge receipt
   Send_Acknowledgment(token, message_content);

// Delete the message
//	Delete_Message (message);

// Check if the action is already in the cache. If nay, cache it!
// TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
   if (Has_Event_By_UUID(timeline, uuid_buffer) == TRUE) {

      // Get the event with the UUID and assign the action with the UUID.
      Event *event = Get_Event_By_UUID(timeline, uuid_buffer);
      if (event != NULL) {

         // start trigger
         Trigger *trigger = Create_Trigger();
         Trigger_Set_Message(trigger, uuid_buffer2);

         // set trigger
         Set_Event_Trigger(event, trigger);

         result = TRUE;
      } else {
         // TODO: If action or nextAction are NULL, stream them in over the Internet.
      }
   } else {
      // TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
      result = FALSE;
   }

   return result;
}

static int8_t Process_Set_Event_Length(Message *message) {

   int8_t status = NULL;
   int8_t result = NULL;

   int token_count = 0;

   char *message_content = (*message).content;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

// i.e., "set event <event-uuid> action <action-uuid>"

// Extract parameters
   status = Get_Token(message_content, uuid_buffer, 2);     // Get UUID of action (parameter index 2)
   status = Get_Token(message_content, uuid_buffer2, 4);     // Get state of action (parameter index 4)

// Send message to sender to acknowledge receipt
   Send_Acknowledgment(token, message_content);

// Delete the message
//	Delete_Message (message);

// Check if the action is already in the cache. If nay, cache it!
// TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
   if (Has_Event_By_UUID(timeline, uuid_buffer) == TRUE) {

      // Get the event with the UUID and assign the action with the UUID.
      Event *event = Get_Event_By_UUID(timeline, uuid_buffer);
      //	Action *action = Get_Cached_Action_By_UUID (uuid_buffer2);
      if (event != NULL) {
         //Set_Event_State(event, uuid_buffer2);
         (*event).repeat_period = atoi(uuid_buffer2);
         result = TRUE;
      } else {
         // TODO: If action or nextAction are NULL, stream them in over the Internet.
      }
   } else {
      // TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
      result = FALSE;
   }

   return result;
}

static int8_t Process_Get_Event_State(Message * message) {

   int8_t result = FALSE;
   Channel_Number number;
   char response_message_content[MAXIMUM_MESSAGE_LENGTH];
   Message * response_message = NULL;

//get the profile index from the message -- "get channel <number> state"

   Get_Token((*message).content, response_message_content, 2);

   number = atoi(response_message_content) - 1;

//get the value from channel_profile
   if (channel_profile[number].direction == CHANNEL_DIRECTION_INPUT) {
      if (channel_profile[number].type == CHANNEL_TYPE_TOGGLE) {
//    	  sprintf(response_message_content, "channel %d state %d", number + 1, channel_profile[number].data->toggle_value);

         // <OPTIMIZE> (Optimize syntax to be smaller, preferably one line.)

         // Get observable set...
         Observable_Set *observable_set = channel_profile[number].observable_set;
         Observable *observable = NULL;

         // ...then get data from channel profile...
         observable = Get_Observable(observable_set, "toggle_value");
         int32_t toggle_value = Get_Observable_Data_Int32(observable);

         // </OPTIMIZE>

         sprintf(response_message_content, "channel %d state %d", number + 1, toggle_value);
         result = TRUE;
      } else if (channel_profile[number].type == CHANNEL_TYPE_WAVEFORM) {
//         sprintf(response_message_content, "channel %d state %d", number + 1, channel_profile[number].data->waveform_sample_value);

         // <OPTIMIZE> (Optimize syntax to be smaller, preferably one line.)

         // Get observable set...
         Observable_Set *observable_set = channel_profile[number].observable_set;
         Observable *observable = NULL;

         // ...then get data from channel profile...
         observable = Get_Observable(observable_set, "waveform_sample_value");
         int32_t waveform_sample_value = Get_Observable_Data_Int32(observable);

         // </OPTIMIZE>

         sprintf(response_message_content, "channel %d state %d", number + 1, waveform_sample_value);

         result = TRUE;
      } else {
         result = TRUE;
      }
   }

   if (result) {

      response_message = Create_Message(response_message_content);
      Set_Message_Destination(response_message, message->source);
      Set_Message_Source(response_message, message->destination);
      Set_Message_Type(response_message, message->type);

      Queue_Message(&outgoingMessageQueue, response_message);
   }

   return result;
}

void Send_Acknowledgment(char *token, char *messageContent) {

//	// Send the acknowledgment (i.e., "got <message-uuid> <message-content>")
//	sprintf (token, "got %s\n", messageContent);
//
//	// Queue the outgoing acknowledgment message!
//	Message *responseMessage;
//
//	responseMessage = Create_Message (token);
//	Set_Message_Type(responseMessage, "tcp");
//	Set_Message_Source(responseMessage, "192.168.1.6:1002");
//	Set_Message_Destination(responseMessage, "192.168.1.3:1002");
//	Queue_Message(&outgoingMessageQueue, responseMessage);
}

// TODO: Combine this with other Send_Acknowledgment_ functions, and add logic for choosing protocol, socket, device, etc.
void Send_Acknowledgment_UDP(char *token, char *messageContent) {

// Send the acknowledgment (i.e., "got <message-uuid> <message-content>")
   sprintf(token, "got %s\n", messageContent);

// Queue the outgoing acknowledgment message!
   Message *responseMessage;

   responseMessage = Create_Message(token);
   Set_Message_Type(responseMessage, "udp");
   Set_Message_Destination(responseMessage, "10.0.0.255:4445");     // <HACK />
   Queue_Message(&outgoingMessageQueue, responseMessage);

   responseMessage = Create_Message(token);
   Set_Message_Type(responseMessage, "udp");
   Set_Message_Destination(responseMessage, "10.0.0.255:4445");     // <HACK />
   Queue_Message(&outgoingMessageQueue, responseMessage);

   responseMessage = Create_Message(token);
   Set_Message_Type(responseMessage, "udp");
   Set_Message_Destination(responseMessage, "10.0.0.255:4445");     // <HACK />
   Queue_Message(&outgoingMessageQueue, responseMessage);

   responseMessage = Create_Message(token);
   Set_Message_Type(responseMessage, "udp");
   Set_Message_Destination(responseMessage, "10.0.0.255:4445");     // <HACK />
   Queue_Message(&outgoingMessageQueue, responseMessage);
}

static int8_t Receive_Interactive_Assembly_Message(Message * message) {

   int8_t result = FALSE;

   if (Message_Content_Parameter_Equals(message, FIRST_PARAMETER, "interactive_assembly")) {
      result = Process_Interactive_Assembly_Message(message);
   }

   return result;
}
