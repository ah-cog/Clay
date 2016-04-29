#ifndef MESSAGE_H
#define MESSAGE_H

/**
 * Message
 */

#include "Clay_Config.h"

#define MAXIMUM_MESSAGE_LENGTH 256
#define MAXIMUM_SOURCE_LENGTH 100
#define MAXIMUM_DESTINATION_LENGTH 100

typedef struct Message
{
	char source[MAXIMUM_SOURCE_LENGTH];
	char destination[MAXIMUM_DESTINATION_LENGTH];
	char content[MAXIMUM_MESSAGE_LENGTH];
	char type[CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH];
} Message;

// extern Message Create_Message (const char *content);
// extern Delete_Message (Message *message);
extern void Initialize_Message(Message *message, char *message_type,
		char *source, char *destination, char *content);

#endif
