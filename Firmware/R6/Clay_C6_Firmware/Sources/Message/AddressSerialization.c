/*
 * AddressSerialization.c
 *
 *  Created on: Mar 2, 2016
 *      Author: thebh_000
 */

#include "PE_Types.h"
#include "string.h"
#include "AddressSerialization.h"


uint32_t Serialize_Address(struct sockaddr_in * Source, uint8_t* Destination, uint32_t DestinationLength)
{
   uint32_t rval = 0;
   rval += snprintf(Destination + rval,
                    DestinationLength - rval,
                    "%u,%u,%u,%u",
                    ntohl(Source->sin_addr.s_addr),
                    Source->sin_family,
                    Source->sin_len,
                    ntohs(Source->sin_port));

//   printf("dest pre array: [%s]\n", Destination);

   if (rval <= DestinationLength + SIN_ZERO_LEN)
   {
      int i;
      for (i = 0; i < SIN_ZERO_LEN; ++i)
      {
         rval += snprintf(Destination + rval, DestinationLength - rval, "%s%u", i < SIN_ZERO_LEN ? "," : "", Source->sin_zero[i]);
         if (rval >= DestinationLength)
         {
//            printf("rval too long\n");
            Destination[DestinationLength - 1] = '!';
            rval = DestinationLength;
            break;
         }
      }
      if (rval < DestinationLength)
      {
         Destination[rval] = '!';
      }
   }
//   printf("dest final: [%s]\n", Destination);
}

void Deserialize_Address(uint8_t* Source, uint32_t SourceLength, struct sockaddr_in * Destination)
{
   uint8_t * token;
   char Comma = ',';
   uint32_t temp;

//   printf("tryna toke\n");
   token = strtok(Source, &Comma);
//   printf("s_addr [%s]\n", token);
   sscanf(token, "%d", &temp);
   Destination->sin_addr.s_addr = htonl(temp);

   token = strtok(NULL, &Comma);
   sscanf(token, "%d", &temp);
//   printf("family [%s]\n", token);
   Destination->sin_family = temp & 0xFF;

   token = strtok(NULL, &Comma);
   sscanf(token, "%d", &temp);
//   printf("len [%s]\n", token);
   Destination->sin_len = temp & 0xFF;

   token = strtok(NULL, &Comma);
   sscanf(token, "%d", &temp);
//   printf("port [%s]\n", token);
   Destination->sin_port = htons(temp & 0xFFFF);

   int i;
   for (i = 0; i < SIN_ZERO_LEN && token != NULL; ++i)
   {
      token = strtok(NULL, &Comma);
//      printf("zero[%d] [%s]\n", i, token);
      sscanf(token, "%d", &temp);
      Destination->sin_zero[i] = temp & 0xFF;
   }
}
