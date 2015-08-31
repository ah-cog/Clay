#include "Application.h"
#include "ESP8266_RxBuf.h"
#include "AS1.h"
#include "ESP8266.h"
#include <stdlib.h>

void APP_Run (void) {
	int  i            = 0;
	int  lineReceived = FALSE;
	char buffer[64]   = { '\0' };
	int  ch           = (int) '\0';
	  
	ESP8266_Init ();
	
	printf ("Clay\r\n");
	printf ("\r\n");
	
	// "REPL" framework
	for (;;) {
		i = 0;
		lineReceived = 0;
		ch = (int) 0;
		printf ("> "); // Print terminal prompt.
		do {
			ch = getchar (); // ch = getc (stdin);
			buffer[i++] = ch; // Append the character to the buffer.
			putchar (ch); // Echo the character.
			if (ch == '\n') { /* printf ("<newline>"); */ lineReceived = 1; } // Show when a newline character is entered.
		} while (lineReceived == 0);
		// buffer[i] = '\0'; // Terminate the string
		buffer[i - 1] = '\r';
		buffer[i]     = '\n';
		buffer[i + 1] = '\0'; // Terminate the string
		// printf ("%s", (unsigned char*) buffer); // Echo the entered text
		// fflush (stdout);
		
		// TODO: Process the buffer.
		
		// Relay buffer to the bridged serial peripheral (UART0)
		
		ESP8266_SendString ((unsigned char*) buffer, &deviceData); // Send the data to the bridged serial peripheral (UART0)
		
		// int rxBufferSize = (int) RxBuf_NofElements (); // Check if any data has been received
		// printf ("Received %d bytes:\r\n", rxBufferSize);
		if (ESP8266_RxBuf_NofElements () > 0) { // Check if any data has been received
			// SendString ((unsigned char*)"echo: ", &deviceData); // Print "echo: " to the device. This will be followed by what was received from the device, echoing it.
			while (ESP8266_RxBuf_NofElements() > 0) { // Read each of the received characters from the buffer and send them to the device.
				unsigned char ch;
				(void) ESP8266_RxBuf_Get (&ch); // Get the next character from the buffer.
				printf ("%c", (unsigned char) ch);
			}
			// printf ("\r\n");
		}
		// fflush (stdout);
	}
	
	/*
	// Receive incoming data from the buffer and echo it back
//	SendString((unsigned char*)"Hello World\r\n", &deviceData); // Send to the device
	while (1) {
		int rxBufferSize = (int) RxBuf_NofElements (); // Check if any data has been received
		if (RxBuf_NofElements() != 0) {
//		if (rxBufferSize != 0) {
			printf ("Received %d bytes: ", rxBufferSize);
			// SendString ((unsigned char*)"echo: ", &deviceData); // Print "echo: " to the device. This will be followed by what was received from the device, echoing it.
			while (RxBuf_NofElements() != 0) { // Read each of the received characters from the buffer and send them to the device.
				unsigned char ch;
				(void) RxBuf_Get (&ch);
				SendChar (ch, &deviceData);
				printf ("%c\r\n", (unsigned char) ch);
			}
		}
	}
	*/
}
