#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include "Drivers/ESP8266.h"
#include "PE_Types.h"

typedef struct shared_bootloader_data
{
    uint32_t ApplicationKey;
    bool UpdateApplication;
    bool ApplicationUpdateAvailable;
    uint16_t pad;
}shared_bootloader_data;

extern shared_bootloader_data SharedData;

uint8_t Verify_Firmware ();

uint8_t Has_Latest_Firmware ();

uint32_t Calculate_Checksum_On_Bytes (const uint8_t *bytes, uint32_t length);

uint8_t Verify_Firmware_Bytes (const uint8_t *bytes, uint32_t length);

uint8_t Write_Firmware_Bytes (uint32_t address, const uint8_t *bytes, uint32_t length);

void Update_Firmware ();

void Jump_To_Application();

#endif /* BOOTLOADER_H_ */
