#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#include "Message.h"
#include "CRC16.h"

#define DEFAULT_UUID_LENGTH 37

char messageUuidBuffer[DEFAULT_UUID_LENGTH] =
{ 0 };
char grammarSymbolBuffer[MAXIMUM_GRAMMAR_SYMBOL_LENGTH] =
{ 0 };

Message* Create_Message()
{

	// Allocate memory for message structure.
	Message *message = (Message *) malloc(sizeof(Message));

	(*message).message_type = NULL;
	(*message).source = NULL;
	(*message).destination = NULL;
	(*message).content_length = 0;
	(*message).content_checksum = 0;
	(*message).content_type = NULL;
	(*message).content = NULL;

	// Set up links for queue
	(*message).previous = NULL;
	(*message).next = NULL;

	return message;
}

int8_t Delete_Message(Message *message)
{
	if (message != NULL)
	{
		// TODO: Remove references to the message in the queue.

		if ((*message).message_type != NULL)
		{
			free((*message).message_type);
			(*message).message_type = NULL;
		}

		if ((*message).source != NULL)
		{
			free((*message).source);
			(*message).source = NULL;
		}

		if ((*message).destination != NULL)
		{
			free((*message).destination);
			(*message).destination = NULL;
		}

		if ((*message).content_type != NULL)
		{
			free((*message).content_type);
			(*message).content_type = NULL;
		}

		if ((*message).content != NULL)
		{
			free((*message).content);
			(*message).content = NULL;
		}

		free(message);
		message = NULL;

		return true;
	}

	return false;
}

void Set_Message_Type(Message *message, const char *type)
{

	// Free the message's destination stored type from memory
	if ((*message).message_type != NULL)
	{
		free((*message).message_type);
		(*message).message_type = NULL;
	}

	// Copy the type into the structure
	(*message).message_type = (char *) zalloc(strlen(type) + 1);
	memset((*message).message_type, '\0', strlen(type) + 1);

	strcpy((*message).message_type, type);
}

void Set_Message_Source(Message *message, const char *address)
{

	// Free the message's destination address from memory
	if ((*message).source != NULL)
	{
		free((*message).source);
		(*message).source = NULL;
	}

	// Copy the message destination address
	(*message).source = (char *) zalloc(strlen(address) + 1);
	memset((*message).source, '\0', strlen(address) + 1);

	strcpy((*message).source, address);
}

void Set_Message_Destination(Message *message, const char *address)
{

	// Free the message's destination address from memory
	if ((*message).destination != NULL)
	{
		free((*message).destination);
		(*message).destination = NULL;
	}

	// Copy the message destination address
	(*message).destination = (char *) zalloc(strlen(address) + 1);
	memset((*message).destination, '\0', strlen(address) + 1);

	strcpy((*message).destination, address);
}

void Set_Message_Content(Message * message, const char *content,
		uint32_t content_length)
{

	(*message).content_length = content_length;

	// Allocate memory for the message's content.
	(*message).content = (char *) malloc((*message).content_length + 1);
	(*message).content_checksum = Calculate_Checksum_On_Bytes(content,
			content_length);

	memset((*message).content, 0, (*message).content_length + 1);

	// Copy message content
	memcpy((*message).content, content, (*message).content_length);
}

extern void Set_Message_Content_Type(Message *message, const char *content_type)
{

	// Free the message's destination address from memory
	if ((*message).content_type != NULL)
	{
		free((*message).content_type);
		(*message).content_type = NULL;
	}

	// Copy the message content_type address
	(*message).content_type = (char *) malloc(strlen(content_type) + 1);
	memset((*message).content_type, '\0', strlen(content_type) + 1);

	strcpy((*message).content_type, content_type);
}

char * Get_Message_Type(Message *message)
{
	return (*message).message_type;
}

char * Get_Message_Source(Message *message)
{
	return (*message).source;
}

char * Get_Message_Destination(Message *message)
{
	return (*message).destination;
}

char * Get_Message_Content(Message *message)
{
	return (*message).content;
}

uint32_t Get_Message_Content_Length(Message *message)
{
	return (*message).content_length;
}

char * Get_Message_Content_Type(Message *message)
{
	return (*message).message_type;
}

