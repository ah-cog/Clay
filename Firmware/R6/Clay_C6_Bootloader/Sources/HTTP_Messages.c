/*
 * HTTP_Messages.c
 *
 *  Created on: Apr 25, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

#include "HTTP_Messages.h"
#include "WiFi.h"
#include "Message.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static char * http_get_request_format = "GET %s HTTP/1.1\r\n";

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
bool Send_HTTP_GET_Request(char * destination, char * source, char * request_content) {

   bool result = FALSE;

   if (destination != NULL && source != NULL && request_content != NULL) {
      char * request_buffer = calloc(strlen(request_content) + strlen(http_get_request_format) + 2, sizeof(char));

      sprintf(request_buffer, http_get_request_format, request_content);

      Message * request = Create_Message(request_buffer);
      Set_Message_Destination(request, destination);
      Set_Message_Source(request, source);
      Set_Message_Type(request, "tcp");

      free(request_buffer);

      result = Wifi_Send(request);
   }

   return result;
}

bool Parse_HTTP_Response(char * response_content, char * output_buffer) {

   bool result = FALSE;



   return result;
}

////Local implementations /////////////////////////////////////////

