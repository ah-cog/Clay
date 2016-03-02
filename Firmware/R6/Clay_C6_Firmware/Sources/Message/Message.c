#include "Message.h"
#include "string.h"

void Initialize_Message(Message *message, char *source, char *destination, char *content)
{
   memcpy((*message).source, source, strlen(source) + 1);
   (*message).source[(strlen(source) + 1)] = '\n';
   (*message).source[(strlen(source) + 2)] = '\0';

   memcpy((*message).destination, destination, strlen(destination) + 1);
   (*message).destination[(strlen(destination) + 1)] = '\n';
   (*message).destination[(strlen(destination) + 2)] = '\0';

   memcpy((*message).content, content, strlen(content) + 1);
   (*message).content[(strlen(content) + 1)] = '\n';
   (*message).content[(strlen(content) + 2)] = '\0';
}

