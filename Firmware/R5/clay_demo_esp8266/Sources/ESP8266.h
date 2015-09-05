/*
 * ESP8266.h
 *
 *  Created on: Aug 31, 2015
 *      Author: mokogobo
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include "PE_Types.h"
#include "PE_LDD.h"

#define SSID_DEFAULT "Jackson 5" // "AWS" // "joopal"
#define PASSWORD_DEFAULT "Michael Jackson" // "Codehappy123" // "Cassandra2048"

typedef struct {
	LDD_TDeviceData *handle;
	volatile uint8_t isSent;
	uint8_t rxChar;
	uint8_t (*rxPutFct)(uint8_t);
} ESP8266_UART_Device; // NOTE: This was named "UART_Desc" previously.

ESP8266_UART_Device deviceData;

void ESP8266_Init ();
void ESP8266_Send_Char (unsigned char ch, ESP8266_UART_Device *desc);
void ESP8266_Send_String (const unsigned char *str, ESP8266_UART_Device *desc);

byte ESP8266_Get_Incoming_Buffer_Size ();
byte ESP8266_Get_Incoming_Character (byte *elemP);

#define RESPONSE_SIGNATURE_OK    "\r\r\n\r\nOK\r\n"
#define RESPONSE_SIGNATURE_ERROR "\r\r\n\r\nERROR\r\n"
#define RESPONSE_SIGNATURE_FAIL  "\r\n\r\nFAIL\r\n"    // e.g., AT+CWJAP=\"AWS\",\"Codehappy123\"\r\r\n+CWJAP:3\r\n\r\nFAIL\r\n

#define RESPONSE_ERROR      0 // Defined this as 0 (FALSE) so it can be used in conditional statements when returned.
#define RESPONSE_OK         1 // Defined this as 1 (TRUE) so it can be used in conditional statements when returned.
#define RESPONSE_FOUND      1
#define RESPONSE_NOT_FOUND -1
#define RESPONSE_TIMEOUT   -2

#define DEFAULT_RESPONSE_TIMEOUT 10000

int8_t ESP8266_Search_For_Response (const char *response, const char *buffer, int bufferSize);
int8_t ESP8266_Wait_For_Response (const char *response, uint32_t milliseconds);
// TODO: ESP8266_Wait_For_Responses (...) and return the index for the parameter from the argument list that was returned

int8_t ESP8266_Send_Command_AT ();
int8_t ESP8266_Send_Command_AT_RST ();
int8_t ESP8266_Send_Command_AT_CWMODE (uint8_t mode);
int8_t ESP8266_Send_Command_AT_CWJAP (const char *ssid, const char *password);

void ESP8266_Start_Web_Server ();

#endif /* ESP8266_H_ */
