/*
 * String.c
 *
 *  Created on: Sep 22, 2015
 *      Author: mokogobo
 */

#include "String.h"

int getTokenCount (const char *string) {
	
	
}

#define DEFAULT_TOKEN_SECONDARY_DELIMIETER '"'

int8_t getToken (const char *string, char *tokenBuffer, int tokenIndex) {
	
	int i = 0;
	char *token = NULL;
	char *tokenStop = NULL;
	
	if (string != NULL && tokenBuffer != NULL) {
		
		// Handle case when tokenIndex is 0
		if (tokenIndex == 0) {
			
			token = string;
			tokenStop = strchr (token, ' '); // i.e., the case for a multi-token message (e.g., "turn light 1 on")
			if (tokenStop == NULL) {
				tokenStop = token + strlen (token); // i.e., the case for a single-token message
			}
			
		} else {
		
			// Iterate to the specified token index
			token = string;
			for (i = 0; i < tokenIndex; i++) {
				token = strchr (token, DEFAULT_TOKEN_DELIMIETER);
				if (token != NULL) {
					token = token + 1; // Move past the delimiter to the first character of the token.
					if (token[0] == DEFAULT_TOKEN_SECONDARY_DELIMIETER) {
						tokenStop = strchr (token + 1, DEFAULT_TOKEN_SECONDARY_DELIMIETER) + 1;
					} else {
						tokenStop = strchr (token, ' ');
					}
					
					if (tokenStop == NULL) {
						tokenStop = string + strlen (string); // Go to the end of the string (i.e., to the terminating '\0' character for the string).
					}
					
				} else {
					tokenStop = NULL;
				}
			}
		}
		
		// Copy the string into the specified buffer
		if (token != NULL && tokenStop != NULL) {
			
			if (token[0] == DEFAULT_TOKEN_SECONDARY_DELIMIETER) {
				strncpy (tokenBuffer, token + 1, tokenStop - token - 2);
			} else {
				strncpy (tokenBuffer, token, tokenStop - token);
			}
			tokenBuffer[tokenStop - token] = '\0'; // Terminate the string in the token buffer.
			
		}
		
		return TRUE; // (tokenStop - token); // Return the length of the token
		
	}
	
	return NULL;
}
