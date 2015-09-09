/*
 * ESP8266.c
 * 
 * Driver for the ESP8266.
 * 
 * Notes:
 * - This file depends on ESP8266_RxBuf.h (ring buffer driver used for 
 *   buffering incoming data) and AS1.h (serial device driver). The dependency 
 *   hierarchy is illustrated below.
 *   
 *   ESP8266.h
 *   + ESP8266_RxBuf.h (ring buffer driver used for buffering incoming data)
 *   + AS1.h (serial device driver)
 *
 *  Created on: Aug 31, 2015
 *      Author: mokogobo
 */

#include "ESP8266.h"
#include "ESP8266_RxBuf.h"

#include <stdio.h>
#include <string.h>

void ESP8266_Init (void) {
	
	// Initialize the ESP8266 device data structure
	deviceData.handle   = AS1_Init (&deviceData);
	deviceData.isSent   = FALSE;
	deviceData.rxChar   = '\0';
	deviceData.rxPutFct = ESP8266_RxBuf_Put;

	// Initialize a buffer for storing incoming data from the ESP8266
	ESP8266_RxBuf_Init ();

	// Read any pending data to "clear the line"
	while (AS1_ReceiveBlock (deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof (deviceData.rxChar)) != ERR_OK) {

	}
}

void ESP8266_Send_Char (unsigned char ch, ESP8266_UART_Device *desc) {
	desc -> isSent = FALSE;
	while (AS1_SendBlock (desc -> handle, (LDD_TData*) &ch, 1) != ERR_OK) {

	}
	while (!desc->isSent) {

	}
}

void ESP8266_Send_String (const unsigned char *str, ESP8266_UART_Device *desc) {
	while (*str != '\0') {
		ESP8266_Send_Char (*str++, desc);
	}
}

byte ESP8266_Get_Incoming_Buffer_Size () {
	return ESP8266_RxBuf_NofElements ();
}

byte ESP8266_Get_Incoming_Character (byte *elemP) {
	return ESP8266_RxBuf_Get (elemP);
}

/**
 * Searches the entire specified buffer string for the specified response.
 * 
 * buffer : Pointer to the "response buffer" to search for one of the expected responses. The "response buffer" is where the characters received from the ESP8266 in response to a command are stored temporarily for processing.
 * bufferSize : The current size of the response buffer <code>buffer</code>.
 * 
 * returns : a code corresponding to an expected response (e.g., COMMAND_RESPONSE_OK, COMMAND_RESPONSE_ERROR, etc.)
 */
int8_t ESP8266_Search_For_Response (const char *response, const char *buffer, int bufferSize) {
	printf ("\t\tESP8266_Search_For_Response \"%s\" in \"%s\" (bufferSize: %d)\r\n", response, buffer, bufferSize);
	
	uint8_t found = FALSE;
	int i, j;
	
	if (bufferSize >= strlen (response)) { // Wait until enough characters have been buffered to search the string for the terminal character sequence.
		
		
		// Search for the specified response in the specified buffer (by searching for the substring, character-wise)...
		if ((bufferSize - strlen (response)) >= 0) {
			for (i = 0; i < bufferSize - strlen (response); i++) {
				if (buffer[i] == response[0]) { // Check if the current character is the same as the starting character of the buffer
					found = TRUE;
					for (j = 0; j < strlen (response); j++) {
						if (buffer[i + j] != response[j]) {
							found = FALSE;
							printf ("Found a mismatch!\r\n");
							break;
						}
					}
					if (found == TRUE) {
						printf ("Found a match!");
						return RESPONSE_FOUND;
					}
				}
			}
		}
		
		return RESPONSE_NOT_FOUND;
		
//		if (strncmp ((char *) (buffer + (bufferSize - strlen (response))), response, strlen (response)) == 0) {
//			printf ("\tFound \"%s\" response.\r\n", response);
//			return RESPONSE_FOUND;
//		}
	}
	
	// TODO: return STRING_TO_SEARCH_TOO_SMALL or something like it
	
//	// Check if the response from the ESP8266 matches one of the expected responses for the command according to the specification (e.g., as defined by Espressif for the AT command set for this firmware version).
//	if (bufferSize >= strlen (RESPONSE_SIGNATURE_OK)) { // Wait until enough characters have been buffered to search the string for the terminal character sequence.
//		if (strncmp ((char *) (buffer + (bufferSize - strlen (RESPONSE_SIGNATURE_OK))), RESPONSE_SIGNATURE_OK, strlen (RESPONSE_SIGNATURE_OK)) == 0) {
//			printf ("\tGot OK response!\r\n");
//			return RESPONSE_OK;
//		}
//	}
//	
//	if (strlen (buffer) >= strlen (RESPONSE_SIGNATURE_ERROR)) {
//		if (strncmp ((char *) (buffer + (bufferSize - strlen (RESPONSE_SIGNATURE_ERROR))), RESPONSE_SIGNATURE_ERROR, strlen (RESPONSE_SIGNATURE_ERROR)) == 0) {
//			printf ("\tGot ERROR response!\r\n");
//			return RESPONSE_ERROR;
//		}
//	}
	
//	else {
//				// DEBUG: printf ("Received unknown response! Clay will report this message.\r\n");
//				// TODO: If this was executed, then an unhandled response was encountered, so send a message to the Clay team's email address so they can fix it. This probably means the AT command set was changed or wasn't completely implemented.
//				return RESPONSE_NOT_FOUND;
//			}
	
	return RESPONSE_NOT_FOUND;
	
}

