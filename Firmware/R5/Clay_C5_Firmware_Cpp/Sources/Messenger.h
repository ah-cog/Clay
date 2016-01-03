/**
 * Implements FIFO queues for incoming and outgoing messages.
 */

#ifndef MESSENGER_H
#define MESSENGER_H

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

//#include <stdio.h>
#include <string.h>

#include "Utilities/Debug.h"
#include "Utilities/String.h"

#include "Timer_1ms.h"
#include "GPIO.h"
#include "Drivers/PCA9552.h"
#include "Drivers/ESP8266.h"

#include "Behavior.h"

#define MAXIMUM_MESSAGE_LENGTH 140
#define MAXIMUM_GRAMMAR_SYMBOL_LENGTH 64

typedef struct Message {
	// TODO: char *uuid;
	char *source;
	char *destination;
	char *content;
	
	struct Message *previous;
	struct Message *next;
} Message;

extern Message *incomingMessageQueue;
extern Message *outgoingMessageQueue;

extern Message* Create_Message (const char *content);
extern int8_t Delete_Message (Message *message);

// Message Queue
extern uint8_t Initialize_Message_Queue (Message **messageQueue);
extern int16_t Queue_Message (Message **messageQueue, Message *message); // Circular queue of incoming messages.
extern Message* Dequeue_Message (Message **messageQueue); // Get the message on the front of the incoming message queue.
extern int8_t Has_Messages (Message **messageQueue);

// Incoming Message Queue
extern int8_t Process_Incoming_Message (Message *message);

// Outgoing Message Queue
extern int16_t Queue_Outgoing_Message (char *address, Message *message);
extern int8_t Process_Outgoing_Message (Message *message);

#endif /* MESSENGER_H */
