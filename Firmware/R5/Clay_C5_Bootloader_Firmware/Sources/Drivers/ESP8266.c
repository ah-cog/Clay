/**
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
 *  Copyright (C) Computer Camp
 */

#include "ESP8266.h"

uint8_t Enable_ESP8266 () {
	
	// Initialize the ESP8266 device data structure
	deviceData.handle   = ESP8266_Serial_Init (&deviceData);
	deviceData.isSent   = FALSE;
	deviceData.rxChar   = '\0';
	deviceData.rxPutFct = Ring_Buffer_Put; // ESP8266_RxBuf_Put;

	// Initialize a buffer for storing incoming data from the ESP8266
	Ring_Buffer_Init ();

	// Read any pending data to "clear the line"
	while (ESP8266_Serial_ReceiveBlock (deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof (deviceData.rxChar)) != ERR_OK) {

	}
	
	return TRUE;
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
/*
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
			
			if (incomingDataQueueSize < HTTP_RESPONSE_BUFFER_SIZE) {
				incomingDataQueue[incomingDataQueueSize++] = ch; // Store the received character in the buffer.
			} else {
				// Shift the elements to the left
				for (i = 0; i < HTTP_RESPONSE_BUFFER_SIZE - 1; i++) {
					incomingDataQueue[i] = incomingDataQueue[i + 1];
				}
				
				// Add the newest element to the end of the buffer
				incomingDataQueue[HTTP_RESPONSE_BUFFER_SIZE - 1] = ch;
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
*/

void ESP8266_Reset_Data_Buffer () {
	int i;
	
	// Reset the buffer size
	incomingDataQueueSize = 0;
	incomingDataQueue[0] = NULL;
	
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
	for (incomingDataQueueSize = 0; incomingDataQueueSize < HTTP_RESPONSE_BUFFER_SIZE; incomingDataQueueSize++) { incomingDataQueue[incomingDataQueueSize] = (char) 0; } // Initialize the buffer. This might not be necessary.
	incomingDataQueueSize = 0;
	uint8_t incomingBufferSize = 0;
	
	// TODO: Start a timer.
	uint32_t startTime   = Millis ();
	uint32_t currentTime = 0;
	
	while (commandResponse < 0) {
		// TODO: Check timer in while condition and break if timeout period expires.
		
		currentTime = Millis ();
		if ((currentTime - startTime) > milliseconds) {
			return RESPONSE_TIMEOUT;
		}
		
		// Buffer all incoming characters
		incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
		if (incomingBufferSize > 0) { // Check if any data has been received
			// DEBUG: printf ("incomingBufferSize (before) = %d\r\n", incomingBufferSize);
			while (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Read each of the received characters from the buffer and send them to the device.
				unsigned char ch;
				(void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
				incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
				// DEBUG: printf ("incomingBufferSize (after) = %d (ch: %c)\r\n", incomingBufferSize, ch);
				
				if (incomingDataQueueSize < HTTP_RESPONSE_BUFFER_SIZE) {
					incomingDataQueue[incomingDataQueueSize++] = ch; // Store the received character in the buffer.
				} else {
					// Shift the elements to the left
					for (i = 0; i < HTTP_RESPONSE_BUFFER_SIZE - 1; i++) {
						incomingDataQueue[i] = incomingDataQueue[i + 1];
					}
					
					// Add the newest element to the end of the buffer
					incomingDataQueue[HTTP_RESPONSE_BUFFER_SIZE - 1] = ch;
				}
				
//				// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
//				// Option 1: Search for an expected response after every character to avoid removing characters from the buffer that aren't associated with this command.
				commandResponse = ESP8266_Search_Tail_For_Response (response, incomingDataQueue, incomingDataQueueSize);
				if (commandResponse > 0) { break; }
			}
			
			// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
			// Option 1: Search for an expected response after every character to avoid removing characters from the buffer that aren't associated with this command.
			// commandResponse = ESP8266_Search_For_Response (response, responseBuffer, bufferSize);
			
			// Update the start time of the receive operation after each segment of data is received FROM THE ESP8266 to ensure that continuous segments are read in their entirety.
//			startTime = Millis ();
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

//#define AT_RESPONSE_OK 1
//#define AT_RESPONSE_ERROR 2
//#define AT_RESPONSE_ALREADY_CONNECT 3
//char AT_CIPSTART_RESPONSES[] = {
//		"OK",
//		"ERROR",
//		"ALREADY CONNECTED\r\n\r\nERROR"
//};
int8_t ESP8266_Wait_For_Response_v2 (const char* response1, const char* response2, const char* response3, uint32_t milliseconds) {
	// DEBUG: printf ("\tESP8266_Wait_For_Response \"%s\"\r\n", response);
	
	// Block until receive "OK" or "ERROR" is received, an unknown response was received, or a timeout period has expired.
	// char httpResponseBuffer[RESPONSE_BUFFER_SIZE]; // TODO: Make this big enough only to store expected responses and only buffer the most recent set of received characters (i.e., shift characters into and out of the "sliding window" buffer).
	// int bufferSize;
	int i;
	int8_t commandResponse = RESPONSE_NOT_FOUND;
	for (incomingDataQueueSize = 0; incomingDataQueueSize < HTTP_RESPONSE_BUFFER_SIZE; incomingDataQueueSize++) { incomingDataQueue[incomingDataQueueSize] = (char) 0; } // Initialize the buffer. This might not be necessary.
	incomingDataQueueSize = 0;
	uint8_t incomingBufferSize = 0;
	
	// TODO: Start a timer.
	uint32_t startTime   = Millis ();
	uint32_t currentTime = 0;
	
	while (commandResponse < 0) {
		// TODO: Check timer in while condition and break if timeout period expires.
		
		currentTime = Millis ();
		if ((currentTime - startTime) > milliseconds) {
			return RESPONSE_TIMEOUT;
		}
		
		// Buffer all incoming characters
		incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
		if (incomingBufferSize > 0) { // Check if any data has been received
			// DEBUG: printf ("incomingBufferSize (before) = %d\r\n", incomingBufferSize);
			while (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Read each of the received characters from the buffer and send them to the device.
				unsigned char ch;
				(void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
				incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
				// DEBUG: printf ("incomingBufferSize (after) = %d (ch: %c)\r\n", incomingBufferSize, ch);
				
				if (incomingDataQueueSize < HTTP_RESPONSE_BUFFER_SIZE) {
					incomingDataQueue[incomingDataQueueSize++] = ch; // Store the received character in the buffer.
				} else {
					// Shift the elements to the left
					for (i = 0; i < HTTP_RESPONSE_BUFFER_SIZE - 1; i++) {
						incomingDataQueue[i] = incomingDataQueue[i + 1];
					}
					
					// Add the newest element to the end of the buffer
					incomingDataQueue[HTTP_RESPONSE_BUFFER_SIZE - 1] = ch;
				}
				
//				// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
//				// Option 1: Search for an expected response after every character to avoid removing characters from the buffer that aren't associated with this command.
				if (response1 != NULL) {
					commandResponse = ESP8266_Search_Tail_For_Response (response1, incomingDataQueue, incomingDataQueueSize);
					if (commandResponse > 0) {
						return 0;
					}
//					if (commandResponse > 0) { break; }
				}
				
				if (response2 != NULL) {
					commandResponse = ESP8266_Search_Tail_For_Response (response2, incomingDataQueue, incomingDataQueueSize);
					if (commandResponse > 0) {
						return 1;
					}
//					if (commandResponse > 0) { break; }
				}
				
				if (response3 != NULL) {
					commandResponse = ESP8266_Search_Tail_For_Response (response3, incomingDataQueue, incomingDataQueueSize);
					if (commandResponse > 0) {
						return 2;
					}
//					if (commandResponse > 0) { break; }
				}
			}
			
			// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
			// Option 1: Search for an expected response after every character to avoid removing characters from the buffer that aren't associated with this command.
			// commandResponse = ESP8266_Search_For_Response (response, responseBuffer, bufferSize);
			
			// Update the start time of the receive operation after each segment of data is received FROM THE ESP8266 to ensure that continuous segments are read in their entirety.
//			startTime = Millis ();
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

void Generate_Discovery_Message () {
	// Periodically send a datagram announcing the presence of this device.
	// TODO: Only broadcast UDP message if an address has been received!
	if (Has_Internet_Address () == TRUE) {
		char *address = Get_Internet_Address ();
		char *uuid = Get_Unit_UUID ();
		// TODO: Create and buffer the command to broadcast the unit's address.
//		n = 
		sprintf (discoveryMessage, "set unit %s address to %s", uuid, address); // Create message to send.
//			printf("buffer = %s\r\n", buffer2);
//		Broadcast_UDP_Message (buffer2, 4445);
		// TODO: Queue a (periodic) UDP broadcast announcing the unit's presence on the network.
	}
}

/**
 * Transfers data from the shared circular queue to the per-channel queues.
 * 
 * Returns: Returns the channel number for which the data was received. This corresponds to the data received from a single "+IPD" data segment.
 */
int8_t ESP8266_Receive_Incoming_Data (uint32_t milliseconds) {
	
	int8_t commandResponse = RESPONSE_NOT_FOUND;
//	char *ipd = NULL;
	char *connectionPtr = NULL;
	char *sizePtr       = NULL;
	
	// State machine status flags.
	uint8_t receivingIpdHeader =  FALSE; // if FALSE, then we're LOOKING_FOR_SEGMENT
	uint8_t receivedIpdHeader  =  FALSE;
	uint8_t receivingData   =  FALSE;
	uint8_t receivedData    =  FALSE;
	
	// Parameters for the parsed IPD encoded message.
	int8_t connectionID            = -1;
	uint16_t dataSize            =  0;
	
	uint16_t receivedDataSize = 0;
	
	
	// TODO: Start a timer.
	uint32_t startTime   = Millis ();
	uint32_t currentTime = 0;
	
	while (commandResponse < 0) {
		// TODO: Check timer in while condition and break if timeout period expires.
		
		currentTime = Millis ();
		if ((currentTime - startTime) > milliseconds) {
			return RESPONSE_TIMEOUT;
		}
		
		// Buffer all incoming characters
//		incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
		if (Ring_Buffer_NofElements () > 0) { // Check if any data has been received
			// DEBUG: printf ("incomingBufferSize (before) = %d\r\n", incomingBufferSize);
			while (Ring_Buffer_NofElements () > 0) { // Read each of the received characters from the buffer and send them to the device.
				unsigned char ch;
				byte bufferStatus = ERR_OK;
				
				// Get the next character at the front of the circular queue.
				bufferStatus = Ring_Buffer_Get (&ch);
				
				// If a character was received off the queue, put it into the corresponding local buffer.
				if (bufferStatus == ERR_OK) {
				
					// Skip everything until "+IPD,<connection number>,<bytes in frame>:" then buffer until the specified number of bytes has been received in the buffer
					
					// Get "+IPD," and set flag
					// Buffer the following character (until ',') which will be the connection ID. Set a flag when the ID is stored.
					// Buffer the following characters until ':') which will provide the number of bytes to receive, following the ':'. Put those bytes into a buffer for the connection ID.
					
					if (receivedIpdHeader == FALSE) { // Check if the IPD message header has been received...
						
						if (receivingIpdHeader == FALSE) { // ...if not, check if it is receiving the header. If not look for it.
							
							if (ch == '+') { // Look for "+IPD"
								
								// Reset the buffering process so the first character in the shared buffer is the '+' character.
								incomingDataQueueSize = 0;
								incomingDataQueue[incomingDataQueueSize] = '\0';
								
								// Started receiving data starting with the "+" until ":".
								receivingIpdHeader = TRUE;
								
								// Queue the received character in the shared queue.
								incomingDataQueue[incomingDataQueueSize++] = ch;
							}
							
						} else if (receivingIpdHeader == TRUE) { // ...if so, start buffering it and extract parameters as they're received to direct further queueing (i.e., data flow) operations.
							
							// TODO: Keep on-going pointers to data and depending on the state of the pointers, look for certain data, buffer into certain data, etc.
							
							// Check if the final ':' character was received.
							if (ch == ':') {
								// TODO: receivingSegment = FALSE;
								
								incomingDataQueue[6] = NULL; // Terminate the connection ID string by replacing the ',' following the connection ID with NULL.
								incomingDataQueue[incomingDataQueueSize] = '\0'; // HACK to quickly NULL-terminate. Instead, should search for the ':' character
								
								// Parse the IPD header (connection ID and data byte size)
								connectionID  = atoi (&incomingDataQueue[5]); // Point to the connection byte
//								size        = &httpResponseBuffer[7]; // connection + 2; // Point to the incoming byte count
								dataSize = atoi (&incomingDataQueue[7]);
								
								// Flag the IPD header as received.
								receivedIpdHeader = TRUE;
								
								// Tell the state machine to start receiving data.
								receivingData = TRUE;
								
								// Reset the buffering process so the first character in the shared buffer is the '+' character.
								incomingDataQueueSize = 0;
								incomingDataQueue[incomingDataQueueSize] = '\0';
								
								// HACK: Reset the connection's data queue every time an IPD packet is received.
								// TODO: Reset the connection's data queue UNLESS the data packet being buffered is continued from the previous packet.
								connectionDataQueueSize[connectionID] = 0;
								
								// TODO: Select the queue based on the connection ID
																
								// TODO: Reset the selected queue
								
							} else {
								
								// Queue the received character in the shared queue until receive the ':' character (or until timing out).
								incomingDataQueue[incomingDataQueueSize++] = ch;
							}
							
						}
					
					// Check if the "+IPD,<connection>,<size>:" segment was received. If so, parse it and set the connection-specific buffer.
					} else if (receivingData == TRUE) {
						
						// NOTE: At this point, data is queued into the channel-specific data queue for the channel specified in the IPD header.
						
						if (receivedData == FALSE) {
							
//							if (receivedSegmentHeader == TRUE) {
								
								// Buffer incoming bytes until the expected number of bytes has been reached (or exceeded).
								if (receivedDataSize < dataSize) {
									connectionDataQueue[connectionID][(connectionDataQueueSize[connectionID]++)] = ch; // incomingDataQueue[incomingDataQueueSize++] = ch;
									receivedDataSize++;
								}
								
								// Tell the state machine that the segment's data has been received.
								if (receivedDataSize == dataSize) {
									receivedData = TRUE;
								}
								
		//						connection = atoi(httpResponseBuffer[5]); // Point to the connection byte
		//						size       = &httpResponseBuffer[7]; // connection + 2; // Point to the incoming byte count
		//						httpResponseBuffer[10] = '\0'; // HACK to quickly null-terminate. Instead, should search for the ':' character
								
//							}
						}
						
						if (receivedData) {
							// TODO: Parse the segment data!
							
							return connectionID;
							
							// TODO: Return the channel number on which data was received (or sent?). (Later, after getting the data, check the status of the connection and close it if necessary!)
						}
					}
					
					// TODO: Non-blocking read until "+IPD,"
					// TODO: Blocking read until ',' for connection (i.e., "+IPD,3")
					// TODO: Blocking read until ":" for byte size (i.e., "+IPD,3,15:)
					// TODO: Blocking read until specified number of bytes are read into the corresponding buffer.
					
				}
				
				// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
				
			}
			
			// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
			
			// Update the start time of the receive operation after each segment of data is received to ensure that continuous segments are read in their entirety.
			startTime = Millis ();
			
		}
		
		// Empty the remaining characters on the buffer
		
		/*
		// Option 2: Search for a response after every received character has been buffered.
		receivedResponse = ESP8266_Search_For_Response (atCommandResponseBuffer, bufferSize);
		*/
	}
	
	// TODO: Check the buffer size to see if it's overflowed. If so, return a "buffer size exceeded"/"buffer overflow" error.
	
	// TODO: Return RESPONSE_TIMEOUT if timeout period expires.
	return -1; // Hack. Replace with suggestion in the TODO on the previous line.
	
}

//int8_t ESP8266_Receive_Incoming_Request (uint32_t milliseconds) {
//	// DEBUG: printf ("\tESP8266_Wait_For_Response \"%s\"\r\n", response);
//	
//	// Block until receive "OK" or "ERROR" is received, an unknown response was received, or a timeout period has expired.
//	// char httpResponseBuffer[RESPONSE_BUFFER_SIZE]; // TODO: Make this big enough only to store expected responses and only buffer the most recent set of received characters (i.e., shift characters into and out of the "sliding window" buffer).
//	// int bufferSize;
//	int i;
//	int8_t commandResponse = RESPONSE_NOT_FOUND;
////	for (responseBufferSize = 0; responseBufferSize < HTTP_RESPONSE_BUFFER_SIZE; responseBufferSize++) { httpResponseBuffer[responseBufferSize] = (char) 0; } // Initialize the buffer. This might not be necessary.
////	responseBufferSize = 0;
//	uint8_t incomingBufferSize = 0;
//	char *responseLocation = NULL;
//	const char *response = "\r\n\r\n";
//	int responseCount = 0;
//	const int expectedResponseCount = 2;
//	
//	
//	// TODO: Start a timer.
//	uint32_t startTime   = Millis ();
//	uint32_t currentTime = 0;
//	
//	while (commandResponse < 0) {
//		// TODO: Check timer in while condition and break if timeout period expires.
//		
////		currentTime = Millis ();
////		if (currentTime - startTime > milliseconds) {
////			printf ("TIMEOUT!!!\r\n");
////			return RESPONSE_TIMEOUT;
////		}
//		
//		// Buffer all incoming characters
////		incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
//		if (Ring_Buffer_NofElements () > 0) { // Check if any data has been received
//			// DEBUG: printf ("incomingBufferSize (before) = %d\r\n", incomingBufferSize);
//			while (Ring_Buffer_NofElements () > 0) { // Read each of the received characters from the buffer and send them to the device.
//				unsigned char ch;
//				(void) Ring_Buffer_Get (&ch); // (void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
////				incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
//				// DEBUG: printf ("incomingBufferSize (after) = %d (ch: %c)\r\n", incomingBufferSize, ch);
//				
//				if (incomingDataQueueSize < HTTP_RESPONSE_BUFFER_SIZE) {
//					incomingDataQueue[incomingDataQueueSize++] = ch; // Store the received character in the buffer.
//				}
//				
////				else {
////					// Shift the elements to the left
////					for (i = 0; i < HTTP_RESPONSE_BUFFER_SIZE - 1; i++) {
////						httpResponseBuffer[i] = httpResponseBuffer[i + 1];
////					}
////					
////					// Add the newest element to the end of the buffer
////					httpResponseBuffer[HTTP_RESPONSE_BUFFER_SIZE - 1] = ch;
////				}
//				
////				// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
////				// Option 1: Search for an expected response after every character to avoid removing characters from the buffer that aren't associated with this command.
////				commandResponse = ESP8266_Search_Tail_For_Response (response, httpResponseBuffer, responseBufferSize);
////				if (commandResponse > 0) { break; }
//			}
//			
//			// TODO: Don't use strstr. Just compare the most recent four characters and search for the pattern.
//			
//			if (incomingDataQueueSize > 4) {
//				if (incomingDataQueue[incomingDataQueueSize - 4] == '\r' && incomingDataQueue[incomingDataQueueSize - 3] == '\n' && incomingDataQueue[incomingDataQueueSize - 2] == '\r' && incomingDataQueue[incomingDataQueueSize - 1] == '\n') {
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
//			
////			if ((responseLocation = strstr (httpResponseBuffer, response)) != NULL) {
//////				printf ("FOUND!");
////				responseCount++;
////				
////				if (responseCount >= expectedResponseCount) {
////					commandResponse = RESPONSE_FOUND;
////				}
////			}
//			
//			// Check the buffer after every character to see if an expected response was received. Check this after every character prevents reading characters in the buffer that may be sent in response to a different command.
//			// Option 1: Search for an expected response after every character to avoid removing characters from the buffer that aren't associated with this command.
//			// commandResponse = ESP8266_Search_For_Response (response, responseBuffer, bufferSize);
//		}
//		
////		// Empty the remaining characters on the buffer
////		incomingBufferSize = ESP8266_Get_Incoming_Buffer_Size ();
////		if (incomingBufferSize > 0) { // Check if any data has been received
////			while (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Read each of the received characters from the buffer and send them to the device.
////				unsigned char ch;
////				(void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
////			}
////		}
//		
//		/*
//		// Option 2: Search for a response after every received character has been buffered.
//		receivedResponse = ESP8266_Search_For_Response (atCommandResponseBuffer, bufferSize);
//		*/
//	}
//	
//	// TODO: Check the buffer size to see if it's overflowed. If so, return a "buffer size exceeded"/"buffer overflow" error.
//	
//	// TODO: Return RESPONSE_TIMEOUT if timeout period expires.
//	return commandResponse; // Hack. Replace with suggestion in the TODO on the previous line.
//	
//}

int8_t ESP8266_Send_Command_AT () {
	// DEBUG: printf ("ESP8266_Send_Command_AT\r\n");
	
	// TODO: (Optional) Insert a wait here, if the function isn't consistently reliable.
	// TODO: Set up a timer that expires after specified amount of time to terminate this operation if the ESP8266 does not respond as expected in a typically timely manner.
	
	int8_t response = NULL;
	
	if (ESP8266_Send_Block ("AT\r\n") == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, ESP8266_DEFAULT_RESPONSE_TIMEOUT); // TODO: (New) Handle OK and ERROR here or elsewhere!
	}
	
	return response;
}

int8_t ESP8266_Send_Command_AT_RST () {
	// DEBUG: printf ("ESP8266_Send_Command_AT_RST\r\n");
	
	int8_t response = NULL;
	
	if (ESP8266_Send_Block ("AT+RST\r\n") == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, ESP8266_DEFAULT_RESPONSE_TIMEOUT);
		response = ESP8266_Wait_For_Response ("ready", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // Wait for "ready\r\n" (or might be slighly different character sequence like "ready\r\r\n")
	}
	
	return response;
}


int8_t ESP8266_Send_Command_AT_CWMODE (uint8_t mode) {
	// DEBUG: printf ("ESP8266_Send_Command_AT_CWMODE\r\n");
	
	int8_t response = NULL;
	char buffer[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	int n;
	
	n = sprintf (buffer, "AT+CWMODE_CUR=%d\r\n", mode);
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, ESP8266_DEFAULT_RESPONSE_TIMEOUT);
	}
	
	return response;
}


int8_t ESP8266_Send_Command_AT_CWJAP (const char *ssid, const char *password) {
	// DEBUG: printf ("ESP8266_Send_Command_AT_CWJAP\r\n");
	
	int8_t response = NULL;
	char buffer[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	int n;
	
	n = sprintf (buffer, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID_DEFAULT, PASSWORD_DEFAULT);
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, ESP8266_DEFAULT_RESPONSE_TIMEOUT);
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
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK_VARIANT, ESP8266_DEFAULT_RESPONSE_TIMEOUT);
		
//		if (response != NULL) {
			// ESP8266_Parse_Response (i.e., using httpResponseBuffer and httpBufferSize)
			if (incomingDataQueueSize > 0) {
				
				// TODO: Block until receive IP address!
				
				// Store the IP address in memory.
				if ((stationIP = strstr (incomingDataQueue, "STAIP,\"")) != NULL) {
					// Copy substring starting at location pointed to by stationIP. The IP address of the station is the substring from "STAIP,\"" to the following "\"". 
					stationIP = stationIP + strlen ("STAIP,\""); // Go to start of IP address substring
					length = strchr (stationIP, '"') - stationIP;
					stationIP[length] = '\0';
					strncpy (internetProfile.stationIPBuffer, stationIP, length);
//					D(printf ("IP: %s\r\n", esp8266_profile.stationIPBuffer));
				}
				
				// TODO: Block until receive MAC address in buffer!
				
				// Store the MAC address in memory.
				if ((stationMAC = strstr (incomingDataQueue, "STAMAC,\"")) != NULL) {
					// Copy substring starting at location pointed to by stationMAC. The MAC address of the station is the substring from "STAMAC,\"" to the following "\"".
					stationMAC = stationMAC + strlen ("STAMAC,\""); // Go to start of MAC address substring
					length = strchr (stationMAC, '"') - stationMAC; // Measure the length of the MAC address substring
					stationMAC[length] = '\0'; // Terminate the stored MAC address string.
					strncpy (internetProfile.stationMACBuffer, stationMAC, length);
//					D(printf ("MAC: %s\r\n", esp8266_profile.stationMACBuffer));
				}
			}
//		}
		
	}
	
	return response;
}

int8_t ESP8266_Send_Command_AT_CIPMUX (uint8_t enable) {
	// DEBUG: printf ("ESP8266_Send_Command_AT_CIPMUX\r\n");
	
	int8_t response = NULL;
	char buffer[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	int n;
	
	n = sprintf (buffer, "AT+CIPMUX=%d\r\n", enable);
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, ESP8266_DEFAULT_RESPONSE_TIMEOUT);
	}
	
	return response;
}

int8_t ESP8266_Send_Command_AT_CIPSERVER (uint8_t mode, uint8_t port) {
	// DEBUG: printf ("ESP8266_Send_Command_AT_CIPSERVER\r\n");
	
	int8_t response = NULL;
	char buffer[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	int n;
	
	n = sprintf (buffer, "AT+CIPSERVER=%d,%d\r\n", mode, port);
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK, ESP8266_DEFAULT_RESPONSE_TIMEOUT);
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
//int8_t ESP8266_Receive_Request_Header_Line () {
//	printf ("ESP8266_Receive_Request\r\n");
//
//	char* tokenEnd    = NULL;
//	
//	char  connection  = NULL; // 0 to 4
//	char* operation   = NULL; // "CONNECT"
//	
//	char* httpMethod  = NULL;
//	char* httpUri     = NULL;
//	char* httpVersion = NULL;
//	int8_t response   = RESPONSE_NOT_FOUND;
//	
//	char *responseData = "<html><h1>Clay</h1><button>I/O</button></html>";
//	char buffer[MAXIMUM_MESSAGE_LENGTH] = { 0 };
//	int n;
//	
//	// TODO: Extract client number (0-4) and command ("CONNECT" or else)
//	// response = ESP8266_Wait_For_Response ("0,CONNECT\r\n\r\n", DEFAULT_RESP8ONSE_TIMEOUT); // "0,CONNECT\r\n\r\n"
//	response = ESP8266_Wait_For_Response ("HTTP/1.1\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // "HTTP/1.1\r\n" (e.g., "+IPD,0,343:GET / HTTP/1.1\r\n")
//	
//	/* Extract connection information from received data. */
//	
//	// Search the buffer of the received data. Find the connection number (0-4).
//	connection = incomingDataQueue[0];
//	// TODO: Search for the connection ID.
//	printf ("Connection: %c\r\n", connection);
//	
//	// Search the buffer of the received data. Find the connection number (0-4).
//	operation  = strchr (incomingDataQueue, ',') + 1;
//	tokenEnd   = strchr (operation, '\r');
//	*tokenEnd  = NULL; // Terminate the string.
//	// TODO: Search for the connection ID.
//	printf ("Operation: %s\r\n", operation);
//	
//	/* Extract HTTP request data for the connection (if valid for the connection). */
//	
//	// Search the buffer of the received data. Find ':' and read until ' ' to get HTTP method
//	// The HTTP/1.1 methods are GET, HEAD, POST, PUT, DELETE, TRACE, OPTIONS, CONNECT, and PATCH.
//	httpMethod = strchr (tokenEnd + 1, ':') + 1; // strchr (httpResponseBuffer, ':') + 1;
//	tokenEnd   = strchr (httpMethod, ' ');
//	*tokenEnd  = NULL; // Terminate the string.
//	// TODO: Search for the method (i.e., "GET", "POST", etc.) and set a flag.
//	printf ("Method: %s\r\n", httpMethod);
//	
//	// Search the buffer of the received data. Find the first ' ' following the HTTP method to read the URI
//	httpUri   = tokenEnd + 1;
//	tokenEnd  = strchr (httpUri, ' ');
//	*tokenEnd = NULL; // Terminate the string.
//	// TODO: Copy the URI.
//	printf ("URI: %s\r\n", httpUri);
//	
//	httpVersion  = tokenEnd + 1;
//	tokenEnd     = strchr (httpVersion, '\r');
//	*tokenEnd    = NULL; // Terminate the string.
//	// TODO: Verify the correctness of the HTTP version.
//	printf ("Version: %s\r\n", httpVersion);
//	
//	/* Process the request. */
//	
//	if (strncmp (httpUri, "/hello", strlen ("/hello")) == 0) {
//		
//		/* Respond to the "/hello" request */
//		
//		// Send data to the connected client.
//		n = sprintf (buffer, "AT+CIPSEND=%c,%d\r\n", connection, strlen (responseData));
//		if (ESP8266_Send_Block (buffer) == TRUE) {
//			// Wait for ">" before sending data.
//			response = ESP8266_Wait_For_Response (">", ESP8266_DEFAULT_RESPONSE_TIMEOUT);
//		}
//		
//		// Send data to ESP8266.
//		n = sprintf (buffer, "%s", responseData);
//		if (ESP8266_Send_Block (buffer) == TRUE) {
//			response = ESP8266_Wait_For_Response ("SEND OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
//		}
//		
//		// TODO: Insert a brief pause here before closing the connection.
//		Wait (500);
//		
//		// Close the TCP connection.
//		n = sprintf (buffer, "AT+CIPCLOSE=%c\r\n", connection);
//		if (ESP8266_Send_Block (buffer) == TRUE) {
//			// Wait for "OK\r\n".
//			Wait (500);
//			response = ESP8266_Wait_For_Response ("OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
//		}
//		
//		// TODO: Wait for a short period of time before allowing additional AT commands.
//		
//	}
//	
////	if (strncmp (httpUri, "/favicon.ico", strlen ("/favicon.ico")) == 0) {
////		
////		/* Respond to the "/hello" request */
////		
////		// Send data to the connected client.
//////		n = sprintf (buffer, "AT+CIPSEND=%c,%d\r\n", connection, strlen (responseData));
//////		if (ESP8266_Send_Block (buffer) == TRUE) {
//////			// Wait for ">" before sending data.
//////			response = ESP8266_Wait_For_Response (">", ESP8266_DEFAULT_RESPONSE_TIMEOUT);
//////		}
//////		
//////		// Send data to ESP8266.
//////		n = sprintf (buffer, "%s", responseData);
//////		if (ESP8266_Send_Block (buffer) == TRUE) {
//////			response = ESP8266_Wait_For_Response ("SEND OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
//////		}
////		
////		// TODO: Insert a brief pause here before closing the connection.
////		Wait (500);
////		
////		// Close the TCP connection.
////		n = sprintf (buffer, "AT+CIPCLOSE=%c\r\n", connection);
////		if (ESP8266_Send_Block (buffer) == TRUE) {
////			// Wait for "OK\r\n".
////			response = ESP8266_Wait_For_Response ("OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
////		}
////		
////		// TODO: Wait for a short period of time before allowing additional AT commands.
////		
////	}
//	
//	return response;
//}

void Set_WiFi_Network (char *ssid, char *password) {
	strncpy (internetProfile.wifi_ssid, ssid, strlen (ssid));
	strncpy (internetProfile.wifi_password, password, strlen (password));
}

uint8_t Has_Internet_Address () {
	return TRUE; // TODO: Implement this!
}

char* Get_Internet_Address () {
	return internetProfile.stationIPBuffer;
}

void Set_Internet_Address (char *address) { // TODO: Set_Internet_Address (ESP8266_Profile *hardwareProfile)
	// Copy substring starting at location pointed to by stationIP. The IP address of the station is the substring from "STAIP,\"" to the following "\"". 
	//stationIP = stationIP + strlen ("STAIP,\""); // Go to start of IP address substring
	//length = strchr (stationIP, '"') - stationIP;
	//stationIP[length] = '\0';
	strncpy (internetProfile.stationIPBuffer, address, strlen (address));
//	D(printf ("IP: %s\r\n", esp8266_profile.stationIPBuffer));
}

void Start_UDP_Server (uint16_t port) {
	// DEBUG: printf ("ESP8266_Send_Command_AT_CIPSERVER\r\n");
	
	int8_t response = NULL;
	char buffer[MAXIMUM_MESSAGE_LENGTH] = { 0 };
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
//	D(printf ("%s\r\n", buffer));
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK_VARIANT, ESP8266_DEFAULT_RESPONSE_TIMEOUT);
	}
	
	return response;
}

void Send_UDP_Message (const char* address, uint16_t port, const char *message) {
	
	int8_t response = NULL;
	char buffer[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	int n;
	
	// The following variables correspond to parameters in the following AT command:
	// i.e., AT+CIPSTART=<channel index>,<protocol>,<remote address>,<remote port>[,(<local port>),(<mode>)]
	// e.g., AT+CIPSTART=1,"UDP","255.255.255.255",4445,1002,2
	
	uint8_t     channel    = 1; // i.e., the <channel> parameter
	const char *protocol   = "UDP";
	uint16_t    remotePort = port;
	uint16_t    localPort  = 1002; // TODO: Randomize this!? Could that enable multiple outgoing messages to the same destination port?
	uint8_t     mode       = 2;
	
	// Create the AT command string to connect to the device with the specified address and prepare for UDP communication. Then, send the string to the ESP8266.
	// e.g., AT+CIPSTART=0,"UDP","0.0.0.0",4445,1002,2
	n = sprintf (buffer, "AT+CIPSTART=%d,\"%s\",\"%s\",%d,%d,%d\r\n", channel, protocol, address, remotePort, localPort, mode);
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK_VARIANT, ESP8266_DEFAULT_RESPONSE_TIMEOUT);
	}
	
	// TODO: Put this into a separate command?
	
	// Prepare the ESP8266 to send data. To do so, create the AT command to initiate sending the message.
	// e.g., AT+CIPSEND=1,7,"255.255.255.255",4445
	n = sprintf (buffer, "AT+CIPSEND=%d,%d\r\n", channel, strlen (message));
	if (ESP8266_Send_Block (buffer) == TRUE) {
		// Wait for ">" before sending data.
		response = ESP8266_Wait_For_Response (">", ESP8266_DEFAULT_RESPONSE_TIMEOUT);
	}
	
	// Communicate data to send to the ESP8266.
	n = sprintf (buffer, "%s", message);
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response ("SEND OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
	}
	
	// TODO: Wait for a response (optionally), looking for "+IPD,..." for a time (with timeout).
	// +IPD,0,18:1443563177.377612
	//
	//	OK
	
	// Brief pause here before closing the connection.
	Wait (50); // Wait (200); // TODO: Make a preprocessor directive for this timeout!
	
	// TODO: Put this into a separate command?
	
	// Close the TCP connection.
	n = sprintf (buffer, "AT+CIPCLOSE=%d\r\n", channel);
	if (ESP8266_Send_Block (buffer) == TRUE) {
		// Wait for "OK\r\n".
		Wait (200); // Wait (500);
		response = ESP8266_Wait_For_Response ("OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
	}
	
	// Wait for a short period of time before allowing additional AT commands.
	Wait (100); // Wait (300);
	
	return response;
}

void Broadcast_UDP_Message (const char *message, uint16_t port) {
	int8_t response = NULL;
	char buffer[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	int n;
	
	// The following variables correspond to parameters in the following AT command:
	//     AT+CIPSTART=<channel index>,<protocol>,<remote address>,<remote port>[,(<local port>),(<mode>)]
	// e.g., AT+CIPSTART=1,"UDP","255.255.255.255",4445,1002,2
	uint8_t     channel       = 1; // i.e., the <channel> parameter
	const char *protocol      = "UDP";
	const char *remoteAddress = "255.255.255.255";
	//const char *remoteAddress = "192.168.43.122";
	uint16_t    remotePort    = port; // port; // 4445
	uint16_t    localPort     = 1002; // 1002 // TODO: Randomize this!
	uint8_t     mode          = 2;
	
	// AT+CIPSTART=0,"UDP","0.0.0.0",4445,4445,2
	n = sprintf (buffer, "AT+CIPSTART=%d,\"%s\",\"%s\",%d,%d,%d\r\n", channel, protocol, remoteAddress, remotePort, localPort, mode);
//	D(printf ("--> UDP Broadcast: %s\r\n", buffer));
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK_VARIANT, ESP8266_DEFAULT_RESPONSE_TIMEOUT);
	}
	
	// TODO: Put this into a separate command?
	
	//	AT+CIPSEND=1,7,"255.255.255.255",4445
	
	// Broadcast data to the broadcast address.
	// e.g., n = sprintf (buffer, "AT+CIPSEND=%d,%d,\"%s\",%d\r\n", channel, strlen ("HELLO\r\n"), remoteAddress, remotePort);
//	n = sprintf (buffer, "AT+CIPSEND=%d,%d,\"%s\",%d\r\n", channel, strlen (message), remoteAddress, remotePort);
	n = sprintf (buffer, "AT+CIPSEND=%d,%d\r\n", channel, strlen (message));
	if (ESP8266_Send_Block (buffer) == TRUE) {
		// Wait for ">" before sending data.
		response = ESP8266_Wait_For_Response (">", ESP8266_DEFAULT_RESPONSE_TIMEOUT);
	}
	
	// Send data to ESP8266.
//	n = sprintf (buffer, "%s", "HELLO\r\n");
	n = sprintf (buffer, "%s", message);
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response ("SEND OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
	}
	
	// TODO: Wait for a response (optionally), looking for "+IPD,..." for a time (with timeout).
	// +IPD,0,18:1443563177.377612
	//
	//	OK

	
	// Brief pause here before closing the connection.
	Wait (50); // Wait (200); // TODO: Make a preprocessor directive for this timeout!
	
	// TODO: Put this into a separate command?
	
	// Close the TCP connection.
	n = sprintf (buffer, "AT+CIPCLOSE=%d\r\n", channel);
	if (ESP8266_Send_Block (buffer) == TRUE) {
		// Wait for "OK\r\n".
		Wait (200); // Wait (500);
		response = ESP8266_Wait_For_Response ("OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
	}
	
	// Wait for a short period of time before allowing additional AT commands.
	Wait (100); // Wait (300);
	
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
 * Enables Wi-Fi. This is accomplished by configuring the ESP8266 and 
 * connecting to a Wi-Fi hotspot.
 * 
 * The following sequence of AT commands configures the ESP8266 for Wi-Fi.
 * 
 * AT // Test device
 * AT+RST // Reset device
 * AT+CWMODE=3 // Set AP mode
 * AT+CWJAP="AWS","Codehappy123" // Join access point
 * AT+CIFSR // Get local IP address
 * AT+CIPMUX=1 // Configure for multiple connections
 */
uint8_t Enable_WiFi (const char* ssid, const char *password) {
	// DEBUG: printf ("Enable_WiFi\r\n");
	
	int step = 0;
	int8_t status = 0;
	
	while (1) {
		if (step == 0) {
			// Resetting ESP8266.
			if ((status = ESP8266_Send_Command_AT_RST ()) > 0) {
				// "ESP8266 reset successfully.z
			} else {
				// ESP8266 reset failed.
				return step;
			}
			step++;
		} else if (step == 1) {
			// Testing communications with ESP8266.
			if ((status = ESP8266_Send_Command_AT ()) > 0) {
				// ESP8266 online.
			} else {
				// ESP8266 not responding.
				return step;
			}
			step++;
		} else if (step == 2) {
			// Setting mode of ESP8266.
			if ((status = ESP8266_Send_Command_AT_CWMODE ((uint8_t) 3)) > 0) {
				// ESP8266 mode set.
			} else {
				// ESP8266 mode NOT set.
				return step;
			}
			step++;
		} else if (step == 3) {
			// Joining access point.
			// TODO: Get list of APs and see if the specified one exists.
			Set_WiFi_Network (ssid, password); // Set the Wi-Fi network.
			if ((status = ESP8266_Send_Command_AT_CWJAP (internetProfile.wifi_ssid, internetProfile.wifi_password)) > 0) { // if ((status = ESP8266_Send_Command_AT_CWJAP (esp8266_profile.wifi_ssid, esp8266_profile.wifi_password)) > 0) { // if ((status = ESP8266_Send_Command_AT_CWJAP (SSID_DEFAULT, PASSWORD_DEFAULT)) > 0) {
				// ESP8266 joined access point.
			} else {
				// ESP8266 could NOT join access point.
				return step;
			}
			step++;
		} else if (step == 4) {
			// Getting IP address.
			if ((status = ESP8266_Send_Command_AT_CIFSR ()) > 0) {
				// IP info received.
			} else {
				// ESP8266 could NOT join access point.
				return step;
			}
			step++;
		} else if (step == 5) {
			// Configuring to accept multiple incoming connections.
			if ((status = ESP8266_Send_Command_AT_CIPMUX (TRUE)) > 0) {
				// ESP8266 set up for multiple connections.
			} else {
				// ESP8266 could NOT join access point.
				return FALSE;
			}
			step++;
		} else {
			// No command to run.
			break;
		}
		
//		ESP8266_Reset_TCP_Buffer (); // Reset the buffer where Clay stores responses to AT commands.
	}
	
	return TRUE;
}

/**
 * Set up web server.
 * 
 * This assumes the following sequence of AT commands has been issued previously:
 * 
 * AT // Test device
 * AT+RST // Reset device
 * AT+CWMODE=3 // Set AP mode
 * AT+CWJAP="AWS","Codehappy123" // Join access point
 * AT+CIFSR // Get local IP address
 * AT+CIPMUX=1 // Configure for multiple connections
 * 
 * The following sequence of AT commands configures the ESP8266 as a web server.
 * 
 * AT+CIPSERVER=1,80 // Turn server on port 80
 * NOTE: At this point start looking for +IPD
 */
uint8_t Start_HTTP_Server (uint16_t port) {
	// DEBUG: printf ("ESP8266_Start_Web_Server\r\n");
	
	int step = 0;
	int8_t status = 0;
	
	while (1) {

		if (step == 0) {
//			D(printf ("Configuring as TCP server. "));
			if ((status = ESP8266_Send_Command_AT_CIPSERVER (TRUE, port)) > 0) {
//				D(printf ("ESP8266 server listening on port 80.\r\n"));
				// TODO: Set status here.
			} else {
//				D(printf ("ESP8266 could not start server.\r\n"));
				// TODO: Write error to memory.
				// TODO: Throw interrupt to stop debugger (when in debug mode) so the error message can be inspected. Otherwise, when not in debug mode, reset device or send error to remote database.
				return FALSE;
			}
			step++;
		} else {
			break;
			// printf ("No command to run.\r\n");
		}
		
//		ESP8266_Reset_TCP_Buffer (); // Reset the buffer where Clay stores responses to AT commands.
	}
	
	return TRUE;
}

// TODO: void Process_HTTP_Request (Connection *connection, HTTP_Request httpRequest)
void Process_Incoming_HTTP_Request (int connection, const char *httpMethod, const char *httpUri) {
	
	int8_t status = NULL;
	int n;
	int i;
	int j;
	char buffer[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	int8_t response = RESPONSE_NOT_FOUND;
		
	const char *responseData = "<html><h1>Clay</h1><button>I/O</button></html>";
	
	if (strncmp (httpUri, "/hello", strlen ("/hello")) == 0) {
		
		/* Respond to the "/hello" request */
		
		// Send data to the connected client.
		n = sprintf (buffer, "AT+CIPSEND=%c,%d\r\n", connection, strlen (responseData));
		if (ESP8266_Send_Block (buffer) == TRUE) {
			// Wait for ">" before sending data.
			response = ESP8266_Wait_For_Response (">", ESP8266_DEFAULT_RESPONSE_TIMEOUT);
		}
		
		// Send data to ESP8266.
		n = sprintf (buffer, "%s", responseData);
		if (ESP8266_Send_Block (buffer) == TRUE) {
			response = ESP8266_Wait_For_Response ("SEND OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
		}
		
	} else if (strncmp (httpUri, "/channel/", strlen ("/channel/")) == 0) {
		
		if (strncmp (httpMethod, "GET", strlen ("GET")) == 0) {
//			D(printf ("Getting state of channel.\r\n"));
		} else if (strncmp (httpMethod, "POST", strlen ("POST")) == 0) {
//			D(printf ("Setting state of channel.\r\n"));
			// TODO: Read POST data
		}
		
	} else if (strncmp (httpUri, "/message", strlen ("/message")) == 0) {
		
		// e.g., for "turn 1 on" the httpUri string would be "/message?content=turn%201%20on"
		
		// TODO: Copy and clean the string contained in the message content.
		
		/* Extract message from request. */
		
#define MAXIMUM_MESSAGE_LENGTH 128
		int messageContentLength = 0;
		char messageContent[MAXIMUM_MESSAGE_LENGTH] = { 0 };
		
		Message *message = NULL;
		int messageCount = 0;
		
		if (strncmp (httpMethod, "GET", strlen ("GET")) == 0) {
//			printf ("Getting state of channel.\r\n");
			
			//strncpy (message, httpUri, MAXIMUM_MESSAGE_LENGTH);
			i = strchr (httpUri, '?') - httpUri; // Computes the offset between the beginning of the URI and the message content.
			if (i > 0) { // The offset will be greater than 0 if the '?' character was found.
				
				i = i + 9; // HACK: Move past the "?content=" string. // TODO: Actually search for parameters in the parameter list.
				j = 0;
				for ( ; i < strlen (httpUri); ) {
					
					// Copy the character from the HTTP request to the message.
					// When copying, replace any occurrences of the "%20" string with a ' ' character in the message.
					if (httpUri[i] == '%') {
						messageContent[j] = ' '; // Write a ' ' character instead of the "%20" string.
						i = i + 3; // Skip past the "%20" string.
					} else {
						messageContent[j] = httpUri[i];
						i++;
					}
					
					// Move to the next character in the message.
					j++;
				}
				messageContent[j] = '\0'; // Terminate the message.
				
				messageContentLength = j; // TODO: Replace the use of j above with messageLength
				
//				printf ("Message: %s\r\n", messageContent); // DEBUG
			} else {
//				D(printf ("Error: There was no message.\r\n"));
			}
			
			/* Process the extracted message */
			
			// TODO: Place the extracted message onto the message queue.
			
//			status = Process_Message (message);
			// TODO: Get response code from Process_Message ()
			// status = Process_Message (message);
//			printf ("Creating message. ");
			message = Create_Message (messageContent);
//			printf ("Queueing message \"%s\". ", (*message).content);
			messageCount = Queue_Message (&incomingMessageQueue, message);
//			printf ("Size: %d.\r\n", messageCount);
			
			status = TRUE;
			
//			Wait (200);
			
			/* Send HTTP request response (e.g., "200 OK" or "400 Bad Request"). */
			
			if (status == TRUE) {
				
				// Send data to the connected client.
				n = sprintf (buffer, "AT+CIPSEND=%d,%d\r\n", connection, strlen ("HTTP/1.1 200 OK\r\n"));
				if (ESP8266_Send_Block (buffer) == TRUE) {
					// Wait for ">" before sending data.
					response = ESP8266_Wait_For_Response (">", ESP8266_DEFAULT_RESPONSE_TIMEOUT);
				}
				
				// Send data to ESP8266.
				n = sprintf (buffer, "%s", "HTTP/1.1 200 OK\r\n");
				if (ESP8266_Send_Block (buffer) == TRUE) {
					response = ESP8266_Wait_For_Response ("SEND OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
				}
				
			} else {
				
				// Send data to the connected client.
				n = sprintf (buffer, "AT+CIPSEND=%d,%d\r\n", connection, strlen ("HTTP/1.1 400 Bad Request\r\n"));
				if (ESP8266_Send_Block (buffer) == TRUE) {
					// Wait for ">" before sending data.
					response = ESP8266_Wait_For_Response (">", ESP8266_DEFAULT_RESPONSE_TIMEOUT);
				}
				
				// Send data to ESP8266.
				n = sprintf (buffer, "%s", "HTTP/1.1 400 Bad Request\r\n");
				if (ESP8266_Send_Block (buffer) == TRUE) {
					response = ESP8266_Wait_For_Response ("SEND OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
				}
				
			}
			
		}
		
	}
}

void Monitor_Network_Communications () {
	
	int8_t status = NULL;
	char buffer[MAXIMUM_MESSAGE_LENGTH] = { 0 };
	int n;
	
	char* tokenEnd    = NULL;
	
	// "+IDP,<connection>,<operation>:" parameters.
	int8_t connection = -1;   // 0 to 4
	char* operation   = NULL; // "CONNECT"
	
	// HTTP request data
	char* httpMethod  = NULL;
	char* httpUri     = NULL;
	char* httpVersion = NULL;
	int8_t response   = RESPONSE_NOT_FOUND;
	
	Message *message = NULL;
	int messageCount = 0;
	
//	const char *responseData = "<html><h1>Clay</h1><button>I/O</button></html>";
	
	//if ((n = Ring_Buffer_Has_Data ()) == TRUE) {
	if (Ring_Buffer_NofElements () > 0) {
		
		/* Transfer data from the "common" circular queue (originally from the MCU's hardware serial FIFO buffer registers) to another connection-specific buffer. */
		
		// Start of message tokens:
		// - "0,CONNECT\r\n\r\n"
		// - "+IPD,0,1430:<data(1430)>"
		//
		// End of message tokens:
		// - "0,CLOSED\r\n\r\n"
		
		//if ((connection = ESP8266_Receive_Incoming_Data (ESP8266_DEFAULT_RESPONSE_TIMEOUT)) >= 0) { // e.g., "Accept: */*\r\n\r\n"; //if ((connection = ESP8266_Receive_Incoming_Data (ESP8266_DEFAULT_RESPONSE_TIMEOUT)) >= 0) { // e.g., "Accept: */*\r\n\r\n";
		if ((connection = ESP8266_Receive_Incoming_Data (10)) >= 0) {
			
			// Check the protocol type being used on the specified connection ID: UDP or TCP/HTTP.
			// Parse the data based on the protocol being used.
			
//			D(printf("connectionDataQueue[connection] = %s\r\n", connectionDataQueue[connection]));
			
			if (strstr (connectionDataQueue[connection], "HTTP/1.1") != NULL) { // if (strstr (incomingDataQueue, "HTTP/1.1") != NULL) {
//				printf ("RECEIVING TCP/HTTP DATA\r\n");
			
	
				/* Extract connection information from received data. */
				
				// TODO: Search for (e.g.,) "0,CONNECT\r\n\r\n"
				// TODO: Extract client number (0-4) and command ("CONNECT" or else)
				// TODO: Check the connection protocol type (UDP or TCP)
				// TODO: Parse the data accordingly, according to whether it's UDP or TCP
				
//				// Search the buffer of the received data. Find the connection number (0-4).
//				connection = httpResponseBuffer[0]; // (strchr (httpResponseBuffer, '+IPD,') + 1)[0]
//				// TODO: Search for the connection ID.
//				printf ("Connection: %d\r\n", connection);
//				Set_Connection_Type ((atoi (connection)), TCP_CONNECTION_TYPE);
//				
//				// TODO: Search for byte count of incoming data (e.g., the "82" in "+IPD,0,82:" from "+IPD,0,82:GET /hello HTTP/1.1\r\n")
//				
//				// Search the buffer of the received data. Find the operation (e.g., "CONNECT").
//				operation  = strchr (httpResponseBuffer, ',') + 1;
//				tokenEnd   = strchr (operation, '\r');
//				*tokenEnd  = NULL; // Terminate the string.
//				// TODO: Search for the connection ID.
//				printf ("Operation: %s\r\n", operation);
				
				/* Extract HTTP request data for the connection (if valid for the connection). */
				
				// Search the buffer of the received data. Find ':' and read until ' ' to get HTTP method
				// The HTTP/1.1 methods are GET, HEAD, POST, PUT, DELETE, TRACE, OPTIONS, CONNECT, and PATCH.
				httpMethod = & (connectionDataQueue[connection][0]); // &(incomingDataQueue[0]); // httpMethod = strchr (tokenEnd + 1, ':') + 1; // strchr (httpResponseBuffer, ':') + 1;
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
				
				ESP8266_Reset_Data_Buffer ();
				
				// TODO: Handle request that matches httpUri
				Process_Incoming_HTTP_Request (connection, httpMethod, httpUri);
				
				
				
				// Brief pause here before closing the connection.
				Wait (200);
				
				// Close the TCP connection.
				n = sprintf (buffer, "AT+CIPCLOSE=%d\r\n", connection);
				if (ESP8266_Send_Block (buffer) == TRUE) {
					// Wait for "OK\r\n".
					Wait (500);
					response = ESP8266_Wait_For_Response ("OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
					// TODO: Check if a timeout occurred. If so, check the status of the connection and close it.
				}
				
			} else {
				
				// UDP datagram
				
				int messageContentLength = 0;
				char messageContent[MAXIMUM_MESSAGE_LENGTH] = { 0 };
				
				strncpy (messageContent, connectionDataQueue[connection], connectionDataQueueSize[connection]); // strncpy (message, incomingDataQueue, incomingDataQueueSize);
				messageContent[(connectionDataQueueSize[connection])] = NULL; // message[incomingDataQueueSize] = NULL;
				
				ESP8266_Reset_Data_Buffer ();
				
				// TODO: Run AT commands to get IP for the connection ID (before closing it)
				
				// TODO: Queue the message for later processing.
//				status = Process_Message (message);
//				printf ("Creating message. ");
				message = Create_Message (messageContent);
	//			printf ("Queueing message \"%s\". ", (*message).content);
				messageCount = Queue_Message (&incomingMessageQueue, message);
	//			printf ("Size: %d.\r\n", messageCount);
				
				status = TRUE;
				
				// TODO: Move the acknowledgment code here?
				
//				printf ("RECEIVING UDP DATA: %s\r\n", messageContent);
				
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
	//				//response = ESP8266_Wait_For_Response ("OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
	//				ESP8266_Wait_For_Response ("OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT);
	//			}
			
	//			printf ("BUFFER!");
		}
	}
	
}


//AT+CIPSTART=0,"TCP","192.168.1.105",8080
//AT+CIPSEND=0,104
//POST /experiment HTTP/1.1
//Host: 192.168.1.105:8080
//Content-Type: text/plain
//Content-Length: 4
//
//data
//AT+CIPCLOSE=0
uint8_t Send_HTTP_POST_Request (const char *address, uint16_t port, const char *uri, const char *message) {
	int8_t response = NULL;
	char buffer[1024] = { 0 };
	int n;
	
	// The following variables correspond to parameters in the following AT command:
	//     AT+CIPSTART=<channel index>,<protocol>,<remote address>,<remote port>[,(<local port>),(<mode>)]
	// e.g., AT+CIPSTART=1,"UDP","255.255.255.255",4445,1002,2
	uint8_t     channel       = 2; // i.e., the <channel> parameter
	const char *protocol      = "TCP";
	const char *remoteAddress = address;
	//const char *remoteAddress = "192.168.43.122";
	uint16_t    remotePort    = port; // port; // 4445
//	uint16_t    localPort     = 1002; // 1002 // TODO: Randomize this!
//	uint8_t     mode          = 2;
	
	// AT+CIPSTART=0,"TCP","192.168.1.105",8080
	n = sprintf (buffer, "AT+CIPSTART=%d,\"%s\",\"%s\",%d\r\n", channel, protocol, remoteAddress, remotePort);
//	D(printf ("--> UDP Broadcast: %s\r\n", buffer));
	
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK_VARIANT, ESP8266_DEFAULT_RESPONSE_TIMEOUT);
	}
	
	// TODO: Put this into a separate command?
	
	//	AT+CIPSEND=1,7,"255.255.255.255",4445
	
	// TODO: Support different endpoints other than /experiment and Content-Type types (e.g., JSON).
	n = sprintf (buffer, "POST %s HTTP/1.1\r\nHost: %s:%d\r\nContent-Type: text/plain\r\nContent-Length: %d\r\n\r\n%s", uri, address, remotePort, strlen (message), message); 

	// Broadcast data to the broadcast address.
	// e.g., n = sprintf (buffer, "AT+CIPSEND=%d,%d,\"%s\",%d\r\n", channel, strlen ("HELLO\r\n"), remoteAddress, remotePort);
	n = sprintf (buffer, "AT+CIPSEND=%d,%d\r\n", channel, n);
	if (ESP8266_Send_Block (buffer) == TRUE) {
		// Wait for ">" before sending data.
		response = ESP8266_Wait_For_Response (">", ESP8266_DEFAULT_RESPONSE_TIMEOUT);
	}
	
	// Send data to ESP8266.
	n = sprintf (buffer, "POST %s HTTP/1.1\r\nHost: %s:%d\r\nContent-Type: text/plain\r\nContent-Length: %d\r\n\r\n%s", uri, address, remotePort, strlen (message), message); 
	if (ESP8266_Send_Block (buffer) == TRUE) {
		response = ESP8266_Wait_For_Response ("SEND OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // Wait for "\r\r\nSEND OK\r\n".
	}
	
	// TODO: Wait for a response (optionally), looking for "+IPD,..." for a time (with timeout).
	// +IPD,0,18:1443563177.377612
	//
	//	OK

	
	// Brief pause here before closing the connection.
	Wait (200); // TODO: Make a preprocessor directive for this timeout!
	
	// TODO: Put this into a separate command?
	
	// Close the TCP connection.
	n = sprintf (buffer, "AT+CIPCLOSE=%d\r\n", channel);
	if (ESP8266_Send_Block (buffer) == TRUE) {
		// Wait for "OK\r\n".
		Wait (500);
		response = ESP8266_Wait_For_Response ("OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT); // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
	}
	
	// Wait for a short period of time before allowing additional AT commands.
	Wait (300);
	
	return response;
}

char httpResponseBuffer[HTTP_RESPONSE_BUFFER_SIZE] = { 0 };
uint16_t httpResponseBufferSize = 0;

/**
 * Receive the HTTP GET response. Receive and parse it incrementally. 
 * First, receive and parse the status line, then general headers, then 
 * response headers, then entity headers, and finally the message body.
 * 
 * This incremental receive and parse process is based on the data 
 * structure of the HTTP generic message format, shown below:
 * 
 *    <status-line>
 *    <general-headers>
 *    <response-headers>
 *    <entity-headers>
 *    <empty-line>
 *    [<message-body>]
 *    [<message-trailers>]
 * 
 * This message format is described in detail at: 
 * 
 * http://www.tcpipguide.com/free/t_HTTPResponseMessageFormat.htm
 * 
 * ESP8266 Usage:
 * 
 * - This function may receive multiple segments of data from the ESP8266 in 
 *   the format "+IPD,<connection number>,<bytes in frame>:<frame bytes>". The   
 *   HTTP response may be distributed across multiple of these segments. The 
 *   bytes received in each frame are buffered in an array until they are 
 *   received in their entirety.
 */
static int8_t Receive_HTTP_GET_Response (int connection, uint32_t milliseconds) {
	
	int8_t response = NULL;
	
	uint8_t hasReceivedStatusLine = FALSE;
	uint8_t hasReceivedHeaders = FALSE;
	uint8_t hasMessageBody = FALSE;
	uint8_t hasReceivedMessageBody = FALSE;
	uint8_t hasReceivedResponse = FALSE;
	
	char *responseStatus = NULL;
	char *responseHeaders = NULL;
	char *responseMessage = NULL;

	char *responseHeaderContentLength = NULL;
	
	int headerContentLength = 0;
	int bytesToReceiveThisTime = 0;
	int receivedMessageByteCount = 0;
	
	// Start a timer.
	uint32_t startTime   = Millis ();
	uint32_t currentTime = 0;
	
	// Reset HTTP response buffer
	httpResponseBuffer[0] = NULL;
	httpResponseBufferSize = 0;
	
	int i;
	
	// TODO: while receive not timed out
	while (!hasReceivedResponse) {
		
		// Check the timer to see if the maximum allowed time for this process has expired.
		currentTime = Millis ();
		if ((currentTime - startTime) > milliseconds) {
			return RESPONSE_TIMEOUT;
		}
		
		// Get response to request.
		if ((connection = ESP8266_Receive_Incoming_Data (10)) >= 0) {
			
			// TODO: Make sure the received data is on the right connection/channel. This should be chosen dynamically, and a request and response structure should be maintained, with a function pointer to a Receive_HTTP_GET_Response function that will parse it (or maybe that's always the same function).
			
			// Copy the received data into the HTTP response buffer.
//			memcpy (httpResponseBuffer + httpResponseBufferSize, connectionDataQueue[connection], connectionDataQueueSize[connection]);
			
		}
		
		// Buffer the received +IPD data.
		
		// Check the state of the HTTP response receiving process.
		
		// Check if the first received line is an HTTP response header.
		if (!hasReceivedStatusLine) {
			if ((responseStatus = strstr (connectionDataQueue[connection], "\r\n")) != NULL) {
				// TODO: Check the header to make sure it's "200 OK" not "400" or another error code.
				hasReceivedStatusLine = TRUE;
			}
		} 
		
		// Check if the headers have been received. The headers are received if the HTTP response status line has been received and the HTTP buffer contains the "\r\n\r\n" pattern.
		if (hasReceivedStatusLine && !hasReceivedHeaders) {
			
			if ((responseHeaders = strstr (connectionDataQueue[connection], "\r\n\r\n")) != NULL) {
				
				hasReceivedHeaders = TRUE;
				
////				responseHeaders = responseHeaders + strlen ("\r\n\r\n");
//				
//				if ((responseHeaderContentLength = strstr (connectionDataQueue[connection], "Content-Length: ")) != NULL) {
//					
//					responseHeaderContentLength = responseHeaderContentLength + strlen ("Content-Length: ");
//					((char *) strstr (connectionDataQueue[connection], "\r\n"))[0] = '\0'; // Terminate the "Content-Length" header value.
//					headerContentLength = atoi (responseHeaderContentLength);
//					if (headerContentLength > 0) {
//						hasReceivedMessageBody = TRUE;
//					}
//				}
			}
		}
		
		// Check the header for the "Content-Length" header. Only receive the response if it contains the Content-Length header.
		if (hasReceivedStatusLine && hasReceivedHeaders && !hasMessageBody) {
			
			if ((responseHeaderContentLength = strstr (connectionDataQueue[connection], "Content-Length: ")) != NULL) {
				
				// The "Content-Length" header was found.
				
				responseHeaderContentLength = responseHeaderContentLength + strlen ("Content-Length: ");
				((char *) strstr (connectionDataQueue[connection], "\r\n"))[0] = '\0'; // Terminate the "Content-Length" header value.
				headerContentLength = atoi (responseHeaderContentLength);
				if (headerContentLength > 0) {
					hasMessageBody = TRUE;
				}
				
			} else {
				
				// The "Content-Length" header was not found in the header.
				
				hasReceivedResponse = TRUE;
				
			}
			
		}
		
		// Receive the message body (if any) based on the "Content-Length" header.
		if (hasReceivedStatusLine && hasReceivedHeaders && hasMessageBody && !hasReceivedMessageBody) {
			
			// Check if the message has been received and if not, continue to buffer bytes until the expected number of bytes has been received.
			if (receivedMessageByteCount < headerContentLength) {
			
				//responseMessage = responseHeaders;
				//responseMessage = ((char *) strstr (connectionDataQueue[connection], "\r\n\r\n"))[4];
//				if (responseMessage == NULL) {
//					responseMessage = responseHeaders;
//				}
				
				// Buffer the binary data
				//strncpy (httpResponseBuffer, connectionDataQueue[connection], connectionDataQueueSize[connection]);
				// # of bytes to copy: (IPD_Bytes_Received_In_Packet - responseMessage)
				
				if (connectionDataQueueSize[connection] == 136) {
					
					connectionDataQueueSize[connection] = connectionDataQueueSize[connection] + 1;
					connectionDataQueueSize[connection] = connectionDataQueueSize[connection] + 1;
					connectionDataQueueSize[connection] = connectionDataQueueSize[connection] + 1;
					connectionDataQueueSize[connection] = connectionDataQueueSize[connection] - 2;
					connectionDataQueueSize[connection] = connectionDataQueueSize[connection] - 1;
				}
				
				//bytesToReceiveThisTime = (responseMessage + 4) - connectionDataQueueSize[connection]; 
				if (receivedMessageByteCount == 0 && responseMessage == NULL) {
					responseMessage = (responseHeaders + 4);
					bytesToReceiveThisTime = (connectionDataQueue[connection] + connectionDataQueueSize[connection]) - responseMessage; // Assumes HTTP status line and headers are in the buffer (since the header's terminal "\r\n\r\n" was found)!
				} else if (receivedMessageByteCount == 0 && responseMessage != NULL) {
					responseMessage = connectionDataQueue[connection];
					bytesToReceiveThisTime = connectionDataQueueSize[connection]; // (connectionDataQueue[connection] + connectionDataQueueSize[connection]) - responseMessage; // Assumes HTTP status line and headers are in the buffer (since the header's terminal "\r\n\r\n" was found)!
				} else {
					responseMessage = connectionDataQueue[connection];
					bytesToReceiveThisTime = connectionDataQueueSize[connection]; // Receive all the data in the +IPD message.
				}
//				if (bytesToReceiveThisTime < 512) {
//					bytesToReceiveThisTime = bytesToReceiveThisTime + 0;
//				}
				
//				headerContentLength = connectionDataQueueSize[connection]; // 136
//				headerContentLength = connectionDataQueue[connection]; // address
//				headerContentLength = responseMessage; // address;
				
//				if (connectionDataQueueSize[connection] < 648) {
//					bytesToReceiveThisTime = bytesToReceiveThisTime + 0;
//				}
				
				if (connectionDataQueueSize[connection] < 512) {
					httpResponseBufferSize = httpResponseBufferSize + 1;
					httpResponseBufferSize = httpResponseBufferSize + 1;
					httpResponseBufferSize = httpResponseBufferSize + 1;
					httpResponseBufferSize = httpResponseBufferSize - 2;
					httpResponseBufferSize = httpResponseBufferSize - 1;
				}
//				
				if (httpResponseBufferSize >= 2048) {
					httpResponseBufferSize = httpResponseBufferSize + 1;
					httpResponseBufferSize = httpResponseBufferSize + 1;
					httpResponseBufferSize = httpResponseBufferSize + 1;
					httpResponseBufferSize = httpResponseBufferSize - 2 ;
					httpResponseBufferSize = httpResponseBufferSize - 1;
				}
				
//			(connectionDataQueue[connection] + (connectionDataQueueSize[connection])) - responseMessage
//			memcpy (httpResponseBuffer + httpResponseBufferSize, connectionDataQueue[connection], connectionDataQueueSize[connection]);
				//memcpy (httpResponseBuffer, responseHeaders + 4, headerContentLength);
				memcpy (httpResponseBuffer + httpResponseBufferSize, responseMessage, bytesToReceiveThisTime);
				receivedMessageByteCount += bytesToReceiveThisTime;
				httpResponseBufferSize += bytesToReceiveThisTime;
				//httpResponseBufferSize = headerContentLength;
	//				strncpy (httpResponseBuffer, responseHeaders, contentLength);
			
				// Check if the size of the buffer matches the expected number of incoming bytes
				if (httpResponseBufferSize >= headerContentLength) {
					hasReceivedMessageBody = TRUE;
				}
				
			}
			
		}
		
		if (hasReceivedStatusLine && hasReceivedHeaders && hasMessageBody && hasReceivedMessageBody) {
			hasReceivedResponse = TRUE;
//			break;
		}
		
//		if (hasReceivedResponse) {
//			
//			// Update the endianness of the received data for storage.
//			// i.e., Move [0] to [3]
//			//            [1] to [2]
//			//            [2] to [1]
//			//            [3] to [0]
//			
//			for (i = 0; i < httpResponseBufferSize; i += 4) { // when i = 256 what happens when size is 258? i+=4 => 260
//				char updatedBytes[4] = { 0 };
//				
//				// Create the new byte ordering.
//				if (httpResponseBufferSize == 258 && i == 256) {
//					updatedBytes[0] = ((i + 3) < httpResponseBufferSize ? httpResponseBuffer[i + 3] : 0xFF); // httpResponseBuffer[i + 3];
//					updatedBytes[1] = ((i + 2) < httpResponseBufferSize ? httpResponseBuffer[i + 2] : 0xFF); // httpResponseBuffer[i + 2];
//					updatedBytes[2] = ((i + 1) < httpResponseBufferSize ? httpResponseBuffer[i + 1] : 0xFF); // httpResponseBuffer[i + 1];
//					updatedBytes[3] = ((i + 0) < httpResponseBufferSize ? httpResponseBuffer[i + 0] : 0xFF); // httpResponseBuffer[i + 0];
//				} else {
//					updatedBytes[0] = ((i + 3) < httpResponseBufferSize ? httpResponseBuffer[i + 3] : 0xFF); // httpResponseBuffer[i + 3];
//					updatedBytes[1] = ((i + 2) < httpResponseBufferSize ? httpResponseBuffer[i + 2] : 0xFF); // httpResponseBuffer[i + 2];
//					updatedBytes[2] = ((i + 1) < httpResponseBufferSize ? httpResponseBuffer[i + 1] : 0xFF); // httpResponseBuffer[i + 1];
//					updatedBytes[3] = ((i + 0) < httpResponseBufferSize ? httpResponseBuffer[i + 0] : 0xFF); // httpResponseBuffer[i + 0];
//				}
//				
//				// Copy the new byte ordering into memory. The conditionals prevent a buffer overflow.
////				httpResponseBuffer[i + 0] = updatedBytes[0];
////				httpResponseBuffer[i + 1] = updatedBytes[1];
////				httpResponseBuffer[i + 2] = updatedBytes[2];
////				httpResponseBuffer[i + 3] = updatedBytes[3];
//				
//				if ((i + 0) < httpResponseBufferSize) {
//					httpResponseBuffer[i + 0] = updatedBytes[0];
//				}
//				
//				if ((i + 1) < httpResponseBufferSize) {
//					httpResponseBuffer[i + 1] = updatedBytes[1];
//				}
//				
//				if ((i + 2) < httpResponseBufferSize) {
//					httpResponseBuffer[i + 2] = updatedBytes[2];
//				}
//				
//				if ((i + 3) < httpResponseBufferSize) {
//					httpResponseBuffer[i + 3] = updatedBytes[3];
//				}
//				
//				// Handle edge case that occurs when incrementing the index by 4 will skip some of the remaining bytes.
//				// e.g., When httpResponseBufferSize is 258 and the iterator has been increased to i = 256 over the course of looping.
//				//       Incrementing i += 4 will produce i = 260, which will cause the loop to break, and the final 2 bytes will be ignored.
//				/*
//				if (httpResponseBufferSize > 0 && ((httpResponseBufferSize - i) < 4)) {
//					
//					// Create the new byte ordering.
//					updatedBytes[0] = (((i + 4) + 3) < httpResponseBufferSize ? httpResponseBuffer[(i + 4) + 3] : 0); // httpResponseBuffer[i + 3];
//					updatedBytes[1] = (((i + 4) + 2) < httpResponseBufferSize ? httpResponseBuffer[(i + 4) + 2] : 0); // httpResponseBuffer[i + 2];
//					updatedBytes[2] = (((i + 4) + 1) < httpResponseBufferSize ? httpResponseBuffer[(i + 4) + 1] : 0); // httpResponseBuffer[i + 1];
//					updatedBytes[3] = (((i + 4) + 0) < httpResponseBufferSize ? httpResponseBuffer[(i + 4) + 0] : 0); // httpResponseBuffer[i + 0];
//					
//					// Copy the new byte ordering into memory.
//					httpResponseBuffer[(i + 4) + 0] = updatedBytes[0];
//					httpResponseBuffer[(i + 4) + 1] = updatedBytes[1];
//					httpResponseBuffer[(i + 4) + 2] = updatedBytes[2];
//					httpResponseBuffer[(i + 4) + 3] = updatedBytes[3];
//					
////					if ((i + 3 + 1) < httpResponseBufferSize) {
////						
////					}
////					
////					if ((i + 3 + 2) < httpResponseBufferSize) {
////						
////					}
////					
////					if ((i + 3 + 3) < httpResponseBufferSize) {
////						
////					}
//					
////					if ((i + 4) >= httpResponseBufferSize) {
////						
////					}
//					
//				}
//				*/
//			}
//			
//		}
	}
	
	return response;
}

uint8_t ESP8266_Start_Connection (uint8_t connection, const char *protocol, const char *address, uint16_t port) {
	
	// TODO: Handle AT+CIPSTART responses: "OK", "ERROR", "ALREADY CONNECT"
	
	int8_t response = -1;
	char buffer[1024] = { 0 };
	int n;
	
	// AT+CIPSTART=0,"TCP","192.168.1.105",8080
	n = sprintf (buffer, "AT+CIPSTART=%d,\"%s\",\"%s\",%d\r\n", connection, protocol, address, port);
	if (n > 128) {
		// TODO: Buffer overflow.
		return FALSE;
	}
	// TODO: Handle AT+CIPSTART responses: "OK", "ERROR", "ALREADY CONNECT"
	if (ESP8266_Send_Block (buffer) == TRUE) {
		
		response = ESP8266_Wait_For_Response_v2 ("OK\r\n", "\r\r\nALREADY CONNECTED", "ERROR\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT);
		
		if (response == 0) {
			return TRUE; // TODO: Update state of channel[id].connected = TRUE;
		} else if (response == 1) {
			return FALSE; // TODO: Disconnect and then reconnect before continuing!
		} else if (response == 2) {
			return FALSE;
		}
		
		else {
			return FALSE;
		}
		
//		if ((response = ESP8266_Wait_For_Response (RESPONSE_SIGNATURE_OK_VARIANT, ESP8266_DEFAULT_RESPONSE_TIMEOUT)) != RESPONSE_FOUND) {
//			return FALSE; // TODO: Replace with error code: .
//		}
	}
	
	return FALSE;
	
}

uint8_t ESP8266_Close_Connection (uint8_t connection) {
	
	// TODO: Handle AT+CIPSTART responses: "OK", "ERROR", "ALREADY CONNECT"
	
	int8_t response = NULL;
	char buffer[1024] = { 0 };
	int n;
	
	// Close the TCP connection.
	// TODO: Look for "4,CLOSED" and if it's not found, close the connection using AT+CIPCLOSE (like below).
	// TODO: Look for "link is not\r\n\r\nERROR"
	n = sprintf (buffer, "AT+CIPCLOSE=%d\r\n", connection);
	if (ESP8266_Send_Block (buffer) == TRUE) {
		// Wait for "OK\r\n".
//		Wait (500);
		
		response = ESP8266_Wait_For_Response_v2 ("OK\r\n", "ERROR\r\n", NULL, ESP8266_DEFAULT_RESPONSE_TIMEOUT);
		
		if (response == 0) {
			return TRUE;
		} else if (response == 1) {
			return FALSE;
		} else if (response == 2) {
			return FALSE;
		}
		
		else { // e.g., -2
			return FALSE;
		}
		
//		if ((response = ESP8266_Wait_For_Response ("OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT)) != RESPONSE_FOUND) { // "AT+CIPCLOSE=0\r\n0,CLOSED\r\n\r\nOK\r\n"
//			return FALSE; // TODO: Replace with error code.
//		}
	}
	
	// Wait for a short period of time before allowing additional AT commands.
	Wait (300);
	
}

//AT+CIPSTART=0,"TCP","192.168.1.105",8080
//AT+CIPSEND=0,104
//POST /experiment HTTP/1.1
//Host: 192.168.1.105:8080
//Content-Type: text/plain
//Content-Length: 4
//
//data
//AT+CIPCLOSE=0
uint8_t Send_HTTP_GET_Request (const char *address, uint16_t port, const char *uri) {
	
	int8_t response = NULL;
	int8_t status = NULL;
	char buffer[1024] = { 0 };
	int n;
	int nPrev;
	int connection;
	
	// The following variables correspond to parameters in the following AT command:
	//    AT+CIPSTART=<channel index>,<protocol>,<remote address>,<remote port>[,(<local port>),(<mode>)]
	// e.g., AT+CIPSTART=1,"UDP","255.255.255.255",4445,1002,2
	uint8_t channel = 4; // i.e., the <channel> parameter // TODO: Get available channel using AT commands. If none are available, return ERROR_ALL_CHANNELS_OCCUPIED
	const char *protocol = "TCP";
	
	// Connect to the remote host.
	while ((status = ESP8266_Start_Connection (channel, protocol, address, port)) == FALSE) {
		ESP8266_Close_Connection (channel); // Close!
		Wait (200); // Retry frequency.
	}
	// Success! Connected.
	
	// Get the size of the HTTP request.
	n = sprintf (buffer, "GET %s HTTP/1.1\r\n\r\n", uri);

	// Broadcast data to the broadcast address.
	// e.g., n = sprintf (buffer, "AT+CIPSEND=%d,%d,\"%s\",%d\r\n", channel, strlen ("HELLO\r\n"), remoteAddress, remotePort);
	status = FALSE;
	nPrev = n;
	while (status == FALSE) {
		n = sprintf (buffer, "AT+CIPSEND=%d,%d\r\n", channel, nPrev);
		if (ESP8266_Send_Block (buffer) == TRUE) {
			// Wait for ">" before sending data.
			if ((response = ESP8266_Wait_For_Response (">", ESP8266_DEFAULT_RESPONSE_TIMEOUT)) == RESPONSE_FOUND) {
//			if ((response = ESP8266_Wait_For_Response (">", ESP8266_DEFAULT_RESPONSE_TIMEOUT)) != RESPONSE_FOUND) {
				// return FALSE; // TODO: Replace with error code.
				status = TRUE;
//				break;
				Wait (50);
			} else {
				
				// TODO: There's no ">" detected, so we're infinitely looping! Reset. Start over.
				// - reset device, start from scratch! connect to AP, yada, yada...
				
				// TODO: (HACK) Send nPrev characters, followed by \r\n; then type AT until got expected response (with short wait time)... or just put that in a loop until get expected response, then retry AT+CIPSEND.
				
			}
//			Wait (50);
		}
	}
	
//	Wait (200);
//	while (status == FALSE);
		
	// Send data to ESP8266.
	n = sprintf (buffer, "GET %s HTTP/1.1\r\n\r\n", uri);
	if (ESP8266_Send_Block (buffer) == TRUE) {
		// Wait for "\r\r\nSEND OK\r\n".
		if ((response = ESP8266_Wait_For_Response ("SEND OK\r\n", ESP8266_DEFAULT_RESPONSE_TIMEOUT)) != RESPONSE_FOUND) {
			return FALSE; // TODO: Replace with error code.
		}
	}
	
	Wait (100);

	// Receive the HTTP GET response.
	status = Receive_HTTP_GET_Response (channel, 10000);
	
	// Brief pause here before closing the connection.
//	Wait (200); // TODO: Make a preprocessor directive for this timeout!
	
	// TODO: Put this into a separate command?
	
	// Get the status the TCP connection.
	
	// TODO: Before closing the conneciton, make sure it's connected!
	status = ESP8266_Close_Connection (channel);
	
	return TRUE; // TODO: Replace with success code.
}

