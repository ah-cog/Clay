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
uint8_t* Message_Strings[] = { "UDP", "TCP" };
char Terminator = '\n';

////Local vars/////////////////////////////////////////////////////
uint8_t messageTypeTempStr[CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH];
uint8_t ntoaTempStr[30];
uint8_t * octet0Ptr;
uint8_t * octet1Ptr;
uint8_t * octet2Ptr;
uint8_t * octet3Ptr;
char dotChar = '.';

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
uint32_t Serialize_Address(struct sockaddr_in * Source,
                           uint8_t* Destination,
                           uint32_t DestinationLength,
                           Message_Type ConnectionType)
{
   ///TODO: add connection type bool

   uint32_t rval = 0;

   uint8_t * ntoaBuf = inet_ntoa(&(Source->sin_addr.s_addr));     //the buffer gets overwritten by subsequent calls.
   uint8_t connectionTypeStr[CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH];

   if (Get_Message_Type_Str(ConnectionType, connectionTypeStr))
   {
      //+ 2 for the terminating '!' and null, +3 for 1 comma and 1 colon
      rval = strlen(ntoaBuf) + 2 + 3 + strlen(connectionTypeStr) + 5;

      if (rval <= DestinationLength)
      {
         rval = snprintf(Destination, DestinationLength, "%s,%s:%d!\n", connectionTypeStr, ntoaBuf, ntohs(Source->sin_port));
      }

      if (rval > DestinationLength)
      {
         rval = -1;
      }
   }

   return rval;
}

void Deserialize_Address(uint8_t* Source, uint32_t SourceLength, struct sockaddr_in * Destination, Message_Type *type)
{
   char Comma = ',';
   char Colon = ':';
   char Bang = '!';

   memset(Destination, 0, sizeof(*Destination));

   //get the string off the front
   uint8_t* typeStart = strtok(Source, &Comma);
   uint8_t* ipStart = strtok(NULL, &Colon);
   uint8_t* portStart = strtok(NULL, &Bang);

   *type = Get_Message_Type_From_Str(typeStart);

   inet_aton(ipStart, &(Destination->sin_addr));
   Destination->sin_port = htons(atoi(portStart));

   Destination->sin_family = AF_INET;
   Destination->sin_len = sizeof(*Destination);
}

bool Get_Message_Type_Str(Message_Type type, uint8_t *returnStr)
{
   bool rval = FALSE;

   if (type < MESSAGE_TYPE_MAX)
   {
      strncpy(returnStr, Message_Strings[type], CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH);
      rval = TRUE;
   }

   return rval;
}

Message_Type Get_Message_Type_From_Str(uint8_t*typeString)
{
   Message_Type rval = MESSAGE_TYPE_MAX;

   int i;
   for (i = 0; i < MESSAGE_TYPE_MAX; ++i)
   {
      if (strcmp(typeString, Message_Strings[i]) == 0)
      {
         rval = (Message_Type) i;
      }
   }

   return rval;
}

uint8_t * inet_ntoa(const in_addr_t * addr)
{
   //max size is 256.256.256.256 -> 15 + null = 16
   sprintf((char*) ntoaTempStr, "%u.%u.%u.%u", *addr & 0xFF, (*addr >> 8) & 0xFF, (*addr >> 16) & 0xFF, (*addr >> 24) & 0xFF);

   return ntoaTempStr;
}

int inet_aton(const uint8_t *cp, in_addr_t * addr)
{
   int rval = -1;
   octet3Ptr = strtok(cp, &dotChar);
   octet2Ptr = strtok(NULL, &dotChar);
   octet1Ptr = strtok(NULL, &dotChar);
   octet0Ptr = strtok(NULL, &dotChar);

   if (octet3Ptr != NULL && octet2Ptr != NULL && octet1Ptr != NULL && octet0Ptr != NULL)
   {
      *addr = ((atoi(octet0Ptr) & 0xFF) << 24)
             + ((atoi(octet1Ptr) & 0xFF) << 16)
             + ((atoi(octet2Ptr) & 0xFF) << 8)
             + (atoi(octet3Ptr) & 0xFF);
      rval = 0;
   }

   return rval;
}
