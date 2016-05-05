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

#include "Message.h"
#include "Multibyte_Ring_Buffer.h"
#include "Wifi_Message_Serialization.h"

////Macros ////////////////////////////////////////////////////////
#define BUFFER_TAIL(buffer)             ((buffer->data) + buffer->tail)
#define BUFFER_HEAD(buffer)             ((buffer->data) + buffer->head)

#define WIFI_FIELD_DELIMITER_COUNT              5
#define WIFI_TOTAL_DELIMITER_COUNT              6

#define WIFI_MESSAGE_TYPE_INDEX                 0
#define WIFI_SOURCE_INDEX                       1
#define WIFI_DESTINATION_INDEX                  2
#define WIFI_CONTENT_TYPE_INDEX                 3
#define WIFI_CONTENT_LENGTH_INDEX               4
#define WIFI_CONTENT_DELIMITER_INDEX            5

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
   SERIAL_STATUS_CONTENT_LENGTH_FOUND = 1,
   SERIAL_STATUS_MESSAGE_COMPLETE = 2,
   SERIAL_STATUS_MORE_AVAILABLE = 4,
   SERIAL_STATUS_MESSAGE_TOO_BIG = 8
} Serial_Parse_Status;

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

   //it's ok if this is nonzero when the buffer's full. rval is used to determine how much data can be put in.
   uint32_t free_bytes_after_tail = (
         (buffer->tail > buffer->head || (buffer->tail == buffer->head && buffer->count == 0)) ? (buffer->max_count - buffer->tail) :
                                                                                                 Multibyte_Ring_Buffer_Get_Free_Size(buffer));

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

//uint32_t Multibyte_Ring_Buffer_Dequeue_Until_Char(Multibyte_Ring_Buffer * buffer, uint8_t * data, uint32_t size, char end_char) {
//
//   uint32_t rval = Multibyte_Ring_Buffer_Get_Bytes_Before_Char(buffer, end_char);
//
//   if (rval > 0 && rval <= size) {
//      rval = Multibyte_Ring_Buffer_Dequeue(buffer, data, rval);
//   } else {
//      rval = 0;
//   }
//
//   return rval;
//}

//uint32_t Multibyte_Ring_Buffer_Get_Bytes_Before_Char(Multibyte_Ring_Buffer * buffer, char end_char) {
//
//   uint32_t bytes_after_head = (buffer->head < buffer->tail ? buffer->count : buffer->max_count - buffer->head);
//   uint32_t rval = 0;
//
//   uint8_t * char_location = memchr(BUFFER_HEAD(buffer), end_char, bytes_after_head);
//
//   if (char_location == NULL && ((buffer->head > buffer->tail) || (buffer->head == buffer->tail && buffer->count > 0))) {
//      char_location = memchr(buffer->data, end_char, buffer->tail);
//
//      if (char_location != NULL) {
//         rval = bytes_after_head + (char_location - buffer->data) + 1;
//      } else {
//         rval = 0;
//      }
//
//   } else if (char_location != NULL) {
//      rval = char_location - BUFFER_HEAD(buffer) + 1;
//   }
//
//   return rval;
//}

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

//end_str must be null terminated, but null is not searched for.
//returns the number of bytes until the end of the string.
uint32_t Multibyte_Ring_Buffer_Get_Bytes_Until_String_End(Multibyte_Ring_Buffer * buffer, char * end_str) {

   return Multibyte_Ring_Buffer_Get_Bytes_Until_String_End_From_Offset(buffer, end_str, 0);
}

