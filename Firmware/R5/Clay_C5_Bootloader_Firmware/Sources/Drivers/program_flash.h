#ifndef PROGRAM_FLASH_H
#define PROGRAM_FLASH_H

#include "PE_Types.h"

#define APP_START_ADDR                0x0000C000U
#define APP_END_ADDR                  0x00040000U
#define FLASH_MEMORY_PAGE_SIZE        0x00000800U
#define APP_CHECKSUM_ADDRESS          0x0003FFFDU

extern volatile bool flash_operation_completed;

//erases the entire program flash
extern uint16_t erase_program_flash();

//erases the page of program flash containing the address
extern uint16_t erase_program_flash_page(uint32_t addr);

//writes data to the program flash
extern uint16_t write_program_block(uint32_t destination, uint8_t * data, uint32_t length);

//sets up the hardware checksum module.
extern void init_checksum(uint32_t tot, uint32_t totr, uint32_t fxor, uint32_t tcrc);

//computes the checksum of the application binary.
extern uint16_t compute_checksum();

#endif /* PROGRAM_FLASH_H */
