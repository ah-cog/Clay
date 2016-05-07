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
#include "CRC16.h"

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
uint8_t* message_type_strings[] = { "udp", "tcp", "command", "status", "http", "invalid" };

uint8_t* content_type_strings[] = { "text", "bin", "invalid" };

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

   //we only have 5 chars for size.
   if (destination_max_length > 99999) return 0;

   uint32_t rval = 0;
   uint16_t message_checksum = 0;

   //format: \f<type>\t<source>\t<destination>\t<content_type>\t<content_length>\t<content>

   //HACK: Padding added because it seems to lessen the likelihood that we miss the end of a message.
   rval = snprintf(destination_string, destination_max_length, "  %s%05d%s%05d%s%s%s%s%s%s%s%d%s%s%s%d%s",     //
                   message_start,     //
                   0,     //placeholder for length. we pad out 5 bytes. TCP frames go up to 1500 bytes, jumbo frames up to 9000. We'd need to tack on > 90k of header to need another figure, which seems unlikely.
                   message_field_delimiter,
                   0,     //placeholder for checksum. we pad out 5 bytes for this, too. This is enough space for a CRC16, which will be <= 65535
                   message_field_delimiter,
                   message->message_type,
                   message_field_delimiter,
                   message->source,
                   message_field_delimiter,
                   message->destination,
                   message_field_delimiter,
                   message->content_length,
                   message_field_delimiter,
                   message->content_type,
                   message_field_delimiter,
                   message->content_checksum,
                   message_field_delimiter);

   if ((rval) + message->content_length <= destination_max_length) {

      memcpy(destination_string + rval, message->content, message->content_length);
      rval += message->content_length;

      sprintf(destination_string + 3, "%05d", rval);     //write the length after the first char (plus 2 for the padding)
      destination_string[8] = *message_field_delimiter;     //put our delimiter back.

      //TODO: checksum the message starting at index 15 (the character after the second \t)
      message_checksum = Calculate_Checksum_On_Bytes(destination_string + 15, rval - 15);

      sprintf(destination_string + 9, "%05d", message_checksum);     //write the checksum after the delimiter between the length and checksum.
      destination_string[14] = *message_field_delimiter;     //put our delimiter back.


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
   return rval;
}
