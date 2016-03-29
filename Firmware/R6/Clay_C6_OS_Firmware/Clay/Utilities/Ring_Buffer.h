/*
 * Ring_Buffer.h
 *
 *  Created on: Sep 16, 2015
 *      Author: mokogobo
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include "stdint.h"

#define Ring_Buffer_BUF_SIZE   2048  /* number of elements in the buffer */

uint8_t Ring_Buffer_Put(char elem);
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

uint8_t Ring_Buffer_Get(char *elemP);
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

uint8_t Ring_Buffer_Has_Data();
/*
 ** ===================================================================
 **     Method      :  Ring_Buffer_Has_Data (component RingBufferUInt8)
 **     Description :
 **         Checks if the buffer contains any data.
 **     Parameters  :
 **         NAME            - DESCRIPTION
 **       * elemP           - Pointer to where to store the received
 **                           element
 **     Returns     :
 **         ---             - Error code
 ** ===================================================================
 */

uint16_t Ring_Buffer_NofElements(void);
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

void Ring_Buffer_Init(void);
/*
 ** ===================================================================
 **     Method      :  Ring_Buffer_Init (component RingBufferUInt8)
 **     Description :
 **         Initializes the data structure
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */

uint16_t Ring_Buffer_NofFreeElements(void);
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

#endif /* RING_BUFFER_H_ */
