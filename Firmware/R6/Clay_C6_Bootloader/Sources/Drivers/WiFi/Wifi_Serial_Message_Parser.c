/*
 * Wifi_Serial_Message_Parser.c
 *
 *  Created on: May 2, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "Wifi_Serial_Message_Parser.h"
#include "Multibyte_Ring_Buffer.h"
#include "Message.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////


////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
Serial_Parse_Status Serial_Parse_From_Multibyte_Queue(Multibyte_Ring_Buffer * buffer,
                                                      uint8_t * output_buffer,
                                                      uint32_t output_buffer_length) {
   Serial_Parse_Status rval = 0;

   uint32_t bytes_before_content_length = Multibyte_Ring_Buffer_Get_Bytes_Until_String_End(buffer, "");


   return rval;
}

////Local implementations /////////////////////////////////////////