/**
 * Searches the end of the specified string "buffer" for the specified pattern "response".
 * 
 * buffer : Pointer to the "response buffer" to search for one of the expected responses. The "response buffer" is where the characters received from the ESP8266 in response to a command are stored temporarily for processing.
 * bufferSize : The current size of the response buffer <code>buffer</code>.
 * 
 * returns : a code corresponding to an expected response (e.g., COMMAND_RESPONSE_OK, COMMAND_RESPONSE_ERROR, etc.)
 */
int8_t ESP8266_Search_Tail_For_Response (const char *response, const char *buffer, int bufferSize) {
	printf ("\t\tESP8266_Search_For_Response \"%s\" in \"%s\" (bufferSize: %d)\r\n", response, buffer, bufferSize);
	
	if (bufferSize >= strlen (response)) { // Wait until enough characters have been buffered to search the string for the terminal character sequence.
		if (strncmp ((char *) (buffer + (bufferSize - strlen (response))), response, strlen (response)) == 0) {
			printf ("\tFound \"%s\" response.\r\n", response);
			return RESPONSE_FOUND;
		}
	}
	
	// TODO: Return STRING_TO_SEARCH_TOO_SMALL or something like it.
	
	return RESPONSE_NOT_FOUND;
	
}

int8_t ESP8266_Wait_For_Response (const char* response, uint32_t milliseconds) {
	printf ("\tESP8266_Wait_For_Response \"%s\"\r\n", response);
	
	// Block until receive "OK" or "ERROR" is received, an unknown response was received, or a timeout period has expired.
	// char httpResponseBuffer[RESPONSE_BUFFER_SIZE]; // TODO: Make this big enough only to store expected responses and only buffer the most recent set of received characters (i.e., shift characters into and out of the "sliding window" buffer).
	// int bufferSize;
	int i;
	int8_t commandResponse;
	for (httpBufferSize = 0; httpBufferSize < HTTP_RESPONSE_BUFFER_SIZE; httpBufferSize++) { httpResponseBuffer[httpBufferSize] = (char) 0; } // Initialize the buffer. This might not be necessary.
	httpBufferSize = 0;
	uint8_t incomingBufferSize = 0;
	commandResponse = RESPONSE_NOT_FOUND;
	
	// TODO: Start a timer.
	
	while (commandResponse < 0) {
		// TODO: Check timer in while condition and break if timeout period expires.
		
		// Buffer all incoming characters
		incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
		if (incomingBufferSize > 0) { // Check if any data has been received
			printf ("incomingBufferSize (before) = %d\r\n", incomingBufferSize);
			while (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Read each of the received characters from the buffer and send them to the device.
				unsigned char ch;
				(void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
				incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
				printf ("incomingBufferSize (after) = %d (ch: %c)\r\n", incomingBufferSize, ch);
				
				if (httpBufferSize < HTTP_RESPONSE_BUFFER_SIZE) {
					httpResponseBuffer[httpBufferSize++] = ch; // Store the received character in the buffer.
				} else {
					// Shift the elements to the left
					for (i = 0; i < HTTP_RESPONSE_BUFFER_SIZE - 1; i++) {
						httpResponseBuffer[i] = httpResponseBuffer[i + 1];
					}
					
					// Add the newest element to the end of the buffer
					httpResponseBuffer[HTTP_RESPONSE_BUFFER_SIZE - 1] = ch;
				}
				
//				// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
//				// Option 1: Search for an expected response after every character to avoid removing characters from the buffer that aren't associated with this command.
				commandResponse = ESP8266_Search_Tail_For_Response (response, httpResponseBuffer, httpBufferSize);
				if (commandResponse > 0) { break; }
			}
			
			// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
			// Option 1: Search for an expected response after every character to avoid removing characters from the buffer that aren't associated with this command.
			// commandResponse = ESP8266_Search_For_Response (response, responseBuffer, bufferSize);
		}
		
//		// Empty the remaining characters on the buffer
//		incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
//		if (incomingBufferSize > 0) { // Check if any data has been received
//			while (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Read each of the received characters from the buffer and send them to the device.
//				unsigned char ch;
//				(void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
//			}
//		}
		
		/*
		// Option 2: Search for a response after every received character has been buffered.
		receivedResponse = ESP8266_Search_For_Response (atCommandResponseBuffer, bufferSize);
		*/
	}
//	bufferSize++; // Move past the final character so the terminating character can be written to the buffer.
//	// TODO: Check the buffer size to see if it's overflowed. If so, return a "buffer size exceeded"/"buffer overflow" error.
//	responseBuffer[bufferSize] = '\0'; // Terminate the buffered response string.
	
//	printf ("%s", atCommandResponseBuffer);
//	fflush (stdout);
	
	// TODO: Return RESPONSE_TIMEOUT if timeout period expires.
	return commandResponse; // Hack. Replace with suggestion in the TODO on the previous line.
	
}


int8_t ESP8266_Send_Command_AT () {
	printf ("ESP8266_Send_Command_AT\r\n");
	
	int8_t response = RESPONSE_NOT_FOUND;
	//ESP8266_Send_String ("AT\r\n", &deviceData);
	if (AS1_SendBlock (deviceData.handle, "AT\r\n", (uint16_t) strlen ((char*) "AT\r\n")) != ERR_OK) {
		return ERR_FAILED;
	}
	
	// TODO: (Optional) Insert a wait here, if the function isn't consistently reliable.
	// TODO: Set up a timer that expires after specified amount of time to terminate this operation if the ESP8266 does not respond as expected in a typically timely manner.
	
	response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT); // TODO: (New) Handle OK and ERROR here or elsewhere!
	return response;
}

