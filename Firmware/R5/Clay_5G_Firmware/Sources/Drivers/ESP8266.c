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
//#include "ESP8266_RxBuf.h"

void Enable_ESP8266 () {
	
	// Initialize the ESP8266 device data structure
	deviceData.handle   = ESP8266_Serial_Init (&deviceData);
	deviceData.isSent   = FALSE;
	deviceData.rxChar   = '\0';
	deviceData.rxPutFct = Ring_Buffer_Put; // ESP8266_RxBuf_Put;

	// Initialize a buffer for storing incoming data from the ESP8266
	Ring_Buffer_Init (); // ESP8266_RxBuf_Init ();

	// Read any pending data to "clear the line"
	while (ESP8266_Serial_ReceiveBlock (deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof (deviceData.rxChar)) != ERR_OK) {

	}
}

void ESP8266_Send_Byte (unsigned char ch) {
	deviceData.isSent = FALSE;
	while (ESP8266_Serial_SendBlock (deviceData.handle, (LDD_TData*) &ch, 1) != ERR_OK) {

	}
	while (!deviceData.isSent) {

	}
}

void ESP8266_Send_Bytes (const unsigned char *str) {
	while (*str != '\0') {
		ESP8266_Send_Byte (*str++);
	}
}

int8_t ESP8266_Send_Block (const char *str) {
	// DEBUG: printf ("ESP8266_Send_Block\r\n");
	
	int8_t success = TRUE;
	
	if (ESP8266_Serial_SendBlock (deviceData.handle, str, (uint16_t) strlen (str)) != ERR_OK) {
		success = FALSE; // return ERR_FAILED;
	}
	
	return success;
}

byte ESP8266_Get_Incoming_Buffer_Size () {
	return Ring_Buffer_NofElements (); // ESP8266_RxBuf_NofElements ();
}

byte ESP8266_Get_Incoming_Character (byte *elemP) {
	return Ring_Buffer_Get (elemP); // ESP8266_RxBuf_Get (elemP);
}

