/*
 * AddressSerialization.c
 *
 *  Created on: Mar 2, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"
#include "Wifi_Message_Serialization.h"
#include "Message.h"

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
char * message_strings[] = { "udp", "tcp", "command", "status", "invalid" };

const char * message_start = "\f";
const char * message_field_delimiter = "\t";
const char * message_end = "\n";
const char * arg_delimiter = ",";

////Local vars/////////////////////////////////////////////////////
static uint8_t message_type_temp_str[CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH];

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////

bool Get_Message_Type_Str(Message_Type type, char * returnStr) {
   bool rval = false;

   if (type < MESSAGE_TYPE_MAX) {
      strncpy(returnStr, message_strings[type], CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH);
      rval = true;
   }

   return rval;
}

Message_Type Get_Message_Type_From_Str(char * typeString) {
   Message_Type rval = MESSAGE_TYPE_MAX;

   int i;
   for (i = 0; i < MESSAGE_TYPE_MAX; ++i) {
      if (strcmp(typeString, message_strings[i]) == 0) {
         rval = (Message_Type) i;
      }
   }

   return rval;
}

uint32_t Serialize_Message(Message * message, uint8_t * destination_string, uint32_t destination_max_length) {
   uint32_t rval = 0;

   //format: \f<type>\t<source>\t<destination>\t<content_type>\t<content_length>\t<content>

   //HACK: Padding added because it seems to lessen the likelihood that we miss the end of a message.
   rval = snprintf(destination_string,
                   destination_max_length,
                   "  %s%s%s%s%s%s%s%s%s%s%s  ",
                   message_start,
                   message->type,
                   message_field_delimiter,
                   message->source,
                   message_field_delimiter,
                   message->destination,
                   message_field_delimiter,
                   message->content_type,
                   message_field_delimiter,
                   message->content_length,
                   message_field_delimiter);

   if ((rval) + message->content_length <= destination_max_length) {
      memcpy(destination_string + rval, message->content, message->content_length);
      rval += message->content_length;
   } else {
      rval = 0;
   }

   return rval;
}

//parse a message, including start character.
Message * Deserialize_Message(uint8_t * message) {

   Message * rval = NULL;
   uint32_t content_length;

   //format: \f<type>\t<source>\t<destination>\t<content_type>\t<content_length>\t<content>

   uint8_t * temp_type = strtok(message, message_start);     //throw out the start character
   temp_type = strtok(NULL, message_field_delimiter);
   uint8_t * temp_source_address = strtok(NULL, message_field_delimiter);
   uint8_t * temp_dest_address = strtok(NULL, message_field_delimiter);
   uint8_t * temp_content_type = strtok(NULL, message_field_delimiter);
   uint8_t * temp_content_length = strtok(NULL, message_field_delimiter);
   uint8_t * temp_content = temp_content_length + strlen(temp_content_length) + 1;

   content_length = atoi(temp_content_length);

   if (temp_type != NULL
       && temp_source_address != NULL
       && temp_dest_address != NULL
       && temp_content_type != NULL
       && temp_content_length != NULL
       && temp_content != NULL) {

      rval = Create_Message();

      // Create message object
      Set_Message_Type(rval, temp_type);
      Set_Message_Source(rval, temp_source_address);
      Set_Message_Destination(rval, temp_dest_address);
      Set_Message_Content_Type(rval, temp_content_type);
      Set_Message_Content(rval, temp_content, content_length);
   }
}
