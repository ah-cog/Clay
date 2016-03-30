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
#include "Message_Info.h"

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
char * message_strings[] = { "UDP", "TCP", "CMD", "INFO", "INVALID" };
const char * address_terminator = "\x12";
const char * address_delimiter = ";";
const char * type_delimiter = ",";
const char * port_delimiter = ":";
const char * arg_delimiter = ",";

////Local vars/////////////////////////////////////////////////////
uint8_t message_type_temp_str[CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH];
uint8_t ntoaTempStr[30];
uint8_t * octet_0_ptr;
uint8_t * octet_1_ptr;
uint8_t * octet_2_ptr;
uint8_t * octet_3_ptr;
char dotChar = '.';

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
