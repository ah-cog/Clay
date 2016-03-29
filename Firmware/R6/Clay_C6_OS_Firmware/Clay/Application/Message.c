#include <Message.h>
#include "Action.h"

#define DEFAULT_UUID_LENGTH 37

Message *incomingMessageQueue = NULL;
Message *outgoingMessageQueue = NULL;

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

		return true;
	}

	return false;
}

uint8_t Initialize_Message_Queue (Message **messageQueue) {

	(*messageQueue) = NULL;
	return true;
}

int16_t Queue_Message (Message **messageQueue, Message *message) {

	Message *lastMessage = NULL;
	uint16_t messageCount = 0;

	if ((*messageQueue) == NULL) {

		// The queue is empty, so add it to the queue as the only element.

		(*messageQueue) = message;

		(*message).previous = NULL;
		(*message).next = NULL;

		messageCount = 1;

	} else {

		// Search for the last element in the queue.
		lastMessage = (*messageQueue); // Get the front of the queue.
		messageCount++;
		while ((*lastMessage).previous != NULL) {
			lastMessage = (*lastMessage).previous;
			messageCount++;
		}

		// Update the linked list to add the message to the back of the queue.
		(*message).previous = NULL; // NOTE: This should already be NULL at this point, so this is redundant, but adds some degree of robustness.
		(*message).next = lastMessage;

		(*lastMessage).previous = message;

		messageCount++;

	}

	return messageCount;
}

Message* Dequeue_Message (Message **messageQueue) {

	Message *message = NULL;

	if ((*messageQueue) != NULL) {

		// Reference the message at the front of the queue.
		message = (*messageQueue);

		// Update the linked list to remove the message from the front of the queue.
		if ((*message).previous != NULL) {

			// There are additional messages on the queue. Set the previous element to the front of the queue.

			(*messageQueue) = (*message).previous;
			// incomingMessageQueue = (*message).next; // NOTE: This should already be NULL at this point, so this is redundant, but adds some degree of robustness.
			(*(*messageQueue)).next = NULL; // Set as the first element in the queue.

			// Unlink the message from linked list to finish dequeuing process.
			(*message).previous = NULL;
			(*message).next = NULL;

		} else {

			// There are no more messages in the queue, so remove links.

			(*messageQueue) = NULL; // Remove the link to any message at the front of the queue.

			// Unlink the message from linked list to finish dequeuing process.
			(*message).previous = NULL;
			(*message).next = NULL;

		}
	}

	return message;
}

int8_t Has_Messages (Message **messageQueue) {

	if ((*messageQueue) != NULL) {
		if ((*(*messageQueue)).content != NULL) {
			return true;
		}
	}

	return false;
}

int16_t Queue_Outgoing_Message (char *address, Message *message) {
	// Allocate memory for the UUID for this action.
	(*message).destination = (char *) malloc (strlen (address) + 1);
	memset ((*message).destination, '\0', strlen (address) + 1);

	strcpy ((*message).destination, address); // Copy the message destination address

	// Queue the message.
	return Queue_Message (&outgoingMessageQueue, message);

}


