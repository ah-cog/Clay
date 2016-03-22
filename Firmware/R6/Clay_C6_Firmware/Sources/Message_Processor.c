#include "Message_Processor.h"
#include "Action.h"

char uuid_buffer[DEFAULT_UUID_LENGTH] = { 0 };
char uuid_buffer2[DEFAULT_UUID_LENGTH] = { 0 };
char state_buffer[MAXIMUM_GRAMMAR_SYMBOL_LENGTH] = { 0 };

int8_t Process_Incoming_Message (Message *message) {

	int8_t status = NULL;
	int8_t result = NULL;
	char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	int token_count = 0;

	char *message_content = NULL;
	message_content = (*message).content;

	token_count = Get_Token_Count (message_content);

	// Reset the buffer
	memset (uuid_buffer2, '\0', DEFAULT_UUID_LENGTH);

	if ((status = Get_Token (message_content, token, 0)) != NULL) {

		// cache action
		// ^
		if (strncmp (token, "cache", strlen ("cache")) == 0) {

			if ((status = Get_Token (message_content, token, 1)) != NULL) {

				// cache action <uuid> /* "turn lights on" */
				//       ^
				if (strncmp (token, "action", strlen ("action")) == 0) {

					// Get UUID (parameter index 2) and command (parenthesized string index 3)
					Get_Token (message_content, uuid_buffer, 2);
//					Get_Token (message_content, state_buffer, 3);

					// Send message to sender to acknowledge receipt
					Send_Acknowledgment (token, message_content);

					// Delete the message
					Delete_Message (message);

					// Check if the action is already in the cache. If nay, cache it!
					// TODO: Get available memory and only create the action if there's enough memory. Otherwise, move something out of memory to make room for it (and stream the moved thing back in when it's needed).
					if (Has_Cached_Action_By_UUID (uuid_buffer) == FALSE) {
						Action *action = Create_Action (uuid_buffer); // Create the action then cache it
						result = Cache_Action (action); // Add the action to the local cache!
					} else {
						result = TRUE; // The action construct already exists in the cache. There's no need to create it!

					}
				}
			}

		} else if (strncmp (token, "start", strlen ("start")) == 0) {

			if ((status = Get_Token (message_content, token, 1)) != NULL) {

				// i.e., "start event <event-uuid> [at <index> [on <timeline-uuid>]]"

				if (strncmp (token, "event", strlen ("event")) == 0) {

					if (token_count == 3) {

						// i.e., "start event <uuid>"

						// Get UUID (parameter index 2)
						status = Get_Token (message_content, uuid_buffer, 2);

						// Send message to sender to acknowledge receipt
						Send_Acknowledgment (token, message_content);

						// Delete the message
						Delete_Message (message);

						// Check if the action is already in the cache. If nay, cache it!
						// TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
//						if (Has_Cached_Action_By_UUID (uuid_buffer) == TRUE) {
//							Event *event = Get_Cached_Action_By_UUID (uuid_buffer);
						Event *event = Create_Event (uuid_buffer, NULL, NULL);
						if (event != NULL) {
							Add_Event (timeline, event);
							result = TRUE;
						} else {
							result = FALSE;
						}
//						} else {
//							result = FALSE;
//						}

					} else if (token_count > 3) {

						// i.e., "start event <event-uuid> at <index>"

						// Extract parameters
						status = Get_Token (message_content, uuid_buffer, 2); // Get UUID of action being added (parameter index 2)
						status = Get_Token (message_content, uuid_buffer2, 4); // Get UUID of action already on the loop (parameter index 4)

						// Send message to sender to acknowledge receipt
						Send_Acknowledgment (token, message_content);

						// Delete the message
						Delete_Message (message);

						// Check if the action is already in the cache. If nay, cache it!
						// TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
//						if (Has_Cached_Action_By_UUID (uuid_buffer) == TRUE && Has_Cached_Action_By_UUID (uuid_buffer2) == TRUE ) {

						Event *event = Create_Event (uuid_buffer, NULL, NULL);
//							Event *event = Get_Cached_Action_By_UUID (uuid_buffer);
						uint16_t event_index = atoi (uuid_buffer2);
						if (event != NULL) {
							result = Insert_Event (timeline, event, event_index);
//								result = TRUE;
						} else {
							result = FALSE;
						}

//							// Parse the message content and perform the corresponding action operation
//							Action *action = Get_Cached_Action_By_UUID (uuid_buffer);
//							Action *nextAction = Get_Cached_Action_By_UUID (uuid_buffer2);
//							if (action != NULL && nextAction != NULL) {
//								Add_Before_Event (timeline, action, nextAction);
//								result = TRUE;
//							} else {
//
//								// TODO: If action or nextAction are NULL, stream them in over the Internet.
//
//							}

//						} else {
//
//							// TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
//
//							result = FALSE;
//
//						}

					}

				}

			}

		} else if (strncmp (token, "stop", strlen ("stop")) == 0) {

			if ((status = Get_Token (message_content, token, 1)) != NULL) {

				// stop event <event-uuid> [on <timeline-uuid>]
				//      ^
				if (strncmp (token, "event", strlen ("event")) == 0) {

					// Get UUID (parameter index 2)
					status = Get_Token (message_content, uuid_buffer, 2);

					// Send message to sender to acknowledge receipt
					Send_Acknowledgment (token, message_content);

					// Delete the message
					Delete_Message (message);

					// Check if the action is already in the cache. If nay, cache it!
					// TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
					// Parse the message content and perform the corresponding action operation
					if (Has_Event_By_UUID (timeline, uuid_buffer) == TRUE) {
						Event *event = Get_Event_By_UUID (timeline, uuid_buffer);
						if (event != NULL) {
							Remove_Event (timeline, event); // Add the action to the local cache!
							Delete_Event (event);
							result = TRUE;
						}

					} else {

						// TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!

						result = FALSE;

					}

				}

			}

		} else if (strncmp (token, "set", strlen ("set")) == 0) {

			// "set event <event-uuid> action <action-uuid>"
			// "set event <event-uuid> state <state>"

			// TODO: Token_Match (message_content, 1, "event")

			if ((status = Get_Token (message_content, token, 1)) != NULL) {
				if (strncmp (token, "event", strlen ("event")) == 0) {

					if ((status = Get_Token (message_content, token, 3)) != NULL) {
						if (strncmp (token, "action", strlen ("action")) == 0) {

							// i.e., "set event <event-uuid> action <action-uuid>"

							// Extract parameters
							status = Get_Token (message_content, uuid_buffer, 2); // Get UUID of action being added (parameter index 2)
							status = Get_Token (message_content, uuid_buffer2, 4); // Get UUID of action already on the loop (parameter index 4)

							// Send message to sender to acknowledge receipt
							Send_Acknowledgment (token, message_content);

							// Delete the message
							Delete_Message (message);

							// Check if the action is already in the cache. If nay, cache it!
							// TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
							if (Has_Event_By_UUID (timeline, uuid_buffer) == TRUE && Has_Cached_Action_By_UUID (uuid_buffer2) == TRUE) {

								// Get the event with the UUID and assign the action with the UUID.
								Event *event = Get_Event_By_UUID (timeline, uuid_buffer);
								Action *action = Get_Cached_Action_By_UUID (uuid_buffer2);
								if (event != NULL && action != NULL) {
									(*event).action = action;
									result = TRUE;
								} else {
									// TODO: If action or nextAction are NULL, stream them in over the Internet.
								}

							} else {
								// TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
								result = FALSE;
							}

						} else if (strncmp (token, "state", strlen ("state")) == 0) {

							// i.e., "set event <event-uuid> action <action-uuid>"

							// Extract parameters
							status = Get_Token (message_content, uuid_buffer, 2); // Get UUID of action (parameter index 2)
							status = Get_Token (message_content, uuid_buffer2, 4); // Get state of action (parameter index 4)

							// Send message to sender to acknowledge receipt
							Send_Acknowledgment (token, message_content);

							// Delete the message
							Delete_Message (message);

							// Check if the action is already in the cache. If nay, cache it!
							// TODO: Only call either Get_Cached_Action_By_UUID. Don't call both Has_Cached_Action_By_UUID and Get_Cached_Action_By_UUID. They do the same search work. Don't search multiple times for no reason during action construct recall!
							if (Has_Event_By_UUID (timeline, uuid_buffer) == TRUE) {

								// Get the event with the UUID and assign the action with the UUID.
								Event *event = Get_Event_By_UUID (timeline, uuid_buffer);
//								Action *action = Get_Cached_Action_By_UUID (uuid_buffer2);
								if (event != NULL) {
									Set_Event_State (event, uuid_buffer2);
									result = TRUE;
								} else {
									// TODO: If action or nextAction are NULL, stream them in over the Internet.
								}

							} else {
								// TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
								result = FALSE;
							}

						}
					}
				}
			}

		} else if (strncmp (token, "reset", strlen ("reset")) == 0) {

			// HACK: Remove the "reset" command. This is used for testing!

			// Reset the device
			Reset_Device ();

			// Send message to sender to acknowledge receipt
			Send_Acknowledgment (token, message_content);

			// Delete the message
			Delete_Message (message);

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

void Send_Acknowledgment (char *token, char *messageContent) {

	// Send the acknowledgment (i.e., "got <message-uuid> <message-content>")
	sprintf (token, "got %s\n", messageContent);

	// Queue the outgoing acknowledgment message!
	Message *responseMessage;

	responseMessage = Create_Message (token);
	Set_Message_Type (responseMessage, "UDP");
	Set_Message_Destination (responseMessage, "10.0.0.255:4445"); // <HACK />
	Queue_Message (&outgoingMessageQueue, responseMessage);

	responseMessage = Create_Message (token);
	Set_Message_Type (responseMessage, "UDP");
	Set_Message_Destination (responseMessage, "10.0.0.255:4445"); // <HACK />
	Queue_Message (&outgoingMessageQueue, responseMessage);

	responseMessage = Create_Message (token);
	Set_Message_Type (responseMessage, "UDP");
	Set_Message_Destination (responseMessage, "10.0.0.255:4445"); // <HACK />
	Queue_Message (&outgoingMessageQueue, responseMessage);

	responseMessage = Create_Message (token);
	Set_Message_Type (responseMessage, "UDP");
	Set_Message_Destination (responseMessage, "10.0.0.255:4445"); // <HACK />
	Queue_Message (&outgoingMessageQueue, responseMessage);
}