uint8_t ESP8266_Has_Incoming_Data () {
	if (ESP8266_Get_Incoming_Buffer_Size() > 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/**
 * Moves all bytes stored in the <code>ESP8266_RxBuf</code> ring buffer to the larger <code>incomingSerialBuffer</code>.
 * 
 * TODO: Return the number of bytes stored in the buffer.
 */
void ESP8266_Buffer_Incoming_Data () {
	
	uint8_t incomingBufferSize = 0;
	int i;
	
	// Buffer all incoming characters
	incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
	if (incomingBufferSize > 0) { // Check if any data has been received
		// DEBUG: printf ("incomingBufferSize (before) = %d\r\n", incomingBufferSize);
		while (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Read each of the received characters from the buffer and send them to the device.
			unsigned char ch;
			(void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
			incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
			// DEBUG: printf ("incomingBufferSize (after) = %d (ch: %c)\r\n", incomingBufferSize, ch);
			
			if (responseBufferSize < HTTP_RESPONSE_BUFFER_SIZE) {
				httpResponseBuffer[responseBufferSize++] = ch; // Store the received character in the buffer.
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
//			commandResponse = ESP8266_Search_Tail_For_Response (response, incomingSerialBuffer, incomingSerialBufferSize);
//			if (commandResponse > 0) { break; }
		}
		
		// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
		// Option 1: Search for an expected response after every character to avoid removing characters from the buffer that aren't associated with this command.
		// commandResponse = ESP8266_Search_For_Response (response, responseBuffer, bufferSize);
	}
	
//	if (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Check if any data has been received
//		while (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Read each of the received characters from the buffer and send them to the device.
//			
//			// TODO: Check if TCP buffer is full. If so, return "TCP buffer is full" error and do not buffer any data. Possibly try to process or compress the TCP buffer.
//			
//			unsigned char ch;
//			(void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
//			incomingSerialBuffer[incomingSerialBufferSize++] = ch; // Store the received character in the buffer.
//			incomingSerialBuffer[incomingSerialBufferSize] = '\0'; // Terminate the buffered string.
//			bufferedByteCount++; // Count the byte
//			
//		}
//		
//		// TODO: Perform final operations on the buffered data.
//	}
}

void ESP8266_Reset_TCP_Buffer () {
	int i;
	
	// Reset the buffer size
	responseBufferSize = 0;
	
	// Erase the entire buffer
//	for (i = 0; i < HTTP_RESPONSE_BUFFER_SIZE; i++) {
//		httpResponseBuffer[i] = '\0';
//	}
}

uint8_t ESP8266_Has_Incoming_Request () {
	// TODO: Check if TCP buffer contains a complete incoming request.
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
	// DEBUG: printf ("\t\tESP8266_Search_For_Response \"%s\" in \"%s\" (bufferSize: %d)\r\n", response, buffer, bufferSize);
	
	if (bufferSize >= strlen (response)) { // Wait until enough characters have been buffered to search the string for the terminal character sequence.
		if (strncmp ((char *) (buffer + (bufferSize - strlen (response))), response, strlen (response)) == 0) {
			// DEBUG: printf ("\tFound \"%s\" response.\r\n", response);
			return RESPONSE_FOUND;
		}
	}
	
	// TODO: Return STRING_TO_SEARCH_TOO_SMALL or something like it.
	
	return RESPONSE_NOT_FOUND;
	
}

int8_t ESP8266_Wait_For_Response (const char* response, uint32_t milliseconds) {
	// DEBUG: printf ("\tESP8266_Wait_For_Response \"%s\"\r\n", response);
	
	// Block until receive "OK" or "ERROR" is received, an unknown response was received, or a timeout period has expired.
	// char httpResponseBuffer[RESPONSE_BUFFER_SIZE]; // TODO: Make this big enough only to store expected responses and only buffer the most recent set of received characters (i.e., shift characters into and out of the "sliding window" buffer).
	// int bufferSize;
	int i;
	int8_t commandResponse = RESPONSE_NOT_FOUND;
	for (responseBufferSize = 0; responseBufferSize < HTTP_RESPONSE_BUFFER_SIZE; responseBufferSize++) { httpResponseBuffer[responseBufferSize] = (char) 0; } // Initialize the buffer. This might not be necessary.
	responseBufferSize = 0;
	uint8_t incomingBufferSize = 0;
	
	// TODO: Start a timer.
	uint32_t startTime   = Millis ();
	uint32_t currentTime = 0;
	
	while (commandResponse < 0) {
		// TODO: Check timer in while condition and break if timeout period expires.
		
//		currentTime = Millis ();
//		if (currentTime - startTime > milliseconds) {
//			printf ("TIMEOUT!!!\r\n");
//			return RESPONSE_TIMEOUT;
//		}
		
		// Buffer all incoming characters
		incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
		if (incomingBufferSize > 0) { // Check if any data has been received
			// DEBUG: printf ("incomingBufferSize (before) = %d\r\n", incomingBufferSize);
			while (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Read each of the received characters from the buffer and send them to the device.
				unsigned char ch;
				(void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
				incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
				// DEBUG: printf ("incomingBufferSize (after) = %d (ch: %c)\r\n", incomingBufferSize, ch);
				
				if (responseBufferSize < HTTP_RESPONSE_BUFFER_SIZE) {
					httpResponseBuffer[responseBufferSize++] = ch; // Store the received character in the buffer.
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
				commandResponse = ESP8266_Search_Tail_For_Response (response, httpResponseBuffer, responseBufferSize);
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
	
	// TODO: Check the buffer size to see if it's overflowed. If so, return a "buffer size exceeded"/"buffer overflow" error.
	
	// TODO: Return RESPONSE_TIMEOUT if timeout period expires.
	return commandResponse; // Hack. Replace with suggestion in the TODO on the previous line.
	
}

/**
 * Transfers data from the shared circular queue to the per-channel queues.
 * 
 * Returns: Returns the channel number for which the data was received. This corresponds to the data received from a single "+IPD" data segment.
 */
int8_t ESP8266_Receive_Incoming_Data (uint32_t milliseconds) {
	// DEBUG: printf ("\tESP8266_Wait_For_Response \"%s\"\r\n", response);
	
	// Block until receive "OK" or "ERROR" is received, an unknown response was received, or a timeout period has expired.
	// char httpResponseBuffer[RESPONSE_BUFFER_SIZE]; // TODO: Make this big enough only to store expected responses and only buffer the most recent set of received characters (i.e., shift characters into and out of the "sliding window" buffer).
	// int bufferSize;
	int i;
	int8_t commandResponse = RESPONSE_NOT_FOUND;
//	for (responseBufferSize = 0; responseBufferSize < HTTP_RESPONSE_BUFFER_SIZE; responseBufferSize++) { httpResponseBuffer[responseBufferSize] = (char) 0; } // Initialize the buffer. This might not be necessary.
//	responseBufferSize = 0;
	uint8_t incomingBufferSize = 0;
	char *responseLocation = NULL;
	const char *response = "\r\n\r\n";
	int responseCount = 0;
	const int expectedResponseCount = 2;
	char *ipd = NULL;
	char *connection = NULL;
	char *size = NULL;
	
	uint8_t receivingSegmentHeader =  FALSE; // if FALSE, then we're LOOKING_FOR_SEGMENT
	uint8_t receivedSegmentHeader  =  FALSE;
	uint8_t receivingSegmentData   =  FALSE;
	uint8_t receivedSegmentData    =  FALSE;
	char *segmentSizePtr           =  0;
	int8_t channel                 = -1;
	uint16_t segmentDataSize       =  0;
	
	uint16_t segmentBytesReceived = 0;
	
	
	// TODO: Start a timer.
	uint32_t startTime   = Millis ();
	uint32_t currentTime = 0;
	
	while (commandResponse < 0) {
		// TODO: Check timer in while condition and break if timeout period expires.
		
//		currentTime = Millis ();
//		if (currentTime - startTime > milliseconds) {
//			printf ("TIMEOUT!!!\r\n");
//			return RESPONSE_TIMEOUT;
//		}
		
		// Buffer all incoming characters
//		incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
		if (Ring_Buffer_NofElements () > 0) { // Check if any data has been received
			// DEBUG: printf ("incomingBufferSize (before) = %d\r\n", incomingBufferSize);
			while (Ring_Buffer_NofElements () > 0) { // Read each of the received characters from the buffer and send them to the device.
				unsigned char ch;
				byte bufferStatus = ERR_OK;
				
				// Get the next character at the front of the circular queue.
				bufferStatus = Ring_Buffer_Get (&ch);
				
				// +IPD,0,15:turn light 2 on
				// <data(15)>
				
				// TCP DATA FLOW (assuming server started):
				//
				// Then look for the following, which denote incoming connections:
				//
				// - "0,CONNECT\r\n" (receiving data until "0,CLOSED")
				//
				// Then look for the following, which denote incoming data segments:
				//
				// - "+IPD,0,413:GET /hello HTTP/1.1\r\n"
				//
				// Then read the segment until the specified number of bytes have been received in the channel buffer:
				//
				//     <read the specified number of bytes in a blocking loop>
				//
				// Clay will disconnect the channel after the TCP data has been completely received as specified in the HTTP encoding:
				//
				//     AT+CIPCLOSE=0
				//
				
				
				
				// UDP INCOMING DATA FLOW:
				// 
				// Start the server with the following commands:
				//
				//     AT+CIPSTART=0,"UDP","0.0.0.0",4445,4445,2
				//
				//     0,CONNECT
				//
				//     OK
				// 
				// Then look for the following, which denote incoming data segments:
				//
				//     +IPD,0,15:turn light 2 on
				//     OK
				//
				// Clay will terminate the server using the following AT command sequence:
				//
				//     AT+CIPCLOSE=0
				//
				//     0,CLOSED
				//
				//     OK
				//
				

				
				// If a character was received off the queue, put it into the corresponding local buffer.
				if (bufferStatus == ERR_OK) {
				
					// Skip everything until "+IPD,<connection number>,<bytes in frame>:" then buffer until the specified number of bytes has been received in the buffer
					
					// Get "+IPD," and set flag
					// Buffer the following character (until ',') which will be the connection ID. Set a flag when the ID is stored.
					// Buffer the following characters until ':') which will provide the number of bytes to receive, following the ':'. Put those bytes into a buffer for the connection ID.
//					uint8_t ipdReceived = FALSE;
//					uint8_t connectionReceived = FALSE;
//					uint8_t byteCountReceived = FALSE;
//					
//					if (ipdReceived == FALSE) {
//						// Check the buffer for "+IPD" or wait until buffer is empty.
//						if (responseBufferSize < HTTP_RESPONSE_BUFFER_SIZE) {
//							httpResponseBuffer[responseBufferSize++] = ch; // Store the received character in the buffer.
//						}
//						
//						if (ch == '+') { // Look for '+' character leading the "+IPD" token.
//							// Check for the token "+IPD".
//						}
//					}
					
					if (receivedSegmentHeader == FALSE) { // Check if the IPD message header has been received...
						
						if (receivingSegmentHeader == FALSE) { // ...if not, check if it is receiving the header. If not look for it.
							
							if (ch == '+') { // Look for "+IPD"
								
								// Reset the buffering process so the first character in the shared buffer is the '+' character.
								responseBufferSize = 0;
								httpResponseBuffer[responseBufferSize] = '\0';
								
								// Started receiving data starting with the "+" until ":".
								receivingSegmentHeader = TRUE;
								
								// Queue the received character in the shared queue.
								httpResponseBuffer[responseBufferSize++] = ch;
							}
							
						} else if (receivingSegmentHeader == TRUE) { // ...if so, start buffering it and extract parameters as they're received to direct further queueing (i.e., data flow) operations.
							
							// TODO: Keep on-going pointers to data and depending on the state of the pointers, look for certain data, buffer into certain data, etc.
							
							// Check if the final ':' character was received.
							if (ch == ':') {
								// TODO: receivingSegment = FALSE;
								
								httpResponseBuffer[responseBufferSize] = '\0'; // HACK to quickly NULL-terminate. Instead, should search for the ':' character
								
								// Parse the IPD header (connection ID and data byte size)
								channel  = atoi (httpResponseBuffer[5]); // Point to the connection byte
								size        = &httpResponseBuffer[7]; // connection + 2; // Point to the incoming byte count
								segmentDataSize = atoi (size);
								
								// Flag the IPD header as received.
								receivedSegmentHeader = TRUE;
								
								// Tell the state machine to start receiving data.
								receivingSegmentData = TRUE;
								
								// Reset the buffering process so the first character in the shared buffer is the '+' character.
								responseBufferSize = 0;
								httpResponseBuffer[responseBufferSize] = '\0';
								
								// TODO: Select the queue based on the connection ID
																
								// TODO: Reset the selected queue
								
							} else {
								
								// Queue the received character in the shared queue until receive the ':' character (or until timing out).
								httpResponseBuffer[responseBufferSize++] = ch;
							}
							
						}
					
					// Check if the "+IPD,<connection>,<size>:" segment was received. If so, parse it and set the connection-specific buffer.
					} else if (receivingSegmentData == TRUE) {
						
						if (receivedSegmentData == FALSE) {
							
//							if (receivedSegmentHeader == TRUE) {
								
								// Buffer incoming bytes until the expected number of bytes has been reached (or exceeded).
								if (segmentBytesReceived < segmentDataSize) {
									httpResponseBuffer[responseBufferSize++] = ch;
									segmentBytesReceived++;
								}
								
								// Tell the state machine that the segment's data has been received.
								if (segmentBytesReceived == segmentDataSize) {
									receivedSegmentData = TRUE;
								}
								
		//						connection = atoi(httpResponseBuffer[5]); // Point to the connection byte
		//						size       = &httpResponseBuffer[7]; // connection + 2; // Point to the incoming byte count
		//						httpResponseBuffer[10] = '\0'; // HACK to quickly null-terminate. Instead, should search for the ':' character
								
//							}
						}
						
						if (receivedSegmentData) {
							// TODO: Parse the segment data!
							
							return channel;
							
							// TODO: Return the channel number on which data was received (or sent?). (Later, after getting the data, check the status of the connection and close it if necessary!)
						}
					}
					
					// TODO: Non-blocking read until "+IPD,"
					// TODO: Blocking read until ',' for connection (i.e., "+IPD,3")
					// TODO: Blocking read until ":" for byte size (i.e., "+IPD,3,15:)
					// TODO: Blocking read until specified number of bytes are read into the corresponding buffer.
					
				
					// TODO: Make this a channel-specific buffer
//					if (responseBufferSize < HTTP_RESPONSE_BUFFER_SIZE) {
//						httpResponseBuffer[responseBufferSize++] = ch; // Store the received character in the buffer.
//					}
				}
				
//				else {
//					// Shift the elements to the left
//					for (i = 0; i < HTTP_RESPONSE_BUFFER_SIZE - 1; i++) {
//						httpResponseBuffer[i] = httpResponseBuffer[i + 1];
//					}
//					
//					// Add the newest element to the end of the buffer
//					httpResponseBuffer[HTTP_RESPONSE_BUFFER_SIZE - 1] = ch;
//				}
				
//				// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
//				// Option 1: Search for an expected response after every character to avoid removing characters from the buffer that aren't associated with this command.
//				commandResponse = ESP8266_Search_Tail_For_Response (response, httpResponseBuffer, responseBufferSize);
//				if (commandResponse > 0) { break; }
			}
			
			// TODO: Don't use strstr. Just compare the most recent four characters and search for the pattern.
			
//			if (responseBufferSize > 4) {
//				if (httpResponseBuffer[responseBufferSize - 4] == '\r' && httpResponseBuffer[responseBufferSize - 3] == '\n' && httpResponseBuffer[responseBufferSize - 2] == '\r' && httpResponseBuffer[responseBufferSize - 1] == '\n') {
//					
//					responseCount++;
//					
//					if (responseCount >= expectedResponseCount) {
//						commandResponse = RESPONSE_FOUND;
//					}
//					
//					// TODO: Don't buffer unneeded stuff! Enable and disable buffering as data segments are needed based on predictable character sequences.
//				}
//			}
			
			
			
//			if ((responseLocation = strstr (httpResponseBuffer, response)) != NULL) {
////				printf ("FOUND!");
//				responseCount++;
//				
//				if (responseCount >= expectedResponseCount) {
//					commandResponse = RESPONSE_FOUND;
//				}
//			}
			
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
	
	// TODO: Check the buffer size to see if it's overflowed. If so, return a "buffer size exceeded"/"buffer overflow" error.
	
	// TODO: Return RESPONSE_TIMEOUT if timeout period expires.
	return commandResponse; // Hack. Replace with suggestion in the TODO on the previous line.
	
}

int8_t ESP8266_Receive_Incoming_Request (uint32_t milliseconds) {
	// DEBUG: printf ("\tESP8266_Wait_For_Response \"%s\"\r\n", response);
	
	// Block until receive "OK" or "ERROR" is received, an unknown response was received, or a timeout period has expired.
	// char httpResponseBuffer[RESPONSE_BUFFER_SIZE]; // TODO: Make this big enough only to store expected responses and only buffer the most recent set of received characters (i.e., shift characters into and out of the "sliding window" buffer).
	// int bufferSize;
	int i;
	int8_t commandResponse = RESPONSE_NOT_FOUND;
//	for (responseBufferSize = 0; responseBufferSize < HTTP_RESPONSE_BUFFER_SIZE; responseBufferSize++) { httpResponseBuffer[responseBufferSize] = (char) 0; } // Initialize the buffer. This might not be necessary.
//	responseBufferSize = 0;
	uint8_t incomingBufferSize = 0;
	char *responseLocation = NULL;
	const char *response = "\r\n\r\n";
	int responseCount = 0;
	const int expectedResponseCount = 2;
	
	
	// TODO: Start a timer.
	uint32_t startTime   = Millis ();
	uint32_t currentTime = 0;
	
	while (commandResponse < 0) {
		// TODO: Check timer in while condition and break if timeout period expires.
		
//		currentTime = Millis ();
//		if (currentTime - startTime > milliseconds) {
//			printf ("TIMEOUT!!!\r\n");
//			return RESPONSE_TIMEOUT;
//		}
		
		// Buffer all incoming characters
//		incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
		if (Ring_Buffer_NofElements () > 0) { // Check if any data has been received
			// DEBUG: printf ("incomingBufferSize (before) = %d\r\n", incomingBufferSize);
			while (Ring_Buffer_NofElements () > 0) { // Read each of the received characters from the buffer and send them to the device.
				unsigned char ch;
				(void) Ring_Buffer_Get (&ch); // (void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
//				incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
				// DEBUG: printf ("incomingBufferSize (after) = %d (ch: %c)\r\n", incomingBufferSize, ch);
				
				if (responseBufferSize < HTTP_RESPONSE_BUFFER_SIZE) {
					httpResponseBuffer[responseBufferSize++] = ch; // Store the received character in the buffer.
				}
				
//				else {
//					// Shift the elements to the left
//					for (i = 0; i < HTTP_RESPONSE_BUFFER_SIZE - 1; i++) {
//						httpResponseBuffer[i] = httpResponseBuffer[i + 1];
//					}
//					
//					// Add the newest element to the end of the buffer
//					httpResponseBuffer[HTTP_RESPONSE_BUFFER_SIZE - 1] = ch;
//				}
				
//				// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
//				// Option 1: Search for an expected response after every character to avoid removing characters from the buffer that aren't associated with this command.
//				commandResponse = ESP8266_Search_Tail_For_Response (response, httpResponseBuffer, responseBufferSize);
//				if (commandResponse > 0) { break; }
			}
			
			// TODO: Don't use strstr. Just compare the most recent four characters and search for the pattern.
			
			if (responseBufferSize > 4) {
				if (httpResponseBuffer[responseBufferSize - 4] == '\r' && httpResponseBuffer[responseBufferSize - 3] == '\n' && httpResponseBuffer[responseBufferSize - 2] == '\r' && httpResponseBuffer[responseBufferSize - 1] == '\n') {
					
					responseCount++;
					
					if (responseCount >= expectedResponseCount) {
						commandResponse = RESPONSE_FOUND;
					}
					
					// TODO: Don't buffer unneeded stuff! Enable and disable buffering as data segments are needed based on predictable character sequences.
				}
			}
			
//			if ((responseLocation = strstr (httpResponseBuffer, response)) != NULL) {
////				printf ("FOUND!");
//				responseCount++;
//				
//				if (responseCount >= expectedResponseCount) {
//					commandResponse = RESPONSE_FOUND;
//				}
//			}
			
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
	
	// TODO: Check the buffer size to see if it's overflowed. If so, return a "buffer size exceeded"/"buffer overflow" error.
	
	// TODO: Return RESPONSE_TIMEOUT if timeout period expires.
	return commandResponse; // Hack. Replace with suggestion in the TODO on the previous line.
	
}

int8_t ESP8266_Send_Command_AT () {
	// DEBUG: printf ("ESP8266_Send_Command_AT\r\n");
	
	// TODO: (Optional) Insert a wait here, if the function isn't consistently reliable.
	// TODO: Set up a timer that expires after specified amount of time to terminate this operation if the ESP8266 does not respond as expected in a typically timely manner.
	
	int8_t response = NULL;
	
	if (ESP8266_Send_Block ("AT\r\n") == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT); // TODO: (New) Handle OK and ERROR here or elsewhere!
	}
	
	return response;
}

int8_t ESP8266_Send_Command_AT_RST () {
	// DEBUG: printf ("ESP8266_Send_Command_AT_RST\r\n");
	
	int8_t response = NULL;
	
	if (ESP8266_Send_Block ("AT+RST\r\n") == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT);
		response = ESP8266_Wait_For_Response ("ready", DEFAULT_RESPONSE_TIMEOUT); // Wait for "ready\r\n" (or might be slighly different character sequence like "ready\r\r\n")
	}
	
	return response;
}


int8_t ESP8266_Send_Command_AT_CWMODE (uint8_t mode) {
	// DEBUG: printf ("ESP8266_Send_Command_AT_CWMODE\r\n");
	
	int8_t response = NULL;
	char buffer[64] = { 0 };
	int n;
	
	n = sprintf (buffer, "AT+CWMODE_CUR=%d\r\n", mode);
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT);
	}
	
	return response;
}


int8_t ESP8266_Send_Command_AT_CWJAP (const char *ssid, const char *password) {
	// DEBUG: printf ("ESP8266_Send_Command_AT_CWJAP\r\n");
	
	int8_t response = NULL;
	char buffer[64] = { 0 };
	int n;
	
	n = sprintf (buffer, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID_DEFAULT, PASSWORD_DEFAULT);
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT);
	}
	
	return response;
}

int8_t ESP8266_Send_Command_AT_CIFSR () { // ESP8266_Send_Command_AT_CIFSR
	// DEBUG: printf ("ESP8266_Send_Command_AT_CIFSR\r\n");
	
	int8_t response = NULL;
	
	char *stationIP  = NULL;
	char *stationMAC = NULL;
//	char stationIPBuffer[16]  = { 0 };
//	char stationMACBuffer[18] = { 0 };
	int length = 0;
	
	if (ESP8266_Send_Block ("AT+CIFSR\r\n") == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK_VARIANT, DEFAULT_RESPONSE_TIMEOUT);
		
//		if (response != NULL) {
			// ESP8266_Parse_Response (i.e., using httpResponseBuffer and httpBufferSize)
			if (responseBufferSize > 0) {
				
				// TODO: Block until receive IP address!
				
				// Store the IP address in memory.
				if ((stationIP = strstr (httpResponseBuffer, "STAIP,\"")) != NULL) {
					// Copy substring starting at location pointed to by stationIP. The IP address of the station is the substring from "STAIP,\"" to the following "\"". 
					stationIP = stationIP + strlen ("STAIP,\""); // Go to start of IP address substring
					length = strchr (stationIP, '"') - stationIP;
					stationIP[length] = '\0';
					strncpy (esp8266_profile.stationIPBuffer, stationIP, length);
					printf ("IP: %s\r\n", esp8266_profile.stationIPBuffer);
				}
				
				// TODO: Block until receive MAC address in buffer!
				
				// Store the MAC address in memory.
				if ((stationMAC = strstr (httpResponseBuffer, "STAMAC,\"")) != NULL) {
					// Copy substring starting at location pointed to by stationMAC. The MAC address of the station is the substring from "STAMAC,\"" to the following "\"".
					stationMAC = stationMAC + strlen ("STAMAC,\""); // Go to start of MAC address substring
					length = strchr (stationMAC, '"') - stationMAC; // Measure the length of the MAC address substring
					stationMAC[length] = '\0'; // Terminate the stored MAC address string.
					strncpy (esp8266_profile.stationMACBuffer, stationMAC, length);
					printf ("MAC: %s\r\n", esp8266_profile.stationMACBuffer);
				}
			}
//		}
		
	}
	
	return response;
}

int8_t ESP8266_Send_Command_AT_CIPMUX (uint8_t enable) {
	// DEBUG: printf ("ESP8266_Send_Command_AT_CIPMUX\r\n");
	
	int8_t response = NULL;
	char buffer[64] = { 0 };
	int n;
	
	n = sprintf (buffer, "AT+CIPMUX=%d\r\n", enable);
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT);
	}
	
	return response;
}

int8_t ESP8266_Send_Command_AT_CIPSERVER (uint8_t mode, uint8_t port) {
	// DEBUG: printf ("ESP8266_Send_Command_AT_CIPSERVER\r\n");
	
	int8_t response = NULL;
	char buffer[64] = { 0 };
	int n;
	
	n = sprintf (buffer, "AT+CIPSERVER=%d,%d\r\n", mode, port);
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, DEFAULT_RESPONSE_TIMEOUT);
	}
	
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
	// response = ESP8266_Wait_For_Response ("0,CONNECT\r\n\r\n", DEFAULT_RESP8ONSE_TIMEOUT); // "0,CONNECT\r\n\r\n"
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
		
		/* Respond to the "/hello" request */
		
		// Send data to the connected client.
		n = sprintf (buffer, "AT+CIPSEND=%c,%d\r\n", connection, strlen (responseData));
		if (ESP8266_Send_Block (buffer) == TRUE) {
			// Wait for ">" before sending data.
			response = ESP8266_Wait_For_Response (">", DEFAULT_RESPONSE_TIMEOUT);
		}
		
		// Send data to ESP8266.
		n = sprintf (buffer, "%s", responseData);
		if (ESP8266_Send_Block (buffer) == TRUE) {
			response = ESP8266_Wait_For_Response ("SEND OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
		}
		
		// TODO: Insert a brief pause here before closing the connection.
		Wait (500);
		
		// Close the TCP connection.
		n = sprintf (buffer, "AT+CIPCLOSE=%c\r\n", connection);
		if (ESP8266_Send_Block (buffer) == TRUE) {
			// Wait for "OK\r\n".
			Wait (500);
			response = ESP8266_Wait_For_Response ("OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
		}
		
		// TODO: Wait for a short period of time before allowing additional AT commands.
		
	}
	
//	if (strncmp (httpUri, "/favicon.ico", strlen ("/favicon.ico")) == 0) {
//		
//		/* Respond to the "/hello" request */
//		
//		// Send data to the connected client.
////		n = sprintf (buffer, "AT+CIPSEND=%c,%d\r\n", connection, strlen (responseData));
////		if (ESP8266_Send_Block (buffer) == TRUE) {
////			// Wait for ">" before sending data.
////			response = ESP8266_Wait_For_Response (">", DEFAULT_RESPONSE_TIMEOUT);
////		}
////		
////		// Send data to ESP8266.
////		n = sprintf (buffer, "%s", responseData);
////		if (ESP8266_Send_Block (buffer) == TRUE) {
////			response = ESP8266_Wait_For_Response ("SEND OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
////		}
//		
//		// TODO: Insert a brief pause here before closing the connection.
//		Wait (500);
//		
//		// Close the TCP connection.
//		n = sprintf (buffer, "AT+CIPCLOSE=%c\r\n", connection);
//		if (ESP8266_Send_Block (buffer) == TRUE) {
//			// Wait for "OK\r\n".
//			response = ESP8266_Wait_For_Response ("OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
//		}
//		
//		// TODO: Wait for a short period of time before allowing additional AT commands.
//		
//	}
	
	return response;
}

void Start_UDP_Server (uint16_t port) {
	// DEBUG: printf ("ESP8266_Send_Command_AT_CIPSERVER\r\n");
	
	int8_t response = NULL;
	char buffer[64] = { 0 };
	int n;
	
	// The following variables correspond to parameters in the following AT command:
	//     AT+CIPSTART=<channel index>,<protocol>,<remote address>,<remote port>[,(<local port>),(<mode>)]
	// e.g., AT+CIPSTART=0,"UDP","0.0.0.0",4445,4445,2
	uint8_t     channel       = 0; // i.e., the <channel> parameter
	const char *protocol      = "UDP";
	const char *remoteAddress = "0.0.0.0";
	uint16_t    remotePort    = port; // 4445
	uint16_t    localPort     = port; // 4445
	uint8_t     mode          = 2;
	
	// AT+CIPSTART=0,"UDP","0.0.0.0",4445,4445,2
	n = sprintf (buffer, "AT+CIPSTART=%d,\"%s\",\"%s\",%d,%d,%d\r\n", channel, protocol, remoteAddress, remotePort, localPort, mode);
	printf ("%s\r\n", buffer);
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK_VARIANT, DEFAULT_RESPONSE_TIMEOUT);
	}
	
	return response;
}

void Broadcast_UDP_Message (const char *message) {
	int8_t response = NULL;
	char buffer[64] = { 0 };
	int n;
	
	// The following variables correspond to parameters in the following AT command:
	//     AT+CIPSTART=<channel index>,<protocol>,<remote address>,<remote port>[,(<local port>),(<mode>)]
	// e.g., AT+CIPSTART=1,"UDP","255.255.255.255",4445,1002,2
	uint8_t     channel       = 1; // i.e., the <channel> parameter
	const char *protocol      = "UDP";
	const char *remoteAddress = "255.255.255.255";
	uint16_t    remotePort    = 4445; // port; // 4445
	uint16_t    localPort     = 1002; // 1002 // TODO: Randomize this!
	uint8_t     mode          = 2;
	
	// AT+CIPSTART=0,"UDP","0.0.0.0",4445,4445,2
	n = sprintf (buffer, "AT+CIPSTART=%d,\"%s\",\"%s\",%d,%d,%d\r\n", channel, protocol, remoteAddress, remotePort, localPort, mode);
	printf ("%s\r\n", buffer);
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK_VARIANT, DEFAULT_RESPONSE_TIMEOUT);
	}
	
	// TODO: Put this into a separate command?
	
	//	AT+CIPSEND=1,7,"255.255.255.255",4445
	
	// Broadcast data to the broadcast address.
	n = sprintf (buffer, "AT+CIPSEND=%d,%d,\"%s\",%d\r\n", channel, strlen ("HELLO\r\n"), remoteAddress, 4445);
	if (ESP8266_Send_Block (buffer) == TRUE) {
		// Wait for ">" before sending data.
		response = ESP8266_Wait_For_Response (">", DEFAULT_RESPONSE_TIMEOUT);
	}
	
	// Send data to ESP8266.
	n = sprintf (buffer, "%s", "HELLO\r\n");
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response ("SEND OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
	}
	
	// TODO: Wait for a response (optionally), looking for "+IPD,..." for a time (with timeout).
	// +IPD,0,18:1443563177.377612
	//
	//	OK

	
	// Brief pause here before closing the connection.
	Wait (200);
	
	// TODO: Put this into a separate command?
	
	// Close the TCP connection.
	n = sprintf (buffer, "AT+CIPCLOSE=%d\r\n", channel);
	if (ESP8266_Send_Block (buffer) == TRUE) {
		// Wait for "OK\r\n".
		Wait (500);
		response = ESP8266_Wait_For_Response ("OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
	}
	
	// Wait for a short period of time before allowing additional AT commands.
	Wait (300);
	
	return response;
}