int8_t ESP8266_Send_Command_AT_RST () {
	printf ("ESP8266_Send_Command_AT_RST\r\n");
	
	int8_t response = RESPONSE_NOT_FOUND;
	//ESP8266_Send_String ("AT\r\n", &deviceData);
	if (AS1_SendBlock (deviceData.handle, "AT+RST\r\n", (uint16_t) strlen ((char*) "AT+RST\r\n")) != ERR_OK) {
		return ERR_FAILED;
	}
	
	// TODO: (Optional) Insert a wait here, if the function isn't consistently reliable.
	// TODO: Set up a timer that expires after specified amount of time to terminate this operation if the ESP8266 does not respond as expected in a typically timely manner.
	
	response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT); // TODO: (New) Handle OK and ERROR here or elsewhere!
	// TODO: Wait for "ready\r\n" (or might be slighly different character sequence like "ready\r\r\n")
	response = ESP8266_Wait_For_Response ("ready", DEFAULT_RESPONSE_TIMEOUT);
	return response;
	
//	ESP8266_Send_String ("AT+RST\r\n", &deviceData);
//	return ESP8266_Wait_For_Response (DEFAULT_RESPONSE_TIMEOUT);
}


int8_t ESP8266_Send_Command_AT_CWMODE (uint8_t mode) {
	printf ("ESP8266_Send_Command_AT_CWMODE\r\n");
	
	int8_t response = RESPONSE_NOT_FOUND;
	
	if (mode == 1) {
		//ESP8266_Send_String ("AT+CWMODE_CUR=1\r\n", &deviceData); // TODO: Change this to use SendBlock! First check if it works this way... get a feel of it.
		if (AS1_SendBlock (deviceData.handle, "AT+CWMODE_CUR=1\r\n", (uint16_t) strlen ((char*) "AT+CWMODE_CUR=1\r\n")) != ERR_OK) {
			return ERR_FAILED;
		}
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT);
	} else if (mode == 2) {
		//ESP8266_Send_String ("AT+CWMODE_CUR=2\r\n", &deviceData);
		if (AS1_SendBlock (deviceData.handle, "AT+CWMODE_CUR=2\r\n", (uint16_t) strlen ((char*) "AT+CWMODE_CUR=2\r\n")) != ERR_OK) {
			return ERR_FAILED;
		}
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT);
	} else if (mode == 3) {
		//ESP8266_Send_String ("AT+CWMODE_CUR=3\r\n", &deviceData);
		if (AS1_SendBlock (deviceData.handle, "AT+CWMODE_CUR=3\r\n", (uint16_t) strlen ((char*) "AT+CWMODE_CUR=3\r\n")) != ERR_OK) {
			return ERR_FAILED;
		}
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT);
	} else {
		return -3; // TODO: Create a #define directive for this. ERR_FAILED?
	}
	
	return response;
}