uint32_t Multibyte_Ring_Buffer_Get_Bytes_Until_String_End_From_Offset(Multibyte_Ring_Buffer * buffer,
                                                                      char * end_str,
                                                                      uint32_t offset) {

   if (offset > buffer->count) {
      return 0;
   }

   int rval = 0;

   uint32_t buffer_head_index = (buffer->head + offset) % buffer->max_count;
   uint32_t buffer_size_offset = buffer->count - offset;

   char * first_found = NULL;
   char * last_found = NULL;
   bool found = false;
   bool continue_searching = true;

   uint32_t target_length = strlen(end_str);
   uint32_t first_char_index = 0;
   uint32_t target_index = 0;

   int i;
   for (i = buffer_head_index; i < (buffer_size_offset + buffer_head_index) && continue_searching; ++i) {

      if (first_found == NULL) {     //not out of data yet, and we haven't found the first char.

         if ((buffer->data)[i % buffer->max_count] == end_str[target_index]) {
            first_found = (buffer->data + (i % buffer->max_count));
            ++target_index;

            if (target_length == 1) {
               found = true;
               if (((char*) buffer->data + buffer->head) <= first_found) {
                  rval = 1 + (first_found - ((char*) buffer->data + buffer->head));
               } else {
                  rval = 1 + (buffer->max_count - buffer->head) + (first_found - (char *) buffer->data);
               }
            }
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
      continue_searching = !found && ((buffer_size_offset - (i - buffer_head_index)) > ((target_length) - target_index));
   }

   return rval;
}

//returns the number of bytes dequeued. Not the length of the message.
uint32_t Multibyte_Ring_Buffer_Dequeue_Full_Message(Multibyte_Ring_Buffer * buffer, Message ** response_message) {

   uint32_t rval = 0;
   uint32_t delimiter_indices[WIFI_TOTAL_DELIMITER_COUNT];
   uint32_t delimiter_count = 0;
   uint32_t content_length = 0;
   uint32_t total_length = 0;
   char * temp_buffer;

   //         0       1         2              3               4                 5
   //format: \f<type>\t<source>\t<destination>\t<content_type>\t<content_length>\t<content>

   delimiter_indices[0] = Multibyte_Ring_Buffer_Get_Bytes_Until_String_End(buffer, (char *) message_start);

   //found start char
   if (delimiter_indices[0] > 0) {

      //find field delimiters
      for (delimiter_count = 1; delimiter_count < WIFI_TOTAL_DELIMITER_COUNT; ++delimiter_count) {

         delimiter_indices[delimiter_count] = Multibyte_Ring_Buffer_Get_Bytes_Until_String_End_From_Offset(buffer,
                                                                                                           (char*) message_field_delimiter,
                                                                                                           delimiter_indices[delimiter_count
                                                                                                                             - 1]);

         if (delimiter_indices[delimiter_count] <= delimiter_indices[delimiter_count - 1]) {
            break;
         }
      }
   }

   if (delimiter_count == WIFI_TOTAL_DELIMITER_COUNT) {

      //replace delimiters with nulls.
      int i = 0;
      for (; i < WIFI_TOTAL_DELIMITER_COUNT; ++i) {
         *(buffer->data + ((buffer->head + delimiter_indices[i]) % buffer->max_count) - 1) = '\0';
      }

      rval = delimiter_indices[WIFI_CONTENT_DELIMITER_INDEX];

      //read the size out without dequeueing. we have to account for potential wrap around.
      for (i = delimiter_indices[WIFI_CONTENT_LENGTH_INDEX]; i < (delimiter_indices[WIFI_CONTENT_DELIMITER_INDEX] - 1); ++i) {
         //convert decimal text to ints,  shift current content length up by 1 significant digit.
         content_length = (content_length * 10) + (*(buffer->data + (i + buffer->head) % buffer->max_count) - 0x30);
      }

      if (content_length != 0 && (content_length + rval) <= buffer->count) {
         rval += content_length;

         temp_buffer = malloc(MAXIMUM_MESSAGE_LENGTH);

         (*response_message) = Create_Message();

         //dequeue, including delimiter. for everything except the content field, which has no terminating delimiter, the delimiter has been replaced with null.
         Multibyte_Ring_Buffer_Dequeue(buffer, temp_buffer, delimiter_indices[WIFI_MESSAGE_TYPE_INDEX]);     ///throw away up to start byte

         Multibyte_Ring_Buffer_Dequeue(buffer,
                                       temp_buffer,
                                       delimiter_indices[WIFI_SOURCE_INDEX] - delimiter_indices[WIFI_MESSAGE_TYPE_INDEX]);     ///dequeue message type.
         Set_Message_Type((*response_message), temp_buffer);

         Multibyte_Ring_Buffer_Dequeue(buffer,
                                       temp_buffer,
                                       delimiter_indices[WIFI_DESTINATION_INDEX] - delimiter_indices[WIFI_SOURCE_INDEX]);     ///dequeue source
         Set_Message_Source((*response_message), temp_buffer);

         Multibyte_Ring_Buffer_Dequeue(buffer,
                                       temp_buffer,
                                       delimiter_indices[WIFI_CONTENT_TYPE_INDEX] - delimiter_indices[WIFI_DESTINATION_INDEX]);     ///dequeue destination
         Set_Message_Destination((*response_message), temp_buffer);

         Multibyte_Ring_Buffer_Dequeue(buffer,
                                       temp_buffer,
                                       delimiter_indices[WIFI_CONTENT_LENGTH_INDEX] - delimiter_indices[WIFI_CONTENT_TYPE_INDEX]);     ///dequeue content type
         Set_Message_Content_Type((*response_message), temp_buffer);

         Multibyte_Ring_Buffer_Dequeue(buffer,
                                       temp_buffer,
                                       delimiter_indices[WIFI_CONTENT_DELIMITER_INDEX]
                                       - delimiter_indices[WIFI_CONTENT_LENGTH_INDEX]);     ///dequeue content length

         Multibyte_Ring_Buffer_Dequeue(buffer, temp_buffer, content_length);     ///dequeue content.

         Set_Message_Content((*response_message), temp_buffer, content_length);

         free(temp_buffer);

      } else {

         *(buffer->data + ((buffer->head + delimiter_indices[0] - 1) % buffer->max_count)) = *message_start;

         //replace the delimiters for next time.
         int i = 1;
         for (; i < WIFI_TOTAL_DELIMITER_COUNT; ++i) {
            *(buffer->data + ((buffer->head + delimiter_indices[i] - 1) % buffer->max_count)) = *message_field_delimiter;
         }

         rval = 0;
      }
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
//
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
//      while (Multibyte_Ring_Buffer_Dequeue_Until_String(&test_buffer, dq_data, dq_max - dq_count, "\n")) {
//         Multibyte_Ring_Buffer_Get_Count(&test_buffer);
//      }
//   }
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

//static char * test_msg = "\ftcp\t192.168.1.3:3000\t192.168.1.21:3000\ttext\t40\tmmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeee";
//static char * test_msg = "\ftcp\t192.168.1.3:3000\t192.168.1.21:3000\ttext\t256\tmmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmm256";

//uint32_t Multibyte_Ring_Buffer_Test() {
//   char dq_data[1024];
//   char serial_data[1024];
//   uint32_t dq_max = 1024;
//   uint32_t dq_count = 0;
//
//   Message * m;
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
//      while ((dq_count = Multibyte_Ring_Buffer_Dequeue_Full_Message(&test_buffer, &m)) > 0) {
//         Multibyte_Ring_Buffer_Get_Count(&test_buffer);
//         Serialize_Message(m, serial_data, 1024);
//         Delete_Message(m);
//         memset(serial_data, 0, 1024);
//      }
//   }
//}
