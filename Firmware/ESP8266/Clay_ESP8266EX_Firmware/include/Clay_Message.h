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
extern uint32 Fill_Buffer_With_Message(Clay_Message * Source, uint8* Destination, uint32 SourceLength);
extern uint32 Create_Message_From_Buffer(uint8 * Source, uint32 SourceLength, Clay_Message * Destination);
extern uint32 Serialize_Address(struct sockaddr_in * Source, uint8* Destination, uint32 DestinationLength);
extern void Deserialize_Address(uint8* Source, uint32 SourceLength, struct sockaddr_in * Destination);
extern void Message_Conversion_Test();

#endif /* INCLUDE_CLAY_MESSAGE_H_ */
