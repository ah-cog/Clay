#include "esp_common.h"
#include "Message.h"
#include "string.h"
#include "UART.h"
#include "AddressSerialization.h"

void ICACHE_RODATA_ATTR Initialize_Message(Message *message,
		char * message_type, char *source, char *destination, char *content)
{
	//set type
	memcpy((*message).type, message_type, strlen(message_type) + 1);
	message->type[strlen(message_type)] = '\0';

	// Set source
	memcpy((*message).source, source, strlen(source) + 1);
	message->source[strlen(source)] = '\0';

	// Set destination
	memcpy((*message).destination, destination, strlen(destination));
	message->destination[strlen(destination)] = '\0';

	// Set contents
	memcpy((*message).content, content, strlen(content) + 1);
	strtok(message->content, message_delimiter);
}
