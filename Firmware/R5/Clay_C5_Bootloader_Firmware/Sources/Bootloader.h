#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include "Drivers/ESP8266.h"

typedef struct shared_bootloader_data
{
    uint32_t ApplicationKey;
    bool UpdateApplication;
    bool ApplicationUpdateAvailable;
    uint16_t pad;
}shared_bootloader_data;

extern shared_bootloader_data SharedData;

extern bool UserApprovedUpdate();

extern uint8_t Verify_Firmware ();

extern uint8_t Has_Latest_Firmware ();

extern uint32_t Calculate_Checksum_On_Bytes (const uint8_t *bytes, uint32_t length);

extern uint8_t Verify_Firmware_Bytes (const uint8_t *bytes, uint32_t length);

extern uint8_t Write_Firmware_Bytes (uint32_t address, const uint8_t *bytes, uint32_t length);

extern void Update_Firmware ();

extern void Jump_To_Application();

#endif /* BOOTLOADER_H_ */
