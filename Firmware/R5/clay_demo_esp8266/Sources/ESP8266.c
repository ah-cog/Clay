/*
 * ESP8266.c
 *
 *  Created on: Aug 31, 2015
 *      Author: mokogobo
 */

#include "ESP8266.h"
#include "ESP8266_RxBuf.h"

#include <stdio.h>
#include <string.h>

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

// buffer : Pointer to the "response buffer" to search for one of the expected responses. The "response buffer" is where the characters received from the ESP8266 in response to a command are stored temporarily for processing.
// bufferSize : The current size of the response buffer <code>buffer</code>.
//
// returns a code corresponding to an expected response (e.g., COMMAND_RESPONSE_OK, COMMAND_RESPONSE_ERROR, etc.)
//
int8_t ESP8266_Search_For_Response (const char *buffer, int bufferSize) {
	printf ("\t\tESP8266_Search_For_Response %s\r\n", buffer);
	
	// Check if the response from the ESP8266 matches one of the expected responses for the command according to the specification (e.g., as defined by Espressif for the AT command set for this firmware version).
	if (strlen (buffer) >= strlen (RESPONSE_SIGNATURE_OK)) { // Wait until enough characters have been buffered to search the string for the terminal character sequence.
		if (strncmp ((char *) (buffer + (strlen (buffer) - strlen (RESPONSE_SIGNATURE_OK))), RESPONSE_SIGNATURE_OK, strlen (RESPONSE_SIGNATURE_OK)) == 0) {
			printf ("\tGot OK response!\r\n");
			return RESPONSE_OK;
		}
	}
	
	if (strlen (buffer) >= strlen (RESPONSE_SIGNATURE_ERROR)) {
		if (strncmp ((char *) (buffer + (strlen (buffer) - strlen (RESPONSE_SIGNATURE_ERROR))), RESPONSE_SIGNATURE_ERROR, strlen (RESPONSE_SIGNATURE_ERROR)) == 0) {
			printf ("\tGot ERROR response!\r\n");
			return RESPONSE_ERROR;
		}
	}
	
//	else {
//				// DEBUG: printf ("Received unknown response! Clay will report this message.\r\n");
//				// TODO: If this was executed, then an unhandled response was encountered, so send a message to the Clay team's email address so they can fix it. This probably means the AT command set was changed or wasn't completely implemented.
//				return RESPONSE_NOT_FOUND;
//			}
	
	return RESPONSE_NOT_FOUND;
	
}

int8_t ESP8266_Wait_For_Response (uint32_t milliseconds) {
	printf ("\tESP8266_Wait_For_Response\r\n");
	
	// Block until receive "OK" or "ERROR" is received, an unknown response was received, or a timeout period has expired.
	char atCommandResponseBuffer[128]; // TODO: Make this big enough only to store expected responses and only buffer the most recent set of received characters (i.e., shift characters into and out of the "sliding window" buffer).
	int bufferSize;
	int8_t commandResponse;
	for (bufferSize = 0; bufferSize < 128; bufferSize++) { atCommandResponseBuffer[bufferSize] = (char) 0; } // Initialize the buffer. This might not be necessary.
	bufferSize = 0;
	commandResponse = RESPONSE_NOT_FOUND;
	
	// TODO: Start a timer.
	
	while (commandResponse < 0) {
		// TODO: Check timer in while condition and break if timeout period expires.
		
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
	bufferSize++;
	atCommandResponseBuffer[bufferSize] = '\0'; // Terminate the buffered response string.
	
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
	
	response = ESP8266_Wait_For_Response (DEFAULT_RESPONSE_TIMEOUT); // TODO: (New) Handle OK and ERROR here or elsewhere!
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
	
	response = ESP8266_Wait_For_Response (DEFAULT_RESPONSE_TIMEOUT); // TODO: (New) Handle OK and ERROR here or elsewhere!
	return response;
	
//	ESP8266_Send_String ("AT+RST\r\n", &deviceData);
	return ESP8266_Wait_For_Response (DEFAULT_RESPONSE_TIMEOUT);
}


int8_t ESP8266_Send_Command_AT_CWMODE (uint8_t mode) {
	printf ("ESP8266_Send_Command_AT_CWMODE\r\n");
	
	if (mode == 1) {
		ESP8266_Send_String ("AT+CWMODE_CUR=1\r\n", &deviceData);
	} else if (mode == 2) {
		ESP8266_Send_String ("AT+CWMODE_CUR=2\r\n", &deviceData);
	} else if (mode == 3) {
		ESP8266_Send_String ("AT+CWMODE_CUR=3\r\n", &deviceData);
	} else {
		return -3; // TODO: Create a #define directive for this.
	}
	
	return ESP8266_Wait_For_Response (DEFAULT_RESPONSE_TIMEOUT);
}


int8_t ESP8266_Send_Command_AT_CWJAP (const char *ssid, const char *password) {
	printf ("ESP8266_Send_Command_AT_CWJAP\r\n");
	
	ESP8266_Send_String ("AT+CWJAP=\"AWS\",\"Codehappy123\"\r\n", &deviceData);
	
	return ESP8266_Wait_For_Response (DEFAULT_RESPONSE_TIMEOUT);
}


void ESP8266_Start_Web_Server () {
	// DEBUG: printf ("ESP8266_Start_Web_Server\r\n");
	
//	int i;
//	char ch;
//	char response[64] = { 0 };
	int8_t status = 0;
	
	// TODO: Set up expected response for the command (e.g., "\r\r\n\r\nOK\r\n" is the terminal string for the AT+CWLAP command, so read response until it is received or the timer times out).
	
	// TODO: Set up web server
	// AT // Test device
	// AT+RST // Reset device
	// AT+CWMODE=3 // Set AP mode
	// AT+CWJAP="AWS","Codehappy123" // Join access point
	// AT+CIFSR // Get local IP address
	// AT+CIPMUX=1 // Configure for multiple connections
	// AT+CIPSERVER=1,80 // Turn server on port 80
	// NOTE: At this point start looking for +IPD
	
//	if (ESP8266_Send_Command_AT_RST () > 0) { // ESP8266_Send_String ("AT\r\n", desc);
//		printf ("ESP8266 reset successful.\r\n");
//	} else {
//		printf ("ESP8266 reset error.\r\n");
//	}
	
	status = ESP8266_Send_Command_AT ();
	if (status > 0) { // ESP8266_Send_String ("AT\r\n", desc);
		printf ("ESP8266 online.\r\n");
	} else {
		printf ("ESP8266 not responding.\r\n");
	}
	
//	if ((status = ESP8266_Send_Command_AT_CWMODE (3)) > 0) {
//		printf ("ESP8266 mode set.\r\n");
//	} else {
//		printf ("ESP8266 mode NOT set.\r\n");
//	}
//	
//	if ((status = ESP8266_Send_Command_AT_CWJAP (SSID_DEFAULT, PASSWORD_DEFAULT)) > 0) {
//		printf ("ESP8266 joined access point.\r\n");
//	} else {
//		printf ("ESP8266 could NOT join access point.\r\n");
//	}
	
	
	

	
}