int8_t ESP8266_Send_Command_AT_CWJAP (const char *ssid, const char *password) {
	printf ("ESP8266_Send_Command_AT_CWJAP\r\n");
	
	char buffer[64] = { 0 };
	int n;
	
	int8_t response = RESPONSE_NOT_FOUND;
	
	n = sprintf (buffer, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID_DEFAULT, PASSWORD_DEFAULT);
	
	// ESP8266_Send_String ("AT+CWJAP=\"AWS\",\"Codehappy123\"\r\n", &deviceData);
	if (AS1_SendBlock (deviceData.handle, buffer, (uint16_t) strlen (buffer)) != ERR_OK) {
		return ERR_FAILED;
	}
	response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT);
	// TODO: Handle response "\r\n\r\nFAIL\r\n" (e.g., from full response string "AT+CWJAP=\"AWS\",\"Codehappy123\"\r\r\n+CWJAP:3\r\n\r\nFAIL\r\n")
	
	return response;
}

int8_t ESP8266_Send_Command_AT_CIFSR () {
	printf ("ESP8266_Send_Command_AT_CIFSR\r\n");
	
	int8_t response = RESPONSE_NOT_FOUND;
	
	// ESP8266_Send_String ("AT+CWJAP=\"AWS\",\"Codehappy123\"\r\n", &deviceData);
	if (AS1_SendBlock (deviceData.handle,"AT+CIFSR\r\n", (uint16_t) strlen ((char*) "AT+CIFSR\r\n")) != ERR_OK) {
		return ERR_FAILED;
	}
	response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK_VARIANT, DEFAULT_RESPONSE_TIMEOUT);
	// TODO: Handle response "\r\n\r\nFAIL\r\n" (e.g., from full response string "AT+CWJAP=\"AWS\",\"Codehappy123\"\r\r\n+CWJAP:3\r\n\r\nFAIL\r\n")
	
	return response;
}

int8_t ESP8266_Send_Command_AT_CIPMUX (uint8_t enable) {
	printf ("ESP8266_Send_Command_AT_CIPMUX\r\n");
	
	int8_t response = RESPONSE_NOT_FOUND;
	
	if (enable == TRUE) {
	
		// ESP8266_Send_String ("AT+CWJAP=\"AWS\",\"Codehappy123\"\r\n", &deviceData);
		if (AS1_SendBlock (deviceData.handle,"AT+CIPMUX=1\r\n", (uint16_t) strlen ((char*) "AT+CIPMUX=1\r\n")) != ERR_OK) {
			return ERR_FAILED;
		}
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT);
		// TODO: Handle response "\r\n\r\nFAIL\r\n" (e.g., from full response string "AT+CWJAP=\"AWS\",\"Codehappy123\"\r\r\n+CWJAP:3\r\n\r\nFAIL\r\n")
		
	} else {
		
		// ESP8266_Send_String ("AT+CWJAP=\"AWS\",\"Codehappy123\"\r\n", &deviceData);
		if (AS1_SendBlock (deviceData.handle,"AT+CIPMUX=0\r\n", (uint16_t) strlen ((char*) "AT+CIPMUX=0\r\n")) != ERR_OK) {
			return ERR_FAILED;
		}
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT);
		// TODO: Handle response "\r\n\r\nFAIL\r\n" (e.g., from full response string "AT+CWJAP=\"AWS\",\"Codehappy123\"\r\r\n+CWJAP:3\r\n\r\nFAIL\r\n")
		
	}
	
	return response;
}

