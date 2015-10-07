/*
 * Interpreter.c
 *
 *  Created on: Sep 24, 2015
 *      Author: mokogobo
 */

#include "Messenger.h"

int8_t Process_Message (const char *message) {
	
	int8_t status = NULL;
	int8_t result = NULL;
	char token[32] = { 0 };
	int tokenInt = 0;
	int i;
	
	// TODO: Queue the message rather than executing it immediately (unless specified)
	// TODO: Parse the message rather than brute force like this.
	
	// turn light 1 on
	// ^
	if ((status = getToken (message, token, 0)) != NULL) { // status = getToken (message, token, 0);
		if (strncmp (token, "turn", strlen ("turn")) == 0) {
			
			if ((status = getToken (message, token, 1)) != NULL) {
			
				// turn lights on
				//      ^
				if (strncmp (token, "lights", strlen ("lights")) == 0) {
					
					if ((status = getToken (message, token, 2)) != NULL) { // TODO: Remove this! The parameter is used later.
						
						// turn lights on
						//             ^
						if (strncmp (token, "on", strlen ("on")) == 0) {
							
							// Turn all LEDs on
							for (i = 0; i < 12; i++) {
								Set_Channel_State (i, ON_CHANNEL);
							}
							
							result = TRUE;
							
						} else if (strncmp (token, "off", strlen ("off")) == 0) {
							
							// Turn all LEDs off
							for (i = 0; i < 12; i++) {
								Set_Channel_State (i, OFF_CHANNEL);
							}
							
							result = TRUE;
							
						}
					}
				
				// turn light 1 on
				//      ^
				} else if (strncmp (token, "light", strlen ("light")) == 0) {
					
					if ((status = getToken (message, token, 2)) != NULL) { // TODO: Remove this! The parameter is used later.
						
						if ((status = getToken (message, token, 3)) != NULL) {
							
							// turn light 1 on
							//              ^
							if (strncmp (token, "on", strlen ("on")) == 0) {
								
								// Turn the specified LED off
								status = getToken (message, token, 2);
								tokenInt = atoi (token);
								Set_LED_Output ((RGB_LED) tokenInt,  &onColor);
								
								result = TRUE;
								
							} else if (strncmp (token, "off", strlen ("off")) == 0) {
								
								// Turn the specified LED off
								status = getToken (message, token, 2);
								tokenInt = atoi (token);
								Set_LED_Output ((RGB_LED) tokenInt,  &offColor);
								
								result = TRUE;
								
							}
						}
					}
					
				// turn channel 1 on
				//      ^
				} else if (strncmp (token, "channel", strlen ("channel")) == 0) {
					
					if ((status = getToken (message, token, 2)) != NULL) { // TODO: Remove this! The parameter is used later.
						
						// turn channel 1 on
						//              ^
						
						if ((status = getToken (message, token, 3)) != NULL) {
							
							// turn channel 1 on
							//                ^
							if (strncmp (token, "on", strlen ("on")) == 0) {
								
								// Turn the specified LED off
								status = getToken (message, token, 2);
								tokenInt = atoi (token);
								Set_Channel_State (tokenInt, ON_CHANNEL);
								
								result = TRUE;
								
							} else if (strncmp (token, "off", strlen ("off")) == 0) {
								
								// Turn the specified LED off
								status = getToken (message, token, 2);
								tokenInt = atoi (token);
								Set_Channel_State (tokenInt, OFF_CHANNEL);
								
								result = TRUE;
								
							}
						}
					}
					
				}
				
			}
		}
	}
	
	return result;
}
