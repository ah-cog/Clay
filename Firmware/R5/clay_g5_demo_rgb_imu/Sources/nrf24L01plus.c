/*
 * temp.h
 *
 *  Created on: Sep 14, 2015
 *      Author: thebh_000
 */

#ifndef __SPI0_H
#include "SPI0.h"
#endif

#ifndef NRF24L01PLUS_H_
#include "nrf24l01plus.h"
#endif

// includes //////////////////

// defines ///////////////////

// structs ///////////////////

// global vars ///////////////

// local vars ////////////////

// prototypes ////////////////

// implementations ///////////
void nrf24l01_init()
{
    uint8_t tx_data[] = { NRF24L01_CMD_R_REGISTER(NRF24L01_REG_SETUP_AW) };
    SPI0_SendBlock(SPI0_DeviceData, tx_data, 1);

    uint8_t rx_data[0];
    SPI0_ReceiveBlock(SPI0_DeviceData, rx_data, 1);

}

void nrf24l01_sendMessage(uint8_t * data)
{

}

