#ifndef PROGRAM_FLASH_H
#define PROGRAM_FLASH_H

#include "PE_Types.h"

#define APP_START_ADDR                0x00008000U
#define APP_END_ADDR                  0x000FFEFFU  //leave 256 bytes for information region.
#define FLASH_MEMORY_PAGE_SIZE        0x00001000U

///information about the application firmware is stored at the end of application flash
// The size of the firmware is stored in flash memory as an integer (4 bytes) 
// at locations 0x3FFFA through 0x3FFFD.
#define APP_SIZE_ADDRESS          0x000FFFE8U
#define APP_SIZE_SIZE             4

// The size of the version is stored in flash memory as an integer (4 bytes)
// at locations 0x3FFF6 through 0x3FFF9.
#define APP_VERSION_ADDRESS       0x000FFFF0U
#define APP_VERSION_SIZE          4

// The checksum of the application firmware is stored in flash memory
// at locations 0x3FFFE and 0x3FFFF.
#define APP_CHECKSUM_ADDRESS          0x000FFFF8U
#define APP_CHECKSUM_SIZE             4

extern volatile bool flash_operation_completed;

// Erases the entire program flash
extern uint16_t Erase_Program_Flash();

// Erases the page of program flash containing the address
extern uint16_t Erase_Program_Flash_Page(uint32_t addr);

// Writes data to the program flash
extern uint16_t Write_Program_Block(uint32_t destination, const uint8_t *data, uint32_t length);

// Writes the specified data to flash memory.
extern uint16_t Write_Program_Checksum(uint32_t checksum);

// Reads the checksum of the application firmware.
extern uint32_t Read_Program_Checksum();

// Writes the specified data to flash memory.
extern uint16_t Write_Program_Size(uint32_t checksum);

// Reads the checksum of the application firmware.
extern uint32_t Read_Program_Size();

extern uint16_t Write_Program_Version(uint32_t version);

// Reads the version of the application firmware.
extern uint32_t Read_Program_Version();

#endif /* PROGRAM_FLASH_H */
