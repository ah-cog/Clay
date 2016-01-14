/*
 * flash.c
 *
 *  Created on: Dec 19, 2015
 *      Author: Ben
 */

#include "PE_Types.h"
#include "FLASH1.h"
#include "program_flash.h"

#define CRC16_POLY 0x8005U

bool checksum_initialized = FALSE;
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

    while (!rval && !flash_operation_completed)
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
    while (!rval && !flash_operation_completed)
    {
        //run operation by calling flash1_main
        FLASH1_Main(FLASH1_DeviceData );
    }

    return rval;
}

static uint32_t poly = CRC16_POLY;
//static uint32_t tot = 0;
//static uint32_t totr = 0;
//static uint32_t fxor = 0;
//static uint32_t tcrc = 0;

void init_checksum(uint32_t tot, uint32_t totr, uint32_t fxor, uint32_t tcrc)
{
//    if (checksum_initialized) return;
    SIM_SCGC6 |= SIM_SCGC6_CRC_MASK;
    CRC_Config(poly, tot, totr, fxor, tcrc);        //use polynomial given above, don't transpose on read or write, don't read bits xor'd, do 16-bit crc.
    checksum_initialized = TRUE;
}

//computes the checksum of the application binary.
uint16_t compute_checksum()
{
    if (!checksum_initialized)
    {
//        init_checksum();
    }
    //use seed vlue of 0
    return (uint16_t) CRC_Cal_16(0, (uint8_t *) APP_START_ADDR, APP_END_ADDR - APP_START_ADDR - 2);
}
