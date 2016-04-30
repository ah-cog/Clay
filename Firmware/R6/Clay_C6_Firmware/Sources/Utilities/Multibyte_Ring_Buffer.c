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

   memset(buffer->data, 0, buffer->max_count);
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
         memset(BUFFER_HEAD(buffer), 0, bytes_after_head);
         buffer->head = (buffer->head + bytes_after_head) % buffer->max_count;

         memcpy(data + bytes_after_head, BUFFER_HEAD(buffer), rval - bytes_after_head);
         memset(BUFFER_HEAD(buffer), 0, rval - bytes_after_head);
         buffer->head = (buffer->head + (rval - bytes_after_head)) % buffer->max_count;
      }

      buffer->count -= rval;
   }

   return rval;
}

uint32_t Multibyte_Ring_Buffer_Dequeue_Until_Char(Multibyte_Ring_Buffer * buffer, uint8_t * data, uint32_t size, char end_char) {

   uint32_t rval = Multibyte_Ring_Buffer_Get_Bytes_Before_Char(buffer, end_char);

   if (rval > 0 && rval <= size) {
      rval = Multibyte_Ring_Buffer_Dequeue(buffer, data, rval);
   } else {
      rval = 0;
   }

   return rval;
}

uint32_t Multibyte_Ring_Buffer_Get_Bytes_Before_Char(Multibyte_Ring_Buffer * buffer, char end_char) {

   uint32_t bytes_after_head = (buffer->head < buffer->tail ? buffer->count : buffer->max_count - buffer->head);
   uint32_t rval = 0;

   uint8_t * char_location = memchr(BUFFER_HEAD(buffer), end_char, bytes_after_head);

   if (char_location == NULL && ((buffer->head > buffer->tail) || (buffer->head == buffer->tail && buffer->count > 0))) {
      char_location = memchr(buffer->data, end_char, buffer->tail);

      if (char_location != NULL) {
         rval = bytes_after_head + (char_location - buffer->data) + 1;
      } else {
         rval = 0;
      }

   } else if (char_location != NULL) {
      rval = char_location - BUFFER_HEAD(buffer) + 1;
   }

   return rval;
}

uint32_t Multibyte_Ring_Buffer_Dequeue_Until_String(Multibyte_Ring_Buffer * buffer,
                                                    uint8_t * data,
                                                    uint32_t size,
                                                    char * end_string) {

   uint32_t rval = Multibyte_Ring_Buffer_Get_Bytes_Until_String_End(buffer, end_string);

   if (rval > 0 && rval <= size) {
      rval = Multibyte_Ring_Buffer_Dequeue(buffer, data, rval);
   } else {
      rval = 0;
   }

   return rval;
}

//end_str must be null terminated.
//returns the number of bytes until the end of the string.
uint32_t Multibyte_Ring_Buffer_Get_Bytes_Until_String_End(Multibyte_Ring_Buffer * buffer, char * end_str) {

   int rval = 0;
   char * first_found = NULL;
   char * last_found = NULL;
   bool found = false;
   bool continue_searching = true;

   uint32_t target_length = strlen(end_str);
   uint32_t first_char_index = 0;
   uint32_t target_index = 0;

   for (int i = buffer->head; i < (buffer->count + buffer->head) && continue_searching; ++i) {

      if (first_found == NULL) {     //not out of data yet, and we haven't found the first char.

         if ((buffer->data)[i % buffer->max_count] == end_str[target_index]) {
            first_found = (buffer->data + (i % buffer->max_count));
            ++target_index;
         }
      } else {     //we're not out of data, and we found the first char.

         if ((buffer->data)[i % buffer->max_count] == end_str[target_index]) {
            last_found = (buffer->data + (i % buffer->max_count));
            ++target_index;
         } else {
            //start over
            first_found = NULL;
            found = false;
            target_index = 0;
         }

         if (last_found != NULL) {
            if (last_found > first_found) {     //our search hasn't wrapped around yet.

               if (1 + (last_found - first_found) == target_length) {
                  found = true;
                  rval = 1 + (i - buffer->head);
               }
            } else if (1 + (last_found - (char *) buffer->data) + (buffer->max_count - (first_found - (char *) buffer->data))
                       == target_length) {     //search has wrapped
               found = true;
               rval = 1 + (buffer->max_count - buffer->head) + (last_found - (char *) buffer->data);
            }
         }
      }

      //haven't found the whole string, and we still have room.
      continue_searching = !found && ((buffer->count - (i - buffer->head)) > ((target_length) - target_index));
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

////Local implementations /////////////////////////////////////////

//test code for single byte search////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

//test code for multi byte search////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//106 chars + 9 char terminating string. buffer should contain no termination strings with 104 bytes left.
//  the next time around, the first message is 219 bytes (104 extra m's that didn't get parsed) , and the buffer will be cleared.
//  watch for the termination string to wrap around the end of the ring buffer.
//static char * test_msg = "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmstringend";
//static char * search_str = "stringend";

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
//      while (Multibyte_Ring_Buffer_Dequeue_Until_String(&test_buffer, dq_data, dq_max - dq_count, search_str)) {
//         Multibyte_Ring_Buffer_Get_Count(&test_buffer);
//      }
//   }
//}

