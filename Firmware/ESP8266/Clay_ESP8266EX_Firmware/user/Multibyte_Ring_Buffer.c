/*
 * Multibyte_Ring_Buffer.c
 *
 *  Created on: Apr 17, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"

#include "Message.h"
#include "Multibyte_Ring_Buffer.h"
#include "Wifi_Message_Serialization.h"
#include "CRC16.h"

////Macros ////////////////////////////////////////////////////////
#define EnterCritical taskENTER_CRITICAL
#define ExitCritical  taskEXIT_CRITICAL

#define BUFFER_TAIL(buffer)             ((buffer->data) + buffer->tail)
#define BUFFER_HEAD(buffer)             ((buffer->data) + buffer->head)

#define WIFI_FIELD_DELIMITER_COUNT              5
#define WIFI_TOTAL_DELIMITER_COUNT              9
#define WIFI_CONTENT_DELIMITER_COUNT            4

#define WIFI_MESSAGE_LENGTH_INDEX               0
#define WIFI_MESSAGE_CHECKSUM_INDEX             1
#define WIFI_MESSAGE_TYPE_INDEX                 2
#define WIFI_SOURCE_INDEX                       3
#define WIFI_DESTINATION_INDEX                  4
#define WIFI_CONTENT_LENGTH_INDEX               5
#define WIFI_CONTENT_CHECKSUM_INDEX             6
#define WIFI_CONTENT_TYPE_INDEX                 7
#define WIFI_CONTENT_INDEX                      8

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
void Multibyte_Ring_Buffer_Init(Multibyte_Ring_Buffer * buffer, uint32_t size)
{

	EnterCritical();
	buffer->max_count = size;
	buffer->data = malloc(buffer->max_count);
	buffer->head = 0;
	buffer->tail = 0;
	buffer->count = 0;

	memset(buffer->data, 0, buffer->max_count);
	ExitCritical();
}

void Multibyte_Ring_Buffer_Free(Multibyte_Ring_Buffer * buffer)
{

	EnterCritical();
	if (buffer->data != NULL)
	{
		free(buffer->data);
		buffer->max_count = 0;
	}
	ExitCritical();
}

void Multibyte_Ring_Buffer_Reset(Multibyte_Ring_Buffer * buffer)
{
	EnterCritical();
	buffer->head = 0;
	buffer->tail = 0;
	buffer->count = 0;
	memset(buffer->data, 0, buffer->max_count);
	ExitCritical();
}

uint32_t Multibyte_Ring_Buffer_Enqueue(Multibyte_Ring_Buffer * buffer,
		uint8_t * data, uint32_t size)
{

	if (buffer->data == NULL)
	{
		return 0;
	}

	uint32_t rval = (
			(Multibyte_Ring_Buffer_Get_Free_Size(buffer) > size) ?
					size : Multibyte_Ring_Buffer_Get_Free_Size(buffer));

	//it's ok if this is nonzero when the buffer's full. rval is used to determine how much data can be put in.
	uint32_t free_bytes_after_tail = (
			(buffer->tail > buffer->head
					|| (buffer->tail == buffer->head && buffer->count == 0)) ?
					(buffer->max_count - buffer->tail) :
					Multibyte_Ring_Buffer_Get_Free_Size(buffer));

	if (rval > 0)
	{
		if (rval < free_bytes_after_tail)
		{
			memcpy(BUFFER_TAIL(buffer), data, rval);
			buffer->tail = (buffer->tail + rval) % buffer->max_count;
		}
		else
		{
			memcpy(BUFFER_TAIL(buffer), data, free_bytes_after_tail);
			buffer->tail = (buffer->tail + free_bytes_after_tail)
					% buffer->max_count;

			memcpy(buffer->data, data + free_bytes_after_tail,
					rval - free_bytes_after_tail);
			buffer->tail = (buffer->tail + (rval - free_bytes_after_tail))
					% buffer->max_count;
		}

		buffer->count += rval;
	}

	return rval;
}

uint32_t Multibyte_Ring_Buffer_Dequeue(Multibyte_Ring_Buffer * buffer,
		uint8_t * data, uint32_t size)
{

	if (buffer->data == NULL)
	{
		return 0;
	}

	EnterCritical();
	uint32_t bytes_after_head = (
			buffer->head < buffer->tail ?
					buffer->count : buffer->max_count - buffer->head);
	uint32_t rval = (buffer->count > size ? size : buffer->count);
	ExitCritical();

	if (rval > 0)
	{
		if (rval < bytes_after_head)
		{
			memcpy(data, BUFFER_HEAD(buffer), rval);
			memset(BUFFER_HEAD(buffer), 0, rval);
			EnterCritical();
			buffer->head = (buffer->head + rval) % buffer->max_count;
			ExitCritical();

		}
		else
		{
			memcpy(data, BUFFER_HEAD(buffer), bytes_after_head);
			memset(BUFFER_HEAD(buffer), 0, bytes_after_head);

			EnterCritical();
			buffer->head = (buffer->head + bytes_after_head)
					% buffer->max_count;
			ExitCritical();

			memcpy(data + bytes_after_head, BUFFER_HEAD(buffer),
					rval - bytes_after_head);
			memset(BUFFER_HEAD(buffer), 0, rval - bytes_after_head);

			EnterCritical();
			buffer->head = (buffer->head + (rval - bytes_after_head))
					% buffer->max_count;
			ExitCritical();
		}

		EnterCritical();
		buffer->count -= rval;
		ExitCritical();
	}

	return rval;
}

#if 0

uint32_t Multibyte_Ring_Buffer_Dequeue_Until_Char(Multibyte_Ring_Buffer * buffer, uint8_t * data, uint32_t size, char end_char)
{

	uint32_t rval = Multibyte_Ring_Buffer_Get_Bytes_Before_Char(buffer, end_char);

	if (rval > 0 && rval <= size)
	{
		rval = Multibyte_Ring_Buffer_Dequeue(buffer, data, rval);
	}
	else
	{
		rval = 0;
	}

	return rval;
}

uint32_t Multibyte_Ring_Buffer_Get_Bytes_Before_Char(Multibyte_Ring_Buffer * buffer, char end_char)
{

	uint32_t bytes_after_head = (buffer->head < buffer->tail ? buffer->count : buffer->max_count - buffer->head);
	uint32_t rval = 0;

	uint8_t * char_location = memchr(BUFFER_HEAD(buffer), end_char, bytes_after_head);

	if (char_location == NULL && ((buffer->head > buffer->tail) || (buffer->head == buffer->tail && buffer->count > 0)))
	{
		char_location = memchr(buffer->data, end_char, buffer->tail);

		if (char_location != NULL)
		{
			rval = bytes_after_head + (char_location - buffer->data) + 1;
		}
		else
		{
			rval = 0;
		}

	}
	else if (char_location != NULL)
	{
		rval = char_location - BUFFER_HEAD(buffer) + 1;
	}

	return rval;
}

#endif

uint32_t Multibyte_Ring_Buffer_Dequeue_Until_String(
		Multibyte_Ring_Buffer * buffer, uint8_t * data, uint32_t size,
		char * end_string)
{
	if (buffer->data == NULL)
	{
		return 0;
	}

	uint32_t rval = Multibyte_Ring_Buffer_Get_Bytes_Until_String_End(buffer,
			end_string);

	if (rval > 0 && rval <= size)
	{
		rval = Multibyte_Ring_Buffer_Dequeue(buffer, data, rval);
	}
	else
	{
		rval = 0;
	}

	return rval;
}

//end_str must be null terminated, but null is not searched for.
//returns the number of bytes until the end of the string.
uint32_t Multibyte_Ring_Buffer_Get_Bytes_Until_String_End(
		Multibyte_Ring_Buffer * buffer, char * end_str)
{

	return Multibyte_Ring_Buffer_Get_Bytes_Until_String_End_From_Offset(buffer,
			end_str, 0);
}

uint32_t Multibyte_Ring_Buffer_Get_Bytes_Until_String_End_From_Offset(
		Multibyte_Ring_Buffer * buffer, char * end_str, uint32_t offset)
{
	if (buffer->data == NULL || offset > buffer->count)
	{
		return 0;
	}

	int rval = 0;

	EnterCritical();
	uint32_t buffer_head_index = (buffer->head + offset) % buffer->max_count;
	uint32_t buffer_size_offset = buffer->count - offset;
	ExitCritical();

	char * first_found = NULL;
	char * last_found = NULL;
	bool found = false;
	bool continue_searching = true;

	uint32_t target_length = strlen(end_str);
	uint32_t first_char_index = 0;
	uint32_t target_index = 0;

	int i;
	for (i = buffer_head_index;
			i < (buffer_size_offset + buffer_head_index) && continue_searching;
			++i)
	{

		if (first_found == NULL)
		{     //not out of data yet, and we haven't found the first char.

			if ((buffer->data)[i % buffer->max_count] == end_str[target_index])
			{
				first_found = (buffer->data + (i % buffer->max_count));
				++target_index;

				if (target_length == 1)
				{
					found = true;
					if (((char*) buffer->data + buffer->head) <= first_found)
					{
						rval =
								1
										+ (first_found
												- ((char*) buffer->data
														+ buffer->head));
					}
					else
					{
						rval = 1 + (buffer->max_count - buffer->head)
								+ (first_found - (char *) buffer->data);
					}
				}
			}
		}
		else
		{     //we're not out of data, and we found the first char.
			if ((buffer->data)[i % buffer->max_count] == end_str[target_index])
			{

				last_found = (buffer->data + (i % buffer->max_count));
				++target_index;
			}
			else
			{
				//start over
				first_found = NULL;
				found = false;
				target_index = 0;
			}

			if (last_found != NULL)
			{
				if (last_found > first_found)
				{     //our search hasn't wrapped around yet.
					if (1 + (last_found - first_found) == target_length)
					{
						found = true;
						rval = 1 + (i - buffer->head);
					}
				}
				else if (1 + (last_found - (char *) buffer->data)
						+ (buffer->max_count
								- (first_found - (char *) buffer->data))
						== target_length)
				{     //search has wrapped
					found = true;
					rval = 1 + (buffer->max_count - buffer->head)
							+ (last_found - (char *) buffer->data);
				}
			}
		}

		//haven't found the whole string, and we still have room.
		continue_searching = !found
				&& ((buffer_size_offset - (i - buffer_head_index))
						> ((target_length) - target_index));
	}

	return rval;
}

//allocates memory for a message if one is found in the buffer.
//  The message header fields are checked for <message_start>, to see if a message was partially received. In this case, destination
//      will be null and the number of bytes before the start of the interrupting message are dequeued, and that count is returned.
//  If no <message_start> is found in the headers, message length is parsed out of serialized message and used to determine if there is enough
//  data for the message
//  If enough data is not present, the queue will dequeue until a start character, if one is found. destination will be null upon return and
//      the return value will be the number of bytes dequeued.
//  If enough data is present, then destination will be allocated for message_length bytes, and the message will be dequeued into it.
//  The message is then checksummed.
//  If the checksum fails, destination is free'd and set to NULL, and the return is the number of bytes dequeued for the corrupt message, including
//      any bytes that were dequeued before the message.
//  If the checksum succeeds, the destination will contain the dequeued message upon return, and the return value is the number of bytes dequeued
//      for the corrupt message, including any bytes that were dequeued before the message.
uint32_t Multibyte_Ring_Buffer_Dequeue_Serialized_Message_With_Message_Header(
		Multibyte_Ring_Buffer * buffer, uint8_t * * destination)
{
	if (buffer->data == NULL || buffer->count == 0)
	{
		return 0;
	}

	uint32_t rval = 0;
	uint32_t delimiter_indices[WIFI_TOTAL_DELIMITER_COUNT];
	uint32_t delimiter_count = 0;

	uint32_t message_length = 0;
	uint16_t message_checksum = 0;

	uint32_t content_length = 0;
	uint32_t content_checksum = 0;

	bool parse_error = false;

	//         0                 1                   2               3         4              5                 6                   7               8
	//format: \f<message_length>\t<message_checksum>\t<message_type>\t<source>\t<destination>\t<content_length>\t<content_checksum>\t<content_type>\t<content>

	delimiter_indices[0] = Multibyte_Ring_Buffer_Get_Bytes_Until_String_End(
			buffer, (char *) message_start);

	//found start char
	if (delimiter_indices[0] > 0)
	{

		//find the other field delimiters
		for (delimiter_count = 1; delimiter_count < WIFI_TOTAL_DELIMITER_COUNT;
				++delimiter_count)
		{

			delimiter_indices[delimiter_count] =
					Multibyte_Ring_Buffer_Get_Bytes_Until_String_End_From_Offset(
							buffer, (char*) message_field_delimiter,
							delimiter_indices[delimiter_count - 1]);

			if (delimiter_indices[delimiter_count]
					<= delimiter_indices[delimiter_count - 1])
			{
				break;
			}
		}
	}

	if (delimiter_count == WIFI_TOTAL_DELIMITER_COUNT)
	{

		rval = Multibyte_Ring_Buffer_Get_Bytes_Until_String_End_From_Offset(
				buffer, (char *) message_start,
				delimiter_indices[WIFI_MESSAGE_LENGTH_INDEX]);

		//if we find a message start in the header fields, we just throw away the interrupted header.
		if ((rval != 0 && rval <= delimiter_indices[WIFI_CONTENT_INDEX]))
		{

			rval -= 1;

			EnterCritical();
			buffer->head = ((buffer->head + rval) % buffer->max_count);
			buffer->count -= rval;
			ExitCritical();

		}
		else if (((delimiter_indices[WIFI_MESSAGE_CHECKSUM_INDEX]
				- delimiter_indices[WIFI_MESSAGE_LENGTH_INDEX]) > 6) //also, verify that we only get 5 size bytes, 5 checksum bytes.
				|| ((delimiter_indices[WIFI_MESSAGE_TYPE_INDEX]
						- delimiter_indices[WIFI_MESSAGE_CHECKSUM_INDEX]) > 6))
		{
			//throw away up to the end of what was assumed to be a message header. We can safely discard up to the
			//     end of the checksum field, as we have found \f<size>\t<checksum>\t, so if either is wrong, then
			//     this isn't a valid message header.
			rval = delimiter_indices[WIFI_MESSAGE_CHECKSUM_INDEX];

			EnterCritical();
			buffer->head = ((buffer->head + rval) % buffer->max_count);
			buffer->count -= rval;
			ExitCritical();
		}
		else
		{
			//  If no <message_start> is found in the headers, message length is parsed out of serialized message and used to determine if there is enough
			//  data for the message
			int i;
			int temp;

			//read the message length without dequeueing. we have to account for potential wrap around.
			for (i = delimiter_indices[WIFI_MESSAGE_LENGTH_INDEX];
					i < (delimiter_indices[WIFI_MESSAGE_CHECKSUM_INDEX] - 1);
					++i)
			{
				temp = (*(buffer->data + (i + buffer->head) % buffer->max_count)
						- 0x30);     //get next byte, convert to number.

				if (temp >= 0 && temp <= 9)
				{     //verify that the character is a valid digit
					message_length = (message_length * 10) + temp;
				}
				else
				{
					//if it's not a digit, then we can dequeue up to this point safely.

					EnterCritical();
					buffer->head = ((buffer->head + i) % buffer->max_count);
					buffer->count -= i;
					ExitCritical();

					parse_error = true;
				}
			}

			if (!parse_error)
			{
				if (buffer->count
						< (message_length
								+ delimiter_indices[WIFI_MESSAGE_LENGTH_INDEX]
								- 1))
				{     //include the data before the start character.
					//  If enough data is not present, the queue will dequeue until a start character, if one is found. destination will be null upon return and
					//      the return value will be the number of bytes dequeued.
					rval = delimiter_indices[WIFI_MESSAGE_LENGTH_INDEX] - 1;

					EnterCritical();
					buffer->head = (buffer->head + rval) % buffer->max_count;
					buffer->count -= rval;
					ExitCritical();

				}
				else
				{

					//read the message checksum out without dequeueing. we have to account for potential wrap around.
					for (i = delimiter_indices[WIFI_MESSAGE_CHECKSUM_INDEX];
							i < (delimiter_indices[WIFI_MESSAGE_TYPE_INDEX] - 1);
							++i)
					{
						temp =
								(*(buffer->data
										+ (i + buffer->head) % buffer->max_count)
										- 0x30); //get next byte, convert to number.

						if (temp >= 0 && temp <= 9)
						{     //verify that the character is a valid digit
							message_checksum = (message_checksum * 10) + temp;
						}
						else
						{
							//if it's not a digit, then we can dequeue up to this point safely.
							EnterCritical();
							buffer->head = ((buffer->head + i)
									% buffer->max_count);
							buffer->count -= i;
							ExitCritical();

							parse_error = true;
						}
					}

					if (!parse_error)
					{
						*destination = malloc(message_length);
						//dequeue until start of message
						rval = Multibyte_Ring_Buffer_Dequeue(buffer,
								*destination,
								delimiter_indices[WIFI_MESSAGE_LENGTH_INDEX]
										- 1);

						//  If enough data is present, then destination will be allocated for message_length bytes, and the message will be dequeued into it.
						rval += Multibyte_Ring_Buffer_Dequeue(buffer,
								*destination, message_length);

						//  The message is then checksummed.
						//  If the checksum fails, destination is free'd and set to NULL, and the return is the number of bytes dequeued for the corrupt message

						if (message_checksum
								!= Calculate_Checksum_On_Bytes(
										(*destination)
												+ (delimiter_indices[WIFI_MESSAGE_TYPE_INDEX]
														- delimiter_indices[WIFI_MESSAGE_LENGTH_INDEX]
														+ 1),
										(message_length
												- (delimiter_indices[WIFI_MESSAGE_TYPE_INDEX]
														- delimiter_indices[WIFI_MESSAGE_LENGTH_INDEX]
														+ 1))))
						{
							free(*destination);
							*destination = NULL;
						}
					}
				}
			}
		}
	}

	return rval;
}

//allocates memory for a message without the message header and frame fields
//  get the length and checksum from the queue
//  if a \f is found in there, we dequeue until that, and drop the message we were working on
//  if no \f is found, and there's enough data to get the entire message, we dequeue.
uint32_t Multibyte_Ring_Buffer_Dequeue_Serialized_Message_Content(
		Multibyte_Ring_Buffer * buffer, uint8_t * * destination)
{

	if (buffer->data == NULL || buffer->count == 0)
	{
		return 0;
	}

	uint32_t rval = 0;
	uint32_t delimiter_indices[WIFI_CONTENT_DELIMITER_COUNT];
	uint32_t delimiter_count = 0;

	uint32_t message_length = 0;
	uint32_t content_length = 0;
	uint16_t content_checksum = 0;

	bool parse_error = false;

	//         0                 1                   2               3
	//format: \f<content_length>\t<content_checksum>\t<content_type>\t<content>

	delimiter_indices[0] = Multibyte_Ring_Buffer_Get_Bytes_Until_String_End(
			buffer, (char *) message_start);

	//found start char
	if (delimiter_indices[0] > 0)
	{

//find the other field delimiters
		for (delimiter_count = 1;
				delimiter_count < WIFI_CONTENT_DELIMITER_COUNT;
				++delimiter_count)
		{

			delimiter_indices[delimiter_count] =
					Multibyte_Ring_Buffer_Get_Bytes_Until_String_End_From_Offset(
							buffer, (char*) message_field_delimiter,
							delimiter_indices[delimiter_count - 1]);

			if (delimiter_indices[delimiter_count]
					<= delimiter_indices[delimiter_count - 1])
			{
				break;
			}
		}
	}

	if (delimiter_count == WIFI_CONTENT_DELIMITER_COUNT)
	{

		rval =
				Multibyte_Ring_Buffer_Get_Bytes_Until_String_End_From_Offset(
						buffer, (char *) message_start,
						delimiter_indices[WIFI_CONTENT_INDEX
								- WIFI_CONTENT_LENGTH_INDEX]);

//if we find a message start in the header fields, we just throw away the interrupted header.
		if (rval != 0
				&& rval
						<= delimiter_indices[WIFI_CONTENT_INDEX
								- WIFI_CONTENT_LENGTH_INDEX])
		{
			rval -= 1;

			EnterCritical();
			buffer->head = ((buffer->head + rval) % buffer->max_count);
			buffer->count -= rval;
			ExitCritical();
		}
		else
		{
			//  If no <message_start> is found in the headers, content length is parsed out of serialized message and used to determine if there is enough
			//  data for the message
			int i;
			int temp;

			//read the message length without dequeueing. we have to account for potential wrap around.
			for (i = delimiter_indices[WIFI_CONTENT_LENGTH_INDEX
					- WIFI_CONTENT_LENGTH_INDEX];
					i
							< (delimiter_indices[WIFI_CONTENT_CHECKSUM_INDEX
									- WIFI_CONTENT_LENGTH_INDEX] - 1); ++i)
			{
				temp = (*(buffer->data + (i + buffer->head) % buffer->max_count)
						- 0x30);     //get next byte, convert to number.

				if (temp >= 0 && temp <= 9)
				{     //verify that the character is a valid digit
					content_length = (content_length * 10) + temp;
				}
				else
				{
					//if it's not a digit, then we can dequeue up to this point safely.
					EnterCritical();
					buffer->head = ((buffer->head + i) % buffer->max_count);
					buffer->count -= i;
					ExitCritical();

					parse_error = true;
				}
			}

			if (!parse_error)
			{
				message_length = content_length
						+ (delimiter_indices[WIFI_CONTENT_INDEX
								- WIFI_CONTENT_LENGTH_INDEX]
								- delimiter_indices[WIFI_CONTENT_LENGTH_INDEX
										- WIFI_CONTENT_LENGTH_INDEX]) + 1;

				if (buffer->count
						< (message_length
								+ delimiter_indices[WIFI_CONTENT_LENGTH_INDEX
										- WIFI_CONTENT_LENGTH_INDEX] - 1))
				{
					//  If enough data is not present, the queue will dequeue until a start character, if one is found. destination will be null upon return and
					//      the return value will be the number of bytes dequeued.

					rval = delimiter_indices[WIFI_CONTENT_LENGTH_INDEX
							- WIFI_CONTENT_LENGTH_INDEX] - 1;
					EnterCritical();
					buffer->head = (buffer->head + rval) % buffer->max_count;
					buffer->count -= rval;
					ExitCritical();

				}
				else
				{

					//read the message checksum out without dequeueing. we have to account for potential wrap around.
					for (i = delimiter_indices[WIFI_CONTENT_CHECKSUM_INDEX
							- WIFI_CONTENT_LENGTH_INDEX];
							i
									< (delimiter_indices[WIFI_CONTENT_TYPE_INDEX
											- WIFI_CONTENT_LENGTH_INDEX] - 1);
							++i)
					{
						temp =
								(*(buffer->data
										+ (i + buffer->head) % buffer->max_count)
										- 0x30); //get next byte, convert to number.

						if (temp >= 0 && temp <= 9)
						{     //verify that the character is a valid digit
							content_checksum = (content_checksum * 10) + temp;
						}
						else
						{
							//if it's not a digit, then we can dequeue up to this point safely.
							EnterCritical();
							buffer->head = ((buffer->head + i)
									% buffer->max_count);
							buffer->count -= i;
							ExitCritical();

							parse_error = true;
						}
					}

					if (!parse_error)
					{
						*destination = malloc(message_length);

						//dequeue until start of message
						rval = Multibyte_Ring_Buffer_Dequeue(buffer,
								*destination,
								delimiter_indices[WIFI_CONTENT_LENGTH_INDEX
										- WIFI_CONTENT_LENGTH_INDEX] - 1);

						//  If enough data is present, then destination will be allocated for message_length bytes, and the message will be dequeued into it.
						rval += Multibyte_Ring_Buffer_Dequeue(buffer,
								*destination, message_length);

						//  The message is then checksummed.
						//  If the checksum fails, destination is free'd and set to NULL, and the return is the number of bytes dequeued for the corrupt message

						if (content_checksum
								!= Calculate_Checksum_On_Bytes(
										(*destination)
												+ (delimiter_indices[WIFI_CONTENT_INDEX
														- WIFI_CONTENT_LENGTH_INDEX]
														- delimiter_indices[WIFI_CONTENT_LENGTH_INDEX
																- WIFI_CONTENT_LENGTH_INDEX]
														+ 1), content_length))
						{
							free(*destination);
							*destination = NULL;
						}
					}
				}
			}
		}
	}

	return rval;
}

uint32_t Multibyte_Ring_Buffer_Get_Free_Size(Multibyte_Ring_Buffer * buffer)
{

	EnterCritical();
	uint32_t rval = buffer->max_count - buffer->count;
	ExitCritical();
	return rval;
}

uint32_t Multibyte_Ring_Buffer_Get_Count(Multibyte_Ring_Buffer * buffer)
{

	EnterCritical();
	uint32_t rval = buffer->count;
	ExitCritical();
	return rval;
}

bool Multibyte_Ring_Buffer_Full(Multibyte_Ring_Buffer * buffer)
{

	EnterCritical();
	bool rval = buffer->count >= buffer->max_count;
	ExitCritical();

	return rval;
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

//static char * test_msg = "\ftcp\t192.168.1.3:3000\t192.168.1.21:3000\ttext\t256\tmmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmm256";

//uint32_t Multibyte_Ring_Buffer_Test() {
//
//   char * test_msg_type = "tcp";
//   char * test_msg_source = "192.168.1.3:3000";
//   char * test_msg_dest = "192.168.1.21:3000";
//   char * test_msg_content_type = "text";
////   char * test_msg_content = "mmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeee";     //40 chars
////   char * test_msg_content = "mmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmm256"; //256 chars
//   char * test_msg_content = "mmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmm!!mmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemm512";     //512 chars
//
//   Message * test_msg = Create_Message();
//   Set_Message_Type(test_msg, test_msg_type);
//   Set_Message_Source(test_msg, test_msg_source);
//   Set_Message_Destination(test_msg, test_msg_dest);
//   Set_Message_Content_Type(test_msg, test_msg_content_type);
//   Set_Message_Content(test_msg, test_msg_content, strlen(test_msg_content));
//
//   uint32_t test_msg_str_len = 1024;
//   char test_msg_str[test_msg_str_len];
//   memset(test_msg_str, 0, test_msg_str_len);
//   Serialize_Message_With_Message_Header(test_msg, test_msg_str, test_msg_str_len);
//
//   uint8_t * serial_data;
//   uint32_t dq_count = 0;
//
//   Message * deserialized_message;
//   Message * deserialized_message_content;
//
//   Multibyte_Ring_Buffer test_buffer;
//
//   Multibyte_Ring_Buffer_Init(&test_buffer, 2048);
//
//   for (;;) {
//      while (!Multibyte_Ring_Buffer_Full(&test_buffer)) {
//         Multibyte_Ring_Buffer_Enqueue(&test_buffer, test_msg_str, strlen(test_msg_str));
//      }
//
//      while ((dq_count = Multibyte_Ring_Buffer_Dequeue_Serialized_Message_With_Message_Header(&test_buffer, &serial_data)) > 0) {
//         if (serial_data != NULL) {
//            deserialized_message = Deserialize_Message_With_Message_Header(serial_data);
//            Serialize_Message_Content(deserialized_message, serial_data, dq_count);
//            Delete_Message(deserialized_message);
//            free(serial_data);
//            serial_data = NULL;
//         }
//      }
//   }
//}

//uint32_t Multibyte_Ring_Buffer_Test() {
//
//   char * test_msg_type = "tcp";
//   char * test_msg_source = "192.168.1.3:3000";
//   char * test_msg_dest = "192.168.1.21:3000";
//   char * test_msg_content_type = "text";
////   char * test_msg_content = "mmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeee";     //40 chars
////   char * test_msg_content = "mmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmm256"; //256 chars
//   char * test_msg_content = "mmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmm!!mmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemmmmmeeeeemm512";     //512 chars
//
//   Message * test_msg = Create_Message();
//   Set_Message_Type(test_msg, test_msg_type);
//   Set_Message_Source(test_msg, test_msg_source);
//   Set_Message_Destination(test_msg, test_msg_dest);
//   Set_Message_Content_Type(test_msg, test_msg_content_type);
//   Set_Message_Content(test_msg, test_msg_content, strlen(test_msg_content));
//
//   uint32_t test_msg_str_len = 1024;
//   char test_msg_str[test_msg_str_len];
//   memset(test_msg_str, 0, test_msg_str_len);
////   Serialize_Message_Content(test_msg, test_msg_str, test_msg_str_len);
//   Serialize_Message_With_Message_Header(test_msg, test_msg_str, test_msg_str_len);
//
//   uint8_t * serial_data;
//   uint32_t dq_count = 0;
//
//   Message * deserialized_message;
//   Message * deserialized_message_content;
//
//   Multibyte_Ring_Buffer test_buffer;
//
//   Multibyte_Ring_Buffer_Init(&test_buffer, 2048);
//
//   for (;;) {
//      while (!Multibyte_Ring_Buffer_Full(&test_buffer)) {
//         Multibyte_Ring_Buffer_Enqueue(&test_buffer, test_msg_str, strlen(test_msg_str));
//         Multibyte_Ring_Buffer_Enqueue(&test_buffer,
//                                       test_msg_content,
//                                       strlen(test_msg_content) - (Millis() % (strlen(test_msg_content) - 10)));
//      }
//
////      while ((dq_count = Multibyte_Ring_Buffer_Dequeue_Serialized_Message_Content(&test_buffer, &serial_data)) > 0) {
//      while ((dq_count = Multibyte_Ring_Buffer_Dequeue_Serialized_Message_With_Message_Header(&test_buffer, &serial_data)) > 0) {
//         if (serial_data != NULL) {
//            deserialized_message = Deserialize_Message_With_Message_Header(serial_data);
////            deserialized_message = Deserialize_Message_Content(serial_data);
//            Serialize_Message_With_Message_Header(deserialized_message, serial_data, dq_count);
////            Serialize_Message_Content(deserialized_message, serial_data, dq_count);
//            Delete_Message(deserialized_message);
//            free(serial_data);
//            serial_data = NULL;
//         }
//      }
//   }
//}
