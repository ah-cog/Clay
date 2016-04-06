#include "Event.h"

uint8_t Reset_Device () {

	// TODO: Reset_Timeline ();

	Initialize_Channels ();
	Apply_Channels ();

	return TRUE;
}

Event* Create_Event (char *uuid, Action *action, char *state) {

	// Allocate memory for action construct.
	Event *event = (Event *) malloc (sizeof(Event));

	// Allocate memory for the UUID for this action construct.
	// TODO: (*actionConstruct).uuid = (char *) malloc (strlen (uuid));
	// TODO: strcpy ((*actionConstruct).uuid, uuid); // Copy action construct content

	// Allocate memory for the UUID for this action.
	(*event).uuid = (char *) malloc (strlen (uuid) + 1);
	strncpy ((*event).uuid, uuid, strlen (uuid)); // Copy the action construct's UUID
	(*event).uuid[strlen (uuid)] = NULL;

	// Assign the action construct to the specified action (or NULL).
	(*event).action = (Action *) action;

	// Allocate memory for the content (i.e., the starting symbol to the grammar defining Clay's action).
	if (state != NULL) {
		(*event).state = (char *) malloc (strlen (state) + 1);
		strncpy ((*event).state, state, strlen (state)); // Copy action construct content
		(*event).state[strlen (state)] = NULL;
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
		(*event).state = (char *) malloc (strlen (state) + 1);
		strncpy ((*event).state, state, strlen (state)); // Copy action construct content
		(*event).state[strlen (state)] = '\0';
	}
}

/**
 * Performs the physical action for the specified action as it is defined
 * by the formal grammar that defines the capabilities of Clay.
 *
 * Presently, the grammar is implemented as a series of conditional statements.
 */
int8_t Process_Event (Event *event) {

	int8_t result = NULL;

	// Check if event's action or state are not yet assigned.
	if ((*event).action == NULL || (*event).state == NULL) {
		return TRUE;
	}

	// TODO: Queue the message rather than executing it immediately (unless specified)
	// TODO: Parse the message rather than brute force like this.
	// TODO: Decompose the action into atomic actions and perform them!

	// TODO: Check event condition, and only call script if it is met.

	result = Perform_Action ((*event).action, (*event).state);

	return result;
}


