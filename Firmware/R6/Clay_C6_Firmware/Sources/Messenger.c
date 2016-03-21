#include "Messenger.h"
#include "Action.h"

#define DEFAULT_UUID_LENGTH 37

Message *incomingMessageQueue = NULL;
Message *outgoingMessageQueue = NULL;

char messageUuidBuffer[DEFAULT_UUID_LENGTH] = { 0 };
char grammarSymbolBuffer[MAXIMUM_GRAMMAR_SYMBOL_LENGTH] = { 0 };

Message* Create_Message (const char *content) {

	// Allocate memory for message structure.
	Message *message = (Message *) malloc (sizeof (Message));

	(*message).source = NULL;
	(*message).destination = NULL;

	// Allocate memory for the message's content.
//	(*message).content = (char *) malloc (strlen (content + 1)); // Add one for "\0"
	(*message).content = (char *) malloc (strlen (content));

	// Copy message content
	strcpy ((*message).content, content);
//	(*message).content[strlen(content)] = '\0';

	// Set up links for queue
	(*message).previous = NULL;
	(*message).next = NULL;

	return message;
}

void Set_Message_Source (Message *message, const char *address) {

	// Free the message's destination address from memory
	if ((*message).source != NULL) {
		free ((*message).source);
		(*message).source = NULL;
	}

	// Copy the message destination address
	(*message).source = (char *) malloc (strlen (address));
	strcpy ((*message).source, address);
}

void Set_Message_Destination (Message *message, const char *address) {

	// Free the message's destination address from memory
	if ((*message).destination != NULL) {
		free ((*message).destination);
		(*message).destination = NULL;
	}

	// Copy the message destination address
	(*message).destination = (char *) malloc (strlen (address));
	strcpy ((*message).destination, address);
}

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

uint8_t Initialize_Message_Queue (Message **messageQueue) {
	
	(*messageQueue) = NULL;
	return TRUE;
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
			return TRUE;
		}
	}
	
	return FALSE;
}

int16_t Queue_Outgoing_Message (char *address, Message *message) {
	// Allocate memory for the UUID for this action.
	(*message).destination = (char *) malloc (strlen (address));
	strcpy ((*message).destination, address); // Copy the message destination address
	
	// Queue the message.
	return Queue_Message (&outgoingMessageQueue, message);
	
}


