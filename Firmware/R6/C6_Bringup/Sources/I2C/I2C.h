/*
 * I2C.h
 *
 *  Created on: Feb 13, 2016
 *      Author: thebh
 */

#ifndef SOURCES_I2C_I2C_H_
#define SOURCES_I2C_I2C_H_

// includes //////////////////
#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

// defines ///////////////////

// structs ///////////////////

// global vars ///////////////
extern bool i2c_tx_complete;
extern bool i2c_rx_complete;

// prototypes ////////////////

LDD_TError I2C_Receive_Message(uint8_t * tx_buf, int32 tx_size, uint8_t * rx_buf, int32 rx_size, uint8_t address);
LDD_TError I2C_Receive_Message(uint8_t * tx_buf, int32 tx_size, uint8_t * rx_buf, int32 rx_size, uint8_t address);

#endif /* SOURCES_I2C_I2C_H_ */
