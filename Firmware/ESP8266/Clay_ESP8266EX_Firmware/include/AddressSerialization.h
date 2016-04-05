/*
 * Clay_Message.h
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 */

#ifndef INCLUDE_ADDRESSSERIALIZATION_H_
#define INCLUDE_ADDRESSSERIALIZATION_H_
////Includes //////////////////////////////////////////////////////
#include "esp_common.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "Clay_Config.h"

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
extern const char * address_terminator;
extern const char * address_delimiter;
extern const char * type_delimiter;
extern const char * message_delimiter;
extern const char * port_delimiter;

const char * message_start;
const char * message_field_delimiter;
const char * message_end;

////Prototypes/////////////////////////////////////////////////////
extern void Deserialize_Address(uint8* Source, struct sockaddr_in * Destination,
		Message_Type *type);

uint32 ICACHE_RODATA_ATTR Serialize_Address(in_addr_t source, int32 port,
		uint8* Destination, uint32 DestinationLength);

bool Get_Message_Type_Str(Message_Type type, uint8 *returnStr);
Message_Type Get_Message_Type_From_Str(uint8*typeString);
#endif /* INCLUDE_ADDRESSSERIALIZATION_H_ */
