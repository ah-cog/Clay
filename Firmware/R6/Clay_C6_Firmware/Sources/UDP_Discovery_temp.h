/*
 * UDP_Discovery_temp.h
 *
 *  Created on: May 14, 2016
 *      Author: thebh_000
 */

#ifndef SOURCES_UDP_DISCOVERY_TEMP_H_
#define SOURCES_UDP_DISCOVERY_TEMP_H_

////Includes //////////////////////////////////////////////////////
#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#include "PE_Types.h"
#include "UDP_Discovery_temp.h"
#include "Message.h"
#include "clayString.h"
#include "UUID.h"
#include "Action.h"

////Macros ////////////////////////////////////////////////////////
#define MODULE_DISCOVERY_COUNT   10

////Typedefs  /////////////////////////////////////////////////////
typedef struct
{
      bool allocated;
      char uuid[DEFAULT_UUID_LENGTH];
      char address[100];
} remote_clay_module;

////Globals   /////////////////////////////////////////////////////
extern remote_clay_module discovered_modules[];
extern char broadcast_address_module[];

////Function Prototypes ///////////////////////////////////////////
extern int8_t Find_Uuid_In_Discovered_Modules(char * uuid_buffer);
extern int8_t Process_Module_Announce_Message(Message * message);
extern remote_clay_module* Get_Device_By_UUID (char *uuid);
extern int8_t Check_For_Discovery_Message(Message*message);
extern void Discovery_Broadcast_Presence_4446();

#endif /* SOURCES_UDP_DISCOVERY_TEMP_H_ */
