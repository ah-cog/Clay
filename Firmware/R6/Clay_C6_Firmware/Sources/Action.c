#include "Action.h"
#include "Clock.h"
#include "RGB_LED.h"
#include "GPIO.h"

Event* cache;

Timeline *timeline;

Timeline* Create_Timeline (char *uuid) {

	// Allocate memory for timeline structure.
	Timeline *timeline = (Timeline *) malloc (sizeof (Timeline));

	// Allocate memory for the UUID for this action.
	(*timeline).uuid = (char *) malloc (strlen (uuid));
	strcpy ((*timeline).uuid, uuid); // Copy the action construct's UUID

	// Set event references to null.
	(*timeline).first_event = NULL;
	(*timeline).current_event = NULL;

	return timeline;
}

void Delete_Timeline (Timeline *timeline) {
	if (timeline != NULL) {

		// UUID
		free ((*timeline).uuid);
		(*timeline).uuid = NULL;

		// Timeline
		free (timeline);
		timeline = NULL;
	}
}

uint8_t Reset_Device () {

	// TODO: Reset_Timeline ();

	Initialize_Channels ();
	Apply_Channels ();

	return TRUE;
}

// Remove actions constructs from loop
// Delete actions
// Set loop to null
// Delete actions
// Remove action constructs from cache
// Set cache to null
void Reset_Timeline (Timeline *timeline) {

	Event *event = NULL;
	Action *action = NULL;

	// Remove all action constructs from the loop.
	event = (*timeline).first_event; // Point the action construct to the first element in the the loop.
	while (event != NULL) {

		// Remove the action from the loop.
		// This function:
		// (1) Removes the action construct associated with the specified action from the loop,
		// (2) Updates the linked list of action constructs representing the loop to reflect the removal, and
		// (3) Deletes the action construct from memory.
		action = Remove_Event (timeline, (*event).action);
		// NOTE: The action construct associated with the action is deleted in Remove_Action ((*actionConstruct).action), which calls Delete_Action_Construct (actionConstruct).

		// NOTE: The actual action associated with the action construct is deleted below, when deleting the cache.

		// Continue to the next action.
		event = (*timeline).first_event; // NOTE: This is similar to "actionConstruct = (*actionConstruct).next;" when removing actions.
	}

	// Reset cache
	event = cache;
	while (event != NULL) {

		action = Remove_Action_From_Cache ((*event).action);

		Delete_Action (action);

		event = cache; // NOTE: This is similar to "actionConstruct = (*actionConstruct).next;" when removing actions.

	}
}

Event* Create_Event (char *uuid, Action *action, char *state) {

	// Allocate memory for action construct.
	Event *event = (Event *) malloc (sizeof(Event));

	// Allocate memory for the UUID for this action construct.
	// TODO: (*actionConstruct).uuid = (char *) malloc (strlen (uuid));
	// TODO: strcpy ((*actionConstruct).uuid, uuid); // Copy action construct content

	// Allocate memory for the UUID for this action.
	(*event).uuid = (char *) malloc (strlen (uuid));
	strcpy ((*event).uuid, uuid); // Copy the action construct's UUID

	// Assign the action construct to the specified action (or NULL).
	(*event).action = (Action *) action;

	// Allocate memory for the content (i.e., the starting symbol to the grammar defining Clay's action).
	if (state != NULL) {
		(*event).state = (char *) malloc (strlen (state));
		strcpy ((*event).state, state); // Copy action construct content
	} else {
		(*event).state = NULL;
	}

	// Set up links for queue
	(*event).previous = NULL;
	(*event).next = NULL;

	return event;
}

/**
 * NOTE: This does not free the action itself from memory!
 */
int8_t Delete_Event (Event *event) {

	if (event != NULL) {

		// TODO: Remove references to the message in the queue.

		// Free the action's UUID from memory
		free ((*event).uuid);
		(*event).uuid = NULL;

		// Free the message's content from memory
		free ((*event).state);
		(*event).state = NULL;

		// Free the message from memory
		free (event);
		event = NULL;
	}

	return TRUE;
}

void Set_Event_State (Event *event, char *state) {
	if (state != NULL) {

		// Free previous state
		if ((*event).state != NULL) {
			free ((*event).state);
		}

		// Copy new state
		(*event).state = (char *) malloc (strlen (state));
		strcpy ((*event).state, state); // Copy action construct content
	}
}

uint8_t Initialize_Action_Cache () {
	cache = NULL;
	return TRUE;
}

