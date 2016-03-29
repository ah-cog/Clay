#include "Message_Processor.h"
#include "Action.h"
#include "Event.h"
#include "Timeline.h"

#define FIRST_PARAMETER  0
#define SECOND_PARAMETER 1
#define THIRD_PARAMETER  2
#define FOURTH_PARAMETER 3
#define FIFTH_PARAMETER  4
#define SIXTH_PARAMETER  5

char uuid_buffer[DEFAULT_UUID_LENGTH] = { 0 };
char uuid_buffer2[512] = { 0 }; // char uuid_buffer2[DEFAULT_UUID_LENGTH] = { 0 };
char state_buffer[MAXIMUM_GRAMMAR_SYMBOL_LENGTH] = { 0 };

static uint8_t Message_Content_Parameter_Equals (Message *message, int token_index, const char *pattern);
static int8_t Process_Cache_Action (Message *message);
static int8_t Process_Start_Event (Message *message);
static int8_t Process_Stop_Event (Message *message);
static int8_t Process_Set_Event_Action (Message *message);
static int8_t Process_Set_Event_State (Message *message);

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

	// TODO: Handle messages from ESP8266:
	// TODO: - INFO,CONNECTED

	if (Message_Content_Parameter_Equals (message, FIRST_PARAMETER, "cache")) {
		if (Message_Content_Parameter_Equals (message, SECOND_PARAMETER, "action")) {
			return Process_Cache_Action (message);
		}
	} else if (Message_Content_Parameter_Equals (message, FIRST_PARAMETER, "start")) {
		if (Message_Content_Parameter_Equals (message, SECOND_PARAMETER, "event")) {
			return Process_Start_Event (message);
		}
	} else if (Message_Content_Parameter_Equals (message, FIRST_PARAMETER, "stop")) {
		if (Message_Content_Parameter_Equals (message, SECOND_PARAMETER, "event")) {
			return Process_Stop_Event (message);
		}
	} else if (Message_Content_Parameter_Equals (message, FIRST_PARAMETER, "set")) {
		if (Message_Content_Parameter_Equals (message, SECOND_PARAMETER, "event")) {
			if (Message_Content_Parameter_Equals (message, FOURTH_PARAMETER, "action")) {
				return Process_Set_Event_Action (message);
			} else if (Message_Content_Parameter_Equals (message, FOURTH_PARAMETER, "state")) {
				return Process_Set_Event_State (message);
			}
		}
	} else {
		Delete_Message (message);
	}

	// TODO: Store message UUID for use in message acknowledgment protocol. If it has been received, then don't apply it again, just send the acknowledgment packet.

	return NULL;
}

int8_t Process_Outgoing_Message (Message *message) {

	int8_t result = NULL;

	if (message != NULL) {

//		// Broadcast_UDP_Message (token, DISCOVERY_BROADCAST_PORT);
//		Send_UDP_Message ((*message).destination, DISCOVERY_BROADCAST_PORT, (*message).content);

		// Send message over Wi-Fi
		result = Wifi_Send (message);

		result = true;

	}

	return result;
}

static uint8_t Message_Content_Parameter_Equals (Message *message, int token_index, const char *pattern) {
	int8_t status = NULL;
	int8_t result = NULL;
	char *message_content = (*message).content;
	char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	if ((status = Get_Token (message_content, token, token_index)) != NULL) {
		if (strncmp (token, pattern, strlen (pattern)) == 0) {
			return true;
		}
	}
	return false;
}

