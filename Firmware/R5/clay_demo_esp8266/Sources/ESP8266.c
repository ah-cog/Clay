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

byte ESP8266_Incoming_Buffer_Size () {
	return ESP8266_RxBuf_NofElements ();
}

byte ESP8266_Get_Incoming_Character (byte *elemP) {
	return ESP8266_RxBuf_Get (elemP);
}

// TODO: Add a timeout so this function will wait for a known response for only a finite amount of time. Return an error if it times out or doesn't receive an expected response.
void ESP8266_Send_String_for_Response (const unsigned char *str, ESP8266_UART_Device *desc) {
	int i;
	char response[32] = { 0 };
	
	int j;
	char OK_response[32] = { 0 };
	char ERROR_response[32] = { 0 };
	const char *OK_response_body = "\r\nOK\r\n";
	const char *ERROR_response_body = "ERROR\r\n";
	
	ESP8266_Send_String (str, desc);
	
	// Wait a few milliseconds for a response
	for (i = 0; i < 100000; i++) {} // TODO: Set a timer that times out after some time if no expected response is received.
	
	// TODO: Read incoming buffer
	i = 0;
	if (ESP8266_Incoming_Buffer_Size () > 0) { // Check if any data has been received
		while (ESP8266_Incoming_Buffer_Size () > 0) { // Read each of the received characters from the buffer and send them to the device.
			unsigned char ch;
			(void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
			response[i++] = ch;
			printf ("%c", (unsigned char) ch);
		}
	}
	
	// Buffer the expected "OK" response strings for comparison.
	for (i = 0; i < strlen (str); i++) { OK_response[i] = str[i]; } // Copy entered text to the beginning of the expected response.
	for (j = 0; j < strlen (OK_response_body); i++, j++) { OK_response[i] = OK_response_body[j]; } // Copy the constant body of the response into the buffer.
	OK_response[i] = '\0'; // Terminate the string.
	
	// Buffer the expected "ERROR" response strings for comparison.
	for (i = 0; i < strlen (str); i++) { ERROR_response[i] = str[i]; } // Copy entered text to the beginning of the expected response.
	for (j = 0; j < strlen (ERROR_response_body); i++, j++) { ERROR_response[i] = ERROR_response_body[j]; } // Copy the constant body of the response into the buffer.
	ERROR_response[i] = '\0'; // Terminate the string.
	
	// TODO: Add alternative check that just skips strlen(str) characters at the beginning of the string and checks for the rest.
	//       This would eliminate the need for buffering expected responses.
	
	if (strncmp (response, OK_response, strlen (OK_response)) == 0) { // if (strncmp (response, "\r\nOK\r\n", (sizeof (str) + strlen ("\r\nOK\r\n"))) == 0) { // Success response is "AT\r\r\n\r\nOK\r\n". // if (strncmp (response, "AT\r\n\r\nOK\r\n", 10) == 0) { // Success response is "AT\r\r\n\r\nOK\r\n".
		printf ("Got OK response!\r\n");
	} else if (strncmp (response, ERROR_response, strlen (ERROR_response)) == 0) { // } else if (strncmp (response, "\r\nERROR\r\n", (sizeof (str) + strlen ("\r\nERROR\r\n"))) == 0) { // Error response is "<command>\r\nERROR\r\n". (NOTE: Subtract 2 from str length to remove the \r\n from the entered string, such as "ART\r\n" when the intent was "AT\r\n".)
		printf ("Got ERROR response!\r\n");
	} else {
		printf ("Received unknown response! Clay will report this message.\r\n");
		// TODO: If this was executed, then an unhandled response was encountered, so send a message to the Clay team's email address so they can fix it. This probably means the AT command set was changed or wasn't completely implemented.
	}
	
}