int8_t ESP8266_Send_Command_AT_CIPSERVER (uint8_t mode, uint8_t port) {
	printf ("ESP8266_Send_Command_AT_CIPSERVER\r\n");
	
	char buffer[64] = { 0 };
	int n;
	
	int8_t response = RESPONSE_NOT_FOUND;
	
	n = sprintf (buffer, "AT+CIPSERVER=%d,%d\r\n", mode, port);
	
	// ESP8266_Send_String ("AT+CWJAP=\"AWS\",\"Codehappy123\"\r\n", &deviceData);
	if (AS1_SendBlock (deviceData.handle, buffer, (uint16_t) strlen (buffer)) != ERR_OK) {
		return ERR_FAILED;
	}
	response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT);
	// TODO: Handle response "\r\n\r\nFAIL\r\n" (e.g., from full response string "AT+CWJAP=\"AWS\",\"Codehappy123\"\r\r\n+CWJAP:3\r\n\r\nFAIL\r\n")
	
	return response;
}

/**
 * From section 5.1 of RFC 2616 Fielding, et al. at http://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html:
 * 
 * "The Request-Line begins with a method token, followed by the Request-URI and the protocol version, and ending with CRLF. The elements are separated by SP characters. No CR or LF is allowed except in the final CRLF sequence."
 * 
 * The format given in the section is "Request-Line   = Method SP Request-URI SP HTTP-Version CRLF".
 */
