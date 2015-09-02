/*
 * ESP8266.c
 *
 *  Created on: Aug 31, 2015
 *      Author: mokogobo
 */

#include "ESP8266.h"
#include "ESP8266_RxBuf.h"

#include <stdio.h>

// ESP8266.h
// |- ESP8266_RxBuf.h (ring buffer driver used for buffering incoming data)
// |- AS1.h (serial device driver)

void ESP8266_Init (void) { // static void Init (void) {
	deviceData.handle = AS1_Init (&deviceData);
	deviceData.isSent = FALSE;
	deviceData.rxChar = '\0';
	deviceData.rxPutFct = ESP8266_RxBuf_Put;

	ESP8266_RxBuf_Init ();

	while (AS1_ReceiveBlock (deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof (deviceData.rxChar)) != ERR_OK) {

	}
}

void ESP8266_Send_Char (unsigned char ch, ESP8266_UART_Device *desc) { // static void SendChar(unsigned char ch, ESP8266_UART_Device *desc) {
	desc -> isSent = FALSE;
	while (AS1_SendBlock (desc -> handle, (LDD_TData*) &ch, 1) != ERR_OK) {

	}
	while (!desc->isSent) {

	}
}

void ESP8266_Send_String (const unsigned char *str, ESP8266_UART_Device *desc) { // static void SendString (const unsigned char *str, ESP8266_UART_Device *desc) {
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

// TODO: Add a timeout so this function will wait for a known response for only a finite amount of time. Return an error if it times out or doesn't receive an expected response.
void ESP8266_Send_String_for_Response (const unsigned char *command, ESP8266_UART_Device *desc) {
	int i;
	char response[64] = { 0 };
	
//	int j;
	int commandLength = strlen (command) - 2; // Subtract 2 to exclude the "\r\n" characters from count.
//	char OK_response[32] = { 0 };
//	char ERROR_response[32] = { 0 };
//	const char *OK_response_body = "\r\n\r\nOK\r\n"; // "\r\n\r\nOK\r\n"
//	const char *ERROR_response_body = "ERROR\r\n"; // "\r\nERROR\r\n"
	
	// TODO: Set up expected response for the command (e.g., "\r\r\n\r\nOK\r\n" is the terminal string for the AT+CWLAP command, so read response until it is received or the timer times out).
	
	// TODO: Set up web server
	// AT // Test device
	// AT+RST // Reset device
	// AT+CWJAP="AWS","Codehappy123" // Join access point
	// AT+CIFSR // Get local IP address
	
	ESP8266_Send_String (command, desc);
	
	
	
	// Wait a few milliseconds for a response
	for (i = 0; i < 1000000; i++) {} // TODO: Set a timer that times out after some time if no expected response is received.
	for (i = 0; i < 1000000; i++) {} // TODO: Set a timer that times out after some time if no expected response is received.
	for (i = 0; i < 1000000; i++) {} // TODO: Set a timer that times out after some time if no expected response is received.
	
	
	
	// TODO: Read incoming buffer
	i = 0;
	if (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Check if any data has been received
		while (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Read each of the received characters from the buffer and send them to the device.
			unsigned char ch;
			(void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
			response[i++] = ch;
			printf ("%c", (unsigned char) ch);
		}
	}
	
//	// Buffer the expected "OK" response strings for comparison.
//	for (i = 0; i < strlen (str); i++) { OK_response[i] = str[i]; } // Copy entered text to the beginning of the expected response.
//	for (j = 0; j < strlen (OK_response_body); i++, j++) { OK_response[i] = OK_response_body[j]; } // Copy the constant body of the response into the buffer.
//	OK_response[i] = '\0'; // Terminate the string.
//	
//	// Buffer the expected "ERROR" response strings for comparison.
//	for (i = 0; i < strlen (str); i++) { ERROR_response[i] = str[i]; } // Copy entered text to the beginning of the expected response.
//	for (j = 0; j < strlen (ERROR_response_body); i++, j++) { ERROR_response[i] = ERROR_response_body[j]; } // Copy the constant body of the response into the buffer.
//	ERROR_response[i] = '\0'; // Terminate the string.
	
	// TODO: Add alternative check that just skips strlen(str) characters at the beginning of the string and checks for the rest.
	//       This would eliminate the need for buffering expected responses.
	
	if (strncmp ((char *) (response + (strlen (response) - strlen ("\r\r\n\r\nOK\r\n"))), "\r\r\n\r\nOK\r\n", (strlen (response) - strlen ("\r\r\n\r\nOK\r\n"))) == 0) { // if (strncmp ((char *) (response + commandLength), "\r\r\n\r\nOK\r\n", strlen ("\r\r\n\r\nOK\r\n")) == 0) { // Success response is "AT\r\r\n\r\nOK\r\n". // if (strncmp (response, "AT\r\n\r\nOK\r\n", 10) == 0) { // Success response is "AT\r\r\n\r\nOK\r\n".
		printf ("Got OK response!\r\n");
	} else if (strncmp ((char *) (response + commandLength), "\r\r\n\r\nERROR\r\n", strlen ("\r\r\n\r\nERROR\r\n")) == 0) { // Error response is "<command>\r\nERROR\r\n". (NOTE: Subtract 2 from str length to remove the \r\n from the entered string, such as "ART\r\n" when the intent was "AT\r\n".)
		printf ("Got ERROR response!\r\n");
	} else {
		printf ("Received unknown response! Clay will report this message.\r\n");
		// TODO: If this was executed, then an unhandled response was encountered, so send a message to the Clay team's email address so they can fix it. This probably means the AT command set was changed or wasn't completely implemented.
	}
	
}

#define RESPONSE_ERROR    0 // Defined this as 0 (FALSE) so it can be used in conditional statements when returned.
#define RESPONSE_OK       1 // Defined this as 1 (TRUE) so it can be used in conditional statements when returned.
#define RESPONSE_UNKNOWN -1
#define RESPONSE_TIMEOUT -2

// buffer : Pointer to the "response buffer" to search for one of the expected responses. The "response buffer" is where the characters received from the ESP8266 in response to a command are stored temporarily for processing.
// bufferSize : The current size of the response buffer <code>buffer</code>.
//
// returns a code corresponding to an expected response (e.g., COMMAND_RESPONSE_OK, COMMAND_RESPONSE_ERROR, etc.)
//
int8_t ESP8266_Search_For_Response (const char *buffer, int bufferSize) {
	
	// Check if the response from the ESP8266 matches one of the expected responses for the command according to the specification (e.g., as defined by Espressif for the AT command set for this firmware version).
	if (strlen (buffer) >= strlen ("\r\r\n\r\nOK\r\n")) { // Wait until enough characters have been buffered to search the string for the terminal character sequence.
		if (strncmp ((char *) (buffer + (strlen (buffer) - strlen ("\r\r\n\r\nOK\r\n"))), "\r\r\n\r\nOK\r\n", (strlen (buffer) - strlen ("\r\r\n\r\nOK\r\n"))) == 0) { // if (strncmp ((char *) (response + commandLength), "\r\r\n\r\nOK\r\n", strlen ("\r\r\n\r\nOK\r\n")) == 0) { // Success response is "AT\r\r\n\r\nOK\r\n". // if (strncmp (response, "AT\r\n\r\nOK\r\n", 10) == 0) { // Success response is "AT\r\r\n\r\nOK\r\n".
			// DEBUG: printf ("Got OK response!\r\n");
			return RESPONSE_OK;
		} else if (strncmp ((char *) (buffer + (strlen (buffer) - strlen ("\r\r\n\r\nERROR\r\n"))), "\r\r\n\r\nERROR\r\n", (strlen (buffer) - strlen ("\r\r\n\r\nERROR\r\n"))) == 0) { // Error response is "<command>\r\nERROR\r\n". (NOTE: Subtract 2 from str length to remove the \r\n from the entered string, such as "ART\r\n" when the intent was "AT\r\n".)
			// DEBUG: printf ("Got ERROR response!\r\n");
			return RESPONSE_ERROR;
		} else {
			// printf ("Received unknown response! Clay will report this message.\r\n");
			// TODO: If this was executed, then an unhandled response was encountered, so send a message to the Clay team's email address so they can fix it. This probably means the AT command set was changed or wasn't completely implemented.
			return RESPONSE_UNKNOWN;
		}
	}
	
}

int8_t ESP8266_Wait_For_Response () {
	
	// Block until receive "OK" or "ERROR" is received, an unknown response was received, or a timeout period has expired.
	char atCommandResponseBuffer[128] = { 0 }; // TODO: Make this big enough only to store expected responses and only buffer the most recent set of received characters (i.e., shift characters into and out of the "sliding window" buffer).
	int bufferSize = 0;
	uint8_t commandResponse = RESPONSE_UNKNOWN;
	while (commandResponse < 0) {
		
		// Buffer all incoming characters
		if (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Check if any data has been received
			while (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Read each of the received characters from the buffer and send them to the device.
				unsigned char ch;
				(void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
				atCommandResponseBuffer[bufferSize++] = ch; // Store the received character in the buffer.
				
				// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
				// Option 1: Search for an expected response after every character to avoid removing characters from the buffer that aren't associated with this command.
				commandResponse = ESP8266_Search_For_Response (atCommandResponseBuffer, bufferSize);
				if (commandResponse >= 0) { break; }
			}
		}
		
		/*
		// Option 2: Search for a response after every received character has been buffered.
		receivedResponse = ESP8266_Search_For_Response (atCommandResponseBuffer, bufferSize);
		*/
	}
	atCommandResponseBuffer[bufferSize] = '\0'; // Terminate the buffered response string.
	
}


void ESP8266_Send_Command_AT () {
	
	printf ("ESP8266_Send_Command_AT\r\n");
	
	// Send "AT\r\n" to the ESP8266
	ESP8266_Send_String ("AT\r\n", &deviceData);
	
	// TODO: (Optional) Insert a wait here, if the function isn't consistently reliable.
	
	// TODO: Set up a timer that expires after specified amount of time to terminate this operation if the ESP8266 does not respond as expected in a typically timely manner.
	
	ESP8266_Wait_For_Response ();
	
	// printf ("Received response:\r\n");
	// printf ("%s", response);
	
}


void ESP8266_Start_Web_Server () {
	int i;
	char response[64] = { 0 };
	
	// TODO: Set up expected response for the command (e.g., "\r\r\n\r\nOK\r\n" is the terminal string for the AT+CWLAP command, so read response until it is received or the timer times out).
	
	// TODO: Set up web server
	// AT // Test device
	// AT+RST // Reset device
	// AT+CWJAP="AWS","Codehappy123" // Join access point
	// AT+CIFSR // Get local IP address
	// AT+CIPMUX=1 // Configure for multiple connections
	// AT+CIPSERVER=1,80 // Turn server on port 80
	// NOTE: At this point start looking for +IPD
	
	ESP8266_Send_Command_AT (); // ESP8266_Send_String ("AT\r\n", desc);

	
}