int8_t Cache_Action (Action *action) {
	int8_t status = FALSE;

	if (action != NULL) {

		Event *previousEvent = NULL; // The action construct presently at the end of the list. This will be set as the previous action construct to the one created for the newly-cached action.

		// TODO: Consider checking the cache for the existing action. That, or note that doing it manually is required with Has_Cached_Action ().

		// Create a action construct to denote to the action.
		Event *event = Create_Event ((*action).uuid, action, NULL);

		if (cache == NULL) {

			// The loop is empty, so add it to the loop as the only element.
			cache = event;

			(*event).previous = NULL;
			(*event).next = NULL;

			status = TRUE;

			// Set the loop pointer to the only action

			//currentAction = action;

		} else {
			// Search for the last element in the queue.
			previousEvent = cache; // Get the front of the queue.
			while ((*previousEvent).next != NULL) {
				previousEvent = (*previousEvent).next;
			}

			// Update the linked list to add the message to the back of the queue.
			// (*message).previous = NULL; // NOTE: This should already be NULL at this point, so this is redundant, but adds some degree of robustness.
			(*event).previous = previousEvent;
			(*previousEvent).next = event;

			status = TRUE;
		}
	}

	return status;
}

Action* Get_Cached_Action_By_UUID (char *uuid) {

	Event *event = NULL;

	if (cache != NULL) {

		// Search for the action construct associated with the action that has the specified UUID.
		event = cache; // Get the first action construct in the cache list.
		while (event != NULL) {
			Action *action = (*event).action;
			if (strncmp (uuid, (*action).uuid, strlen ((*action).uuid)) == 0) {
				return action; // Return the action associated with the specified action construct.
			}
			event = (*event).next;
		}
	}

	return NULL;
}

uint8_t Has_Cached_Actions () {
	return (cache != NULL ? TRUE : FALSE);
}

uint8_t Has_Cached_Action_By_UUID (char *uuid) {

	Event *event = NULL;

	if (cache != NULL) {

		// Search for the last element in the queue.
		event = cache; // Get the front of the queue.
		while (event != NULL) {
			if (strncmp (uuid, (*((*event).action)).uuid, (*((*event).action)).uuid) == 0) {
				return TRUE;
			}
			event = (*event).next;
		}
	}

	return FALSE;
}

Event* Get_Cached_Action_Construct_By_UUID (char *uuid) {

	Event *event = NULL;

	if (cache != NULL) {

		// Search for the action construct associated with the action that has the specified UUID.
		event = cache; // Get the first action construct in the cache list.
		while (event != NULL) {
			if (strncmp (uuid, (*event).uuid, strlen ((*event).uuid)) == 0) {
				return event; // Return the action associated with the specified action construct.
			}
			event = (*event).next;
		}
	}

	return NULL;
}

Action* Remove_Action_From_Cache (Action *action) {

	Event *event = NULL;

	// Get the action construct associated with the specified action.
	if (action != NULL && (*action).uuid != NULL) {
		event = Get_Cached_Action_Construct_By_UUID ((*action).uuid);
	}

	if (event != NULL && cache != NULL) {

		// Reference the action at the front of the queue.
		// actionConstruct = loop;

		// Update the linked list to remove the action from the front of the queue.
		if ((*event).previous == NULL && (*event).next != NULL) {

			// The action in the first in the loop.

			cache = (*event).next; // Update the loop's first action to be the next one.

			// TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

			(*cache).next = NULL; // Update the the new first action in the loop so it doesn't link to a "previous" action.

			// Unlink the action from linked list to finish dequeuing process.
			(*event).previous = NULL;
			(*event).next = NULL;

		} else if ((*event).previous != NULL && (*event).next != NULL) {

			// The action is within the loop. It has previous and next actions.

			(*(*event).previous).next = (*event).next; // Update the previous action to skip this action and point to the next action.

			(*(*event).next).previous = (*event).previous; // Update the next action skip this action and point to the previous action.

			// TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

			// Unlink the action from linked list to finish dequeuing process.
			(*event).previous = NULL;
			(*event).next = NULL;

		} else if ((*event).previous != NULL && (*event).next == NULL) {

			// The action is the last in the loop. It has previous actions only.

			(*(*event).previous).next = NULL; // Update the previous action be the new last action in the loop. That is, make it point to no other action (and point to NULL).

			// TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

			// Unlink the action from linked list to finish dequeuing process.
			(*event).previous = NULL;
			(*event).next = NULL;

		} else {

			// There are no more actions in the loop, so remove all links and reset the loop to its "empty" state.

			cache = NULL; // Remove the link to any actions at the front of the loop.

			// Is this needed? I don't _think_ so. But test.
//			currentEvent = NULL; // Reset the current action to NULL, so no action will be performed.

			// Unlink the actions from linked list to finish dequeuing process.
			(*event).previous = NULL;
			(*event).next = NULL;

		}

		// Free the action construct from memory.
		// TODO: Consider keeping it in a temporary cache for a short amount of time in case it is being reused. This might not be worth it!
		Delete_Event (event);
	}

	return NULL;
}

//uint8_t Initialize_Action () {
//	timeline = NULL;
//	currentEvent = NULL;
//	return TRUE;
//}

Action* Create_Action (char *uuid) {

	// Allocate memory for action construct.
	Action *action = (Action *) malloc (sizeof(Action));

	// Allocate memory for the UUID for this action.
	(*action).uuid = (char *) malloc (strlen (uuid));
	strcpy ((*action).uuid, uuid); // Copy action construct content

//	// Allocate memory for the content (i.e., the starting symbol to the grammar defining Clay's action).
//	(*action).state = (char *) malloc (strlen (state));
//	strcpy ((*action).state, state); // Copy action construct content

	// TODO: Set up link to the action's loop. This will be NULL for the basic actions provided by the formal grammar defining Clay's physical action.

	return action;
}

