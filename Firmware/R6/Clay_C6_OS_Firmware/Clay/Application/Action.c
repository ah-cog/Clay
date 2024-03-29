#include "Action.h"
#include "Event.h"
#include "Clock.h"
#include "RGB_LED.h"
#include "GPIO.h"

// TODO: These should be loaded from the section of memory where basic...
// TODO: ...actions are stored.
#define LIGHT_ACTION_UUID   "1470f5c4-eaf1-43fb-8fb3-d96dc4e2bee4"
#define SIGNAL_ACTION_UUID  "bdb49750-9ead-466e-96a0-3aa88e7d246c"
#define MESSAGE_ACTION_UUID "99ff8f6d-a0e7-4b6e-8033-ee3e0dc9a78e"
#define PAUSE_ACTION_UUID   "56d0cf7d-ede6-4529-921c-ae9307d1afbc"
#define SAY_ACTION_UUID     "269f2e19-1fc8-40f5-99b2-6ca67e828e70"

uint32_t action_start_time = 0;
uint32_t action_wait_time = 0;

Event* cache;

static int8_t Perform_Light_Action(char *state);
static int8_t Perform_Signal_Action(char *state);
static int8_t Perform_Pause_Action(char *state);
static int8_t Perform_Message_Action(char *state);
static int8_t Perform_Say_Action(char *state);

uint8_t Initialize_Action_Cache() {
   cache = NULL;
   return true;
}

int8_t Cache_Action(Action *action) {
   int8_t status = false;

   if (action != NULL) {

      Event *previousEvent = NULL;     // The action construct presently at the end of the list. This will be set as the previous action construct to the one created for the newly-cached action.

      // TODO: Consider checking the cache for the existing action. That, or note that doing it manually is required with Has_Cached_Action ().

      // Create a action construct to denote to the action.
      Event *event = Create_Event((*action).uuid, action, NULL);

      if (cache == NULL) {

         // The loop is empty, so add it to the loop as the only element.
         cache = event;

         (*event).previous = NULL;
         (*event).next = NULL;

         status = true;

         // Set the loop pointer to the only action

         //currentAction = action;

      } else {
         // Search for the last element in the queue.
         previousEvent = cache;     // Get the front of the queue.
         while ((*previousEvent).next != NULL) {
            previousEvent = (*previousEvent).next;
         }

         // Update the linked list to add the message to the back of the queue.
         // (*message).previous = NULL; // NOTE: This should already be NULL at this point, so this is redundant, but adds some degree of robustness.
         (*event).previous = previousEvent;
         (*previousEvent).next = event;

         status = true;
      }
   }

   return status;
}

Action* Get_Cached_Action_By_UUID(char *uuid) {

   Event *event = NULL;

   if (cache != NULL) {

      // Search for the action construct associated with the action that has the specified UUID.
      event = cache;     // Get the first action construct in the cache list.
      while (event != NULL) {
         Action *action = (*event).action;
         if (strncmp(uuid, (*action).uuid, strlen((*action).uuid)) == 0) {
            return action;     // Return the action associated with the specified action construct.
         }
         event = (*event).next;
      }
   }

   return NULL;
}

uint8_t Has_Cached_Actions() {
   return (cache != NULL ? true : false);
}

uint8_t Has_Cached_Action_By_UUID(char *uuid) {

   Event *event = NULL;

   if (cache != NULL) {

      // Search for the last element in the queue.
      event = cache;     // Get the front of the queue.
      while (event != NULL) {
         if (strncmp(uuid, (*((*event).action)).uuid, strlen((*((*event).action)).uuid)) == 0) {
            return true;
         }
         event = (*event).next;
      }
   }

   return false;
}

Event* Get_Cached_Action_Construct_By_UUID(char *uuid) {

   Event *event = NULL;

   if (cache != NULL) {

      // Search for the action construct associated with the action that has the specified UUID.
      event = cache;     // Get the first action construct in the cache list.
      while (event != NULL) {
         if (strncmp(uuid, (*event).uuid, strlen((*event).uuid)) == 0) {
            return event;     // Return the action associated with the specified action construct.
         }
         event = (*event).next;
      }
   }

   return NULL;
}

