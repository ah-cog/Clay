#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include "Drivers/ESP8266.h"

//char firmwareBuffer[1024] = { 0 };
//uint16_t firmwareBufferSize = 0;

uint8_t Verify_Firmware ();

uint8_t Has_Latest_Firmware ();

uint32_t Calculate_Checksum_On_Bytes (const uint8_t *bytes, uint32_t length);

uint8_t Verify_Firmware_Bytes (const uint8_t *bytes, uint32_t length);

uint8_t Write_Firmware_Bytes (const uint8_t *bytes, uint32_t length);

void Update_Firmware ();

#endif /* BOOTLOADER_H_ */
