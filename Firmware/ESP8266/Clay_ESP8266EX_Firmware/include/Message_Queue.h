#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <string.h>

#include "Message.h"

#ifndef bool
typedef int bool;
enum
{
	false, true};
#endif

#ifndef NULL
#define NULL 0
#endif

/**
 * Message Queue
 */

#define MAXIMUM_MESSAGE_COUNT 20

typedef struct Message_Queue
{
	Message messages[MAXIMUM_MESSAGE_COUNT];
	volatile int front;
	volatile int back;
	volatile int count;
} Message_Queue;

extern Message_Queue incoming_message_queue;
extern Message_Queue incoming_command_queue;
extern Message_Queue outgoing_UDP_message_queue;
extern Message_Queue outgoing_TCP_message_queue;

extern bool Initialize_Message_Queue(Message_Queue *message_queue);
extern Message* Get_Next_Message(Message_Queue *message_queue);
extern int Queue_Message(Message_Queue *message_queue, Message *message);
extern Message* Peek_Message(Message_Queue *message_queue);
extern bool Dequeue_Message(Message_Queue *message_queue, Message * destination);
extern bool Has_Messages(Message_Queue *message_queue);
#endif
