#include "Message_Processor.h"
#include "Behavior.h"

char uuidBuffer[DEFAULT_UUID_LENGTH] = { 0 };
char uuidBuffer2[DEFAULT_UUID_LENGTH] = { 0 };
char behaviorDescriptionBuffer[MAXIMUM_GRAMMAR_SYMBOL_LENGTH] = { 0 };

int8_t Process_Incoming_Message (Message *message) {

	int8_t status = NULL;
	int8_t result = NULL;
	char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	int tokenCount = 0;

	char *messageContent = NULL;
	messageContent = (*message).content;

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
//					Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT); // Broadcast_UDP_Message (token, UDP_SERVER_PORT);
					Message *responseMessage = Create_Message (token);
					Set_Message_Destination(responseMessage, "UDP,192.168.1.255:4445!"); // <HACK />
					Queue_Message(&outgoingMessageQueue, responseMessage);
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
//						Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT); // Broadcast_UDP_Message (token, UDP_SERVER_PORT);
						Message *responseMessage = Create_Message (token);
						Set_Message_Destination(responseMessage, message->source);
						Queue_Message(&outgoingMessageQueue, responseMessage);
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
//						Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT); // Broadcast_UDP_Message (token, UDP_SERVER_PORT);
						Message *responseMessage = Create_Message (token);
						Set_Message_Destination(responseMessage, message->source);
						Queue_Message(&outgoingMessageQueue, responseMessage);
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
//					Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT); // Broadcast_UDP_Message (token, UDP_SERVER_PORT);
					Message *responseMessage = Create_Message (token);
					Set_Message_Destination(responseMessage, message->source);
					Queue_Message(&outgoingMessageQueue, responseMessage);
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
//			Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT); // Broadcast_UDP_Message (token, UDP_SERVER_PORT);
			Message *responseMessage = Create_Message (token);
			Set_Message_Destination(responseMessage, message->source);
			Queue_Message(&outgoingMessageQueue, responseMessage);
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

int8_t Process_Outgoing_Message (Message *message) {

	int8_t result = NULL;

	if (message != NULL) {

//		// Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT);
//		Send_UDP_Message ((*message).destination, DISCOVERY_BROADCAST_PORT, (*message).content);

		// Send message over Wi-Fi
		result = Wifi_Send (message);

		result = TRUE;

	}

	return result;
}
