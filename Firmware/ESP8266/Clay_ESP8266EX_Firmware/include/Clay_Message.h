/*
 * Clay_Message.h
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 */

#ifndef INCLUDE_CLAY_MESSAGE_H_
#define INCLUDE_CLAY_MESSAGE_H_
////Includes //////////////////////////////////////////////////////
#include "esp_common.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "Clay_Config.h"

////Typedefs  /////////////////////////////////////////////////////
typedef struct
{
	uint8 Message[CLAY_MESSAGE_LENGTH_MAX_BYTES];
	uint32 Length;
	struct sockaddr_in Address;
	//size is CLAY_MESSAGE_LENGTH_MAX_BYTES + sizeof(uint32) + sizeof(sockaddr)
	//    Keep the #define in Clay_Config up to date!
} Clay_Message;

////Globals   /////////////////////////////////////////////////////
extern char Terminator;

////Prototypes/////////////////////////////////////////////////////
extern void Deserialize_Address(uint8* Source, uint32 SourceLength,
		struct sockaddr_in * Destination, Message_Type *type);
extern uint32 Serialize_Address(struct sockaddr_in * Source, uint8* Destination,
		uint32 DestinationLength, Message_Type ConnectionTypeStr);
bool Get_Message_Type_Str(Message_Type type, uint8 *returnStr);
Message_Type Get_Message_Type_From_Str(uint8*typeString);
#endif /* INCLUDE_CLAY_MESSAGE_H_ */
