#include "Application.h"

void Application (void) {
	int  i            = 0;
//	int  lineReceived = FALSE;
//	char buffer[64]   = { '\0' };
//	int  ch           = (int) '\0';
//	int server_started = FALSE;
//	byte bufferSize;
	char buffer[64] = { 0 };
	int n;
	
	int incomingByteCount = 0; // number of bytes available to read
	byte bufferedByteCount = 0;
	
	char* tokenEnd    = NULL;
	
	char  connection  = NULL; // 0 to 4
	char* operation   = NULL; // "CONNECT"
	
	char* httpMethod  = NULL;
	char* httpUri     = NULL;
	char* httpVersion = NULL;
	int8_t response   = RESPONSE_NOT_FOUND;
	
	const char *responseData = "<html><h1>Clay</h1><button>I/O</button></html>";
	
	bool led_state = FALSE; // LEDs
	Color_RGB colors[] = {
			{ LED_MODE_MAX, LED_MODE_OFF, LED_MODE_LOW },
			{ LED_MODE_LOW, LED_MODE_MAX, LED_MODE_OFF },
			{ LED_MODE_OFF, LED_MODE_LOW, LED_MODE_MAX }
	}; // LEDs

	int led_index = 0; // LEDs
	int color_index = 0; // LEDs
	
	printf ("Clay\r\n");
	
	printf ("\r\n");
	
	printf ("Enabling clock. ");
	Enable_Clock ();
	printf ("Done.\r\n");
	
	printf ("Starting clock. ");
	Start_Clock ();
	printf ("Done.\r\n");
	
	printf ("\r\n");
	
	printf ("Starting LEDs. ");
	Enable_PCA9552();
	Wait (5);
	printf ("Done.\r\n");
	
	printf ("\r\n");
	
	printf ("Enabling ESP8266. ");
	Enable_ESP8266 ();
	printf ("Done.\r\n");
	
	printf ("\r\n");
	
	Start_HTTP_Server (HTTP_SERVER_PORT);
	
	Color_RGB onColor  = { LED_MODE_MAX, LED_MODE_OFF, LED_MODE_LOW };
	Color_RGB offColor = { LED_MODE_OFF, LED_MODE_OFF, LED_MODE_OFF };
	Set_LED_Output ((RGB_LED) 0,  &offColor);
	Set_LED_Output ((RGB_LED) 1,  &onColor);
	Set_LED_Output ((RGB_LED) 2,  &offColor);
	Set_LED_Output ((RGB_LED) 3,  &onColor);
	Set_LED_Output ((RGB_LED) 4,  &offColor);
	Set_LED_Output ((RGB_LED) 5,  &onColor);
	Set_LED_Output ((RGB_LED) 6,  &offColor);
	Set_LED_Output ((RGB_LED) 7,  &onColor);
	Set_LED_Output ((RGB_LED) 8,  &offColor);
	Set_LED_Output ((RGB_LED) 9,  &onColor);
	Set_LED_Output ((RGB_LED) 10, &offColor);
	Set_LED_Output ((RGB_LED) 11, &onColor);
	
	for (;;) {
		if (Ring_Buffer_NofElements () > 0) {
			
			ESP8266_Reset_TCP_Buffer (); // Clear the incoming data buffer
			// ESP8266_Receive_Incoming_Request ("\r\n\r\n", DEFAULT_RESPONSE_TIMEOUT); // i.e., "0,CONNECT\r\n\r\n"
			ESP8266_Receive_Incoming_Request (DEFAULT_RESPONSE_TIMEOUT); // e.g., "Accept: */*\r\n\r\n";
			// Wait (5000); // TODO: Reduce this to about 200 ms (or possibly zero since the processing below isn't related to communications with the ESP)
			
			/* Extract connection information from received data. */
			
			// TODO: Search for (e.g.,) "0,CONNECT\r\n\r\n"
			// TODO: Extract client number (0-4) and command ("CONNECT" or else)
			
			// Search the buffer of the received data. Find the connection number (0-4).
			connection = httpResponseBuffer[0]; // (strchr (httpResponseBuffer, '+IPD,') + 1)[0]
			// TODO: Search for the connection ID.
			printf ("Connection: %c\r\n", connection);
			
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
				}
				
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
			
			printf ("BUFFER!");
		}
		
		
		// LEDs
		if (tick_1msec)
			{
				tick_1msec = FALSE;

			}
			if (tick_250msec)
			{
				tick_250msec = FALSE;

			}
			if (tick_500msec)
			{
				tick_500msec = FALSE;

				//toggle LEDs
//				LED1_PutVal(LED1_DeviceData, !led_state);
//				LED2_PutVal(LED2_DeviceData, led_state);
				led_state = !led_state;

//				Color_RGB * derp = colors + color_index;
//
//				Set_LED_Output((RGB_LED) led_index, derp);
//
//				if (++led_index % RGB_INVALID == 0)
//				{
//					led_index = 0;
//					color_index = (color_index + 1) % 3;
//				}
			}
	}
	
			
//			ESP8266_Reset_TCP_Buffer ();
//			ESP8266_Receive_Request_Header_Line ();
//			ESP8266_Buffer_Until ("\r\n\r\n", DEFAULT_RESPONSE_TIMEOUT); // i.e., "0,CONNECT\r\n\r\n"
//			ESP8266_Buffer_Until ("\r\n\r\n", DEFAULT_RESPONSE_TIMEOUT); // e.g., "Accept: */*\r\n\r\n"
			
//			+IPD,0,82:
			
//			printf ("BUFFER!");
			
////			printf ("ESP8266_RxBuf_NofElements = %d\r\n", ESP8266_RxBuf_NofElements ());
//			i = 0;
//			while (ESP8266_RxBuf_NofElements () > 0) { // Read each of the received characters from the buffer and send them to the device.
//				unsigned char ch;
//
	
//	// "REPL" framework
//	for (;;) {
//		i = 0;
//		lineReceived = 0;
//		ch = (int) 0;
//		printf ("> "); // Print terminal prompt.
//		do {
//			ch = getchar (); // ch = getc (stdin);
//			buffer[i++] = ch; // Append the character to the buffer.
//			putchar (ch); // Echo the character.
//			if (ch == '\n') { printf ("<newline>"); lineReceived = 1; } // Show when a newline character is entered.
//		} while (lineReceived == 0);
//		// buffer[i] = '\0'; // Terminate the string
//		buffer[i - 1] = '\r';
//		buffer[i]     = '\n';
//		buffer[i + 1] = '\0'; // Terminate the string
//		// printf ("%s", (unsigned char*) buffer); // Echo the entered text
//		// fflush (stdout);
//		
//		// ESP8266_Start_Web_Server (HTTP_SERVER_PORT);
//		
////		ESP8266_Send_String ((unsigned char*) buffer, &deviceData); // Send the data to the bridged serial peripheral (UART0)
//		
//		// int rxBufferSize = (int) RxBuf_NofElements (); // Check if any data has been received
//		// printf ("Received %d bytes:\r\n", rxBufferSize);
////		if (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Check if any data has been received
////			// SendString ((unsigned char*)"echo: ", &deviceData); // Print "echo: " to the device. This will be followed by what was received from the device, echoing it.
////			while (ESP8266_Get_Incoming_Buffer_Size () > 0) { // Read each of the received characters from the buffer and send them to the device.
////				unsigned char ch;
////				(void) ESP8266_Get_Incoming_Character (&ch); // Get the next character from the buffer.
////				printf ("%c", (unsigned char) ch);
////			}
////			// printf ("\r\n");
////		}
//		// fflush (stdout);
//	}
}
