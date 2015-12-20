/*
 * flash.c
 *
 *  Created on: Dec 19, 2015
 *      Author: Ben
 */

#include "PE_Types.h"
#include "FLASH1.h"
#include "program_flash.h"

volatile bool flash_operation_completed;

//erases the entire program flash
uint16_t erase_program_flash()
{
    uint32_t address = APP_START_ADDR;
    uint16_t rval = 0;

    while (!rval && address < APP_END_ADDR)
    {
        rval = erase_program_flash_page(address);

        if (rval > 0) break;

        address += FLASH_MEMORY_PAGE_SIZE;
    }

    return rval;
}

//erases the page of program flash containing the address
uint16_t erase_program_flash_page(uint32_t addr)
{
    //set up erase block operation
    uint16_t rval = FLASH1_Erase(FLASH1_DeviceData, addr, FLASH_MEMORY_PAGE_SIZE);

    flash_operation_completed = FALSE;

    while (!flash_operation_completed)
    {
        //run operation by calling flash1_main
        FLASH1_Main(FLASH1_DeviceData );
    }

    return rval;
}

//writes data to the program flash
uint16_t write_program_block(uint32_t destination, uint8_t * data, uint32_t length)
{
    //set up flash operation
    uint16_t rval = FLASH1_Write(FLASH1_DeviceData, data, destination, length);

    flash_operation_completed = FALSE;
    while (!flash_operation_completed)
    {
        //run operation by calling flash1_main
        FLASH1_Main(FLASH1_DeviceData );
    }

    return rval;
}

//computes the checksum of the application binary.
uint16_t compute_checksum()
{
    return 0;
}
