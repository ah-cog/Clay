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

//local vars


//function prototypes
static void boot_jump(uint32_t address);

//implementations


//Returns true if an update is available and writes the ApplicationKey value so 
//        the bootloader will know that the application has run.
bool UpdateAvailable()
{
    if(SharedData.ApplicationKey != APPLICATION_KEY_VALUE)
    {
        SharedData.ApplicationKey = APPLICATION_KEY_VALUE;
    }
    
    return SharedData.ApplicationUpdateAvailable;
}

//Call to jump to the bootloader and update the application.
void Jump_To_Bootloader_And_Update_Application()
{
    //change vector table offset register to application vector table
    SCB_VTOR = BOOT_START_ADDR & 0x1FFFFF80;

    //set stack pointer/pc to the reset interrupt.
    boot_jump(BOOT_START_ADDR);
}


//executes bootloader jump
static void boot_jump(uint32_t address)
{
    //Load new stack pointer address
    asm("LDR SP, [R0]");
    //Load new program counter address
    asm("LDR PC, [R0,#4]");
}
