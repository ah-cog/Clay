/**
 * Implements FIFO queues for incoming and outgoing messages.
 */

#ifndef MESSAGE_H
#define MESSAGE_H

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

typedef struct Message
{
      // TODO: char *uuid;
      char * message_type;
      char * source;
      char * destination;
      uint32_t content_length;
      uint16_t content_checksum;
      char * content_type;
      char * content;

      struct Message *previous;
      struct Message *next;
} Message;

extern Message* Create_Message();
extern int8_t Delete_Message(Message *message);

extern void Set_Message_Type(Message *message, const char *type);
extern void Set_Message_Source(Message *message, const char *address);
extern void Set_Message_Destination(Message *message, const char *address);
extern void Set_Message_Content(Message *message, const char *content, uint32_t content_length);
extern void Set_Message_Content_Type(Message *message, const char *content_type);

extern char * Get_Message_Type(Message *message);
extern char * Get_Message_Source(Message *message);
extern char * Get_Message_Destination(Message *message);
extern char * Get_Message_Content(Message *message);
extern uint32_t Get_Message_Content_Length(Message *message);
extern char * Get_Message_Content_Type(Message *message);

#endif
