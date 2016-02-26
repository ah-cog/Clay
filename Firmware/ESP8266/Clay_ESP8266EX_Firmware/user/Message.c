#include "esp_common.h"
#include "Message.h"
#include "string.h"
#include "UART.h"

void Initialize_Message(Message *message, char *source, char *destination, char *content)
{
   // Set source
//   printf("source len: %d\n", strlen(source) + 1);
//   printf("source [%s]\n", source);
   memcpy((*message).source, source, strlen(source) + 1);
   (*message).source[(strlen(source) + 1)] = '\n';
   (*message).source[(strlen(source) + 2)] = '\0';

   // Set destination
//   printf("dest len: %d\n", strlen(destination) + 1);
//   printf("dest [%s]\n", destination);
   memcpy((*message).destination, destination, strlen(destination) + 1);
   (*message).destination[(strlen(destination) + 1)] = '\n';
   (*message).destination[(strlen(destination) + 2)] = '\0';

   // Set contents
//   printf("content len: %d\n", strlen(content) + 1);
//   printf("content [%s]\n", content);
   memcpy((*message).content, content, strlen(content) + 1);
   (*message).content[(strlen(content) + 1)] = '\n';
   (*message).content[(strlen(content) + 2)] = '\0';
}