int8_t Delete_Action (Action *action) {

	if (action != NULL) {

		// TODO: Remove references (i.e., set to NULL) to the specified action in the loop and cache.

		// Free the message's UUID from memory
		free ((*action).uuid);
		(*action).uuid = NULL;

//		// Free the message's content from memory
//		free ((*action).state);
//		(*action).state = NULL;

		// Free the message from memory
		free (action);
		action = NULL;

		// TODO: Look for references to the action in cache and loop.
	}

	return TRUE;
}

int16_t Add_Event (Timeline *timeline, Event *event) {
	// TODO: Consider changing to "int16_t Add_Action (char *actionUuid)" and search for the action in the local cache and universal repository.

	Event *previous_event = NULL; // The action construct presently at the end of the list. This will be set as the previous action construct to the one created for the newly-cached action.
	uint16_t event_count = 0;

	// Create a action construct to denote to the action for the loop!
	// NOTE: This construct must be different than the construct for the action cache to preserve their unique link structures and prevent infinite looping during list traversal.
//	Event *event = Create_Event ((*action).uuid, action);

	// TODO: Consider checking of the action has a action construct in the cache. If so reference that one. If not, create one. That, or note that doing it manually is required with Has_Cached_Action () _before_ calling Add_Action.

	if ((*timeline).first_event == NULL) {

		// The loop is empty, so add it to the loop as the only element.
		(*timeline).first_event = event;

		(*event).previous = NULL;
		(*event).next = NULL;

		event_count = 1;

		// Set the loop pointer to the only action

		(*timeline).current_event = event;

	} else {

		// Search for the last element in the loop (represented as a list).
		previous_event = (*timeline).first_event; // Get the front of the queue.
		event_count++;
		while ((*previous_event).next != NULL) {
			previous_event = (*previous_event).next;
			event_count++;
		}

		// Update the linked list to add the message to the back of the queue.
		// (*actionConstruct).previous = NULL; // NOTE: This should already be NULL at this point, so this is redundant, but adds some degree of robustness.
		(*event).previous = previous_event;
		(*previous_event).next = event;
		event_count++;

	}

	return event_count;
}

int16_t Insert_Event (Timeline *timeline, Event *event, uint16_t index) {

	Event *previous_event = NULL; // The action construct presently at the end of the list. This will be set as the previous action construct to the one created for the newly-cached action.
	uint16_t previous_event_index = 0;

	// Create a action construct to denote to the action for the loop!
	// NOTE: This construct must be different than the construct for the action cache to preserve their unique link structures and prevent infinite looping during list traversal.
//	Event *event = Create_Event ((*action).uuid, action);

	// TODO: Consider checking of the action has a action construct in the cache. If so reference that one. If not, create one. That, or note that doing it manually is required with Has_Cached_Action () _before_ calling Add_Action.

	if ((*timeline).first_event == NULL) {

		// Check if attempting to insert anywhere except index 0
		if (index != 0) {
			return -1;
		}

		// The loop is empty, so add it to the loop as the only element.
		(*timeline).first_event = event;

		(*event).previous = NULL;
		(*event).next = NULL;

		previous_event_index = 1;

		// Set the loop pointer to the only action

		(*timeline).current_event = event;

	} else {

		previous_event_index = 0;

		// Search for the last element in the loop (represented as a list).
		previous_event = (*timeline).first_event; // Get the front of the queue.
		while ((*previous_event).next != NULL) {
			if (previous_event_index == (index - 1)) {
				break;
			}
			previous_event = (*previous_event).next;
			previous_event_index++;
		}

		// Check if an event prior to the specified index position was found,
		// and if so, add the new event to the timeline.
		if (previous_event_index == (index - 1)) {
			// Update the linked list to add the message to the back of the queue.
			// (*actionConstruct).previous = NULL; // NOTE: This should already be NULL at this point, so this is redundant, but adds some degree of robustness.
			(*event).previous = previous_event;
			(*previous_event).next = event;
			previous_event_index++;
		}

	}

	return previous_event_index;
}