void Initialize_Remote_Connections () {
	
	int i;
	for (i = 0; i < REMOTE_CONNECTION_COUNT; i++) {
		Reset_Connection (i);
	}
}

void Reset_Connection (int id) {
	
	// Initialize the channel
	remoteConnections[id].id   = DISCONNECTED_CONNECTION_ID;
	remoteConnections[id].type = DISCONNECTED_CONNECTION_TYPE;
}

void Set_Connection_Type (int id, int type) {
	
	remoteConnections[id].type = type;
}

/**
 * Set up web server.
 * 
 * The following sequence of AT commands configures the ESP8266 as a web server.
 * 
 * AT // Test device
 * AT+RST // Reset device
 * AT+CWMODE=3 // Set AP mode
 * AT+CWJAP="AWS","Codehappy123" // Join access point
 * AT+CIFSR // Get local IP address
 * AT+CIPMUX=1 // Configure for multiple connections
 * AT+CIPSERVER=1,80 // Turn server on port 80
 * NOTE: At this point start looking for +IPD
 */
int step = 0;
void Start_HTTP_Server (uint16_t port) {
	// DEBUG: printf ("ESP8266_Start_Web_Server\r\n");
	
	int8_t status = 0;
	
	while (1) {
		if (step == 0) {
			printf ("Resetting ESP8266.");
			if ((status = ESP8266_Send_Command_AT_RST ()) > 0) {
				printf ("ESP8266 reset successfully.\r\n");
			} else {
				printf ("ESP8266 reset failed.\r\n");
			}
			step++;
		} else if (step == 1) {
			printf ("Testing communications with ESP8266. ");
			if ((status = ESP8266_Send_Command_AT ()) > 0) {
				printf ("ESP8266 online.\r\n");
			} else {
				printf ("ESP8266 not responding.\r\n");
			}
			step++;
		} else if (step == 2) {
			printf ("Setting mode of ESP8266. ");
			if ((status = ESP8266_Send_Command_AT_CWMODE ((uint8_t) 3)) > 0) {
				printf ("ESP8266 mode set.\r\n");
			} else {
				printf ("ESP8266 mode NOT set.\r\n");
			}
			step++;
		} else if (step == 3) {
			printf ("Joining access point. ");
			if ((status = ESP8266_Send_Command_AT_CWJAP (SSID_DEFAULT, PASSWORD_DEFAULT)) > 0) {
				printf ("ESP8266 joined access point.\r\n");
			} else {
				printf ("ESP8266 could NOT join access point.\r\n");
			}
			step++;
		} else if (step == 4) {
			printf ("Getting IP address. ");
			if ((status = ESP8266_Send_Command_AT_CIFSR ()) > 0) {
				printf ("IP info received.\r\n");
			} else {
				printf ("ESP8266 could NOT join access point.\r\n");
			}
			step++;
		} else if (step == 5) {
			printf ("Configuring to accept multiple incoming connections. ");
			if ((status = ESP8266_Send_Command_AT_CIPMUX (TRUE)) > 0) {
				printf ("ESP8266 set up for multiple connections.\r\n");
			} else {
				printf ("ESP8266 could NOT join access point.\r\n");
			}
			step++;
		} else if (step == 6) {
			printf ("Configuring as TCP server. ");
			if ((status = ESP8266_Send_Command_AT_CIPSERVER (TRUE, port)) > 0) {
				printf ("ESP8266 server listening on port 80.\r\n");
			} else {
				printf ("ESP8266 could not start server.\r\n");
			}
			step++;
//		} else if (step == 7) {
//			printf ("Waiting for incoming connections with HTTP requests. ");
//			if ((status = ESP8266_Receive_Request_Header_Line ()) > 0) {
//				printf ("ESP8266 server received incoming line on port 80.\r\n");
//			} else {
//				printf ("ESP8266 server did not receive any lines!\r\n");
//			}
//			step++;
		} else {
			break;
			// printf ("No command to run.\r\n");
		}
		
//		ESP8266_Reset_TCP_Buffer (); // Reset the buffer where Clay stores responses to AT commands.
	}
}

