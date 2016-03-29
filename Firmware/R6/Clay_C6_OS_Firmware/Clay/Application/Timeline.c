#include "Timeline.h"

Timeline *timeline;

Timeline* Create_Timeline (char *uuid) {

	// Allocate memory for timeline structure.
	Timeline *timeline = (Timeline *) malloc (sizeof (Timeline));

	// Allocate memory for the UUID for this action.
	(*timeline).uuid = (char *) malloc (strlen (uuid) + 1);
	strcpy ((*timeline).uuid, uuid); // Copy the action construct's UUID
	(*timeline).uuid[(strlen (uuid))] = '\0';


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
		action = Remove_Event (timeline, (Event *)(*event).action);
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
	return ((*timeline).current_event != NULL ? true : false);
}

uint8_t Has_Event_By_UUID (Timeline *timeline, char *uuid) {

	Event *event = NULL;

	if ((*timeline).first_event != NULL) {

		// Search for the last element in the queue.
		event = (*timeline).first_event; // Get the front of the queue.
		while (event != NULL) {
			if (strncmp (uuid, (*event).uuid, strlen ((*event).uuid)) == 0) {
				return true;
			}
			event = (*event).next;
		}
	}

	return false;
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


