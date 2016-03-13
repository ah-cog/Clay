#include "esp_common.h"
#include "Message.h"
#include "string.h"
#include "UART.h"

void ICACHE_RODATA_ATTR Initialize_Message(Message *message, char *source, char *destination,
		char *content)
{
	// Set source
	memcpy((*message).source, source, strlen(source) + 1);
	(*message).source[(strlen(source) + 1)] = '\n';
	(*message).source[(strlen(source) + 2)] = '\0';

	// Set destination
	memcpy((*message).destination, destination, strlen(destination) + 1);
	(*message).destination[(strlen(destination) + 1)] = '\n';
	(*message).destination[(strlen(destination) + 2)] = '\0';

	// Set contents
	memcpy((*message).content, content, strlen(content) + 1);
	(*message).content[(strlen(content) + 1)] = '\n';
	(*message).content[(strlen(content) + 2)] = '\0';
}