Action* Remove_Action_From_Cache(Action *action) {

   Event *event = NULL;

   // Get the action construct associated with the specified action.
   if (action != NULL && (*action).uuid != NULL) {
      event = Get_Cached_Action_Construct_By_UUID((*action).uuid);
   }

   if (event != NULL && cache != NULL) {

      // Reference the action at the front of the queue.
      // actionConstruct = loop;

      // Update the linked list to remove the action from the front of the queue.
      if ((*event).previous == NULL && (*event).next != NULL) {

         // The action in the first in the loop.

         cache = (*event).next;     // Update the loop's first action to be the next one.

         // TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

         (*cache).next = NULL;     // Update the the new first action in the loop so it doesn't link to a "previous" action.

         // Unlink the action from linked list to finish dequeuing process.
         (*event).previous = NULL;
         (*event).next = NULL;

      } else if ((*event).previous != NULL && (*event).next != NULL) {

         // The action is within the loop. It has previous and next actions.

         (*(*event).previous).next = (*event).next;     // Update the previous action to skip this action and point to the next action.

         (*(*event).next).previous = (*event).previous;     // Update the next action skip this action and point to the previous action.

         // TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

         // Unlink the action from linked list to finish dequeuing process.
         (*event).previous = NULL;
         (*event).next = NULL;

      } else if ((*event).previous != NULL && (*event).next == NULL) {

         // The action is the last in the loop. It has previous actions only.

         (*(*event).previous).next = NULL;     // Update the previous action be the new last action in the loop. That is, make it point to no other action (and point to NULL).

         // TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

         // Unlink the action from linked list to finish dequeuing process.
         (*event).previous = NULL;
         (*event).next = NULL;

      } else {

         // There are no more actions in the loop, so remove all links and reset the loop to its "empty" state.

         cache = NULL;     // Remove the link to any actions at the front of the loop.

         // Is this needed? I don't _think_ so. But test.
//			currentEvent = NULL; // Reset the current action to NULL, so no action will be performed.

         // Unlink the actions from linked list to finish dequeuing process.
         (*event).previous = NULL;
         (*event).next = NULL;

      }

      // Free the action construct from memory.
      // TODO: Consider keeping it in a temporary cache for a short amount of time in case it is being reused. This might not be worth it!
      Delete_Event(event);
   }

   return NULL;
}

//uint8_t Initialize_Action () {
//	timeline = NULL;
//	currentEvent = NULL;
//	return true;
//}

// TODO: Update to automatically scan memory for action structures and create pointers to them.
void Enable_Actions() {

   Action *action = NULL;

   // Light
   action = Create_Action(LIGHT_ACTION_UUID);     // Create the action then cache it
   Set_Action_Script(action, &Perform_Light_Action);
   Cache_Action(action);

   // Signal
   action = Create_Action(SIGNAL_ACTION_UUID);     // Create the action then cache it
   Set_Action_Script(action, &Perform_Signal_Action);
   Cache_Action(action);

   // Message
   action = Create_Action(MESSAGE_ACTION_UUID);     // Create the action then cache it
   Set_Action_Script(action, &Perform_Message_Action);
   Cache_Action(action);

   // Pause
   action = Create_Action(PAUSE_ACTION_UUID);     // Create the action then cache it
   Set_Action_Script(action, &Perform_Pause_Action);
   Cache_Action(action);

   // Say
   action = Create_Action(SAY_ACTION_UUID);     // Create the action then cache it
   Set_Action_Script(action, &Perform_Say_Action);
   Cache_Action(action);
}

Action* Create_Action(char *uuid) {

   // Allocate memory for action construct.
   Action *action = (Action *) malloc(sizeof(Action));

   // Allocate memory for the UUID for this action.
   (*action).uuid = (char *) malloc(strlen(uuid) + 1);     // Add one for '\0' null termination of string
   strncpy((*action).uuid, uuid, strlen(uuid));     // Copy action construct content
   (*action).uuid[strlen(uuid)] = '\0';

   // Initialize script function pointer to NULL
   (*action).script = NULL;

//	// Allocate memory for the content (i.e., the starting symbol to the grammar defining Clay's action).
//	(*action).state = (char *) malloc (strlen (state));
//	strcpy ((*action).state, state); // Copy action construct content

   // TODO: Set up link to the action's loop. This will be NULL for the basic actions provided by the formal grammar defining Clay's physical action.

   return action;
}

