/*
 * ESP8266.c
 *
 *  Created on: Aug 31, 2015
 *      Author: mokogobo
 */

#include "ESP8266.h"
#include "ESP8266_RxBuf.h"

void ESP8266_Init (void) { // static void Init (void) {
	deviceData.handle = AS1_Init (&deviceData);
	deviceData.isSent = FALSE;
	deviceData.rxChar = '\0';
	deviceData.rxPutFct = ESP8266_RxBuf_Put;

	ESP8266_RxBuf_Init ();

	while (AS1_ReceiveBlock (deviceData.handle, (LDD_TData *) &deviceData.rxChar, sizeof (deviceData.rxChar)) != ERR_OK) {

	}
}

void ESP8266_SendChar (unsigned char ch, ESP8266_UART_Device *desc) { // static void SendChar(unsigned char ch, ESP8266_UART_Device *desc) {
	desc -> isSent = FALSE;
	while (AS1_SendBlock (desc -> handle, (LDD_TData*) &ch, 1) != ERR_OK) {

	}
	while (!desc->isSent) {

	}
}

void ESP8266_SendString (const unsigned char *str, ESP8266_UART_Device *desc) { // static void SendString (const unsigned char *str, ESP8266_UART_Device *desc) {
	while (*str != '\0') {
		ESP8266_SendChar (*str++, desc);
	}
}

byte ESP8266_Incoming_Buffer_Size () {
	return ESP8266_RxBuf_NofElements ();
}

byte ESP8266_Get_Incoming_Character (byte *elemP) {
	return ESP8266_RxBuf_Get (elemP);
}
