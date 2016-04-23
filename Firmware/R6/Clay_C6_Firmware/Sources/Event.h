#ifndef EVENT_H
#define EVENT_H

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

#include "stdlib.h"
#include "string.h"

#include "clayString.h"

#include "Action.h"

#ifndef DEFAULT_UUID_LENGTH
#define DEFAULT_UUID_LENGTH 37
#endif

#define ACTION_UUID_LENGTH DEFAULT_UUID_LENGTH // i.e., 36 bytes plus one more for NULL terminating character.

/**
 * Event
 */

extern Event* Create_Event (char *uuid, Action *action, char *state);
extern int8_t Delete_Event (Event *event);
extern void Set_Event_State (Event *event, char *state);

extern void Set_Event_Trigger (Event *event, Trigger *trigger);
// TODO: Add_Event_Trigger, Remove_Event_Trigger

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

int8_t Process_Event (Event *event);

#endif
