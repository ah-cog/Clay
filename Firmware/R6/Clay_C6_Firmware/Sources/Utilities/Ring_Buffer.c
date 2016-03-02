/*
 * Ring_Buffer.c
 *
 *  Created on: Sep 16, 2015
 *      Author: mokogobo
 */

#include "Ring_Buffer.h"

static uint8_t Ring_Buffer_buffer[Ring_Buffer_BUF_SIZE]; /* ring buffer */
static uint16_t Ring_Buffer_inIdx; /* input index */
static uint16_t Ring_Buffer_outIdx; /* output index */
static uint16_t Ring_Buffer_inSize; /* size of input data */
/*
 ** ===================================================================
 **     Method      :  Ring_Buffer_Put (component RingBufferUInt8)
 **     Description :
 **         Puts a new element into the buffer
 **     Parameters  :
 **         NAME            - DESCRIPTION
 **         elem            - New element to be put into the buffer
 **     Returns     :
 **         ---             - Error code
 ** ===================================================================
 */
byte Ring_Buffer_Put(byte elem)
{
   byte res = ERR_OK;

   if (Ring_Buffer_inSize == Ring_Buffer_BUF_SIZE)
   {
      res = ERR_TXFULL;
   }
   else
   {
      Ring_Buffer_buffer[Ring_Buffer_inIdx] = elem;
      Ring_Buffer_inSize++;
      Ring_Buffer_inIdx++;
      if (Ring_Buffer_inIdx == Ring_Buffer_BUF_SIZE)
      {
         Ring_Buffer_inIdx = 0;
      }
   }
   return res;
}

/*
 ** ===================================================================
 **     Method      :  Ring_Buffer_Get (component RingBufferUInt8)
 **     Description :
 **         Removes an element from the buffer
 **     Parameters  :
 **         NAME            - DESCRIPTION
 **       * elemP           - Pointer to where to store the received
 **                           element
 **     Returns     :
 **         ---             - Error code
 ** ===================================================================
 */
byte Ring_Buffer_Get(byte *elemP)
{
   byte res = ERR_OK;

   if (Ring_Buffer_inSize == 0)
   {
      res = ERR_RXEMPTY;
   }
   else
   {
      *elemP = Ring_Buffer_buffer[Ring_Buffer_outIdx];
      Ring_Buffer_inSize--;
      Ring_Buffer_outIdx++;
      if (Ring_Buffer_outIdx == Ring_Buffer_BUF_SIZE)
      {
         Ring_Buffer_outIdx = 0;
      }
   }
   return res;
}

/*
 ** ===================================================================
 **     Method      :  Ring_Buffer_NofElements (component RingBufferUInt8)
 **     Description :
 **         Returns the actual number of elements in the buffer.
 **     Parameters  : None
 **     Returns     :
 **         ---             - Number of elements in the buffer.
 ** ===================================================================
 */
uint8_t Ring_Buffer_Has_Data()
{

   return (Ring_Buffer_inSize > 0 ? TRUE : FALSE);
}

/*
 ** ===================================================================
 **     Method      :  Ring_Buffer_NofElements (component RingBufferUInt8)
 **     Description :
 **         Returns the actual number of elements in the buffer.
 **     Parameters  : None
 **     Returns     :
 **         ---             - Number of elements in the buffer.
 ** ===================================================================
 */
uint16_t Ring_Buffer_NofElements(void)
{
   return Ring_Buffer_inSize;
}

/*
 ** ===================================================================
 **     Method      :  Ring_Buffer_NofFreeElements (component RingBufferUInt8)
 **     Description :
 **         Returns the actual number of free elements/space in the
 **         buffer.
 **     Parameters  : None
 **     Returns     :
 **         ---             - Number of elements in the buffer.
 ** ===================================================================
 */
uint16_t Ring_Buffer_NofFreeElements(void)
{
   return (uint16_t) (Ring_Buffer_BUF_SIZE - Ring_Buffer_inSize);
}

/*
 ** ===================================================================
 **     Method      :  Ring_Buffer_Init (component RingBufferUInt8)
 **     Description :
 **         Initializes the data structure
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void Ring_Buffer_Init(void)
{
   Ring_Buffer_inIdx = 0;
   Ring_Buffer_outIdx = 0;
   Ring_Buffer_inSize = 0;
}
