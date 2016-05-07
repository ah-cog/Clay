/*
 * AddressSerialization.h
 *
 *  Created on: Mar 2, 2016
 *      Author: thebh_000
 */

#ifndef MESSAGE_INFO_H_
#define MESSAGE_INFO_H_

#include "stdint.h"
#include "Message.h"

////defines ///////////////////////////////////////////////////////
#define CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH     16

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	MESSAGE_TYPE_UDP,
	MESSAGE_TYPE_TCP,
	MESSAGE_TYPE_COMMAND,
	MESSAGE_TYPE_STATUS,
	MESSAGE_TYPE_HTTP,
	MESSAGE_TYPE_MAX
} Message_Type;

typedef enum
{
	CONTENT_TYPE_TEXT,
	CONTENT_TYPE_BINARY,
	CONTENT_TYPE_MAX
} Content_Type;

////Globals   /////////////////////////////////////////////////////
extern char* message_strings[];
extern const char * message_start;
extern const char * message_field_delimiter;
extern const char * message_end;
extern const char * arg_delimiter;

////Prototypes/////////////////////////////////////////////////////
extern bool Get_Message_Type_Str(Message_Type type, char * returnStr);
extern Message_Type Get_Message_Type_From_Str(char * typeString);
extern Message * Deserialize_Message(uint8_t * message);
extern uint32_t Serialize_Message(Message * message, uint8_t * destination_string, uint32_t destination_max_length);

#endif /* MESSAGE_INFO_H_*/
