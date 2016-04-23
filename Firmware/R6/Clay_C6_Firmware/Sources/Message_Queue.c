#include "Message_Queue.h"

Message *incomingMessageQueue = NULL;
Message *outgoingMessageQueue = NULL;

uint8_t Initialize_Message_Queue (Message **messageQueue) {

	(*messageQueue) = NULL;
	return TRUE;
}

int16_t Queue_Message (Message **messageQueue, Message *message) {

	Message *lastMessage = NULL;
	uint16_t messageCount = 0;

	if (message == NULL) {
		return NULL;
	}

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

Message* Peek_Message (Message **messageQueue) {

	Message *message = NULL;

	// Reference the message at the front of the queue.
	if ((*messageQueue) != NULL) {
		message = (*messageQueue);
	}

	return message;
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

int16_t Get_Message_Count (Message **messageQueue) {

	Message *lastMessage = NULL;
	uint16_t messageCount = 0;

	if ((*messageQueue) == NULL) {

		messageCount = 0;

	} else {

		// Search for the last element in the queue.
		lastMessage = (*messageQueue); // Get the front of the queue.
		messageCount++;
		while ((*lastMessage).previous != NULL) {
			lastMessage = (*lastMessage).previous;
			messageCount++;
		}

	}

	return messageCount;
}

int8_t Has_Messages (Message **messageQueue) {

	if ((*messageQueue) != NULL) {
//		if ((*(*messageQueue)).content != NULL) {
			return TRUE;
//		}
	}

	return FALSE;
}

int16_t Queue_Outgoing_Message (char *address, Message *message) {
	// Allocate memory for the UUID for this action.
	(*message).destination = (char *) malloc (strlen (address) + 1);
	memset ((*message).destination, '\0', strlen (address) + 1);

	strcpy ((*message).destination, address); // Copy the message destination address

	// Queue the message.
	return Queue_Message (&outgoingMessageQueue, message);

}
