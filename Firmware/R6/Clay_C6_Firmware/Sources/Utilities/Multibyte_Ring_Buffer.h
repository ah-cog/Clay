/*
 * Multibyte_Ring_Buffer.h
 *
 *  Created on: Apr 17, 2016
 *      Author: thebh_000
 */

#ifndef SOURCES_UTILITIES_MULTIBYTE_RING_BUFFER_H_
#define SOURCES_UTILITIES_MULTIBYTE_RING_BUFFER_H_

////Includes //////////////////////////////////////////////////////
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

#include "Message.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////
typedef struct
{
      uint8_t * data;
      uint32_t max_count;
      uint32_t head;
      uint32_t tail;
      uint32_t count;
} Multibyte_Ring_Buffer;

////Globals   /////////////////////////////////////////////////////

////Function Prototypes ///////////////////////////////////////////
extern void Multibyte_Ring_Buffer_Init(Multibyte_Ring_Buffer * buffer, uint32_t size);
extern void Multibyte_Ring_Buffer_Free(Multibyte_Ring_Buffer * buffer);
extern void Multibyte_Ring_Buffer_Reset(Multibyte_Ring_Buffer * buffer);

extern uint32_t Multibyte_Ring_Buffer_Enqueue(Multibyte_Ring_Buffer * buffer, uint8_t * data, uint32_t size);
extern uint32_t Multibyte_Ring_Buffer_Dequeue(Multibyte_Ring_Buffer * buffer, uint8_t * data, uint32_t size);
extern uint32_t Multibyte_Ring_Buffer_Dequeue_Until_Char(Multibyte_Ring_Buffer * buffer,
                                                         uint8_t * data,
                                                         uint32_t size,
                                                         char end_char);
extern uint32_t Multibyte_Ring_Buffer_Get_Bytes_Before_Char(Multibyte_Ring_Buffer * buffer, char end_char);

extern uint32_t Multibyte_Ring_Buffer_Get_Bytes_Until_String_End(Multibyte_Ring_Buffer * buffer, char * end_str);
extern uint32_t Multibyte_Ring_Buffer_Dequeue_Until_String(Multibyte_Ring_Buffer * buffer,
                                                           uint8_t * data,
                                                           uint32_t size,
                                                           char * end_string);

extern uint32_t Multibyte_Ring_Buffer_Dequeue_Serialized_Message_With_Message_Header(Multibyte_Ring_Buffer * buffer, uint8_t * * destination);

extern uint32_t Multibyte_Ring_Buffer_Get_Bytes_Until_String_End_From_Offset(Multibyte_Ring_Buffer * buffer,
                                                                             char * end_str,
                                                                             uint32_t offset);

extern uint32_t Multibyte_Ring_Buffer_Get_Free_Size(Multibyte_Ring_Buffer * buffer);
extern uint32_t Multibyte_Ring_Buffer_Get_Count(Multibyte_Ring_Buffer * buffer);
extern bool Multibyte_Ring_Buffer_Full(Multibyte_Ring_Buffer * buffer);

extern uint32_t Multibyte_Ring_Buffer_Test();

#endif /* SOURCES_UTILITIES_MULTIBYTE_RING_BUFFER_H_ */
