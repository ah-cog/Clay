/*
 * Bootloader.c
 *
 *  Created on: Jan 9, 2016
 *      Author: thebh
 */

//includes
#include "bootloader.h"
#include "PE_Types.h"
#include "Cpu.h"
#include "stdlib.h"

//defines
#define APPLICATION_KEY_VALUE  0xA5A5A5A5U
#define BOOT_START_ADDR        0x00000000U

//data types

//global vars -- this guy is placed at the end of RAM, 0x20007FF8. This is 8 bytes from the end, which is the size of the struct.
//shared_bootloader_data __attribute__((section(".BootloaderSharedData"))) SharedData;
shared_bootloader_data SharedData; //TODO: remap to shared section. See line above
bool is_update_available;

//local vars


//function prototypes
static void boot_jump(uint32_t address);

//implementations

uint8_t Initialize_Bootloader () {
	is_update_available = FALSE;
	// TODO: Check value of SharedData.ApplicationUpdateAvailable and other shared data and configure state?
	SharedData.UpdateApplication = FALSE;
}

/**
 * Gets the checksum of the most recent firmware from the server and compares 
 * it to the computed checksum of the device's current firmware. This function 
 * is used to decide whether or not to update the firmware by calling 
 * Update_Firmware (...).
 * 
 * Returns TRUE if the checksums are the same. False if they are different.
 */
uint8_t Has_Latest_Firmware ()
{
	uint8_t result = TRUE; // Return value. Default to true.
	uint16_t firmwareChecksum = NULL; // The stored checksum value.
	uint16_t latestFirmwareChecksum = NULL; // The checksum of the latest firmware.
	
	char *address = FIRMWARE_SERVER_ADDRESS;
	uint16_t port = FIRMWARE_SERVER_PORT;
	char uriParameters[64] = { 0 };
	
	// Retrieve firmware checksum from the server.
	sprintf (uriParameters, "/clay/firmware/checksum/");
	Send_HTTP_GET_Request (address, port, uriParameters);
	latestFirmwareChecksum = atoi (httpResponseBuffer);
	
	// Get the stored checksum
	firmwareChecksum = Read_Program_Checksum ();
	
	// Check if the checksum of the application firmware matches the checksum 
	// of the latest firmware received from the server.
	if (firmwareChecksum != latestFirmwareChecksum) {
		result = FALSE;
	}
	
    //TODO: implement this. If the firmware IS out of date, set the value in the SharedData struct.
    return result;
}

//Returns true if an update is available and writes the ApplicationKey value so 
//        the bootloader will know that the application has run.
bool Update_Available ()
{
	int8_t status = NULL;
	uint8_t result = FALSE;
	
	// Check remote server to see if an update is available.
	// If so, indicate it by writing to the shared flash memory so the bootloader can read it.
	if ((status = Has_Latest_Firmware ()) == TRUE) {
		SharedData.ApplicationUpdateAvailable = TRUE;
	}
	
	// Return the value stored in the shared memory application indicating 
	// whether or not there's an update available.
	result = SharedData.ApplicationUpdateAvailable;
    
    return result;
}

/**
 * Disables all interrupts.
 */
void Disable_Interrupts ()
{
	NVICICER0 = 0xFFFFFFFF;
	NVICICER1 = 0xFFFFFFFF;
	NVICICER2 = 0xFFFFFFFF;
	NVICICER3 = 0xFFFFFFFF;
}

//Call to jump to the bootloader and update the application.
void Jump_To_Bootloader_And_Update_Application()
{
//    SharedData.UpdateApplication = TRUE;
 
	if (SharedData.UpdateApplication) {
		//change vector table offset register to application vector table
		SCB_VTOR = BOOT_START_ADDR & 0x1FFFFF80;
	
		//set stack pointer/pc to the reset interrupt.
		boot_jump(BOOT_START_ADDR);
	}
}


//executes bootloader jump
static void boot_jump(uint32_t address)
{
    //Load new stack pointer address
    asm("LDR SP, [R0]");
    //Load new program counter address
    asm("LDR PC, [R0,#4]");
}
