/*
 * CRC16.h
 *
 *  Created on: May 7, 2016
 *      Author: thebh_000
 */

#ifndef SOURCES_UTILITIES_CRC16_H_
#define SOURCES_UTILITIES_CRC16_H_

////Includes //////////////////////////////////////////////////////
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"

////Macros ////////////////////////////////////////////////////////
#define CRC16 0x8005

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Function Prototypes ///////////////////////////////////////////
uint16_t Calculate_Checksum_On_Bytes(const uint8_t *data, uint32_t size);

#endif /* SOURCES_UTILITIES_CRC16_H_ */
