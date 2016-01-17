#ifndef PROGRAM_FLASH_H
#define PROGRAM_FLASH_H

#include "PE_Types.h"

#define APP_START_ADDR                0x0000C000U
#define APP_END_ADDR                  0x00040000U
#define FLASH_MEMORY_PAGE_SIZE        0x00000800U

// The checksum of the application firmware is stored in flash memory 
// at locations 0x3FFFE and 0x3FFFF.
#define APP_CHECKSUM_ADDRESS          0x0003FFFEU
#define APP_CHECKSUM_SIZE             2

extern volatile bool flash_operation_completed;

// Erases the entire program flash
extern uint16_t Erase_Program_Flash ();

// Erases the page of program flash containing the address
extern uint16_t Erase_Program_Flash_Page (uint32_t addr);

// Writes data to the program flash
extern uint16_t Write_Program_Block (uint32_t destination, uint8_t *data, uint32_t length);

// Writes the specified data to flash memory.
extern uint16_t Write_Program_Checksum (uint16_t checksum);

// Reads the checksum of the application firmware.
extern uint16_t Read_Program_Checksum ();

#endif /* PROGRAM_FLASH_H */
