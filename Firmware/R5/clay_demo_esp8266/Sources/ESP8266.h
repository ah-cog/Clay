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

typedef struct {
	LDD_TDeviceData *handle;
	volatile uint8_t isSent;
	uint8_t rxChar;
	uint8_t (*rxPutFct)(uint8_t);
} ESP8266_UART_Device; // NOTE: This was named "UART_Desc" previously.

ESP8266_UART_Device deviceData;

void ESP8266_Init ();
void ESP8266_SendChar (unsigned char ch, ESP8266_UART_Device *desc);
void ESP8266_SendString (const unsigned char *str, ESP8266_UART_Device *desc);

#endif /* ESP8266_H_ */
