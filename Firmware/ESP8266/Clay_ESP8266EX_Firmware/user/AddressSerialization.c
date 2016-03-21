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
const char * AddressTerminator = "\022";

////Local vars/////////////////////////////////////////////////////
static uint8 messageTypeTempStr[CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH];
static uint8 deserializeTempStr[50];

static const char* TypeDelim = ",";
static const char* PortDelim = ":";

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
			rval = snprintf(Destination, DestinationLength, "%s,%s:%d%c\n",
					connectionTypeStr, ntoaBuf, ntohs(Source->sin_port),
					AddressTerminator);
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

	strcpy(deserializeTempStr, Source);

	//get the string off the front
	uint8* typeStart = strtok(deserializeTempStr, TypeDelim);
	uint8* ipStart = strtok(NULL, PortDelim);
	uint8* portStart = strtok(NULL, AddressTerminator);

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
