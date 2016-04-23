#ifndef ACTION_H
#define ACTION_H

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

#include "stdlib.h"
#include "string.h"

#include "clayString.h"

#include "WiFi.h"

#include "Buzzer.h"
#include "Message.h"
#include "Message_Queue.h"
#include "Trigger.h"
#include "Services/Interactive_Assembly.h"

#ifndef DEFAULT_UUID_LENGTH
#define DEFAULT_UUID_LENGTH 37
#endif

#define ACTION_UUID_LENGTH DEFAULT_UUID_LENGTH // i.e., 36 bytes plus one more for NULL terminating character.

// TODO: Define behavior performance speed (in Hz)

/**
 * Action
 */

typedef struct Action {
	char *uuid;
	int8_t (*script) (char *); // Pointer to the procedure corresponding to the action.
} Action;

/**
 * The action construct points to a action and provides a linked list
 * mechanism for the action repository and loops.
 */
typedef struct Event {
	char *uuid; // The UUID of the action.

	// TODO: Add start condition. Check it before calling Perform_Action(action, state)
	Trigger *trigger;

	// TODO: Add repeat condition. Default is none. If none, does not repeat. Can be number (guaranteed), number (up to), number (no less than). Optionally, can add repeat period (repeat every T ms). Defaults to 0 ms.

	uint32_t repeat_period;
	// TODO: Add stop condition. Default is none. If none, proceeds to next event right away.
	Action *action; // The pointer to the action (if it's present in memory) or NULL (if it's not present in memory).
	char *state;

	// Bookkeeping: Linked list (i.e., timeline)
	struct Event *previous;
	struct Event *next;

	// Bookkeeping: for repeat condition
	uint32_t start_time;
} Event;

extern Event* cache;

extern void Enable_Actions ();
extern Action* Create_Action (char *uuid); // TODO: Add function pointer parameter
extern void Set_Action_Script (Action *action, int8_t (*script) (char *));
extern int8_t Delete_Action (Action *action);

extern int8_t Perform_Action (Action *action, char *state);

#endif
