#include "Message.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define DEFAULT_UUID_LENGTH 37

#define MESSAGE_TERMINATOR '\n'
#define ADDRESS_TERMINATOR '\x12'

char messageUuidBuffer[DEFAULT_UUID_LENGTH] = { 0 };
char grammarSymbolBuffer[MAXIMUM_GRAMMAR_SYMBOL_LENGTH] = { 0 };

Message* Create_Message (const char *content) {

	// Allocate memory for message structure.
	Message *message = (Message *) malloc (sizeof (Message));

	(*message).type = NULL;
	(*message).source = NULL;
	(*message).destination = NULL;

	// Allocate memory for the message's content.
	(*message).content = (char *) malloc (strlen (content) + 1);
	memset ((*message).content, '\0', strlen (content) + 1);

	// Copy message content
	strncpy ((*message).content, content, strlen (content));

	// Set up links for queue
	(*message).previous = NULL;
	(*message).next = NULL;

	return message;
}

void Set_Message_Type (Message *message, const char *type) {

	// Free the message's destination stored type from memory
	if ((*message).type != NULL) {
		free ((*message).type);
		(*message).type = NULL;
	}

	// Copy the type into the structure
	(*message).type = (char *) malloc (strlen (type) + 1);
	memset ((*message).type, '\0', strlen (type) + 1);

	strcpy ((*message).type, type);

//	sprintf ((*message).source, "%s,%s%c", channel, address, ADDRESS_TERMINATOR);
}

void Set_Message_Source (Message *message, const char *address) {

	// Free the message's destination address from memory
	if ((*message).source != NULL) {
		free ((*message).source);
		(*message).source = NULL;
	}

	// Copy the message destination address
	(*message).source = (char *) malloc (strlen (address) + 1);
	memset ((*message).source, '\0', strlen (address) + 1);

	strcpy ((*message).source, address);

//	(*message).source = (char *) malloc (strlen (type) + 1 + strlen (address) + 1); // i.e., <channel>,<address>!
//	strcpy ((*message).source, address);

//	sprintf ((*message).source, "%s,%s%c", type, address, ADDRESS_TERMINATOR);
}

void Set_Message_Destination (Message *message, const char *address) {

	// Free the message's destination address from memory
	if ((*message).destination != NULL) {
		free ((*message).destination);
		(*message).destination = NULL;
	}

	// Copy the message destination address
	(*message).destination = (char *) malloc (strlen (address));
	memset ((*message).destination, '\0', strlen (address) + 1);

	strcpy ((*message).destination, address);

//	(*message).destination = (char *) malloc (strlen (type) + 1 + strlen (address) + 1); // i.e., <channel>,<address>!
//	strcpy ((*message).destination, address);

//	sprintf ((*message).destination, "%s,%s%c", type, address, ADDRESS_TERMINATOR);
}

//void Set_Message_Source (Message *message, const char *address);
//void Set_Message_Destination (Message *message, const char *address);
//void Set_Message_Content (Message *message, const char *content);

int8_t Delete_Message (Message *message) {

	if (message != NULL) {

		// TODO: Remove references to the message in the queue.

		// Free the message's content from memory
		free ((*message).content);
		(*message).content = NULL;

		// Free the message's source address from memory
		if ((*message).source != NULL) {
			free ((*message).source);
			(*message).source = NULL;
		}

		// Free the message's destination address from memory
		if ((*message).destination != NULL) {
			free ((*message).destination);
			(*message).destination = NULL;
		}

		// Free the message from memory
		free (message);
		message = NULL;

		return TRUE;
	}

	return FALSE;
}