int8_t ESP8266_Receive_Request_Header_Line () {
	printf ("ESP8266_Receive_Request\r\n");

	char* tokenEnd    = NULL;
	
	char  connection  = NULL; // 0 to 4
	char* operation   = NULL; // "CONNECT"
	
	char* httpMethod  = NULL;
	char* httpUri     = NULL;
	char* httpVersion = NULL;
	int8_t response   = RESPONSE_NOT_FOUND;
	
	char *responseData = "<html><h1>Clay</h1><button>I/O</button></html>";
	char buffer[64] = { 0 };
	int n;
	
	// TODO: Extract client number (0-4) and command ("CONNECT" or else)
	// response = ESP8266_Wait_For_Response ("0,CONNECT\r\n\r\n", DEFAULT_RESPONSE_TIMEOUT); // "0,CONNECT\r\n\r\n"
	response = ESP8266_Wait_For_Response ("HTTP/1.1\r\n", DEFAULT_RESPONSE_TIMEOUT); // "HTTP/1.1\r\n" (e.g., "+IPD,0,343:GET / HTTP/1.1\r\n")
	
	/* Extract connection information from received data. */
	
	// Search the buffer of the received data. Find the connection number (0-4).
	connection = httpResponseBuffer[0];
	// TODO: Search for the connection ID.
	printf ("Connection: %c\r\n", connection);
	
	// Search the buffer of the received data. Find the connection number (0-4).
	operation  = strchr (httpResponseBuffer, ',') + 1;
	tokenEnd   = strchr (operation, '\r');
	*tokenEnd  = NULL; // Terminate the string.
	// TODO: Search for the connection ID.
	printf ("Operation: %s\r\n", operation);
	
	/* Extract HTTP request data for the connection (if valid for the connection). */
	
	// Search the buffer of the received data. Find ':' and read until ' ' to get HTTP method
	// The HTTP/1.1 methods are GET, HEAD, POST, PUT, DELETE, TRACE, OPTIONS, CONNECT, and PATCH.
	httpMethod = strchr (tokenEnd + 1, ':') + 1; // strchr (httpResponseBuffer, ':') + 1;
	tokenEnd   = strchr (httpMethod, ' ');
	*tokenEnd  = NULL; // Terminate the string.
	// TODO: Search for the method (i.e., "GET", "POST", etc.) and set a flag.
	printf ("Method: %s\r\n", httpMethod);
	
	// Search the buffer of the received data. Find the first ' ' following the HTTP method to read the URI
	httpUri   = tokenEnd + 1;
	tokenEnd  = strchr (httpUri, ' ');
	*tokenEnd = NULL; // Terminate the string.
	// TODO: Copy the URI.
	printf ("URI: %s\r\n", httpUri);
	
	httpVersion  = tokenEnd + 1;
	tokenEnd     = strchr (httpVersion, '\r');
	*tokenEnd    = NULL; // Terminate the string.
	// TODO: Verify the correctness of the HTTP version.
	printf ("Version: %s\r\n", httpVersion);
	
	/* Process the request. */
	
	if (strncmp (httpUri, "/hello", strlen ("/hello")) == 0) {
		// TODO: Respond to the request
		
//		AT+CIPSEND=1,52\r\n
//		<h1>Hello</h1>&lth2>World!</h2><button>LED1</button>
//		AT+CIPSEND=1,21\r\n
//		<button>LED2</button>
//		AT+CIPCLOSE=1\r\n
		
		n = sprintf (buffer, "AT+CIPSEND=%c,%d\r\n", connection, strlen (responseData));
		
		if (AS1_SendBlock (deviceData.handle, buffer, (uint16_t) strlen (buffer)) != ERR_OK) {
			return ERR_FAILED;
		}
		
		// Wait for ">" before sending data.
		response = ESP8266_Wait_For_Response (">", DEFAULT_RESPONSE_TIMEOUT);
		
		// Send data to ESP8266.
		n = sprintf (buffer, "%s", responseData);
				
		if (AS1_SendBlock (deviceData.handle, buffer, (uint16_t) strlen (buffer)) != ERR_OK) {
			return ERR_FAILED;
		}
		
		// Wait for "\r\r\nSEND OK\r\n".
		response = ESP8266_Wait_For_Response ("SEND OK\r\n", DEFAULT_RESPONSE_TIMEOUT);
		
		// Close the TCP connection.
		n = sprintf (buffer, "AT+CIPCLOSE=%c\r\n", connection);
						
		if (AS1_SendBlock (deviceData.handle, buffer, (uint16_t) strlen (buffer)) != ERR_OK) {
			return ERR_FAILED;
		}
		
		// Wait for "OK\r\n".
		response = ESP8266_Wait_For_Response ("OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
		
		// TODO: Wait for a short period of time before allowing additional AT commands.
		
	}
	
	return response;
}

// int8_t ESP8266_Get_Request_Method (); // TODO: Consider changing this to "int8_t ESP8266_Get_Request_Type ();"
// int8_t ESP8266_Get_Request_URI ();
// int8_t ESP8266_Get_Request_HTTP_Version ();

int step = 0;
void ESP8266_Start_Web_Server () {
	// DEBUG: printf ("ESP8266_Start_Web_Server\r\n");
	
	int8_t status = 0;
	
	// TODO: Set up web server
	// AT // Test device
	// AT+RST // Reset device
	// AT+CWMODE=3 // Set AP mode
	// AT+CWJAP="AWS","Codehappy123" // Join access point
	// AT+CIFSR // Get local IP address
	// AT+CIPMUX=1 // Configure for multiple connections
	// AT+CIPSERVER=1,80 // Turn server on port 80
	// NOTE: At this point start looking for +IPD
	
	
	if (step == 0) {
		status = ESP8266_Send_Command_AT ();
		if (status > 0) {
			printf ("ESP8266 online.\r\n");
		} else {
			printf ("ESP8266 not responding.\r\n");
		}
	} else if (step == 1) {
		status = ESP8266_Send_Command_AT_CWMODE ((uint8_t) 3);
		if (status > 0) {
			printf ("ESP8266 mode set.\r\n");
		} else {
			printf ("ESP8266 mode NOT set.\r\n");
		}
	} else if (step == 2) {
		status = ESP8266_Send_Command_AT_CWJAP (SSID_DEFAULT, PASSWORD_DEFAULT);
		if (status > 0) {
			printf ("ESP8266 joined access point.\r\n");
		} else {
			printf ("ESP8266 could NOT join access point.\r\n");
		}
	} else if (step == 3) {
		status = ESP8266_Send_Command_AT_CIFSR ();
		if (status > 0) {
			printf ("IP info received.\r\n");
		} else {
			printf ("ESP8266 could NOT join access point.\r\n");
		}
	} else if (step == 4) {
		status = ESP8266_Send_Command_AT_CIPMUX (TRUE);
		if (status > 0) {
			printf ("ESP8266 set up for multiple connections.\r\n");
		} else {
			printf ("ESP8266 could NOT join access point.\r\n");
		}
	} else if (step == 5) {
		status = ESP8266_Send_Command_AT_CIPSERVER (TRUE, 80);
		if (status > 0) {
			printf ("ESP8266 server listening on port 80.\r\n");
		} else {
			printf ("ESP8266 could not start server.\r\n");
		}
	} else if (step == 6) {
		status = ESP8266_Receive_Request_Header_Line ();
		if (status > 0) {
			printf ("ESP8266 server received incoming line on port 80.\r\n");
		} else {
			printf ("ESP8266 server did not receive any lines!\r\n");
		}
	} else {
		printf ("No command to run.\r\n");
	}
	
	step++;
}
