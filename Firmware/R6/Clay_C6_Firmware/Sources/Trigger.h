#ifndef TRIGGER_H
#define TRIGGER_H

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
#include "Services/Interactive_Assembly.h"

#define TRIGGER_TYPE_MESSAGE 1
#define TRIGGER_TYPE_CHANNEL 2
#define TRIGGER_TYPE_MOTION  3

typedef struct Trigger {
	// char *uuid;
	// int8_t (*script) (char *); // Pointer to the procedure corresponding to the action.

	uint8_t type;

	// for "message" type
	//char *message_uuid;
	char *message_content;

	// for "channel" type
	Channel *channel; // TODO: Channel_Profile
	// int8_t channel_trigger_type; // 0 = on low, 1 = on high, 2 = on change (for digital)

} Trigger;

extern Trigger* Trigger_Create (); // TODO: Add function pointer parameter
extern void Trigger_Set_Message (Trigger *trigger, const char *content);
extern void Trigger_Delete (Trigger *trigger);

#endif
