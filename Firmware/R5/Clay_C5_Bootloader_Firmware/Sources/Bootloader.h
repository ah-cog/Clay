#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include "Drivers/ESP8266.h"

#define FIRMWARE_SERVER_ADDRESS "192.168.16.180" // "107.170.180.158"
#define FIRMWARE_SERVER_PORT 3000

#define DEFAULT_FIRMWARE_CHECKSUM 0x0000
#define DEFAULT_FIRMWARE_SIZE 0 // The total size of the firmware to retrieve from the server.
#define FIRMWARE_BLOCK_SIZE 512 // The number of bytes to request from the firmware server in a single request.

typedef struct shared_bootloader_data
{
    uint32_t ApplicationKey;
    bool UpdateApplication;
    bool ApplicationUpdateAvailable;
    uint16_t pad;
} shared_bootloader_data;

extern shared_bootloader_data SharedData;

extern bool UserApprovedUpdate();

extern uint8_t Verify_Firmware();

extern uint8_t Has_Latest_Firmware();

extern uint16_t Calculate_Checksum_On_Bytes(const uint8_t *data, uint32_t size);

extern uint8_t Verify_Firmware_Bytes(const uint8_t *bytes, uint32_t length);

extern uint8_t Write_Firmware_Bytes(uint32_t address, const uint8_t *bytes, uint32_t length);

extern uint8_t Update_Firmware();

extern void Jump_To_Application();

#endif /* BOOTLOADER_H_ */
