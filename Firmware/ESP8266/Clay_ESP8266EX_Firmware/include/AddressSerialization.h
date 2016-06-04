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

#include "Wifi_Message_Serialization.h"
#include "Clay_Config.h"

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
extern const char * http_uri_delimiter_fs;
extern const char * http_uri_delimiter_bs;
extern const char * address_terminator;
extern const char * address_delimiter;
extern const char * type_delimiter;
extern const char * message_delimiter;
extern const char * port_delimiter;


////Prototypes/////////////////////////////////////////////////////
extern void Deserialize_Address(uint8* Source, struct sockaddr_in * Destination,
		Message_Type *type);

uint32 ICACHE_RODATA_ATTR Serialize_Address(in_addr_t source, int32 port,
		uint8* Destination, uint32 DestinationLength);
#endif /* INCLUDE_ADDRESSSERIALIZATION_H_ */