int16_t Add_Before_Event (Timeline *timeline, Event *event, Event *other_event) {
	// TODO: Consider changing to "int16_t Add_Action (char *actionUuid)" and search for the action in the local cache and universal repository.

	Event *next_event = NULL; // The action construct presently at the end of the list. This will be set as the previous action construct to the one created for the newly-cached action.
	uint16_t event_count = 0;

	// Create a action construct to denote to the action for the loop!
	// NOTE: This construct must be different than the construct for the action cache to preserve their unique link structures and prevent infinite looping during list traversal.
//	Event *event = Create_Event ((*action).uuid, action);

	// TODO: Consider checking of the action has a action construct in the cache. If so reference that one. If not, create one. That, or note that doing it manually is required with Has_Cached_Action () _before_ calling Add_Action.

	if ((*timeline).first_event == NULL) {

		// The loop is empty, so add it to the loop as the only element.
		(*timeline).first_event = event;

		(*event).previous = NULL;
		(*event).next = NULL;

		event_count = 1;

		// Set the loop pointer to the only action
		(*timeline).current_event = event;

	} else {

		// Search for the last element in the loop (represented as a list).
		next_event = (*timeline).first_event; // Get the front of the queue.
		event_count++;
		while (strncmp ((*next_event).uuid, (*other_event).uuid,
				strlen ((*other_event).uuid) != 0)) {
			//while ((*nextActionConstruct).next != otherAction) {
			next_event = (*next_event).next;
			event_count++;
		}

		// Update the linked list to add the message to the back of the queue.
		// (*actionConstruct).previous = NULL; // NOTE: This should already be NULL at this point, so this is redundant, but adds some degree of robustness.

		// Link the new action into the loop.
		(*event).previous = (*next_event).previous;
		(*event).next = next_event;

		// Update the previous action (if it's not NULL)
		if ((*event).previous != NULL) {
			(*(*event).previous).next = event;
		}

		// Update the next action
		(*next_event).previous = event;

		// Update the loop's current action.
		if ((*event).previous == NULL) {
			(*timeline).first_event = event; // Update the added action's links to the be the first in the loop.
		}

		event_count++;

	}

	return event_count;
}

Action* Remove_Event (Timeline *timeline, Event *event) {

//	Event *event = NULL;
//
//	// Get the action construct associated with the specified action.
//	if (event_to_remove != NULL && (*event_to_remove).uuid != NULL) {
//		event = Get_Event_By_UUID (timeline, (*event_to_remove).uuid);
//	}

	if (event != NULL && timeline != NULL) {

		// Reference the action at the front of the queue.
		// actionConstruct = loop;

		// Update the linked list to remove the action from the front of the queue.
		if ((*event).previous == NULL && (*event).next != NULL) {

			// The action in the first in the loop.

			(*timeline).first_event = (*event).next; // Update the loop's first action to be the next one.

			// TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

			(*((*timeline).first_event)).next = NULL; // Update the the new first action in the loop so it doesn't link to a "previous" action.

			// Unlink the action from linked list to finish dequeuing process.
			(*event).previous = NULL;
			(*event).next = NULL;

		} else if ((*event).previous != NULL && (*event).next != NULL) {

			// The action is within the loop. It has previous and next actions.

			(*(*event).previous).next = (*event).next; // Update the previous action to skip this action and point to the next action.

			(*(*event).next).previous = (*event).previous; // Update the next action skip this action and point to the previous action.

			// TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

			// Unlink the action from linked list to finish dequeuing process.
			(*event).previous = NULL;
			(*event).next = NULL;

		} else if ((*event).previous != NULL && (*event).next == NULL) {

			// The action is the last in the loop. It has previous actions only.

			(*(*event).previous).next = NULL; // Update the previous action be the new last action in the loop. That is, make it point to no other action (and point to NULL).

			// TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

			// Unlink the action from linked list to finish dequeuing process.
			(*event).previous = NULL;
			(*event).next = NULL;

		} else {

			// There are no more actions in the loop, so remove all links and reset the loop to its "empty" state.

			timeline = NULL; // Remove the link to any actions at the front of the loop.

			(*timeline).current_event = NULL; // Reset the current action to NULL, so no action will be performed.

			// Unlink the actions from linked list to finish dequeuing process.
			(*event).previous = NULL;
			(*event).next = NULL;

		}

		// Free the action construct from memory.
		// TODO: Consider keeping it in a temporary cache for a short amount of time in case it is being reused. This might not be worth it!
		Delete_Event (event);
	}

	return NULL;
}

uint8_t Has_Events (Timeline *timeline) {
	return ((*timeline).current_event != NULL ? TRUE : FALSE);
}

uint8_t Has_Event_By_UUID (Timeline *timeline, char *uuid) {

	Event *event = NULL;

	if ((*timeline).first_event != NULL) {

		// Search for the last element in the queue.
		event = (*timeline).first_event; // Get the front of the queue.
		while (event != NULL) {
			if (strncmp (uuid, (*event).uuid, strlen ((*event).uuid)) == 0) {
				return TRUE;
			}
			event = (*event).next;
		}
	}

	return FALSE;
}

Event* Get_Event_By_UUID (Timeline *timeline, char *uuid) {

	Event *event = NULL;

	if ((*timeline).first_event != NULL) {

		// Search for the action construct associated with the action that has the specified UUID.
		event = (*timeline).first_event; // Get the first action construct in the cache list.
		while (event != NULL) {
			if (strncmp (uuid, (*event).uuid, strlen ((*event).uuid)) == 0) {
				return event; // Return the action associated with the specified action construct.
			}
			event = (*event).next;
		}
	}

	return NULL;
}

uint32_t actionStartTime = 0;
uint32_t actionWaitTime = 0;

