/*
 * Clay_Message.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 */

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"
#include "string.h"

#include "lwip/sockets.h"

#include "Clay_Message.h"
#include "Clay_Config.h"

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
char Terminator = '\n';

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
uint32 FillBufferWithMessage(Clay_Message * Source, uint8 * Destination, uint32 DestinationLength)
{
   uint32 rval = 0;

   //copy until newline.
   //strtok on the msg to place a null at the \n
   //strcpy to destination buf
   //replace the \n in msg buf
   //add a \n to the destination buf
   //print the address to the buffer
   //return length of all written data.

   strncpy(Destination, Source->Message, Source->Length);
   rval += Source->Length;

   //add on the addr
   rval += snprintf(Destination + rval,
                    DestinationLength - rval,
                    "%d,%d,%d,%d",
                    Source->Address.sin_addr.s_addr,
                    Source->Address.sin_family,
                    Source->Address.sin_len,
                    Source->Address.sin_port);

   if (rval <= DestinationLength + SIN_ZERO_LEN)
   {
      int i;
      for (i = 0; i < SIN_ZERO_LEN; ++i)
      {
         rval += snprintf(Destination + rval, DestinationLength - rval, ",%d", Source->Address.sin_zero[i]);
         if (rval >= DestinationLength)
         {
            Destination[DestinationLength - 1] = '\n';
            rval = DestinationLength;
            break;
         }
      }
   }

   return rval;
}

uint32 CreateMessageFromBuffer(uint8 * Source, uint32 SourceLength, Clay_Message * Destination)
{
   uint32 rval = 0;
   char Comma = ',';
   uint32 temp;

   uint8 * NewlineIndex = strchr(Source, '\n') + 1;
   Destination->Length = NewlineIndex - Source;
   memcpy(Destination->Message, Source, Destination->Length);

   NewlineIndex = strtok(NewlineIndex, &Comma);
   printf("s_addr");
   printf(NewlineIndex);
   printf("\n");
   sscanf(NewlineIndex, "%d", &(Destination->Address.sin_addr.s_addr));

   NewlineIndex = strtok(NewlineIndex, &Comma);
   sscanf(NewlineIndex, "%d", &temp);
   printf("family");
   printf(NewlineIndex);
   printf("\n");
   Destination->Address.sin_family = temp & 0xFF;

   NewlineIndex = strtok(NewlineIndex, &Comma);
   sscanf(NewlineIndex, "%d", &temp);
   printf("len");
   printf(NewlineIndex);
   printf("\n");
   Destination->Address.sin_len = temp & 0xFF;

   NewlineIndex = strtok(NewlineIndex, &Comma);
   sscanf(NewlineIndex, "%d", &temp);
   printf("port");
   printf(NewlineIndex);
   printf("\n");
   Destination->Address.sin_port = temp & 0xFFFF;

   int i;
   for (i = 0; i < SIN_ZERO_LEN && NewlineIndex != NULL; ++i)
   {
      NewlineIndex = strtok(NewlineIndex, &Comma);
      printf("%d zero", i);
      printf(NewlineIndex);
      printf("\n");
      sscanf(NewlineIndex, "%d", &temp);
      Destination->Address.sin_zero[i] = temp & 0xFF;
   }

   if (Destination->Length >= CLAY_MESSAGE_LENGTH_MAX_BYTES)
   {
      Destination->Message[CLAY_MESSAGE_LENGTH_MAX_BYTES - 1] = '\n';
   }

   return rval;
}

void Message_Conversion_Test()
{
   Clay_Message m;
   m.Length = 10;
   int i;
   for (i = 0; i < m.Length - 1; ++i)
   {
      m.Message[i] = 'h';
   }

   m.Message[i] = '\n';
   m.Message[i + 1] = '\0';

   m.Address.sin_addr.s_addr = 0x55;
   m.Address.sin_len = 0;
   m.Address.sin_port = 0;

   uint32 bufferFillLength;
   uint32 messageFillLength;
   char sinZeroStr[50];
   char sinZeroSize;

   uint8 buf[CLAY_MESSAGE_STRUCT_SIZE_BYTES * 2];

   for (;;)
   {
      sinZeroSize = 0;
      for (i = 0; i < SIN_ZERO_LEN; ++i)
      {
         sinZeroSize += sprintf(sinZeroStr + sinZeroSize, "%s%d", ((i == 8 || i == 0) ? "" : ","), m.Address.sin_zero[i]);
         m.Address.sin_zero[i] = m.Address.sin_addr.s_addr + i;
      }

      bufferFillLength = FillBufferWithMessage(&m, buf, CLAY_MESSAGE_STRUCT_SIZE_BYTES * 2);

      m.Message[m.Length + 1] = '\0';
      printf("bfl: %d,len: %d msg: %s, addr: %d, fam: %d, len: %d, port: %d, zero: %s\n",
             messageFillLength,
             m.Length,
             m.Message,
             m.Address.sin_addr.s_addr,
             m.Address.sin_family,
             m.Address.sin_len,
             m.Address.sin_port,
             sinZeroStr);

      printf("len: %d, buf: %s]\n\n", bufferFillLength, buf);

      ++m.Address.sin_addr.s_addr;
      m.Message[0] = 'N';

      messageFillLength = CreateMessageFromBuffer(buf, CLAY_MESSAGE_STRUCT_SIZE_BYTES * 2, &m);
   }
}
////Local implementations /////////////////////////////////////////

