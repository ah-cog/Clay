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

uint32_t Serialize_Message_With_Message_Header(Message * message, uint8_t * destination_string, uint32_t destination_max_length) {

   if (message == NULL || destination_string == NULL) return 0;

   uint32_t rval = 0;
   uint16_t message_checksum = 0;

   //         0                 1                   2               3         4              5                 6                   7               8
   //format: \f<message_length>\t<message_checksum>\t<message_type>\ t<source>\t<destination>\t<content_length>\t<content_checksum>\t<content_type>\t<content>

   rval = snprintf(destination_string, destination_max_length, "%s%05d%s%05d%s%s%s%s%s%s%s%d%s%d%s%s%s",     //
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
                   message->content_checksum,
                   message_field_delimiter,
                   message->content_type,
                   message_field_delimiter);

   if ((rval) + message->content_length <= destination_max_length) {

      memcpy(destination_string + rval, message->content, message->content_length);
      rval += message->content_length;

      sprintf(destination_string + 1, "%05d", rval);     //write the length after the first char (+ 1 for the delimiter.)
      destination_string[6] = *message_field_delimiter;     //put our delimiter back.

      message_checksum = Calculate_Checksum_On_Bytes(destination_string + 13, rval - 13);

      sprintf(destination_string + 7, "%05d", message_checksum);     //write the checksum after the delimiter between the length and checksum.
      destination_string[12] = *message_field_delimiter;     //put our delimiter back.

   } else {
      rval = 0;
   }

   return rval;
}

uint32_t Serialize_Message_Content(Message * message, uint8_t * destination_string, uint32_t destination_max_length) {

   if (message == NULL || destination_string == NULL) return 0;

   uint32_t rval = 0;
   uint16_t message_checksum = 0;

   //         0                 1                   2               3         4              5                 6                   7               8
   //format: \f<message_length>\t<message_checksum>\t<message_type>\ t<source>\t<destination>\t<content_length>\t<content_checksum>\t<content_type>\t<content>

   rval = snprintf(destination_string, destination_max_length, "%s%d%s%d%s%s%s",     //
                   message_start,     //
                   message->content_length,
                   message_field_delimiter,
                   message->content_checksum,
                   message_field_delimiter,
                   message->content_type,
                   message_field_delimiter);

   if ((rval) + message->content_length <= destination_max_length) {

      memcpy(destination_string + rval, message->content, message->content_length);
      rval += message->content_length;

   } else {

      rval = 0;
   }

   return rval;
}

//parse a message, including start character. Start char must be first char in message.
//  note:message is strtok'd by this function.
Message * Deserialize_Message_With_Message_Header(uint8_t * message) {

   //if there's no data, or we don't have a \f at the beginning of the message, we return.
   if (message == NULL || message[0] != *message_start) return NULL;

   Message * rval = NULL;
   uint32_t message_length = 0;
   uint16_t message_checksum = 0;

   char * token_state = NULL;

   //         0                 1                   2               3         4              5                 6                   7               8
   //format: \f<message_length>\t<message_checksum>\t<message_type>\ t<source>\t<destination>\t<content_length>\t<content_checksum>\t<content_type>\t<content>

   //get framing info
   uint8_t * temp_message_length = (uint8_t*) strtok_r((char*) message + 1, message_field_delimiter, &token_state);     //throw out the start character
   uint8_t * temp_message_checksum = NULL;

   if (temp_message_length != NULL) {
      message_length = atoi(temp_message_length);

      temp_message_checksum = strtok_r(NULL, message_field_delimiter, &token_state);
      if (temp_message_checksum != NULL) {
         message_checksum = atoi(temp_message_checksum);
      }
   }

   if (temp_message_length != NULL
       && temp_message_checksum != NULL
       && message_checksum
          == Calculate_Checksum_On_Bytes(temp_message_checksum + strlen(temp_message_checksum) + 1,
                                         message_length
                                         - ((temp_message_checksum + strlen(temp_message_checksum) + 1) - message))) {

      //if message checksum ok, proceed.
      //find serial message header
      uint8_t * temp_message_type = strtok_r(NULL, message_field_delimiter, &token_state);
      uint8_t * temp_source_address = strtok_r(NULL, message_field_delimiter, &token_state);
      uint8_t * temp_dest_address = strtok_r(NULL, message_field_delimiter, &token_state);
      uint8_t * content_header_start = temp_dest_address + strlen(temp_dest_address);

      if (temp_message_type != NULL && temp_source_address != NULL && temp_dest_address != NULL && content_header_start != NULL) {

         //put the message start char in the right place for Deserialize_Message_Content
         *content_header_start = *message_start;
         rval = Deserialize_Message_Content(content_header_start);

         if (rval != NULL) {

            *content_header_start = '\0';
            Set_Message_Type(rval, temp_message_type);
            Set_Message_Source(rval, temp_source_address);
            Set_Message_Destination(rval, temp_dest_address);
         }
      }
   }

   return rval;
}

Message * Deserialize_Message_Content(uint8_t * message) {

   if (message == NULL || *message != *message_start) return NULL;

   Message * rval = NULL;
   char * token_state = NULL;
   uint32_t content_length = 0;

   //find content header
   uint8_t * temp_content_length = strtok_r(message + 1, message_field_delimiter, &token_state);
   uint8_t * temp_content_checksum = strtok_r(NULL, message_field_delimiter, &token_state);
   uint8_t * temp_content_type = strtok_r(NULL, message_field_delimiter, &token_state);

   content_length = atoi(temp_content_length);

   if (temp_content_length != NULL && temp_content_type != NULL && temp_content_checksum != NULL) {

      //get a pointer to the content
      uint8_t * temp_content = temp_content_type + (strlen(temp_content_type) + 1);

      rval = Create_Message();

      // Create message object

      Set_Message_Content_Type(rval, temp_content_type);
      Set_Message_Content(rval, temp_content, content_length);

      //message checksum is set in Set_Message_content. we compare it to the checksum we received.
      if (rval->content_checksum != atoi(temp_content_checksum)) {
         //delete the message if the checksum didn't match
         Delete_Message(rval);
         rval = NULL;
      }
   }

   return rval;
}
