#include "Trigger.h"

Trigger* Create_Trigger () {

	// Allocate memory for action construct.
	Trigger *trigger = (Trigger *) malloc (sizeof(Trigger));

	// Message
	(*trigger).message_content = NULL;

	// Channel
	(*trigger).channel = NULL;

	return trigger;
}

void Trigger_Set_Message (Trigger *trigger, const char *content) {
	if (content != NULL) {

		// Free previous state
		if ((*trigger).message_content != NULL) {
			free ((*trigger).message_content);
		}

		// Copy new state
		(*trigger).message_content = (char *) malloc (strlen (content) + 1);
		strncpy ((*trigger).message_content, content, strlen (content)); // Copy action construct content
		(*trigger).message_content[strlen (content)] = '\0';
	}
}

void Trigger_Delete (Trigger *trigger) {

	// Message
	if ((*trigger).message_content != NULL) {
		free ((*trigger).message_content);
	}

	// Trigger
	free (trigger);
}
