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

#include "Clay_Message.h"
#include "Clay_Config.h"

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
char Terminator = '\n';
uint8 messageTypeTempStr[CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH];

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
uint32 Serialize_Address(struct sockaddr_in * Source, uint8* Destination,
		uint32 DestinationLength, Message_Type ConnectionType)
{
	///TODO: add connection type bool

	uint32 rval = 0;

	uint8 * ntoaBuf = inet_ntoa(Source->sin_addr); //the buffer gets overwritten by subsequent calls.
	uint8 connectionTypeStr[CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH];

	if (Get_Message_Type_Str(ConnectionType, connectionTypeStr))
	{
		//+ 2 for the terminating '!' and null, +3 for 1 comma and 1 colon
		rval = strlen(ntoaBuf) + 2 + 3 + strlen(connectionTypeStr) + 5;

		if (rval <= DestinationLength)
		{
			rval = snprintf(Destination, DestinationLength, "%s,%s:%d!",
					connectionTypeStr, ntoaBuf, ntohs(Source->sin_port));
		}

		if (rval > DestinationLength)
		{
			rval = -1;
		}
	}

	return rval;
}

void Deserialize_Address(uint8* Source, uint32 SourceLength,
		struct sockaddr_in * Destination, Message_Type *type)
{
	char Comma = ',';
	char Colon = ':';
	char Bang = '!';

	memset(Destination, 0, sizeof(*Destination));

	//get the string off the front
	uint8* typeStart = strtok(Source, &Comma);
	uint8* ipStart = strtok(NULL, &Colon);
	uint8* portStart = strtok(NULL, &Bang);

	*type = Get_Message_Type_From_Str(typeStart);

	inet_aton(ipStart, &(Destination->sin_addr));
	Destination->sin_port = htons(atoi(portStart));

	Destination->sin_family = AF_INET;
	Destination->sin_len = sizeof(*Destination);
}

bool Get_Message_Type_Str(Message_Type type, uint8 *returnStr)
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

Message_Type Get_Message_Type_From_Str(uint8*typeString)
{
	Message_Type rval = MESSAGE_TYPE_MAX;

	int i;
	for (i = 0; i < MESSAGE_TYPE_MAX; ++i)
	{
		if (strcmp(typeString, Message_Strings[i]) == 0)
		{
			rval = (Message_Type) i;
		}
	}

	return rval;
}

////Local implementations /////////////////////////////////////////
