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
static char * http_get_request_format = "%s%s";

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
Message * Create_HTTP_GET_Request(char * destination, char * source, char * request_content) {

   Message * result = NULL;

   if (destination != NULL && source != NULL && request_content != NULL) {
      char * request_buffer = calloc(strlen(destination) + strlen(request_content) + 2, sizeof(char));

      sprintf(request_buffer, http_get_request_format, destination, request_content);

      result = Create_Message("none");
      Set_Message_Destination(result, request_buffer);
      Set_Message_Source(result, source);
      Set_Message_Type(result, "http");

      free(request_buffer);
   }

   return result;
}

////Local implementations /////////////////////////////////////////

