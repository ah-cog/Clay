/*
 * temp.h
 *
 *  Created on: Sep 14, 2015
 *      Author: thebh_000
 */

#ifndef NRF24L01PLUS_H_
#define NRF24L01PLUS_H_

// includes //////////////////
#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

// defines ///////////////////

//Register addresses
#define NRF24L01_REG_CONFIG                         0x00
#define NRF24L01_REG_EN_AA                          0x01
#define NRF24L01_REG_EN_RXADDR                      0x02
#define NRF24L01_REG_SETUP_AW                       0x03
#define NRF24L01_REG_SETUP_RTR                      0x04
#define NRF24L01_REG_RF_CHG                         0x05
#define NRF24L01_REG_RF_SETUP                       0x06
#define NRF24L01_REG_STATUS                         0x07
#define NRF24L01_REG_OBSERVE_TX                     0x08
#define NRF24L01_REG_RPD                            0x09
#define NRF24L01_REG_RX_ADDR_P0                     0x0A
#define NRF24L01_REG_RX_ADDR_P1                     0x0B
#define NRF24L01_REG_RX_ADDR_P2                     0x0C
#define NRF24L01_REG_RX_ADDR_P3                     0x0D
#define NRF24L01_REG_RX_ADDR_P4                     0x0E
#define NRF24L01_REG_RX_ADDR_P5                     0x0F
#define NRF24L01_REG_TX_ADDR                        0x10
#define NRF24L01_REG_RX_PW_P0                       0x11
#define NRF24L01_REG_RX_PW_P1                       0x12
#define NRF24L01_REG_RX_PW_P2                       0x13
#define NRF24L01_REG_RX_PW_P3                       0x14
#define NRF24L01_REG_RX_PW_P4                       0x15
#define NRF24L01_REG_RX_PW_P5                       0x16
#define NRF24L01_REG_FIFO_STATUS                    0x17
#define NRF24L01_DYNPD                              0x1C
#define NRF24L01_FEATURE                            0x1D

//Commands
#define NRF24L01_CMD_R_REGISTER(reg)                (0x00 + (reg & 0x1F))
#define NRF24L01_CMD_W_REGISTER(reg)                (0x01 + (reg & 0x1F))
#define NRF24L01_CMD_R_RX_PAYLOAD                   0x61
#define NRF24L01_CMD_W_TX_PAYLOAD                   0xA0
#define NRF24L01_CMD_FLUSH_TX                       0xE1
#define NRF24L01_CMD_FLUSH_RX                       0xE2
#define NRF24L01_CMD_REUSE_TX_PL                    0xE3
#define NRF24L01_CMD_R_RX_PL_WID                    0x60
#define NRF24L01_CMD_W_ACK_PAYLOAD(ack)             (0xA1 + (ack & 0x07))
#define NRF24L01_CMD_W_TX_PAYLOAD_NOACK             0xB0 
#define NRF24L01_CMD_NOP                            0xFF

// structs ///////////////////

// global vars ///////////////

// local vars ////////////////

// prototypes ////////////////
extern void nrf24l01_init();

extern void nrf24l01_sendMessage(uint8_t * data);

#endif
