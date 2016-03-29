#ifndef TIMELINE_H
#define TIMELINE_H

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

#include "stdlib.h"
#include "string.h"

#include "clayString.h"

#include "Event.h"

#ifndef DEFAULT_UUID_LENGTH
#define DEFAULT_UUID_LENGTH 37
#endif

typedef struct Timeline {
	char *uuid;
	struct Event *first_event;
	struct Event *current_event;
} Timeline;

extern Timeline *timeline;

extern Timeline* Create_Timeline (char *uuid);
extern void Reset_Timeline (Timeline *timeline);
extern void Delete_Timeline (Timeline *timeline);

int16_t Add_Event (Timeline *timeline, Event *event); // TODO: int16_t Add_Behavior (Behavior *loop, Behavior *behavior);
int16_t Insert_Event (Timeline *timeline, Event *event, uint16_t index);
int16_t Add_Before_Event (Timeline *timeline, Event *event, Event *other_event);
Action* Remove_Event (Timeline *timeline, Event *event); // TODO: Behavior* Remove_Behavior (Behavior *loop, Behavior *behavior);
uint8_t Has_Events (Timeline *timeline);
uint8_t Has_Event_By_UUID (Timeline *timeline, char *uuid);
Event* Get_Event_By_UUID (Timeline *timeline, char *uuid);

#endif
