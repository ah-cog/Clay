/*
 * I2C.h
 *
 *  Created on: Feb 13, 2016
 *      Author: thebh
 */

#ifndef SOURCES_I2C_I2C_H_
#define SOURCES_I2C_I2C_H_

// includes //////////////////
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"

// defines ///////////////////

// structs ///////////////////

// global vars ///////////////
extern bool i2c_tx_complete;
extern bool i2c_rx_complete;

// prototypes ////////////////

bool I2C_Send_Message(uint8_t * message, int32_t size, uint8_t address);
bool I2C_Receive_Message(uint8_t * tx_buf, int32_t tx_size, uint8_t * rx_buf, int32_t rx_size, uint8_t address);

#endif /* SOURCES_I2C_I2C_H_ */