/**
 * Performs the physical action for the specified action as it is defined
 * by the formal grammar that defines the capabilities of Clay.
 * 
 * Presently, the grammar is implemented as a series of conditional statements.
 */
int8_t Perform_Action (Event *event) {

	int8_t status = NULL;
	int8_t result = NULL;
	char token[32] = { 0 };
	int tokenInt = 0;
	int i;

	Action *action = (*event).action;

	char *actionContent = NULL;
	actionContent = (*event).state;

	if (action == NULL || actionContent == NULL) {
		return TRUE;
	}

	if (actionStartTime == 0) {
		actionStartTime = Millis ();
	}

	// TODO: Queue the message rather than executing it immediately (unless specified)
	// TODO: Parse the message rather than brute force like this.
	// TODO: Decompose the action into atomic actions and perform them!

	// turn light 1 on
	// ^
	if ((status = Get_Token (actionContent, token, 0)) != NULL) {

		if (strncmp (token, "cause", strlen ("cause")) == 0) {

			// cause 1 effect 4
			// ^
			// TODO: Something like: cause TTOT TTOT effect TTOT TTOT TTOT TTOT TTOT TTOT TTOT TTOT TTOT TTOT

			// Update the channels
			// TODO: Update the intermediate data structure and only update the actual LEDs when the state changes.
//			status = getToken (actionContent, token, 1); // Cause
//			status = getToken (actionContent, token, 2); // Effect
			// TODO: Consider updating the cause conditions?: Update_Channel_State ()
			status = Get_Token (actionContent, token, 1); // Cause
			tokenInt = atoi (token) - 1;

			// TODO: Consider NOT automatically changing the I/O state of the cause. Maybe rely on setting the pin mode first!
			// TODO: Update all the input states and then update all the output states.

			updateChannelProfile[tokenInt].enabled = CHANNEL_ENABLED;
			updateChannelProfile[tokenInt].direction = CHANNEL_DIRECTION_INPUT;
			updateChannelProfile[tokenInt].mode = CHANNEL_MODE_TOGGLE;
			updateChannelProfile[tokenInt].value = Get_Channel_Value (updateChannelProfile[tokenInt].number);

//			if (strncmp (token, "switch", strlen ("switch")) == 0) { 
			if (updateChannelProfile[tokenInt].value == CHANNEL_VALUE_TOGGLE_ON) {

				// TODO: Look for "effect"

				status = Get_Token (actionContent, token, 3); // Effect
				tokenInt = atoi (token) - 1;
				updateChannelProfile[tokenInt].enabled = CHANNEL_ENABLED;
				updateChannelProfile[tokenInt].direction = CHANNEL_DIRECTION_OUTPUT;
				updateChannelProfile[tokenInt].mode = CHANNEL_MODE_TOGGLE;
				updateChannelProfile[tokenInt].value = CHANNEL_VALUE_TOGGLE_ON;

			} else if (updateChannelProfile[tokenInt].value
					== CHANNEL_VALUE_TOGGLE_OFF) {

				// TODO: Look for "effect"

				status = Get_Token (actionContent, token, 3); // Effect
				tokenInt = atoi (token) - 1;
				updateChannelProfile[tokenInt].enabled = CHANNEL_ENABLED;
				updateChannelProfile[tokenInt].direction = CHANNEL_DIRECTION_OUTPUT;
				updateChannelProfile[tokenInt].mode = CHANNEL_MODE_TOGGLE;
				updateChannelProfile[tokenInt].value = CHANNEL_VALUE_TOGGLE_OFF;

			}
			// TODO: Get the (cause, effect) condition.

			// TODO: Create (cause, effect) action.

			// Apply channel
			// TODO: Move this to a common place, maybe in Application in the loop logic.
//			if (effect is local) { // TODO: Get UUID of cause and effect units.
			Apply_Channels ();
//			} else if (effect is remote) {
//				Request_Remote_Apply_Channels ();
//			}

			result = TRUE;

		} else if (strncmp (token, "light", strlen ("light")) == 0) {

			// light FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF FFFFFF
			// ^

			//	char *hexString = "FFEEDD";
			//	int hexInt = HexStringToUInt (hexString);
			//	int red   = (hexInt & 0xFF0000) >> 16;
			//	int green = (hexInt & 0x00FF00) >> 8;
			//	int blue  = (hexInt & 0x0000FF) >> 0;

			// Update the channels
			// TODO: Update the intermediate data structure and only update the actual LEDs when the state changes.
			for (i = 0; i < 12; i++) {
				int hex_color = 0x000000;
				int red = 0;
				int green = 0;
				int blue = 0;

				status = Get_Token (actionContent, token, 1 + i);

				hex_color = HexStringToUInt (token);
				red   = (hex_color & 0xFF0000) >> 16;
				green = (hex_color & 0x00FF00) >> 8;
				blue  = (hex_color & 0x0000FF) >> 0;

//				// Set LED state
//				if (token[0] == 'T') {
					updateChannelLightProfiles[i].enabled = TRUE;
//					updateChannelLightProfiles[i].color = &onColor;

					Set_Light_Color (&updateChannelLightProfiles[i], red, green, blue);
//					updateChannelLightProfiles[i].color.R = red;
//					updateChannelLightProfiles[i].color.G = green;
//					updateChannelLightProfiles[i].color.B = blue;
//				} else {
//					updateChannelLightProfiles[i].enabled = TRUE;
//					updateChannelLightProfiles[i].color = &offColor;
//				}

			}

			// Apply channel
			// TODO: Move this to a common place, maybe in Application in the loop logic.
			Apply_Channels ();
			Apply_Channel_Lights ();

			result = TRUE;

		} else if (strncmp (token, "apply", strlen ("apply")) == 0) {

			// apply TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL TTOTL
			// ^

			// Update the channels
			// TODO: Update the intermediate data structure and only update the actual LEDs when the state changes.
			for (i = 0; i < 12; i++) {
				status = Get_Token (actionContent, token, 1 + i);

				// Set LED state
				if (token[0] == 'T') {
					updateChannelLightProfiles[i].enabled = TRUE;
//					updateChannelLightProfiles[i].color = &onColor;
					Set_Light_Color (&updateChannelLightProfiles[i], onColor.R, onColor.G, onColor.B);
				} else {
					updateChannelLightProfiles[i].enabled = TRUE;
					Set_Light_Color (&updateChannelLightProfiles[i], offColor.R, offColor.G, offColor.B);
				}

				// Update the GPIO states
				// TODO: Update the intermediate data structure and only update the actual GPIO when the state changes.
				// TODO: Make 0-indexing (or not) consistent with LEDs
//				Set_Channel ((i + 1), OUTPUT_CHANNEL, NULL);
//				Set_Channel_State ((i + 1), CHANNEL_VALUE_TOGGLE_ON);

				// Enable. Is the channel enabled?
				// TODO: Add an additional state to handle "no change" for channel
				updateChannelProfile[i].enabled = (token[1] == 'T' ? TRUE : FALSE); // HACK

				// Direction. Set channel direction. Is the channel an input or output?
				if (token[2] == 'I') {
					updateChannelProfile[i].direction = CHANNEL_DIRECTION_INPUT;
				} else if (token[2] == 'O') {
					updateChannelProfile[i].direction =
					CHANNEL_DIRECTION_OUTPUT;
				} else if (token[2] == '-') {
					// NOTE: Don't change!
				}

				// Mode. Set channel mode. Is it a toggle (discrete switch), waveform (continuous analog signal), or pulse (e.g., PWM).
				if (token[3] == 'T') {
					updateChannelProfile[i].mode = CHANNEL_MODE_TOGGLE; // TODO: Rename this to MODE_TOGGLE
				} else if (token[3] == 'W') {
					updateChannelProfile[i].mode = CHANNEL_MODE_WAVEFORM;
				} else if (token[3] == 'P') {
					updateChannelProfile[i].mode = CHANNEL_MODE_PULSE;
				} else if (token[3] == '-') {
					// NOTE: Don't change!
				}

				// Value. Set channel value. This depends on the direction and mode of the channel.
				if (updateChannelProfile[i].direction
						== CHANNEL_DIRECTION_OUTPUT) {
					if (updateChannelProfile[i].mode == CHANNEL_MODE_TOGGLE) {
						// Assign the channel's value based on the received data.
						if (token[4] == 'H') {
							updateChannelProfile[i].value =
							CHANNEL_VALUE_TOGGLE_ON;
						} else if (token[4] == 'L') {
							updateChannelProfile[i].value =
							CHANNEL_VALUE_TOGGLE_OFF;
						} else {
							// ERROR: Error. An unrecognized toggle value was specified.
						}
					} else if (updateChannelProfile[i].mode
							== CHANNEL_MODE_WAVEFORM) {
						// TODO: Assign the value differently, depending on the specified channel direction and mode.
						// TODO: Assign this based on the received data.
					} else if (updateChannelProfile[i].mode
							== CHANNEL_MODE_PULSE) {
						// TODO: Assign the value differently, depending on the specified channel direction and mode.
						// TODO: Assign this based on the received data.
					} else {
						// ERROR: Error. An invalid mode was specified.
					}
				} else if (updateChannelProfile[i].direction
						== CHANNEL_DIRECTION_INPUT) {
					// NOTE: The channel direction is input, so its value is set by the pin's voltage state.
					if (updateChannelProfile[i].mode == CHANNEL_MODE_TOGGLE) {
						// Assign the channel value based on the physical pin state.
						updateChannelProfile[i].value = Get_Channel_Value (
								updateChannelProfile[i].number);

//						if (token[4] == 'H') {
//							updateChannelProfile[i].value = CHANNEL_VALUE_TOGGLE_ON;
//						} else if (token[4] == 'L') {
//							updateChannelProfile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
//						} else {
//							// ERROR: Error. An unrecognized toggle value was specified.
//						}
					} else if (updateChannelProfile[i].mode
							== CHANNEL_MODE_WAVEFORM) {
						// TODO: Assign the value differently, depending on the specified channel direction and mode.
						// TODO: Assign this based on the received data.
					} else if (updateChannelProfile[i].mode
							== CHANNEL_MODE_PULSE) {
						// TODO: Assign the value differently, depending on the specified channel direction and mode.
						// TODO: Assign this based on the received data.
					} else {
						// ERROR: Error. An invalid mode was specified.
					}
				} else {
					// ERROR: Error. An unrecognized channel direction was specified.
				}
				// TODO: Apply individual channel here! Only the changed ones!

//				// Set GPIO state
//				// TODO: Add an additional state to handle "no change" for channel
//				if (token[1] == 'T') {
//					Enable_Channel ((i + 1), TRUE);
//				} else {
//					Enable_Channel ((i + 1), FALSE);
//				}
//
//				// Set channel direction. Is the channel an input or output?
//				if (token[2] == 'O') {
//					Set_Channel ((i + 1), OUTPUT_CHANNEL, NULL);
//				} else if (token[2] == 'I') {
//					Set_Channel ((i + 1), OUTPUT_CHANNEL, NULL);
//				}

//				if (tokenInt == 1) {
//					Set_LED_Output ((RGB_LED) (i + 1),  &onColor);
//				} else {
//					Set_LED_Output ((RGB_LED) (i + 1),  &offColor);
//				}
			}

			// Apply channel
			// TODO: Move this to a common place, maybe in Application in the loop logic.
			Apply_Channels ();
			Apply_Channel_Lights ();

			result = TRUE;

		} else if (strncmp (token, "change", strlen ("change")) == 0) {

			// change lights to 1 0 1 1 0 1 0 1 0 0 1 1
			// ^

			if ((status = Get_Token (actionContent, token, 1)) != NULL) {

				// change lights to 1 0 1 1 0 1 0 1 0 0 1 1
				//        ^
				if (strncmp (token, "channel", strlen ("channel")) == 0) {

					if ((status = Get_Token (actionContent, token, 2)) != NULL) { // TODO: Remove this! The parameter is used later.

						// change channel to 1 0 1 1 0 1 0 1 0 0 1 1 1 0 1 1 0 1 0 1 0 0 1 1
						//                   ^                       ^

						/*
						 // Update the LED states
						 // TODO: Update the intermediate data structure and only update the actual LEDs when the state changes.
						 for (i = 0; i < 12; i++) {
						 status = getToken (actionContent, token, 3 + i);
						 tokenInt = atoi (token);
						 if (tokenInt == 1) {
						 Set_LED_Output ((RGB_LED) (i + 1),  &onColor);
						 } else {
						 Set_LED_Output ((RGB_LED) (i + 1),  &offColor);
						 }
						 }

						 // Update the GPIO states
						 // TODO: Update the intermediate data structure and only update the actual GPIO when the state changes.
						 for (i = 0; i < 12; i++) {
						 status = getToken (actionContent, token, 3 + 12 + i);
						 tokenInt = atoi (token);
						 if (tokenInt == 1) {
						 // TODO: Make 0-indexing (or not) consident with LEDs
						 //								Set_Channel ((i + 1), OUTPUT_CHANNEL, NULL);
						 //								Set_Channel_State ((i + 1), CHANNEL_VALUE_TOGGLE_ON);
						 // Update channel
						 updateChannelProfile[i].enabled = TRUE; // HACK
						 updateChannelProfile[i].direction = OUTPUT_CHANNEL;
						 updateChannelProfile[i].mode = MODE_DIGITAL;
						 updateChannelProfile[i].value = CHANNEL_VALUE_TOGGLE_ON;
						 // TODO: Apply individual channel here! Only the changed ones!
						 } else {
						 // TODO: Make 0-indexing (or not) consident with LEDs
						 //								Set_Channel ((i + 1), OUTPUT_CHANNEL, NULL);
						 //								Set_Channel_State ((i + 1), CHANNEL_VALUE_TOGGLE_OFF);
						 // Update channel
						 updateChannelProfile[i].enabled = TRUE; // HACK
						 updateChannelProfile[i].direction = OUTPUT_CHANNEL;
						 updateChannelProfile[i].mode = MODE_DIGITAL;
						 updateChannelProfile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
						 // TODO: Apply individual channel here! Only the changed ones!
						 }
						 }
						 // Apply channel
						 Apply_Channels ();

						 // Update the wait
						 // TODO: Add this as a separate action!
						 status = getToken (actionContent, token, 3 + 24);
						 tokenInt = atoi (token);
						 //						Wait (tokenInt);

						 result = TRUE;

						 //						if (strncmp (token, "on", strlen ("on")) == 0) {
						 //
						 //							// Turn all LEDs on
						 //							for (i = 0; i < 12; i++) {
						 //								Set_Channel_State (i, CHANNEL_VALUE_TOGGLE_ON);
						 //							}
						 //
						 //							result = TRUE;
						 //
						 //						} else if (strncmp (token, "off", strlen ("off")) == 0) {
						 //
						 //							// Turn all LEDs off
						 //							for (i = 0; i < 12; i++) {
						 //								Set_Channel_State (i, CHANNEL_VALUE_TOGGLE_OFF);
						 //							}
						 //
						 //							result = TRUE;
						 //
						 //						}
						 */
					}

				}

			}

		} else if (strncmp (token, "turn", strlen ("turn")) == 0) {

			if ((status = Get_Token (actionContent, token, 1)) != NULL) {

				// turn lights on
				//      ^
				if (strncmp (token, "lights", strlen ("lights")) == 0) {

					if ((status = Get_Token (actionContent, token, 2)) != NULL) { // TODO: Remove this! The parameter is used later.

						// turn lights on
						//             ^
						if (strncmp (token, "on", strlen ("on")) == 0) {

							// Turn all LEDs on
							for (i = 0; i < 12; i++) {
								Set_Channel_Value (i, CHANNEL_VALUE_TOGGLE_ON);
							}

							result = TRUE;

						} else if (strncmp (token, "off", strlen ("off"))
								== 0) {

							// Turn all LEDs off
							for (i = 0; i < 12; i++) {
								Set_Channel_Value (i, CHANNEL_VALUE_TOGGLE_OFF);
							}

							result = TRUE;

						}
					}

				} else if (strncmp (token, "light", strlen ("light")) == 0) {

					// turn light 1 on
					//      ^

					if ((status = Get_Token (actionContent, token, 2)) != NULL) { // TODO: Remove this! The parameter is used later.

						if ((status = Get_Token (actionContent, token, 3))
								!= NULL) {

							// turn light 1 on
							//              ^
							if (strncmp (token, "on", strlen ("on")) == 0) {

								// Turn the specified LED off
								status = Get_Token (actionContent, token, 2);
								tokenInt = atoi (token);
								onColor.B = 200;
								onColor.G = 50;
								RGB_LED_SetColor ((RGB_LED) tokenInt, &onColor);

								result = TRUE;

							} else if (strncmp (token, "off", strlen ("off"))
									== 0) {

								// Turn the specified LED off
								status = Get_Token (actionContent, token, 2);
								tokenInt = atoi (token);
								RGB_LED_SetColor ((RGB_LED) tokenInt, &offColor);

								result = TRUE;

							}
						}
					}

					// turn channel 1 on
					//      ^
				} else if (strncmp (token, "channel", strlen ("channel"))
						== 0) {

					if ((status = Get_Token (actionContent, token, 2)) != NULL) { // TODO: Remove this! The parameter is used later.

						// turn channel 1 on
						//              ^

						if ((status = Get_Token (actionContent, token, 3))
								!= NULL) {

							// turn channel 1 on
							//                ^
							if (strncmp (token, "on", strlen ("on")) == 0) {

								// Turn the specified LED off
								status = Get_Token (actionContent, token, 2);
								tokenInt = atoi (token);
								Set_Channel_Value (tokenInt,
								CHANNEL_VALUE_TOGGLE_ON);

								result = TRUE;

							} else if (strncmp (token, "off", strlen ("off"))
									== 0) {

								// Turn the specified LED off
								status = Get_Token (actionContent, token, 2);
								tokenInt = atoi (token);
								Set_Channel_Value (tokenInt,
								CHANNEL_VALUE_TOGGLE_OFF);

								result = TRUE;

							}
						}
					}

				}

			}

		} else if (strncmp (token, "wait", strlen ("wait")) == 0) {

			if ((status = Get_Token (actionContent, token, 1)) != NULL) {

				// wait 500 ms
				//      ^

				// Set the action wait time (i.e., the time after the action before proceeding to the next one)
				status = Get_Token (actionContent, token, 1); // TODO: This is redundant. Remove redundancy!
				tokenInt = atoi (token);
				if (actionWaitTime == 0) {
					actionWaitTime = tokenInt;
				}

				// Check if the action's wait time has expired
				if ((Millis () - actionStartTime) > actionWaitTime) {
					actionStartTime = 0;
					actionWaitTime = 0;
					result = TRUE;
				} else {
					result = FALSE;
				}

			}

		} else if (strncmp (token, "say", strlen ("say")) == 0) {

			if ((status = Get_Token (actionContent, token, 1)) != NULL) {

				// wait 500 ms
				//      ^

				// Set the action wait time (i.e., the time after the action before proceeding to the next one)
				status = Get_Token (actionContent, token, 1);

				// TODO: Create string "say token"

				// TODO: Add parameter for "say" to specify maximum frequency of phrase
				// TODO: Add parameters for alternative phrases
				//Broadcast_UDP_Message ("say i should say something");
//				Broadcast_UDP_Message(actionContent, 4445);
				// TODO: Queue_Outgoing_Message()

				result = TRUE;

			}

			// TODO: Add commands that render a graphical finger using Clay on your behalf, in response to commands, as if the computer is doing it! The computer can also point things out to you! It mirrors your action? Or shows up as "slip" under a action?
			// TODO: "touch at <x,y>"
			// TOOD: "drag to <x,y>"

		} else {

			result = TRUE;

		}

	} else {

		result = TRUE;
	}

	return result;
}
