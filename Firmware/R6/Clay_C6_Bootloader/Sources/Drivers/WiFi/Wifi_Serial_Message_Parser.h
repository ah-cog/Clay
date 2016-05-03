/*
 * Wifi_Serial_Message_Parser.h
 *
 *  Created on: May 2, 2016
 *      Author: thebh_000
 */

#ifndef SOURCES_DRIVERS_WIFI_WIFI_SERIAL_MESSAGE_PARSER_H_
#define SOURCES_DRIVERS_WIFI_WIFI_SERIAL_MESSAGE_PARSER_H_

////Includes //////////////////////////////////////////////////////
#include "Multibyte_Ring_Buffer.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
   SERIAL_STATUS_CONTENT_LENGTH_FOUND = 1,
   SERIAL_STATUS_MESSAGE_COMPLETE = 2,
   SERIAL_STATUS_MORE_AVAILABLE = 4,
   SERIAL_STATUS_MESSAGE_TOO_BIG = 8
} Serial_Parse_Status;

////Globals   /////////////////////////////////////////////////////

////Function Prototypes ///////////////////////////////////////////
Serial_Parse_Status Serial_Parse_From_Multibyte_Queue(Multibyte_Ring_Buffer * buffer,
                                                      uint8_t * output_buffer,
                                                      uint32_t output_buffer_length);

#endif /* SOURCES_DRIVERS_WIFI_WIFI_SERIAL_MESSAGE_PARSER_H_ */
