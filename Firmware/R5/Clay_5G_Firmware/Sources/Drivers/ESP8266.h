/*
 * ESP8266.h
 *
 *  Created on: Aug 31, 2015
 *      Author: mokogobo
 */

/**
 * Notes on Signals:
 * 
 * - RST (connected to PTC0 set up output on MK20DX256VLH7)
 *   Function: External reset signal (Low: Active)
 * 
 * - XPD_DCDC (connected to PTC3 set as I/O on MK20DX256VLH7)
 *   Function: "Deep-Sleep Wakeup"
 *   - "it appears that [...] XPD_DCDC is a power down pin which may disable the transmitter (X=transmit) without requiring the chip to "reboot" when coming out of power down" (Source: http://www.esp8266.com/viewtopic.php?f=5&t=7&start=10)
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include <stdio.h>
#include <string.h>

#include "PE_Types.h"
#include "PE_LDD.h"

#include "Utilities/Ring_Buffer.h"

#define SSID_DEFAULT "clay-2.4ghz" // "joopal" // "clay-2.4ghz" // "AWS"
#define PASSWORD_DEFAULT "goldenbrown" // "Cassandra2048" // "goldenbrown" // "Codehappy123"

typedef struct {
	LDD_TDeviceData *handle;
	volatile uint8_t isSent;
	uint8_t rxChar;
	uint8_t (*rxPutFct)(uint8_t);
} ESP8266_UART_Device; // NOTE: This was named "UART_Desc" previously.

ESP8266_UART_Device deviceData;

typedef struct {
	char apIPBuffer[16];
	char apMACBuffer[18];
	char stationIPBuffer[16];
	char stationMACBuffer[18];
} ESP8266_Profile;

ESP8266_Profile esp8266_profile;

void Enable_ESP8266 (); // Formerly ESP8266_Initialize ()
void ESP8266_Send_Byte (unsigned char ch); // Formerly ESP8266_Send_Char (unsigned char ch, ESP8266_UART_Device *desc)
void ESP8266_Send_Bytes (const unsigned char *str); // Formerly ESP8266_Send_String (const unsigned char *str, ESP8266_UART_Device *desc)
int8_t ESP8266_Send_Block (const char *str);

byte ESP8266_Get_Incoming_Buffer_Size ();
byte ESP8266_Get_Incoming_Character (byte *elemP);

uint8_t ESP8266_Has_Incoming_Data ();
void ESP8266_Buffer_Incoming_Data ();
void ESP8266_Reset_TCP_Buffer ();
uint8_t ESP8266_Has_Incoming_Request ();
int8_t ESP8266_Receive_Incoming_Request (uint32_t milliseconds);

#define HTTP_SERVER_PORT 80

#define RESPONSE_SIGNATURE_OK    "\r\r\n\r\nOK\r\n"
#define RESPONSE_SIGNATURE_OK_VARIANT "\r\n\r\nOK\r\n"
#define RESPONSE_SIGNATURE_ERROR "\r\r\n\r\nERROR\r\n"
#define RESPONSE_SIGNATURE_FAIL  "\r\n\r\nFAIL\r\n"    // e.g., AT+CWJAP=\"AWS\",\"Codehappy123\"\r\r\n+CWJAP:3\r\n\r\nFAIL\r\n

#define RESPONSE_ERROR      0 // Defined this as 0 (FALSE) so it can be used in conditional statements when returned.
#define RESPONSE_OK         1 // Defined this as 1 (TRUE) so it can be used in conditional statements when returned.
#define RESPONSE_FOUND      1
#define RESPONSE_NOT_FOUND -1
#define RESPONSE_TIMEOUT   -2

#define DEFAULT_RESPONSE_TIMEOUT 10000

#define HTTP_RESPONSE_BUFFER_SIZE 2048 // Store this many of the most recent chars in AT command response buffer

char httpResponseBuffer[HTTP_RESPONSE_BUFFER_SIZE];
int responseBufferSize;

void ESP8266_Reset_TCP_Buffer ();

//typedef struct {
//	uint8_t id; // 0-4
//	char rxBuffer[2048];
//	char txBuffer[1024];
//} Client_Connection; // NOTE: This was named "UART_Desc" previously.
//
//#define CLIENT_CONNECTION_LIMIT 5
//Client_Connection connections[CLIENT_CONNECTION_LIMIT];

int8_t ESP8266_Search_For_Response (const char *response, const char *buffer, int bufferSize); // TODO: Make general system function for use with strings!
int8_t ESP8266_Wait_For_Response (const char *response, uint32_t milliseconds); // TODO: Block until the specified response in received (in a yet to be specified buffer) or the specified duration of time in milliseconds has passed since blocking.
// TODO: ESP8266_Wait_For_Responses (...) and return the index for the parameter from the argument list that was returned

#define AT 0
#define AT_RST 1
#define AT_CWMODE 2 
#define AT_CWJAP 3
#define AT_CIPMUX 4
#define AT_CIPSERVER 5

// int8_t ESP8266_Process_AT_Command (const char *at_command); // Terminal to the ESP8266.
int8_t ESP8266_Send_Command_AT ();
int8_t ESP8266_Send_Command_AT_RST ();
int8_t ESP8266_Send_Command_AT_CWMODE (uint8_t mode);
int8_t ESP8266_Send_Command_AT_CWJAP (const char *ssid, const char *password);
int8_t ESP8266_Send_Command_AT_CIFSR ();
int8_t ESP8266_Send_Command_AT_CIPMUX (uint8_t enable);
int8_t ESP8266_Send_Command_AT_CIPSERVER (uint8_t mode, uint8_t port);

void Start_HTTP_Server (uint16_t port); // ESP8266_Start_HTTP_Server
// TODO: check for any incoming data on serial
// TODO: Put the available data into the local buffer
// TODO: monitor the buffer for complete requests, timeouts, errors, or malformed requests (such as may occur when overwriting two of them unwittingly due to client-server sync mishaps).
int8_t ESP8266_Receive_Request_Header_Line ();
// int8_t HTTP_Server_Has_Request (HTTP_Server *http_server); // Returns TRUE if any incoming requests are queued.
// Request* HTTP_Server_Fetch_Next_Request (); // Returns a pointer to the next request on the queue (if any) or NULL if there are no requests.
// int8_t HTTP_Server_Process_Request (); // or HTTP_Server_Handle_Request (); // Performs the request handler function defined for the received request.
// Stop_HTTP_Server (HTTP_Server *http_server);

// uint8_t Start_UDP_Server (unit16 port);
// uint8_t Send_UDP_Message (const char *ip_address, const char *message);
// uint8_t Broadcast_UDP_Message (const char *message);
// uint8_t Stop_UDP_Server ();

// uint8_t Enable_MPU ();
// MPU_Get_Orientation
// MPU_Get_Acceleration
// uint8_t Slow_MPU (); // Puts the device into sleep.
// uint8_t Disable_MPU ();

// uint8_t Enable_WiFi ();
// WiFi_Get_Orientation
// uint8_t Slow_WiFi (); // Puts the device into sleep.
// uint8_t Disable_WiFi ();

// Enable_Mesh
// Disable_Mesh

// uint8_t Enable_Channels ();
// WiFi_Get_Orientation
// uint8_t Slow_WiFi (); // Puts the device into sleep.
// uint8_t Disable_Channels ();

// Start_Computer // Starts a terminal or interface to cloud computing service such as AWS Lambda
// Stop_Computer

#endif /* ESP8266_H_ */
