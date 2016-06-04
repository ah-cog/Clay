/*
 * UDP_Discovery_temp.c
 *
 *  Created on: May 14, 2016
 *      Author: thebh_000
 */

//hack library
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//This library was created to keep track of remote clay modules
//     by recording incoming udp discovery messages. It is meant
//     to be a temporary workaround for not having mesh working
//     reliably.
//
//References to this file are in message_processor.c and application.c
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
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
#define FIRST_PARAMETER  0
#define SECOND_PARAMETER 1
#define THIRD_PARAMETER  2
#define FOURTH_PARAMETER 3
#define FIFTH_PARAMETER  4
#define SIXTH_PARAMETER  5

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
remote_clay_module discovered_modules[MODULE_DISCOVERY_COUNT] = { 0, 0, 0 };
char broadcast_address_module[32];

////Local vars/////////////////////////////////////////////////////
static char uuid_buffer[DEFAULT_UUID_LENGTH] = { 0 };
static char uuid_buffer2[512] = { 0 };     // char uuid_buffer2[DEFAULT_UUID_LENGTH] = { 0 };
static char state_buffer[MAXIMUM_GRAMMAR_SYMBOL_LENGTH] = { 0 };
static char buffer2[128] = { 0 };

////Local Prototypes///////////////////////////////////////////////
static uint8_t Message_Content_Parameter_Equals(Message *message, int token_index, const char *pattern);

////Global implementations ////////////////////////////////////////
int8_t Check_For_Discovery_Message(Message*message) {

   int8_t result = FALSE;

   //look for announce messages from other clay modules.
   if (strncmp((*message).message_type, "udp", strlen("udp")) == 0
       && Message_Content_Parameter_Equals(message, FIRST_PARAMETER, "announce")
       && Message_Content_Parameter_Equals(message, SECOND_PARAMETER, "device")) {
      result = Process_Module_Announce_Message(message);
   }

   return result;
}

int8_t Find_Uuid_In_Discovered_Modules(char * uuid_buffer) {

   int8_t result = -1;

   for (int i = 0; i < MODULE_DISCOVERY_COUNT; ++i) {
      if (discovered_modules[i].allocated && strcmp(discovered_modules[i].uuid, uuid_buffer) == 0) {
         result = i;
         break;
      }
   }

   return result;
}

remote_clay_module* Get_Device_By_UUID(char *uuid) {

   for (int i = 0; i < MODULE_DISCOVERY_COUNT; ++i) {
      if (discovered_modules[i].allocated && strcmp(discovered_modules[i].uuid, uuid) == 0) {
         return &discovered_modules[i];
         break;
      }
   }

   return NULL;
}

static char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

int8_t Process_Module_Announce_Message(Message * message) {

   //announce device <module_uuid>

   int8_t status = FALSE;
   int8_t result = FALSE;

   char *message_content = (*message).content;

   status = Get_Token(message_content, uuid_buffer, 2);     // get the uuid.

   //if we haven't already found this module, add it
   if (Find_Uuid_In_Discovered_Modules(uuid_buffer) == -1) {

      int free_module = 0;
      for (; free_module < MODULE_DISCOVERY_COUNT; ++free_module) {
         if (!discovered_modules[free_module].allocated) {
            result = TRUE;
            break;
         }
      }

      if (result) {
         discovered_modules[free_module].allocated = TRUE;
         sprintf(discovered_modules[free_module].address, (*message).source);
         sprintf(discovered_modules[free_module].uuid, uuid_buffer);
      }
   } else {
      //TODO: record last time we heard from the module in the remote_clay_module struct.
      result = TRUE;
   }

   return result;
}

void Discovery_Broadcast_Presence_4446() {     // Queue device discovery broadcast
   char *uuid = Get_Unit_UUID();
   sprintf(buffer2, "announce device %s", uuid);
   Message *broadcastMessage = Create_Message();
   Set_Message_Type(broadcastMessage, "udp");
   Set_Message_Source(broadcastMessage, broadcast_address_module);
   Set_Message_Destination(broadcastMessage, broadcast_address_module);
   Set_Message_Content(broadcastMessage, buffer2, strlen(buffer2));
   Set_Message_Content_Type(broadcastMessage, "text");

   Queue_Message(&outgoingMessageQueue, broadcastMessage);
}

uint8_t Get_Module_Count() {
   uint8_t result = 0;

   for (int i = 0; i < MODULE_DISCOVERY_COUNT; ++i) {
      if (discovered_modules[i].allocated) {
         ++result;
      }
   }

   return result;
}

////Local implementations /////////////////////////////////////////

//TODO: can we commonize this with the token array above?
static char token_param_equals[MAXIMUM_MESSAGE_LENGTH] = { 0 };

static uint8_t Message_Content_Parameter_Equals(Message *message, int token_index, const char *pattern) {
   int8_t status = NULL;
   int8_t result = NULL;
   char *message_content = (*message).content;

   if ((status = Get_Token(message_content, token_param_equals, token_index)) != 0) {
      if (strncmp(token_param_equals, pattern, strlen(pattern)) == 0) {
         return TRUE;
      }
   }
   return FALSE;
}