static int8_t Process_Cache_Action (Message *message) {

	int8_t status = NULL;
	int8_t result = NULL;

	char *message_content = NULL;
	char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	message_content = (*message).content;

	// Get UUID (parameter index 2) and command (parenthesized string index 3)
	Get_Token (message_content, uuid_buffer, THIRD_PARAMETER);
//	Get_Token (message_content, state_buffer, FOURTH_PARAMETER);

	// Send message to sender to acknowledge receipt
	Send_Acknowledgment (token, message_content);

	// Delete the message
	Delete_Message (message);

	// Check if the action is already in the cache. If nay, cache it!
	// TODO: Get available memory and only create the action if there's enough memory. Otherwise, move something out of memory to make room for it (and stream the moved thing back in when it's needed).
	if (Has_Cached_Action_By_UUID (uuid_buffer) == false) {
		Action *action = Create_Action (uuid_buffer); // Create the action then cache it
		result = Cache_Action (action); // Add the action to the local cache!
	} else {
		result = true; // The action construct already exists in the cache. There's no need to create it!
	}

	return result;
}

static int8_t Process_Start_Event (Message *message) {

	int8_t status = NULL;
	int8_t result = NULL;

	int token_count = 0;

	char *message_content = (*message).content;
	char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

	token_count = Get_Token_Count (message_content);

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
		//						if (Has_Cached_Action_By_UUID (uuid_buffer) == true) {
		//							Event *event = Get_Cached_Action_By_UUID (uuid_buffer);
		Event *event = Create_Event (uuid_buffer, NULL, NULL);
		if (event != NULL) {
			Add_Event (timeline, event);
			result = true;
		} else {
			result = false;
		}

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
		//						if (Has_Cached_Action_By_UUID (uuid_buffer) == true && Has_Cached_Action_By_UUID (uuid_buffer2) == true ) {

		Event *event = Create_Event (uuid_buffer, NULL, NULL);
//		Event *event = Get_Cached_Action_By_UUID (uuid_buffer);
		uint16_t event_index = atoi (uuid_buffer2);
		if (event != NULL) {
			result = Insert_Event (timeline, event, event_index);
		} else {
			result = false;
		}
	}
	return result;
}

static int8_t Process_Stop_Event (Message *message) {

	int8_t status = NULL;
	int8_t result = NULL;

	int token_count = 0;

	char *message_content = (*message).content;
	char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

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
		if (Has_Event_By_UUID (timeline, uuid_buffer) == true) {
			Event *event = Get_Event_By_UUID (timeline, uuid_buffer);
			if (event != NULL) {
				Remove_Event (timeline, event); // Add the action to the local cache!
				Delete_Event (event);
				result = true;
			}
		} else {
			// TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
			result = false;
		}
	}
	return result;
}

static int8_t Process_Set_Event_Action (Message *message) {

	int8_t status = NULL;
	int8_t result = NULL;

	int token_count = 0;

	char *message_content = (*message).content;
	char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

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
	if (Has_Event_By_UUID (timeline, uuid_buffer) == true && Has_Cached_Action_By_UUID (uuid_buffer2) == true) {

		// Get the event with the UUID and assign the action with the UUID.
		Event *event = Get_Event_By_UUID (timeline, uuid_buffer);
		Action *action = Get_Cached_Action_By_UUID (uuid_buffer2);
		if (event != NULL && action != NULL) {
			(*event).action = action;
			result = true;
		} else {
			// TODO: If action or nextAction are NULL, stream them in over the Internet.
		}
	} else {
		// TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
		result = false;
	}

	return result;
}

static int8_t Process_Set_Event_State (Message *message) {

	int8_t status = NULL;
	int8_t result = NULL;

	int token_count = 0;

	char *message_content = (*message).content;
	char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

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
	if (Has_Event_By_UUID (timeline, uuid_buffer) == true) {

		// Get the event with the UUID and assign the action with the UUID.
		Event *event = Get_Event_By_UUID (timeline, uuid_buffer);
	//	Action *action = Get_Cached_Action_By_UUID (uuid_buffer2);
		if (event != NULL) {
			Set_Event_State (event, uuid_buffer2);
			result = true;
		} else {
			// TODO: If action or nextAction are NULL, stream them in over the Internet.
		}
	} else {
		// TODO: The action is not in the cache! Return response indicating this! Or request it from the cloud!
		result = false;
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
