/*
 * AddressSerialization.h
 *
 *  Created on: Mar 2, 2016
 *      Author: thebh_000
 */

#ifndef MESSAGE_INFO_H_
#define MESSAGE_INFO_H_

#include "stdint.h"

////defines ///////////////////////////////////////////////////////
#define CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH     16

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
   MESSAGE_TYPE_UDP,
   MESSAGE_TYPE_TCP,
   MESSAGE_TYPE_COMMAND,
   MESSAGE_TYPE_INFO,
   MESSAGE_TYPE_MAX
} Message_Type;

////Globals   /////////////////////////////////////////////////////
//max 16 chars
extern char* message_strings[];
extern const char * address_terminator;
extern const char * address_delimiter;
extern const char * type_delimiter;
extern const char * port_delimiter;
extern const char * arg_delimiter;

////Prototypes/////////////////////////////////////////////////////
extern bool Get_Message_Type_Str(Message_Type type, char * returnStr);
extern Message_Type Get_Message_Type_From_Str(char * typeString);

#endif /* MESSAGE_INFO_H_*/
