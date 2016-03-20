#ifndef ACTION_H
#define ACTION_H

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

#include "stdlib.h"
#include "string.h"

#include "String.h"

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
//	char *state;
	// void *script; // TODO: Update this to point to the action's structure.
} Action;

extern Action* Create_Action (char *uuid); // TODO: Add function pointer parameter
extern int8_t Delete_Action (Action *action);

/**
 * Event
 */

/**
 * The action construct points to a action and provides a linked list
 * mechanism for the action repository and loops.
 */
typedef struct Event {
	char *uuid; // The UUID of the action.
	Action *action; // The pointer to the action (if it's present in memory) or NULL (if it's not present in memory).
	char *state;
	struct Event *previous;
	struct Event *next;
} Event;

extern Event* Create_Event (char *uuid, Action *action, char *state);
extern int8_t Delete_Event (Event *event);
extern void Set_Event_State (Event *event, char *state);

// Action Cache
// The local behavior cache.

// TODO: Update this so it doesn't use the Event structure.
extern Event* cache;

// Device
extern uint8_t Reset_Device ();

/**
 * Cache
 */

extern uint8_t Initialize_Action_Cache ();
extern int8_t Cache_Action (Action *action);
extern Action* Get_Cached_Action_By_UUID (char *uuid);
extern Event* Get_Cached_Action_Construct_By_UUID (char *uuid);
extern uint8_t Has_Cached_Actions ();
extern uint8_t Has_Cached_Action_By_UUID (char *uuid);
extern Action* Remove_Action_From_Cache (Action *action);

/**
 * Timeline
 */

typedef struct Timeline {
	char *uuid;
	struct Event *first_event;
	struct Event *current_event;
} Timeline;

extern Timeline *timeline;

extern Timeline* Create_Timeline (char *uuid);
extern void Reset_Timeline (Timeline *timeline);
extern void Delete_Timeline (Timeline *timeline);

//extern Event* timeline;
//extern Event* currentEvent; // Pointer to the loop's current behavior.

//uint8_t Initialize_Action ();

/**
 * Event
 */

int16_t Add_Event (Timeline *timeline, Event *event); // TODO: int16_t Add_Behavior (Behavior *loop, Behavior *behavior);
int16_t Insert_Event (Timeline *timeline, Event *event, uint16_t index);
int16_t Add_Before_Event (Timeline *timeline, Event *event, Event *other_event);
Action* Remove_Event (Timeline *timeline, Event *event); // TODO: Behavior* Remove_Behavior (Behavior *loop, Behavior *behavior);
uint8_t Has_Events (Timeline *timeline);
uint8_t Has_Event_By_UUID (Timeline *timeline, char *uuid);
Event* Get_Event_By_UUID (Timeline *timeline, char *uuid);

int8_t Perform_Action (Event *event);

#endif
