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

//defines
#define APPLICATION_KEY_VALUE  0xA5A5A5A5U
#define BOOT_START_ADDR        0x00000000U

//data types

//global vars -- this guy is placed at the end of RAM, 0x20007FF8. This is 8 bytes from the end, which is the size of the struct.
shared_bootloader_data __attribute__((section(".BootloaderSharedData"))) SharedData;
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


//Returns true if an update is available and writes the ApplicationKey value so 
//        the bootloader will know that the application has run.
bool Update_Available ()
{
//    if(SharedData.ApplicationKey != APPLICATION_KEY_VALUE)
//    {
//        SharedData.ApplicationKey = APPLICATION_KEY_VALUE;
//    }
    
    return SharedData.ApplicationUpdateAvailable;
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