//void Set_Action_Script (Action *action, void (*script)()) {
//void Set_Action_Script (Action *action, void (*script) (const Event *)) {
//void Set_Action_Script (Action *action, int8_t (*script) (Event *)) {
void Set_Action_Script(Action *action, int8_t (*script)(char *)) {
   (*action).script = script;
}

int8_t Delete_Action(Action *action) {

   if (action != NULL) {

      // TODO: Remove references (i.e., set to NULL) to the specified action in the loop and cache.

      // Free the message's UUID from memory
      free((*action).uuid);
      (*action).uuid = NULL;

//		// Free the message's content from memory
//		free ((*action).state);
//		(*action).state = NULL;

      // Free the message from memory
      free(action);
      action = NULL;

      // TODO: Look for references to the action in cache and loop.
   }

   return true;
}

int8_t Perform_Action_2(Action *action, char *state) {

   int8_t result = false;

   // Record action start time.
   if (action_start_time == 0) {
      action_start_time = Millis();
   }

   // Call the action script referred to by this event
   result = (*action).script(state);

   return result;
}

static int8_t Perform_Light_Action(char *state) {

//	int8_t status = NULL; // TODO: unused
   int8_t result = NULL;
   char token[32] = { 0 };
//	int tokenInt = 0; // TODO: unused
   int i;

   // e.g., FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF

   // Update the channels
   // TODO: Update the intermediate data structure and only update the actual LEDs when the state changes.
   for (i = 0; i < 12; i++) {
      int hex_color = 0x000000;
      int red = 0;
      int green = 0;
      int blue = 0;

//		status = // TODO: unused
      Get_Token(state, token, 1 + i);

      // Convert hex-encoded color string to separate red, green, and blue color indices.
      hex_color = Hex_String_To_UInt(token);
      red = (hex_color & 0xFF0000) >> 16;
      green = (hex_color & 0x00FF00) >> 8;
      blue = (hex_color & 0x0000FF) >> 0;

//				// Set LED state
      proposed_light_profiles[i].enabled = true;
      Set_Light_Color(&proposed_light_profiles[i], red, green, blue);

   }

   // Apply channel
   // TODO: Move this to a common place, maybe in Application in the loop logic.
   Apply_Channels();
   Apply_Channel_Lights();

   result = true;

   return result;
}

