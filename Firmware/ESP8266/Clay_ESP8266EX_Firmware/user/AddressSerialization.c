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
const char * address_terminator = "\x12";
const char * address_delimiter = ";";

////Local vars/////////////////////////////////////////////////////
static uint8 deserialize_temp_str[50];

static const char* type_delim = ",";
static const char* port_delim = ":";

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
uint32 ICACHE_RODATA_ATTR Serialize_Address(in_addr_t source, int32 port,
		uint8* Destination, uint32 DestinationLength,
		Message_Type ConnectionType)
{
	uint32 rval = 0;

	uint8 * ntoaBuf = inet_ntoa(source); //the buffer gets overwritten by subsequent calls.
	char connectionTypeStr[CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH];

	if (ConnectionType == MESSAGE_TYPE_MAX
			|| Get_Message_Type_Str(ConnectionType, connectionTypeStr))
	{
		//+ 2 for AddressTerminator and null, +3 for 1 comma and 1 colon
		rval = strlen(ntoaBuf) + 2 + 3 + strlen(connectionTypeStr) + 5;

		if (rval <= DestinationLength)
		{
			rval =
					snprintf(Destination, DestinationLength, "%s%s%s%s%d%s\n",
							(ConnectionType == MESSAGE_TYPE_MAX ?
									"" : connectionTypeStr),
							(ConnectionType == MESSAGE_TYPE_MAX ?
									"" : type_delim), ntoaBuf, port_delim, port,
							address_terminator);
		}

		if (rval > DestinationLength)
		{
			rval = -1;
		}
	}

	return rval;
}

void ICACHE_RODATA_ATTR Deserialize_Address(uint8* Source,
		struct sockaddr_in * Destination, Message_Type *type)
{
	memset(Destination, 0, sizeof(*Destination));

	strcpy(deserialize_temp_str, Source);

	taskENTER_CRITICAL();
	uint8* type_start = strtok(deserialize_temp_str, type_delim);
	uint8* ip_start = strtok(NULL, port_delim);
	uint8* port_start = strtok(NULL, address_terminator);
	taskEXIT_CRITICAL();

	if (type_start != NULL)
	{
		*type = Get_Message_Type_From_Str(type_start);
	}

	if (ip_start != NULL)
	{
		inet_aton(ip_start, &(Destination->sin_addr));
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
		strncpy(returnStr, Message_Strings[type],
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
		if (strstr(typeString, Message_Strings[i]) != NULL)
		{
			rval = (Message_Type) i;
			break;
		}
	}

	return rval;
}

////Local implementations /////////////////////////////////////////
