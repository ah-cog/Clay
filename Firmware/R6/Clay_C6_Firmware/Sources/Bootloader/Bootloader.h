/*
 * Bootloader.h
 *
 *  Created on: Jan 9, 2016
 *      Author: thebh
 */

#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include "ESP8266.h"
#include "program_flash.h"

//includes
#include "PE_Types.h"

//defines
#define APPLICATION_KEY_VALUE  0xA5A5A5A5U // The value that gets written into the shared variable.
#define BOOTLOADER_KEY_VALUE   0x00000000U
#define BOOT_START_ADDR        0x00000000U

#define FIRMWARE_SERVER_ADDRESS "107.170.180.158"
#define FIRMWARE_SERVER_PORT 3000

//data types
typedef struct shared_bootloader_data
{
    uint32_t ApplicationKey;
    bool UpdateApplication;
    bool ApplicationUpdateAvailable;
    uint16_t pad;
}shared_bootloader_data;

//global vars
extern shared_bootloader_data SharedData;
extern bool is_update_available;

//prototypes

extern uint8_t Initialize_Bootloader ();

extern uint8_t Has_Latest_Firmware ();

//Returns true if an update is available and writes the ApplicationKey value so 
//        the bootloader will know that the application has run.
extern bool Update_Available ();

extern void Disable_Interrupts ();

//Call to jump to the bootloader and update the application.
extern void Jump_To_Bootloader_And_Update_Application();


#endif /* BOOTLOADER_H */
