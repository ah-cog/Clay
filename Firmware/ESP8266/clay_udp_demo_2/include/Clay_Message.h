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
extern uint32 FillBufferWithMessage(Clay_Message * Source, uint8* Destination, uint32 SourceLength);
extern uint32 CreateMessageFromBuffer(uint8 * Source, uint32 SourceLength, Clay_Message * Destination);
extern void Message_Conversion_Test();

#endif /* INCLUDE_CLAY_MESSAGE_H_ */
