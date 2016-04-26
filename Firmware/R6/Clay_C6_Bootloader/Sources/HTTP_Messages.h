/*
 * HTTP_Messages.h
 *
 *  Created on: Apr 25, 2016
 *      Author: thebh_000
 */

#ifndef SOURCES_HTTP_MESSAGES_H_
#define SOURCES_HTTP_MESSAGES_H_

////Includes //////////////////////////////////////////////////////
#include "PE_Types.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Function Prototypes ///////////////////////////////////////////
extern bool Send_HTTP_GET_Request(char * destination, char * source, char * request_content);
extern bool Parse_HTTP_Response(char * response_content, char * output_buffer);

#endif /* SOURCES_HTTP_MESSAGES_H_ */
