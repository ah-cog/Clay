/*
 * nvm.c
 *
 *  Created on: Dec 15, 2015
 *      Author: thebh_000
 */

#include "PE_Types.h"
#include "Cpu.h"
#include "nvm.h"
#include "nvm_data.h"

volatile uint8_t active_readers;

//sets up the NVM with the size given.
bool nvm_init()
{
    //see section 28.4.11.14 of K20 sub-family reference manual 
    FTFL_FCCOB0 = FTFL_FCCOB0_CCOBn(0x80);        //PGMPART command
    FTFL_FCCOB1 = 0x00;
    FTFL_FCCOB2 = 0x00;
    FTFL_FCCOB3 = 0x00;
    FTFL_FCCOB4 = 0x33;                         // Subsystem A and B are both 1 KB
    FTFL_FCCOB5 = 0x03;                         // Data flash size = 32 KB

    // EEPROM backup size = 32 KB
    FTFL_FSTAT = FTFL_FSTAT_CCIF_MASK;        // Launch command sequence

    while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK))
        ;        // Wait for command completion
    while (!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK))
        ;        //wait for struct to get loaded.

    active_readers = 0;

    return TRUE;
}

//call this before attempting to read data stored in the flash. reads can't happen while a write is in progress.
bool nvm_busy()
{
    return !(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK);
}

uint8_t read_byte(uint8_t * byte_addr)
{
    start_multibyte_read();
    uint8_t rval = *byte_addr;
    end_multibyte_read();

    return rval;
}

uint16_t read_word(uint16_t * word_addr)
{
    start_multibyte_read();
    uint16_t rval = *word_addr;
    end_multibyte_read();

    return rval;
}

uint32_t read_dword(uint32_t * dword_addr)
{
    start_multibyte_read();
    uint32_t rval = *dword_addr;
    end_multibyte_read();

    return rval;
}

bool write_byte(uint8_t * byte_addr, uint8_t value)
{
    if (active_readers || nvm_busy()) return FALSE;

    *byte_addr = value;
    return TRUE;
}

bool write_word(uint16_t * word_addr, uint16_t value)
{
    if (active_readers || nvm_busy()) return FALSE;

    *word_addr = value;
    return TRUE;
}

bool write_dword(uint32_t * dword_addr, uint32_t value)
{
    if (active_readers || nvm_busy()) return FALSE;

    *dword_addr = value;
    return TRUE;
}

//use to copy data into nvm locations.
bool copy_to_nvm(void * nvm_location, void * source, uint32_t length)
{
    if (active_readers || nvm_busy() || (uint32_t) nvm_location < NVM_START_ADDR || (uint32_t) nvm_location > NVM_END_ADDR
            || (uint32_t) nvm_location > NVM_START_ADDR + sizeof(nvm)) return FALSE;

    for (int i = 0; i < length; ++i)
    {
        while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK))
            ;
        ((uint8_t*) nvm_location)[i] = ((uint8_t*) source)[i];
    }

    return TRUE;
}

//use to copy data out of nvm locations.
bool copy_from_nvm(void * nvm_location, void * destination, uint32_t length)
{
    if (nvm_busy() || (uint32_t) nvm_location < NVM_START_ADDR || (uint32_t) nvm_location > NVM_END_ADDR
            || (uint32_t) nvm_location > NVM_START_ADDR + sizeof(nvm)) return FALSE;

    start_multibyte_read();

    for (int i = 0; i < length; ++i)
    {
        while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK))
            ;
        ((uint8_t*) destination)[i] = ((uint8_t*) nvm_location)[i];
    }

    end_multibyte_read();

    return TRUE;
}

bool start_multibyte_read()
{
    while (nvm_busy())
        ;
    ++active_readers;
    return TRUE;
}

bool end_multibyte_read()
{
    --active_readers;
    return TRUE;
}
