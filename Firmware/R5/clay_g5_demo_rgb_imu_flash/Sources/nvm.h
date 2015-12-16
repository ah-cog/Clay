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

//call this to write data to a variable defined in nvm_data.h
extern bool write_data(void * nvm_location, uint32_t length, void * data);

#endif /* NVM_H_ */