void Monitor_HTTP_Server () {
	
	int8_t status = NULL;
	int i = 0;
	int j = 0;
//	int  lineReceived = FALSE;
//	char buffer[64]   = { '\0' };
//	int  ch           = (int) '\0';
//	int server_started = FALSE;
//	byte bufferSize;
	char buffer[64] = { 0 };
	int n;
	
//	int incomingByteCount = 0; // number of bytes available to read
//	byte bufferedByteCount = 0;
	
	char* tokenEnd    = NULL;
	
	char  connection  = NULL; // 0 to 4
	char* operation   = NULL; // "CONNECT"
	
	char* httpMethod  = NULL;
	char* httpUri     = NULL;
	char* httpVersion = NULL;
	int8_t response   = RESPONSE_NOT_FOUND;
	
	const char *responseData = "<html><h1>Clay</h1><button>I/O</button></html>";
	
	if (Ring_Buffer_NofElements () > 0) {
		
		ESP8266_Reset_TCP_Buffer (); // Clear the incoming data buffer
		// ESP8266_Receive_Incoming_Request ("\r\n\r\n", DEFAULT_RESPONSE_TIMEOUT); // i.e., "0,CONNECT\r\n\r\n"
		ESP8266_Receive_Incoming_Request (DEFAULT_RESPONSE_TIMEOUT); // e.g., "Accept: */*\r\n\r\n";
//		ESP8266_Receive_Incoming_Data (DEFAULT_RESPONSE_TIMEOUT);
		// Wait (5000); // TODO: Reduce this to about 200 ms (or possibly zero since the processing below isn't related to communications with the ESP)
		
		/* Extract connection information from received data. */
		
		// TODO: Search for (e.g.,) "0,CONNECT\r\n\r\n"
		// TODO: Extract client number (0-4) and command ("CONNECT" or else)
		// TODO: Check the connection protocol type (UDP or TCP)
		// TODO: Parse the data accordingly, according to whether it's UDP or TCP
		
		// Search the buffer of the received data. Find the connection number (0-4).
		connection = httpResponseBuffer[0]; // (strchr (httpResponseBuffer, '+IPD,') + 1)[0]
		// TODO: Search for the connection ID.
		printf ("Connection: %c\r\n", connection);
		Set_Connection_Type ((atoi (connection)), TCP_CONNECTION_TYPE);
		
		// TODO: Search for byte count of incoming data (e.g., the "82" in "+IPD,0,82:" from "+IPD,0,82:GET /hello HTTP/1.1\r\n")
		
		// Search the buffer of the received data. Find the operation (e.g., "CONNECT").
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
		
		
		
		ESP8266_Reset_TCP_Buffer ();
		
		// TODO: Handle request that matches httpUri
		if (strncmp (httpUri, "/hello", strlen ("/hello")) == 0) {
			
			/* Respond to the "/hello" request */
			
			// Send data to the connected client.
			n = sprintf (buffer, "AT+CIPSEND=%c,%d\r\n", connection, strlen (responseData));
			if (ESP8266_Send_Block (buffer) == TRUE) {
				// Wait for ">" before sending data.
				response = ESP8266_Wait_For_Response (">", DEFAULT_RESPONSE_TIMEOUT);
			}
			
			// Send data to ESP8266.
			n = sprintf (buffer, "%s", responseData);
			if (ESP8266_Send_Block (buffer) == TRUE) {
				response = ESP8266_Wait_For_Response ("SEND OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
			}
			
//				// Brief pause here before closing the connection.
//				Wait (200);
//				
//				// Close the TCP connection.
//				n = sprintf (buffer, "AT+CIPCLOSE=%c\r\n", connection);
//				if (ESP8266_Send_Block (buffer) == TRUE) {
//					// Wait for "OK\r\n".
//					Wait (500);
//					response = ESP8266_Wait_For_Response ("OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
//				}
//				
//				// Wait for a short period of time before allowing additional AT commands.
//				Wait (300);
			
		} else if (strncmp (httpUri, "/channel/", strlen ("/channel/")) == 0) {
			
			if (strncmp (httpMethod, "GET", strlen ("GET")) == 0) {
				printf ("Getting state of channel.\r\n");
			} else if (strncmp (httpMethod, "POST", strlen ("POST")) == 0) {
				printf ("Setting state of channel.\r\n");
				// TODO: Read POST data
			}
			
		} else if (strncmp (httpUri, "/message", strlen ("/message")) == 0) {
			
			// e.g., for "turn 1 on" the httpUri string would be "/message?content=turn%201%20on"
			
			// TODO: Copy and clean the string contained in the message content.
			
#define MAXIMUM_MESSAGE_LENGTH 128
			int messageLength = 0;
			char message[MAXIMUM_MESSAGE_LENGTH] = { 0 };
//				char *token = NULL;
//				char *tokenStop = NULL;
//				char tokenBuffer[32] = { 0 };
//				int tokenInt = 0;
			
			if (strncmp (httpMethod, "GET", strlen ("GET")) == 0) {
				printf ("Getting state of channel.\r\n");
				
				//strncpy (message, httpUri, MAXIMUM_MESSAGE_LENGTH);
				i = strchr (httpUri, '?') - httpUri; // Computes the offset between the beginning of the URI and the message content.
				if (i > 0) { // The offset will be greater than 0 if the '?' character was found.
					
					i = i + 9; // HACK: Move past the "?content=" string. // TODO: Actually search for parameters in the parameter list.
					j = 0;
					for ( ; i < strlen (httpUri); ) {
						
						// Copy the character from the HTTP request to the message.
						// When copying, replace any occurrences of the "%20" string with a ' ' character in the message.
						if (httpUri[i] == '%') {
							message[j] = ' '; // Write a ' ' character instead of the "%20" string.
							i = i + 3; // Skip past the "%20" string.
						} else {
							message[j] = httpUri[i];
							i++;
						}
						
						// Move to the next character in the message.
						j++;
					}
					message[j] = '\0'; // Terminate the message.
					
					messageLength = j; // TODO: Replace the use of j above with messageLength
					
					printf ("Message: %s\r\n", message);
				} else {
					printf ("Error: There was no message.\r\n");
				}
				
//				// Get tokens from message string
//				token = getToken (message, tokenBuffer, 0);
//				printf ("token 0: %s\r\n", tokenBuffer);
//				token = getToken (message, tokenBuffer, 1);
//				printf ("token 1: %s\r\n", tokenBuffer);
//				token = getToken (message, tokenBuffer, 2);
//				printf ("token 2: %s\r\n", tokenBuffer);
				
				/* Intelligence */
				
				status = Process_Message (message);
				// TODO: Get response code from Process_Message ()
				
				if (status == TRUE) {
					
					// Send data to the connected client.
					n = sprintf (buffer, "AT+CIPSEND=%c,%d\r\n", connection, strlen ("HTTP/1.1 200 OK\r\n"));
					if (ESP8266_Send_Block (buffer) == TRUE) {
						// Wait for ">" before sending data.
						response = ESP8266_Wait_For_Response (">", DEFAULT_RESPONSE_TIMEOUT);
					}
					
					// Send data to ESP8266.
					n = sprintf (buffer, "%s", "HTTP/1.1 200 OK\r\n");
					if (ESP8266_Send_Block (buffer) == TRUE) {
						response = ESP8266_Wait_For_Response ("SEND OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
					}
					
				} else {
					
					// Send data to the connected client.
					n = sprintf (buffer, "AT+CIPSEND=%c,%d\r\n", connection, strlen ("HTTP/1.1 400 Bad Request\r\n"));
					if (ESP8266_Send_Block (buffer) == TRUE) {
						// Wait for ">" before sending data.
						response = ESP8266_Wait_For_Response (">", DEFAULT_RESPONSE_TIMEOUT);
					}
					
					// Send data to ESP8266.
					n = sprintf (buffer, "%s", "HTTP/1.1 400 Bad Request\r\n");
					if (ESP8266_Send_Block (buffer) == TRUE) {
						response = ESP8266_Wait_For_Response ("SEND OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
					}
					
				}
				
			}
			
//			else if (strncmp (httpMethod, "POST", strlen ("POST")) == 0) {
//				printf ("Setting state of channel.\r\n");
//				// TODO: Read POST data
//			}
			
		}
		
		
		
		// Brief pause here before closing the connection.
		Wait (200);
		
		// Close the TCP connection.
		n = sprintf (buffer, "AT+CIPCLOSE=%c\r\n", connection);
		if (ESP8266_Send_Block (buffer) == TRUE) {
			// Wait for "OK\r\n".
			Wait (500);
			response = ESP8266_Wait_For_Response ("OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
		}
		
		// Wait for a short period of time before allowing additional AT commands.
		Wait (300);
		
//			
//			// Close the TCP connection.
//			n = sprintf (buffer, "AT+CIPCLOSE=%c\r\n", connection);
//			if (ESP8266_Send_Block (buffer) == TRUE) {
////			if (ESP8266_Send_Block ("AT+CIPCLOSE=0\r\n") == TRUE) {
//				// Wait for "OK\r\n".
//				Wait (200);
//				//response = ESP8266_Wait_For_Response ("OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
//				ESP8266_Wait_For_Response ("OK\r\n", DEFAULT_RESPONSE_TIMEOUT);
//			}
		
//			printf ("BUFFER!");
	}
	
}

void Monitor_Network_Communications () {
	
	int8_t status = NULL;
	int i = 0;
	int j = 0;
//	int  lineReceived = FALSE;
//	char buffer[64]   = { '\0' };
//	int  ch           = (int) '\0';
//	int server_started = FALSE;
//	byte bufferSize;
	char buffer[64] = { 0 };
	int n;
	
//	int incomingByteCount = 0; // number of bytes available to read
//	byte bufferedByteCount = 0;
	
	char* tokenEnd    = NULL;
	
	// "+IDP,<connection>,<operation>:" parameters.
	int8_t connection = -1;   // 0 to 4
	char* operation   = NULL; // "CONNECT"
	
	// HTTP request data
	char* httpMethod  = NULL;
	char* httpUri     = NULL;
	char* httpVersion = NULL;
	int8_t response   = RESPONSE_NOT_FOUND;
	
	const char *responseData = "<html><h1>Clay</h1><button>I/O</button></html>";
	
	if (Ring_Buffer_Has_Data () == TRUE) {
		
		/* Clear the incoming data buffer */
		
//		ESP8266_Reset_TCP_Buffer ();
		
		/* Transfer data from the "common" circular queue (originally from the MCU's hardware serial FIFO buffer registers) to another connection-specific buffer. */
		
		// Start of message tokens:
		// - "0,CONNECT\r\n\r\n"
		// - "+IPD,0,1430:<data(1430)>"
		//
		// End of message tokens:
		// - "0,CLOSED\r\n\r\n"
		
		if ((connection = ESP8266_Receive_Incoming_Data (DEFAULT_RESPONSE_TIMEOUT)) >= 0) { // e.g., "Accept: */*\r\n\r\n";
			
			// Check the protocol type being used on the specified connection ID: UDP or TCP/HTTP
			
			// TODO: Parse the data based on the protocol being used.
			
//			printf ("Received data for connection %d.\r\n", connection);
			
			if (strstr (httpResponseBuffer, "HTTP/1.1") != NULL) {
				printf ("RECEIVING TCP/HTTP DATA\r\n");
			
	
				/* Extract connection information from received data. */
				
				// TODO: Search for (e.g.,) "0,CONNECT\r\n\r\n"
				// TODO: Extract client number (0-4) and command ("CONNECT" or else)
				// TODO: Check the connection protocol type (UDP or TCP)
				// TODO: Parse the data accordingly, according to whether it's UDP or TCP
				
		//		// Search the buffer of the received data. Find the connection number (0-4).
		//		connection = httpResponseBuffer[0]; // (strchr (httpResponseBuffer, '+IPD,') + 1)[0]
		//		// TODO: Search for the connection ID.
		//		printf ("Connection: %c\r\n", connection);
		//		Set_Connection_Type ((atoi (connection)), TCP_CONNECTION_TYPE);
		//		
		//		// TODO: Search for byte count of incoming data (e.g., the "82" in "+IPD,0,82:" from "+IPD,0,82:GET /hello HTTP/1.1\r\n")
		//		
		//		// Search the buffer of the received data. Find the operation (e.g., "CONNECT").
		//		operation  = strchr (httpResponseBuffer, ',') + 1;
		//		tokenEnd   = strchr (operation, '\r');
		//		*tokenEnd  = NULL; // Terminate the string.
		//		// TODO: Search for the connection ID.
		//		printf ("Operation: %s\r\n", operation);
				
				/* Extract HTTP request data for the connection (if valid for the connection). */
				
				// Search the buffer of the received data. Find ':' and read until ' ' to get HTTP method
				// The HTTP/1.1 methods are GET, HEAD, POST, PUT, DELETE, TRACE, OPTIONS, CONNECT, and PATCH.
				httpMethod = &(httpResponseBuffer[0]); // httpMethod = strchr (tokenEnd + 1, ':') + 1; // strchr (httpResponseBuffer, ':') + 1;
				tokenEnd   = strchr (httpMethod, ' ');
				*tokenEnd  = NULL; // Terminate the string.
				// TODO: Search for the method (i.e., "GET", "POST", etc.) and set a flag.
				// printf ("Method: %s\r\n", httpMethod);
				
				// Search the buffer of the received data. Find the first ' ' following the HTTP method to read the URI
				httpUri   = tokenEnd + 1;
				tokenEnd  = strchr (httpUri, ' ');
				*tokenEnd = NULL; // Terminate the string.
				// TODO: Copy the URI.
				// printf ("URI: %s\r\n", httpUri);
				
				httpVersion  = tokenEnd + 1;
				tokenEnd     = strchr (httpVersion, '\r');
				*tokenEnd    = NULL; // Terminate the string.
				// TODO: Verify the correctness of the HTTP version.
				// printf ("Version: %s\r\n", httpVersion);
				
				/* Handle received message/request. */
				
				ESP8266_Reset_TCP_Buffer ();
				
				// TODO: Handle request that matches httpUri
				if (strncmp (httpUri, "/hello", strlen ("/hello")) == 0) {
					
					/* Respond to the "/hello" request */
					
					// Send data to the connected client.
					n = sprintf (buffer, "AT+CIPSEND=%c,%d\r\n", connection, strlen (responseData));
					if (ESP8266_Send_Block (buffer) == TRUE) {
						// Wait for ">" before sending data.
						response = ESP8266_Wait_For_Response (">", DEFAULT_RESPONSE_TIMEOUT);
					}
					
					// Send data to ESP8266.
					n = sprintf (buffer, "%s", responseData);
					if (ESP8266_Send_Block (buffer) == TRUE) {
						response = ESP8266_Wait_For_Response ("SEND OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
					}
					
		//				// Brief pause here before closing the connection.
		//				Wait (200);
		//				
		//				// Close the TCP connection.
		//				n = sprintf (buffer, "AT+CIPCLOSE=%c\r\n", connection);
		//				if (ESP8266_Send_Block (buffer) == TRUE) {
		//					// Wait for "OK\r\n".
		//					Wait (500);
		//					response = ESP8266_Wait_For_Response ("OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
		//				}
		//				
		//				// Wait for a short period of time before allowing additional AT commands.
		//				Wait (300);
					
				} else if (strncmp (httpUri, "/channel/", strlen ("/channel/")) == 0) {
					
					if (strncmp (httpMethod, "GET", strlen ("GET")) == 0) {
						printf ("Getting state of channel.\r\n");
					} else if (strncmp (httpMethod, "POST", strlen ("POST")) == 0) {
						printf ("Setting state of channel.\r\n");
						// TODO: Read POST data
					}
					
				} else if (strncmp (httpUri, "/message", strlen ("/message")) == 0) {
					
					// e.g., for "turn 1 on" the httpUri string would be "/message?content=turn%201%20on"
					
					// TODO: Copy and clean the string contained in the message content.
					
					/* Extract message from request. */
					
#define MAXIMUM_MESSAGE_LENGTH 128
					int messageLength = 0;
					char message[MAXIMUM_MESSAGE_LENGTH] = { 0 };
					
					if (strncmp (httpMethod, "GET", strlen ("GET")) == 0) {
						printf ("Getting state of channel.\r\n");
						
						//strncpy (message, httpUri, MAXIMUM_MESSAGE_LENGTH);
						i = strchr (httpUri, '?') - httpUri; // Computes the offset between the beginning of the URI and the message content.
						if (i > 0) { // The offset will be greater than 0 if the '?' character was found.
							
							i = i + 9; // HACK: Move past the "?content=" string. // TODO: Actually search for parameters in the parameter list.
							j = 0;
							for ( ; i < strlen (httpUri); ) {
								
								// Copy the character from the HTTP request to the message.
								// When copying, replace any occurrences of the "%20" string with a ' ' character in the message.
								if (httpUri[i] == '%') {
									message[j] = ' '; // Write a ' ' character instead of the "%20" string.
									i = i + 3; // Skip past the "%20" string.
								} else {
									message[j] = httpUri[i];
									i++;
								}
								
								// Move to the next character in the message.
								j++;
							}
							message[j] = '\0'; // Terminate the message.
							
							messageLength = j; // TODO: Replace the use of j above with messageLength
							
							printf ("Message: %s\r\n", message);
						} else {
							printf ("Error: There was no message.\r\n");
						}
						
						/* Process the extracted message */
						
						// TODO: Place the extracted message onto the message queue.
						
						status = Process_Message (message);
						// TODO: Get response code from Process_Message ()
						
						/* Send HTTP request response (e.g., "200 OK" or "400 Bad Request"). */
						
						if (status == TRUE) {
							
							// Send data to the connected client.
							n = sprintf (buffer, "AT+CIPSEND=%d,%d\r\n", connection, strlen ("HTTP/1.1 200 OK\r\n"));
							if (ESP8266_Send_Block (buffer) == TRUE) {
								// Wait for ">" before sending data.
								response = ESP8266_Wait_For_Response (">", DEFAULT_RESPONSE_TIMEOUT);
							}
							
							// Send data to ESP8266.
							n = sprintf (buffer, "%s", "HTTP/1.1 200 OK\r\n");
							if (ESP8266_Send_Block (buffer) == TRUE) {
								response = ESP8266_Wait_For_Response ("SEND OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
							}
							
						} else {
							
							// Send data to the connected client.
							n = sprintf (buffer, "AT+CIPSEND=%d,%d\r\n", connection, strlen ("HTTP/1.1 400 Bad Request\r\n"));
							if (ESP8266_Send_Block (buffer) == TRUE) {
								// Wait for ">" before sending data.
								response = ESP8266_Wait_For_Response (">", DEFAULT_RESPONSE_TIMEOUT);
							}
							
							// Send data to ESP8266.
							n = sprintf (buffer, "%s", "HTTP/1.1 400 Bad Request\r\n");
							if (ESP8266_Send_Block (buffer) == TRUE) {
								response = ESP8266_Wait_For_Response ("SEND OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
							}
							
						}
						
					}
					
				}
				
				
				
				// Brief pause here before closing the connection.
				Wait (200);
				
				// Close the TCP connection.
				n = sprintf (buffer, "AT+CIPCLOSE=%d\r\n", connection);
				if (ESP8266_Send_Block (buffer) == TRUE) {
					// Wait for "OK\r\n".
					Wait (500);
					response = ESP8266_Wait_For_Response ("OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
					// TODO: Check if a timeout occurred. If so, check the status of the connection and close it.
				}
				
			} else {
				
				int messageLength = 0;
				char message[MAXIMUM_MESSAGE_LENGTH] = { 0 };
				
				strncpy (message, httpResponseBuffer, responseBufferSize);
				message[responseBufferSize] = NULL;
				
				status = Process_Message (message);
				
				printf ("RECEIVING UDP DATA: %s\r\n", message);
				
			}
			
			// Wait for a short period of time before allowing additional AT commands.
			Wait (300);
			
	//			
	//			// Close the TCP connection.
	//			n = sprintf (buffer, "AT+CIPCLOSE=%c\r\n", connection);
	//			if (ESP8266_Send_Block (buffer) == TRUE) {
	////			if (ESP8266_Send_Block ("AT+CIPCLOSE=0\r\n") == TRUE) {
	//				// Wait for "OK\r\n".
	//				Wait (200);
	//				//response = ESP8266_Wait_For_Response ("OK\r\n", DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
	//				ESP8266_Wait_For_Response ("OK\r\n", DEFAULT_RESPONSE_TIMEOUT);
	//			}
			
	//			printf ("BUFFER!");
		}
	}
	
}
