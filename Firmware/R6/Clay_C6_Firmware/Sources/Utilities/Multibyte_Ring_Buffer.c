/*
 * Multibyte_Ring_Buffer.c
 *
 *  Created on: Apr 17, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"

#include "Multibyte_Ring_Buffer.h"

////Macros ////////////////////////////////////////////////////////
#define BUFFER_TAIL(buffer)             ((buffer->data) + buffer->tail)
#define BUFFER_HEAD(buffer)             ((buffer->data) + buffer->head)

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
void Multibyte_Ring_Buffer_Init(Multibyte_Ring_Buffer * buffer, uint32_t size) {

   buffer->max_count = size;
   buffer->data = malloc(buffer->max_count);
   buffer->head = 0;
   buffer->tail = 0;
   buffer->count = 0;
}

void Multibyte_Ring_Buffer_Free(Multibyte_Ring_Buffer * buffer) {

   if (buffer->data != NULL) {
      free(buffer->data);
      buffer->max_count = 0;
   }
}

void Multibyte_Ring_Buffer_Reset(Multibyte_Ring_Buffer * buffer) {
   buffer->head = 0;
   buffer->tail = 0;
   buffer->count = 0;
}

uint32_t Multibyte_Ring_Buffer_Enqueue(Multibyte_Ring_Buffer * buffer, uint8_t * data, uint32_t size) {

   uint32_t rval = ((Multibyte_Ring_Buffer_Get_Free_Size(buffer) > size) ? size : Multibyte_Ring_Buffer_Get_Free_Size(buffer));
   uint32_t free_bytes_after_tail = (
         buffer->tail > buffer->head ? buffer->max_count - buffer->tail : Multibyte_Ring_Buffer_Get_Free_Size(buffer));

   if (rval > 0) {
      if (rval < free_bytes_after_tail) {
         memcpy(BUFFER_TAIL(buffer), data, rval);
         buffer->tail = (buffer->tail + rval) % buffer->max_count;
      } else {
         memcpy(BUFFER_TAIL(buffer), data, free_bytes_after_tail);
         buffer->tail = (buffer->tail + free_bytes_after_tail) % buffer->max_count;

         memcpy(buffer->data, data + free_bytes_after_tail, rval - free_bytes_after_tail);
         buffer->tail = (buffer->tail + (rval - free_bytes_after_tail)) % buffer->max_count;
      }

      buffer->count += rval;
   }

   return rval;
}

uint32_t Multibyte_Ring_Buffer_Dequeue(Multibyte_Ring_Buffer * buffer, uint8_t * data, uint32_t size) {

   uint32_t bytes_after_head = (buffer->head < buffer->tail ? buffer->count : buffer->max_count - buffer->head);
   uint32_t rval = (buffer->count > size ? size : buffer->count);

   //TODO: kind of looks like head may not be getting updated correctly. Like the value is 1 more than it should be

   if (rval > 0) {
      if (rval < bytes_after_head) {
         memcpy(data, BUFFER_HEAD(buffer), rval);
         buffer->head = (buffer->head + rval) % buffer->max_count;

      } else {
         memcpy(data, BUFFER_HEAD(buffer), bytes_after_head);
         buffer->head = (buffer->head + bytes_after_head) % buffer->max_count;

         memcpy(data + bytes_after_head, BUFFER_HEAD(buffer), rval - bytes_after_head);
         buffer->head = (buffer->head + (rval - bytes_after_head)) % buffer->max_count;
      }

      buffer->count -= rval;
   }

   return rval;
}

uint32_t Multibyte_Ring_Buffer_Dequeue_Until_Char(Multibyte_Ring_Buffer * buffer, uint8_t * data, uint32_t size, char end_char) {

   uint32_t bytes_after_head = (buffer->head < buffer->tail ? buffer->count : buffer->max_count - buffer->head);
   uint32_t rval = 0;

   uint8_t * char_location = memchr(BUFFER_HEAD(buffer), end_char, bytes_after_head);

   if (char_location == NULL && ((buffer->head > buffer->tail) || (buffer->head == buffer->tail && buffer->count > 0))) {
      char_location = memchr(buffer->data, end_char, buffer->tail);

      if (char_location != NULL) {
         rval = bytes_after_head + (char_location - buffer->data) + 1;
      }

   } else {
      rval = char_location - BUFFER_HEAD(buffer) + 1;
   }

   if (char_location != NULL && rval <= size) {
      rval = Multibyte_Ring_Buffer_Dequeue(buffer, data, rval);
   } else {
      rval = 0;
   }

   return rval;
}

uint32_t Multibyte_Ring_Buffer_Get_Free_Size(Multibyte_Ring_Buffer * buffer) {

   return buffer->max_count - buffer->count;
}

uint32_t Multibyte_Ring_Buffer_Get_Count(Multibyte_Ring_Buffer * buffer) {

   return buffer->count;
}

bool Multibyte_Ring_Buffer_Full(Multibyte_Ring_Buffer * buffer) {
   return buffer->count >= buffer->max_count;
}

//281 chars including newline.
//static char *test_msg =
//      "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n";

//20 chars, no newline
//static char *test_msg = "mmmmmmmmmmmmmmmmmmmm";

//510 chars, 10 messages
//static char *test_msg =
//      "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n";
//256 chars, including newline
//static char *test_msg =
//      "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n";

//161 chars, including newline
//static char * test_msg = "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n";

//uint32_t Multibyte_Ring_Buffer_Test() {
//
//   char dq_data[1024];
//   uint32_t dq_max = 1024;
//   uint32_t dq_count = 0;
//
//   Multibyte_Ring_Buffer test_buffer;
//
//   Multibyte_Ring_Buffer_Init(&test_buffer, 1024);
//
//   for (;;) {
//      while (!Multibyte_Ring_Buffer_Full(&test_buffer)) {
//         Multibyte_Ring_Buffer_Enqueue(&test_buffer, test_msg, strlen(test_msg));
//      }
//
//      while (Multibyte_Ring_Buffer_Dequeue_Until_Char(&test_buffer, dq_data, dq_max - dq_count, '\n')) {
//         Multibyte_Ring_Buffer_Get_Count(&test_buffer);
//      }
//   }
//
//}

////Local implementations /////////////////////////////////////////
