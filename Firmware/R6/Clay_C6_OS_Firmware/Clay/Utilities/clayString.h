#ifndef STRING_H
#define STRING_H

#include "stdint.h"

#define DEFAULT_TOKEN_DELIMIETER ' '
#define DEFAULT_TOKEN_SECONDARY_DELIMIETER '"'

extern int Get_Token_Count(const char *string);

extern int8_t Get_Token(const char *string, char *tokenBuffer, int tokenIndex);

extern int8_t Get_Token_With_Delimiter(const char *string,
                                       const char delimiter,
                                       const char secondaryDelimiter,
                                       char *tokenBuffer,
                                       int tokenIndex);

extern unsigned int Hex_String_To_UInt(char const* hexstring);

#endif
