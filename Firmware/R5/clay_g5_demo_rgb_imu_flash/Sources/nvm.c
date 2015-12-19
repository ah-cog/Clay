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

    return TRUE;
}

//call this before attempting to read data stored in the flash. reads can't happen while a write is in progress.
bool nvm_busy()
{
    return !(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK);
}

//call this to write data to a variable defined in nvm_data.h
bool write_data(void * nvm_location, uint32_t length, void * data)
{
    if (nvm_busy() || (uint32_t) nvm_location < NVM_START_ADDR || (uint32_t) nvm_location > NVM_END_ADDR
            || (uint32_t) nvm_location > NVM_START_ADDR + sizeof(nvm)) return FALSE;

    for (int i = 0; i < length; ++i)
    {
        while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK))
            ;
        ((uint8_t*) nvm_location)[i] = ((uint8_t*) data)[i];
    }

    return TRUE;
}

uint8_t read_byte(uint8_t * byte_addr)
{
    while (nvm_busy())
        ;
    return *byte_addr;
}

uint16_t read_word(uint16_t * word_addr)
{
    while (nvm_busy())
        ;
    return *word_addr;
}

uint32_t read_dword(uint32_t * dword_addr)
{
    while (nvm_busy())
        ;
    return *dword_addr;
}
