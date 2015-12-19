/*
 * nvm.h
 *
 *  Created on: Dec 15, 2015
 *      Author: thebh_000
 */

//this file contains definitions of variables and methods for use when storing files into NVM.
#ifndef NVM_H_
#define NVM_H_

#include "PE_Types.h"

#define NVM_START_ADDR      0x14000000
#define NVM_SIZE            0x00000800
#define NVM_END_ADDR        NVM_START_ADDR + NVM_SIZE - 1


extern bool nvm_init();

//call this before attempting to read data stored in the flash. reads can't happen while a write is in progress.
extern bool nvm_busy();

//these functions can be used to read data out of the nvm. to read pointers, 
//  wait for nvm_busy to return false before you begin reading your data
extern uint8_t read_byte(uint8_t * byte_addr);
extern uint16_t read_word(uint16_t * word_addr);
extern uint32_t read_dword(uint32_t * dword_addr);

extern bool write_byte(uint8_t * byte_addr, uint8_t value);
extern bool write_word(uint16_t * word_addr, uint16_t value);
extern bool write_dword(uint32_t * dword_addr, uint32_t value);

//use to copy data into and out of nvm locations.
extern bool copy_to_nvm(void * nvm_location, void * source, uint32_t length);
extern bool copy_from_nvm(void * nvm_location, void * destination, uint32_t length);

//call start function before performing actions that 
//   require access to multiple memory locations, but 
//   which don't require making a copy of the data.
extern bool start_multibyte_read();
extern bool end_multibyte_read();

//call this to write data to a variable defined in nvm_data.h
extern bool write_data(void * nvm_location, uint32_t length, void * data);

#endif /* NVM_H_ */
