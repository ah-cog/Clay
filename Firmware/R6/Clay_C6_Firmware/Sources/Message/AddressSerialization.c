/*
 * AddressSerialization.c
 *
 *  Created on: Mar 2, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "PE_Types.h"
#include "string.h"
#include "stdlib.h"
#include "AddressSerialization.h"

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
uint8_t* message_strings[] = { "UDP", "TCP", "CMD", "INFO", "INVALID" };
const char * address_terminator = "\x12";
const char * address_delimiter = ";";
const char * type_delimiter = ",";
const char * port_delimiter = ":";

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
uint32_t Serialize_Address(struct sockaddr_in * Source,
                           uint8_t* Destination,
                           uint32_t DestinationLength,
                           Message_Type ConnectionType) {

   uint32_t rval = 0;

   uint8_t * ntoaBuf = inet_ntoa(&(Source->sin_addr.s_addr));     //the buffer gets overwritten by subsequent calls.
   uint8_t connectionTypeStr[CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH];

   if (Get_Message_Type_Str(ConnectionType, connectionTypeStr)) {
      //+ 2 for the terminating '!' and null, +3 for 1 comma and 1 colon
      rval = strlen(ntoaBuf) + 2 + 3 + strlen(connectionTypeStr) + 5;

      if (rval <= DestinationLength) {
         rval = snprintf(Destination,
                         DestinationLength,
                         "%s,%s:%d%c\n",
                         connectionTypeStr,
                         ntoaBuf,
                         ntohs(Source->sin_port),
                         address_terminator);
      }

      if (rval > DestinationLength) {
         rval = -1;
      }
   }

   return rval;
}

void Deserialize_Address(uint8_t* Source, uint32_t SourceLength, struct sockaddr_in * Destination, Message_Type *type) {
   memset(Destination, 0, sizeof(*Destination));

   //get the string off the front
   uint8_t* typeStart = strtok(Source, &type_delimiter);
   uint8_t* ipStart = strtok(NULL, &port_delimiter);
   uint8_t* portStart = strtok(NULL, &address_terminator);

   if (typeStart != NULL) {
      *type = Get_Message_Type_From_Str(typeStart);
   }

   if (ipStart != NULL) {
      inet_aton(ipStart, &(Destination->sin_addr));
   }

   if (portStart != NULL) {
      Destination->sin_port = htons(atoi(portStart));
   }

   if (ipStart != NULL && portStart != NULL) {
      Destination->sin_family = AF_INET;
      Destination->sin_len = sizeof(*Destination);
   }
}

bool Get_Message_Type_Str(Message_Type type, uint8_t *returnStr) {
   bool rval = FALSE;

   if (type < MESSAGE_TYPE_MAX) {
      strncpy(returnStr, message_strings[type], CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH);
      rval = TRUE;
   }

   return rval;
}

Message_Type Get_Message_Type_From_Str(uint8_t*typeString) {
   Message_Type rval = MESSAGE_TYPE_MAX;

   int i;
   for (i = 0; i < MESSAGE_TYPE_MAX; ++i) {
      if (strcmp(typeString, message_strings[i]) == 0) {
         rval = (Message_Type) i;
      }
   }

   return rval;
}

uint8_t * inet_ntoa(const in_addr_t * addr) {
   //max size is 256.256.256.256 -> 15 + null = 16
   sprintf((char*) ntoaTempStr, "%u.%u.%u.%u", *addr & 0xFF, (*addr >> 8) & 0xFF, (*addr >> 16) & 0xFF, (*addr >> 24) & 0xFF);

   return ntoaTempStr;
}

int inet_aton(const uint8_t *cp, in_addr_t * addr) {
   int rval = -1;
   octet_3_ptr = strtok(cp, &dotChar);
   octet_2_ptr = strtok(NULL, &dotChar);
   octet_1_ptr = strtok(NULL, &dotChar);
   octet_0_ptr = strtok(NULL, &dotChar);

   if (octet_3_ptr != NULL && octet_2_ptr != NULL && octet_1_ptr != NULL && octet_0_ptr != NULL) {
      *addr = ((atoi(octet_0_ptr) & 0xFF) << 24)
              + ((atoi(octet_1_ptr) & 0xFF) << 16)
              + ((atoi(octet_2_ptr) & 0xFF) << 8)
              + (atoi(octet_3_ptr) & 0xFF);
      rval = 0;
   }

   return rval;
}
