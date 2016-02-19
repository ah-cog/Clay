/*
 * Interpreter.c
 *
 *  Created on: Sep 24, 2015
 *      Author: mokogobo
 */

#include "Messenger.h"
#include "ESP8266.h"
#include "Behavior.h"

#define DEFAULT_UUID_LENGTH 37

Message *incomingMessageQueue = NULL;
Message *outgoingMessageQueue = NULL;

char messageUuidBuffer[DEFAULT_UUID_LENGTH] = { 0 };
char grammarSymbolBuffer[MAXIMUM_GRAMMAR_SYMBOL_LENGTH] = { 0 };
char uuidBuffer[DEFAULT_UUID_LENGTH] = { 0 };
char uuidBuffer2[DEFAULT_UUID_LENGTH] = { 0 };
char behaviorDescriptionBuffer[MAXIMUM_GRAMMAR_SYMBOL_LENGTH] = { 0 };

Message* Create_Message (const char *content) {
	
	// Allocate memory for message structure.
	Message *message = (Message *) malloc (sizeof (Message));
	
	(*message).source = NULL;
	(*message).destination = NULL;
	
	// Allocate memory for the message's content.
	(*message).content = (char *) malloc (strlen (content));
	
	// Copy message content
	strcpy ((*message).content, content);
	
	// Set up links for queue
	(*message).previous = NULL;
	(*message).next = NULL;
	
	return message;
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
		// (*message).previous = NULL; // NOTE: This should already be NULL at this point, so this is redundant, but adds some degree of robustness.
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

int8_t Process_Incoming_Message (Message *message) {
	
	int8_t status = NULL;
	int8_t result = NULL;
	char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	int tokenCount = 0;
//	int tokenInt = 0;
//	int i;
	
	char *messageContent = NULL;
	messageContent = (*message).content;
	
//	getToken (messageContent, token, 0)
	// TODO: char* tokenX = tokenizeString (char *string, int stringLength, char separator) --OR-- tokenizeString (char *string, char separator, token1, token2, token3, ...)
	
	tokenCount = getTokenCount (messageContent);
	
	if ((status = getToken (messageContent, token, 0)) != NULL) { // status = getToken (message, token, 0);

		// create behavior
		// ^
		if (strncmp (token, "create", strlen ("create")) == 0) {
			
			if ((status = getToken (messageContent, token, 1)) != NULL) {
			
				// create behavior <uuid> "turn lights on"
				//        ^
				if (strncmp (token, "behavior", strlen ("behavior")) == 0) {
					
					// Get UUID (parameter index 2)
					status = getToken (messageContent, uuidBuffer, 2);

					// Get command (parenthesized string index 3)
					status = getToken (messageContent, behaviorDescriptionBuffer, 3);
					
					// TODO: Send the acknowledgment .
					// TODO: Queue_Outgoing_Message (i.e., "got <message-uuid> <message-content>")
					// TODO: Send_UDP_Message ();
					strncpy (token, "got ", 4);
					strncpy (token + 4, messageContent, strlen (messageContent));
					// TODO: Queue the outgoing UDP message!
					Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT); // Broadcast_UDP_Message (token, UDP_SERVER_PORT);
					// TODO: Queue the message rather than executing it immediately (unless specified)
					// TODO: Parse the message rather than brute force like this.
					
					// Delete the message
					if (message != NULL) {
						Delete_Message (message);
					}
					
					// Check if the behavior is already in the cache. If nay, cache it!
					if (Has_Cached_Behavior_By_UUID (uuidBuffer) == FALSE) {
						
						// TODO: Get available memory and only create the behavior if there's enough memory. Otherwise, move something out of memory to make room for it (and stream the moved thing back in when it's needed).
						
						// Parse the message content and perform the corresponding behavior operation
						Behavior *behavior = Create_Behavior (uuidBuffer, behaviorDescriptionBuffer);
						if (behavior != NULL) {
							// NOTE: The behavior was successfully created.
							// Add the behavior to the local cache!
							Cache_Behavior (behavior);
							result = TRUE;
						}
						
					} else {
						
						// The behavior construct already exists in the cache. There's no need to create it!
						result = TRUE;
						
					}
					
//					// TODO: Send the acknowledgment.
//					// TODO: Queue_Outgoing_Message (i.e., "got <message-uuid> <message-content>")
//					// TODO: Send_UDP_Message ();
//					strncpy (token, "got ", 4);
//					strncpy (token + 4, messageContent, strlen (messageContent));
//					// TODO: Queue the outgoing UDP message!
//					Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT); // Broadcast_UDP_Message (token, UDP_SERVER_PORT);
//					
//					// TODO: Queue the message rather than executing it immediately (unless specified)
//					// TODO: Parse the message rather than brute force like this.
					
				}
				
				/*
				// create loop <uuid>
				//        ^
				else if (strncmp (token, "loop", strlen ("loop")) == 0) {
					
					// TODO:
					
				}
				*/
				
			}
			
		} else if (strncmp (token, "add", strlen ("add")) == 0) {
			
			if ((status = getToken (messageContent, token, 1)) != NULL) {
		
				// add behavior <uuid> [to loop <uuid>] [before <uuid>]
				//     ^
				if (strncmp (token, "behavior", strlen ("behavior")) == 0) {
					
					// TODO: Check for "add behavior <uuid> (to loop <loop-uuid>) after <other-uuid>"
					
					// Check for "add behavior <uuid> after <uuid>"
					if (tokenCount == 3) {
						
						// add behavior <uuid>
						//              ^
				
						// Get UUID (parameter index 2)
						status = getToken (messageContent, uuidBuffer, 2);
						
						// TODO: Send the acknowledgment .
						// TODO: Queue_Outgoing_Message (i.e., "got <message-uuid> <message-content>")
						// TODO: Send_UDP_Message ();
						strncpy (token, "got ", 4);
						strncpy (token + 4, messageContent, strlen (messageContent));
						// TODO: Queue the outgoing UDP message!
						Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT); // Broadcast_UDP_Message (token, UDP_SERVER_PORT);
						// TODO: Queue the message rather than executing it immediately (unless specified)
						// TODO: Parse the message rather than brute force like this.
						
						// Delete the message
						if (message != NULL) {
							Delete_Message (message);
						}
						
						// Check if the behavior is already in the cache. If nay, cache it!
						if (Has_Cached_Behavior_By_UUID (uuidBuffer) == TRUE) {
							
							// TODO: Only call either Get_Cached_Behavior_By_UUID. Don't call both Has_Cached_Behavior_By_UUID and Get_Cached_Behavior_By_UUID. They do the same search work. Don't search multiple times for no reason during behavior construct recall!
							
							// Parse the message content and perform the corresponding behavior operation
							Behavior *behavior = Get_Cached_Behavior_By_UUID (uuidBuffer);
							if (behavior != NULL) {
								// NOTE: The behavior was successfully created.
								// Add the behavior to the local cache!
								Add_Behavior (behavior);
								result = TRUE;
							}
							
						} else {
							
							// TODO: The behavior is not in the cache! Return response indicating this! Or request it from the cloud!
							
							result = FALSE;
							
						}
						
					} else if (tokenCount > 3) {
						
						// add behavior <uuid> before <uuid>
						//              ^
				
						// Get UUIDs of behaviors
						status = getToken (messageContent, uuidBuffer, 2); // Get UUID of behavior being added (parameter index 2)
						status = getToken (messageContent, uuidBuffer2, 4); // Get UUID of behavior already on the loop (parameter index 4)
						
						// TODO: Send the acknowledgment .
						// TODO: Queue_Outgoing_Message (i.e., "got <message-uuid> <message-content>")
						// TODO: Send_UDP_Message ();
						strncpy (token, "got ", 4);
						strncpy (token + 4, messageContent, strlen (messageContent));
						// TODO: Queue the outgoing UDP message!
						Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT); // Broadcast_UDP_Message (token, UDP_SERVER_PORT);
						// TODO: Queue the message rather than executing it immediately (unless specified)
						// TODO: Parse the message rather than brute force like this.
						
						// Delete the message
						if (message != NULL) {
							Delete_Message (message);
						}
						
						// Check if the behavior is already in the cache. If nay, cache it!
						if (Has_Cached_Behavior_By_UUID (uuidBuffer) == TRUE && Has_Cached_Behavior_By_UUID (uuidBuffer2) == TRUE ) {
							
							// TODO: Only call either Get_Cached_Behavior_By_UUID. Don't call both Has_Cached_Behavior_By_UUID and Get_Cached_Behavior_By_UUID. They do the same search work. Don't search multiple times for no reason during behavior construct recall!
							
							// Parse the message content and perform the corresponding behavior operation
							Behavior *behavior = Get_Cached_Behavior_By_UUID (uuidBuffer);
							Behavior *nextBehavior = Get_Cached_Behavior_By_UUID (uuidBuffer2);
							if (behavior != NULL && nextBehavior != NULL) {
								// NOTE: The behavior was successfully created.
								// Add the behavior to the local cache!
								Add_Before_Behavior (behavior, nextBehavior);
								result = TRUE;
							} else {
								
								// TODO: If behavior or nextBehavior are NULL, stream them in over the Internet.
								
							}
							
						} else {
							
							// TODO: The behavior is not in the cache! Return response indicating this! Or request it from the cloud!
							
							result = FALSE;
							
						}
						
					}
					
				}
			
			}
			
		} else if (strncmp (token, "remove", strlen ("remove")) == 0) { 
			
			if ((status = getToken (messageContent, token, 1)) != NULL) {
		
				// add behavior <uuid> [to loop <uuid>]
				//     ^
				if (strncmp (token, "behavior", strlen ("behavior")) == 0) {
				
					// Get UUID (parameter index 2)
					status = getToken (messageContent, uuidBuffer, 2);
					
					// TODO: Send the acknowledgment .
					// TODO: Queue_Outgoing_Message (i.e., "got <message-uuid> <message-content>")
					// TODO: Send_UDP_Message ();
					strncpy (token, "got ", 4);
					strncpy (token + 4, messageContent, strlen (messageContent));
					// TODO: Queue the outgoing UDP message!
					Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT); // Broadcast_UDP_Message (token, UDP_SERVER_PORT);
					// TODO: Queue the message rather than executing it immediately (unless specified)
					// TODO: Parse the message rather than brute force like this.
					
					// Delete the message
					if (message != NULL) {
						Delete_Message (message);
					}
					
					// Check if the behavior is already in the cache. If nay, cache it!
					if (Has_Behavior_By_UUID (uuidBuffer) == TRUE) {
						
						// TODO: Only call either Get_Cached_Behavior_By_UUID. Don't call both Has_Cached_Behavior_By_UUID and Get_Cached_Behavior_By_UUID. They do the same search work. Don't search multiple times for no reason during behavior construct recall!
						
						// Parse the message content and perform the corresponding behavior operation
						Behavior *behavior = Get_Behavior_By_UUID (uuidBuffer);
						if (behavior != NULL) {
							// NOTE: The behavior was successfully created.
							// Add the behavior to the local cache!
							Remove_Behavior (behavior);
							result = TRUE;
						}
						
					} else {
						
						// TODO: The behavior is not in the cache! Return response indicating this! Or request it from the cloud!
						
						result = FALSE;
						
					}
					
				}
			
			}
			
		} else if (strncmp (token, "reset", strlen ("reset")) == 0) {
			
			// HACK: Remove the "reset" command. This is used for testing!
			
			// Remove behaviors constructs from loop
			// Delete behaviors
			// Set loop to null
			// Delete behaviors
			// Remove behavior constructs from cache
			// Set cache to null
			Reset_Unit ();
			
			// Delete the message
			if (message != NULL) {
				Delete_Message (message);
			}
			
			// TODO: Send the acknowledgment .
			// TODO: Queue_Outgoing_Message (i.e., "got <message-uuid> <message-content>")
			// TODO: Send_UDP_Message ();
			strncpy (token, "got ", 4);
			strncpy (token + 4, messageContent, strlen (messageContent));
			// TODO: Queue the outgoing UDP message!
			Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT); // Broadcast_UDP_Message (token, UDP_SERVER_PORT);
			// TODO: Queue the message rather than executing it immediately (unless specified)
			// TODO: Parse the message rather than brute force like this.
			
			result = TRUE;
			
		} else if (strncmp (token, "update", strlen ("update")) == 0) {
			
			// Write to the flag in the flash memory shared with the bootloader.
			// This indicates to the bootloader that an update has been requested.
//			SharedData.ApplicationUpdateAvailable = TRUE;
			
			// Perform operating system operations.
			//todo: check this somewhere where it makes sense, get user consent, and then jump to the bootloader.
//			is_update_available = Update_Available ();
//			SharedData.ApplicationUpdateAvailable = TRUE; // HACK
//			if (is_update_available) { // HACK
//				SharedData.UpdateApplication = TRUE;
//			} // HACK
			
//			if (SharedData.UpdateApplication) {
				if (0) {
				
			    // Disable all interrupts before jumping to the application.
			    Disable_Interrupts ();
			    
			    // TODO: Reset the "application key" to indicate the bootloader.
			    // Reset the "application key".
//				SharedData.ApplicationKey = BOOTLOADER_KEY_VALUE;
//			    SharedData.ApplicationKey = APPLICATION_KEY_VALUE;
				
//				if(SharedData.ApplicationKey != APPLICATION_KEY_VALUE)
//				{
//					SharedData.ApplicationKey = APPLICATION_KEY_VALUE;
//				}
				
				// Jump to the bootloader.
				Jump_To_Bootloader_And_Update_Application ();
			}
			
			result = TRUE;
			
		}
			
	}
	
	// TODO: Store message UUID for use in message acknowledgment protocol. If it has been received, then don't apply it again, just send the acknowledgment packet.
	
	return result;
}

int16_t Queue_Outgoing_Message (char *address, Message *message) {
	// Allocate memory for the UUID for this behavior.
	(*message).destination = (char *) malloc (strlen (address));
	strcpy ((*message).destination, address); // Copy the message destination address
	
	// Queue the message.
	return Queue_Message (&outgoingMessageQueue, message);
	
}

int8_t Process_Outgoing_Message (Message *message) {
	
	int8_t result = NULL;
	
	if (message != NULL) {
		
		// Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT);
		Send_UDP_Message ((*message).destination, DISCOVERY_BROADCAST_PORT, (*message).content);
		
		result = TRUE;
		
	}
	
	return result;
}

