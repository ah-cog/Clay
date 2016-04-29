/*
 * Clay_Message.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 */

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"
#include "string.h"

#include "lwip/sockets.h"

#include "../include/AddressSerialization.h"
#include "Clay_Config.h"

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
const char * http_uri_delimiter_fs = "/";
const char * http_uri_delimiter_bs = "\\";
const char * address_terminator = "\x12";
const char * address_delimiter = ";";
const char* type_delimiter = ",";
const char * message_delimiter = "\n";
const char* port_delimiter = ":";

const char * message_start = "\f";
const char * message_field_delimiter = "\t";
const char * message_end = "\n";

////Local vars/////////////////////////////////////////////////////
static uint8 deserialize_temp_str[50];

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
uint32 ICACHE_RODATA_ATTR Serialize_Address(in_addr_t source, int32 port,
		uint8* Destination, uint32 DestinationLength)
{
	uint32 rval = 0;
	uint8 * ntoaBuf = inet_ntoa(source); //the buffer gets overwritten by subsequent calls.

	rval = snprintf(Destination, DestinationLength, "%s%s%d", ntoaBuf,
			port_delimiter, port);

	if (rval > DestinationLength)
	{
		rval = -1;
	}

	return rval;
}

void ICACHE_RODATA_ATTR Deserialize_Address(uint8* Source,
		struct sockaddr_in * Destination, Message_Type *type)
{
	uint8 port_str[5];
	memset(Destination, 0, sizeof(*Destination));

	strcpy(deserialize_temp_str, Source);

	taskENTER_CRITICAL();
	uint8* ip_start = strtok(deserialize_temp_str, port_delimiter);
	uint8* port_start = strtok(NULL, address_terminator);

	//look for the start of a URI. we just need there to be
	//	a null immediately after the port so we can use atoi.
	uint8* uri_start = strtok(NULL, http_uri_delimiter_fs);
	if (uri_start == NULL)
	{
		uri_start = strtok(port_start, http_uri_delimiter_bs);
	}
	taskEXIT_CRITICAL();

	if (ip_start != NULL)
	{
		inet_aton(ip_start, &(Destination->sin_addr.s_addr));
	}

	if (port_start != NULL)
	{
		Destination->sin_port = htons(atoi(port_start));
	}

	if (ip_start != NULL && port_start != NULL)
	{
		Destination->sin_family = AF_INET;
		Destination->sin_len = sizeof(*Destination);
	}
}

bool ICACHE_RODATA_ATTR Get_Message_Type_Str(Message_Type type,
		uint8 *returnStr)
{
	bool rval = false;

	if (type < MESSAGE_TYPE_MAX)
	{
		strncpy(returnStr, message_type_strings[type],
		CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH);
		rval = true;
	}

	return rval;
}

Message_Type ICACHE_RODATA_ATTR Get_Message_Type_From_Str(uint8*typeString)
{
	Message_Type rval = MESSAGE_TYPE_MAX;

	int i;
	for (i = 0; i < MESSAGE_TYPE_MAX; ++i)
	{
		if (strstr(typeString, message_type_strings[i]) != NULL)
		{
			rval = (Message_Type) i;
			break;
		}
	}

	return rval;
}

////Local implementations /////////////////////////////////////////
