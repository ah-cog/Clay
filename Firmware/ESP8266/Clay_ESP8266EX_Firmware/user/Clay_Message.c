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

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
uint32 Fill_Buffer_With_Message(Clay_Message * Source, uint8 * Destination,
		uint32 DestinationLength)
{
	uint32 rval = 0;
	strncpy(Destination, Source->Message, Source->Length);
	rval += Source->Length;

	rval += Serialize_Address(&(Source->Address), Destination + rval,
			DestinationLength - rval);

	//add on the addr

	return rval;
}

uint32 Serialize_Address(struct sockaddr_in * Source, uint8* Destination,
		uint32 DestinationLength)
{
	uint32 rval = 0;
	rval += snprintf(Destination + rval, DestinationLength - rval,
			"%u,%u,%u,%u", ntohl(Source->sin_addr.s_addr), Source->sin_family,
			Source->sin_len, ntohs(Source->sin_port));

//   printf("dest pre array: [%s]\n", Destination);

	if (rval <= DestinationLength + SIN_ZERO_LEN)
	{
		int i;
		for (i = 0; i < SIN_ZERO_LEN; ++i)
		{
			rval += snprintf(Destination + rval, DestinationLength - rval,
					"%s%u", i < SIN_ZERO_LEN ? "," : "", Source->sin_zero[i]);
			if (rval >= DestinationLength)
			{
//            printf("rval too long\n");
				Destination[DestinationLength - 1] = '!';
				rval = DestinationLength;
				break;
			}
		}
		if (rval < DestinationLength)
		{
			Destination[rval] = '!';
		}
	}
//   printf("dest final: [%s]\n", Destination);
}

void Deserialize_Address(uint8* Source, uint32 SourceLength,
		struct sockaddr_in * Destination)
{
	uint8 * token;
	char Comma = ',';
	uint32 temp;

//   printf("tryna toke\n");
	token = strtok(Source, &Comma);
//   printf("s_addr [%s]\n", token);
	sscanf(token, "%d", &temp);
	Destination->sin_addr.s_addr = htonl(temp);

	token = strtok(NULL, &Comma);
	sscanf(token, "%d", &temp);
//   printf("family [%s]\n", token);
	Destination->sin_family = temp & 0xFF;

	token = strtok(NULL, &Comma);
	sscanf(token, "%d", &temp);
//   printf("len [%s]\n", token);
	Destination->sin_len = temp & 0xFF;

	token = strtok(NULL, &Comma);
	sscanf(token, "%d", &temp);
//   printf("port [%s]\n", token);
	Destination->sin_port = htons(temp & 0xFFFF);

	int i;
	for (i = 0; i < SIN_ZERO_LEN && token != NULL; ++i)
	{
		token = strtok(NULL, &Comma);
//      printf("zero[%d] [%s]\n", i, token);
		sscanf(token, "%d", &temp);
		Destination->sin_zero[i] = temp & 0xFF;
	}
}

uint32 Create_Message_From_Buffer(uint8 * Source, uint32 SourceLength,
		Clay_Message * Destination)
{
	uint32 rval = 0;

	uint8 * NewlineIndex = strchr(Source, '\n') + 1;
	Destination->Length = NewlineIndex - Source;
	memcpy(Destination->Message, Source, Destination->Length);

	Deserialize_Address(NewlineIndex + 1, SourceLength - Destination->Length,
			&(Destination->Address));

	if (Destination->Length >= CLAY_MESSAGE_LENGTH_MAX_BYTES)
	{
		Destination->Message[CLAY_MESSAGE_LENGTH_MAX_BYTES - 1] = '\n';
	}

	return rval;
}

void Message_Conversion_Test()
{
	Clay_Message m;
	m.Length = 10;
	int i;
	for (i = 0; i < m.Length - 1; ++i)
	{
		m.Message[i] = 'h';
	}

	m.Message[i] = '\n';
	m.Message[i + 1] = '\0';

	m.Address.sin_addr.s_addr = 0x55;
	m.Address.sin_len = 0;
	m.Address.sin_port = 0;

	uint32 bufferFillLength;
	uint32 messageFillLength;
	char sinZeroStr[50];
	char sinZeroSize;

	uint8 buf[CLAY_MESSAGE_STRUCT_SIZE_BYTES * 2];

	for (;;)
	{
		sinZeroSize = 0;
		for (i = 0; i < SIN_ZERO_LEN; ++i)
		{
			sinZeroSize += sprintf(sinZeroStr + sinZeroSize, "%s%d",
					((i == 8 || i == 0) ? "" : ","), m.Address.sin_zero[i]);
			m.Address.sin_zero[i] = m.Address.sin_addr.s_addr + i;
		}

		bufferFillLength = Fill_Buffer_With_Message(&m, buf,
		CLAY_MESSAGE_STRUCT_SIZE_BYTES * 2);

		m.Message[m.Length + 1] = '\0';
		printf(
				"bfl: %d,len: %d msg: %s, addr: %d, fam: %d, len: %d, port: %d, zero: %s\n",
				messageFillLength, m.Length, m.Message,
				m.Address.sin_addr.s_addr, m.Address.sin_family,
				m.Address.sin_len, m.Address.sin_port, sinZeroStr);

		printf("len: %d, buf: %s]\n\n", bufferFillLength, buf);

		++m.Address.sin_addr.s_addr;
		m.Message[0] = 'N';

		messageFillLength = Create_Message_From_Buffer(buf,
		CLAY_MESSAGE_STRUCT_SIZE_BYTES * 2, &m);
	}
}
////Local implementations /////////////////////////////////////////

