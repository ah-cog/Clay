#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

#include "Message.h"

extern Message *incomingMessageQueue;
extern Message *outgoingMessageQueue;

// Message Queue
extern uint8_t Initialize_Message_Queue (Message **messageQueue);
extern int16_t Queue_Message (Message **messageQueue, Message *message); // Circular queue of incoming messages.
extern Message* Dequeue_Message (Message **messageQueue); // Get the message on the front of the incoming message queue.
extern int16_t Get_Message_Count (Message **messageQueue);
extern int8_t Has_Messages (Message **messageQueue);

// Outgoing Message Queue
extern int16_t Queue_Outgoing_Message (char *address, Message *message);

#endif
