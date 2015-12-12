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

#define MAXIMUM_MESSAGE_LENGTH 128
#define MAXIMUM_GRAMMAR_SYMBOL_LENGTH 64

// TODO: Implement FIFO queue of messages.

typedef struct Message {
	// TODO: char *uuid;
	char *content;
	
	struct Message *previous;
	struct Message *next;
} Message;

Message* Create_Message (const char *content);
int8_t Delete_Message (Message *message);

Message *incomingMessageQueue;
//Message *outgoingMessageQueue;

uint8_t Initialize_Incoming_Message_Queue ();
int16_t Queue_Incoming_Message (Message *message); // Circular queue of incoming messages.
Message* Dequeue_Incoming_Message (); // Get the message on the front of the incoming message queue.
int8_t Has_Incoming_Message ();
int8_t Process_Incoming_Message (Message *message);

//uint8_t Initialize_Outgoing_Message_Queue ();
//int16_t Queue_Outgoing_Message (Message *message); // Circular queue of incoming messages.
//Message* Dequeue_Outgoing_Message (); // Get the message on the front of the incoming message queue.
//int8_t Has_Outgoing_Message ();
//int8_t Process_Outgoing_Message (Message *message);

//int8_t Queue_Outgoing_Message (const char *message); // Circular queue of outgoing messages.
//int8_t Dequeue_Outgoing_Message (const char *message); // Get the message on the front of the outgoing message queue.

#endif /* MESSENGER_H */
