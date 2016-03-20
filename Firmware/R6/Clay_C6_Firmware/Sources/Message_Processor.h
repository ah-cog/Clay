#ifndef MESSAGE_PROCESSOR_H
#define MESSAGE_PROCESSOR_H

#include "Messenger.h"

extern int8_t Process_Incoming_Message (Message *message);

extern int8_t Process_Outgoing_Message (Message *message);

extern void Send_Acknowledgment (char *token, char *messageContent);

#endif
