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

////Typedefs  /////////////////////////////////////////////////////
typedef struct
{
      uint8 Message[512];
      uint16 Length;
      struct sockaddr_in Source;
} Clay_Message;

////Globals   /////////////////////////////////////////////////////
extern char Terminator;

////Prototypes/////////////////////////////////////////////////////

#endif /* INCLUDE_CLAY_MESSAGE_H_ */
