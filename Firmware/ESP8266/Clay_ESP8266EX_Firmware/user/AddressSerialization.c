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

////Local vars/////////////////////////////////////////////////////
static uint8 message_type_temp_str[CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH];
static uint8 deserialize_temp_str[50];

static const char* type_delim = ",";
static const char* port_delim = ":";

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
uint32 ICACHE_RODATA_ATTR Serialize_Address(struct sockaddr_in * Source,
		uint8* Destination, uint32 DestinationLength,
		Message_Type ConnectionType)
{
	uint32 rval = 0;

	uint8 * ntoaBuf = inet_ntoa(Source->sin_addr.s_addr); //the buffer gets overwritten by subsequent calls.
	uint8 connectionTypeStr[CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH];

	if (Get_Message_Type_Str(ConnectionType, connectionTypeStr))
	{
		//+ 2 for AddressTerminator and null, +3 for 1 comma and 1 colon
		rval = strlen(ntoaBuf) + 2 + 3 + strlen(connectionTypeStr) + 5;

		if (rval <= DestinationLength)
		{
			rval = snprintf(Destination, DestinationLength, "%s%s%s%s%d%s\n",
					connectionTypeStr, type_delim, ntoaBuf, port_delim,
					ntohs(Source->sin_port), address_terminator);
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

	//get the string off the front
	uint8* typeStart = strtok(deserialize_temp_str, type_delim);
	uint8* ipStart = strtok(NULL, port_delim);
	uint8* portStart = strtok(NULL, address_terminator);

	if (typeStart != NULL)
	{
		*type = Get_Message_Type_From_Str(typeStart);
	}

	if (ipStart != NULL)
	{
		inet_aton(ipStart, &(Destination->sin_addr));
	}

	if (portStart != NULL)
	{
		Destination->sin_port = htons(atoi(portStart));
	}

	if (ipStart != NULL && portStart != NULL)
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
