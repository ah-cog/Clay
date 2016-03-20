/*
 * String.h
 *
 *  Created on: Sep 22, 2015
 *      Author: mokogobo
 */

#ifndef STRING_H_
#define STRING_H_

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

#define DEFAULT_TOKEN_DELIMIETER ' '
#define DEFAULT_TOKEN_SECONDARY_DELIMIETER '"'

int Get_Token_Count (const char *string);

int8_t Get_Token (const char *string, char *tokenBuffer, int tokenIndex); // TODO: Rename to copyToken?

int8_t getTokenWithDelimiter (const char *string, const char delimiter, const char secondaryDelimiter, char *tokenBuffer, int tokenIndex);

//int convertToInt (const char *string, char *tokenBuffer, int tokenIndex);

#endif /* STRING_H_ */
