/**
 * Implements FIFO queues for incoming and outgoing messages.
 */

#ifndef MESSENGER_H
#define MESSENGER_H

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

//#include <stdio.h>
#include "string.h"

#include "clayString.h"

#define DISCOVERY_BROADCAST_PORT 4445
#define MESSAGE_PORT 4446

#define MAXIMUM_MESSAGE_LENGTH 512 // 140
#define MAXIMUM_GRAMMAR_SYMBOL_LENGTH 64

typedef struct Message {
	// TODO: char *uuid;
	char *source;
	char *destination;
	char *content;

	struct Message *previous;
	struct Message *next;
} Message;

extern Message* Create_Message (const char *content);
extern int8_t Delete_Message (Message *message);

//extern void Set_Message_Source (Message *message, const char *address);
//extern void Set_Message_Destination (Message *message, const char *address);

extern void Set_Message_Source2 (Message *message, const char *channel, const char *address);
extern void Set_Message_Destination2 (Message *message, const char *channel, const char *address);

extern Message *incomingMessageQueue;
extern Message *outgoingMessageQueue;

// Message Queue
extern uint8_t Initialize_Message_Queue (Message **messageQueue);
extern int16_t Queue_Message (Message **messageQueue, Message *message); // Circular queue of incoming messages.
extern Message* Dequeue_Message (Message **messageQueue); // Get the message on the front of the incoming message queue.
extern int8_t Has_Messages (Message **messageQueue);

// Outgoing Message Queue
extern int16_t Queue_Outgoing_Message (char *address, Message *message);

#endif