static int8_t Perform_Signal_Action(char *state) {

//	int8_t status = NULL; // TODO: unused
   int8_t result = NULL;
   char token[32] = { 0 };
//	int tokenInt = 0; // TODO: unused
   int i;

   // e.g., TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL

   // Update the channels
   // TODO: Update the intermediate data structure and only update the actual LEDs when the state changes.
   for (i = 0; i < 12; i++) {

//		status = // TODO: unused
      Get_Token(state, token, 1 + i);

//			// Set LED state
//			if (token[0] == 'T') {
//				updateChannelLightProfiles[i].enabled = true;
////					updateChannelLightProfiles[i].color = &onColor;
//				Set_Light_Color (&updateChannelLightProfiles[i], onColor.R, onColor.G, onColor.B);
//			} else {
//				updateChannelLightProfiles[i].enabled = true;
//				Set_Light_Color (&updateChannelLightProfiles[i], offColor.R, offColor.G, offColor.B);
//			}

      // Update the GPIO states
      // TODO: Update the intermediate data structure and only update the actual GPIO when the state changes.
      // TODO: Make 0-indexing (or not) consistent with LEDs
//				Set_Channel ((i + 1), OUTPUT_CHANNEL, NULL);
//				Set_Channel_State ((i + 1), CHANNEL_VALUE_TOGGLE_ON);

      // Enable. Is the channel enabled?
      // TODO: Add an additional state to handle "no change" for channel
      updated_channel_profile[i].enabled = (token[1] == 'T' ? true : false);     // HACK

      // Direction. Set channel direction. Is the channel an input or output?
      if (token[2] == 'I') {
         updated_channel_profile[i].direction = CHANNEL_DIRECTION_INPUT;
      } else if (token[2] == 'O') {
         updated_channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      } else if (token[2] == '-') {
         // NOTE: Don't change!
      }

      // Mode. Set channel mode. Is it a toggle (discrete switch), waveform (continuous analog signal), or pulse (e.g., PWM).
      if (token[3] == 'T') {
         updated_channel_profile[i].mode = CHANNEL_MODE_TOGGLE;     // TODO: Rename this to MODE_TOGGLE
      } else if (token[3] == 'W') {
         updated_channel_profile[i].mode = CHANNEL_MODE_WAVEFORM;
      } else if (token[3] == 'P') {
         updated_channel_profile[i].mode = CHANNEL_MODE_PULSE;
      } else if (token[3] == '-') {
         // NOTE: Don't change!
      }

      // Value. Set channel value. This depends on the direction and mode of the channel.
      if (updated_channel_profile[i].direction == CHANNEL_DIRECTION_OUTPUT) {
         if (updated_channel_profile[i].mode == CHANNEL_MODE_TOGGLE) {
            // Assign the channel's value based on the received data.
            if (token[4] == 'H') {
               updated_channel_profile[i].value = CHANNEL_VALUE_TOGGLE_ON;
            } else if (token[4] == 'L') {
               updated_channel_profile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
            } else {
               // ERROR: Error. An unrecognized toggle value was specified.
            }
         } else if (updated_channel_profile[i].mode == CHANNEL_MODE_WAVEFORM) {
            // TODO: Assign the value differently, depending on the specified channel direction and mode.
            // TODO: Assign this based on the received data.
         } else if (updated_channel_profile[i].mode == CHANNEL_MODE_PULSE) {
            // TODO: Assign the value differently, depending on the specified channel direction and mode.
            // TODO: Assign this based on the received data.
         } else {
            // ERROR: Error. An invalid mode was specified.
         }
      } else if (updated_channel_profile[i].direction == CHANNEL_DIRECTION_INPUT) {
         // NOTE: The channel direction is input, so its value is set by the pin's voltage state.
         if (updated_channel_profile[i].mode == CHANNEL_MODE_TOGGLE) {
            // Assign the channel value based on the physical pin state.
            updated_channel_profile[i].value = Get_Channel_Value(updated_channel_profile[i].number);
//						if (token[4] == 'H') {
//							updated_channel_profile[i].value = CHANNEL_VALUE_TOGGLE_ON;
//						} else if (token[4] == 'L') {
//							updated_channel_profile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
//						} else {
//							// ERROR: Error. An unrecognized toggle value was specified.
//						}
         } else if (updated_channel_profile[i].mode == CHANNEL_MODE_WAVEFORM) {
            // TODO: Assign the value differently, depending on the specified channel direction and mode.
            // TODO: Assign this based on the received data.
         } else if (updated_channel_profile[i].mode == CHANNEL_MODE_PULSE) {
            // TODO: Assign the value differently, depending on the specified channel direction and mode.
            // TODO: Assign this based on the received data.
         } else {
            // ERROR: Error. An invalid mode was specified.
         }
      } else {
         // ERROR: Error. An unrecognized channel direction was specified.
      }
   }

   // Apply channel
   // TODO: Move this to a common place, maybe in Application in the loop logic.
   Apply_Channels();
   Apply_Channel_Lights();

   result = true;

   return result;
}

// e.g., "500 ms"
static int8_t Perform_Pause_Action(char *state) {

//   int8_t status = NULL;
   int8_t result = NULL;
   char token[32] = { 0 };
   int pause_duration_integer = 0;

   // Set the action wait time (i.e., the time after the action before proceeding to the next one)
//   status = // TODO: unused
         Get_Token(state, token, 1);     // TODO: This is redundant. Remove redundancy!
   if (action_wait_time == 0) {
      pause_duration_integer = atoi(token);
      action_wait_time = pause_duration_integer;
   }

   // Check if the action's wait time has expired
   if ((Millis() - action_start_time) > action_wait_time) {
      action_start_time = 0;
      action_wait_time = 0;
      result = true;
   } else {
      result = false;
   }

   return result;
}

static int8_t Perform_Message_Action(char *state) {
   // TODO: Make an action that queues a message.
   return false;
}

static int8_t Perform_Say_Action(char *state) {
   // TODO: Make action that queues a message specifically to generate speech on the app.
   return false;
}
