/*
 * app_nrf24l01.h
 *
 *  Created on: Oct 1, 2015
 *      Author: Ben
 */

#ifndef APP_NRF24L01_H_
#define APP_NRF24L01_H_

// includes //////////////////
#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

#include "RF1.h"

// defines ///////////////////
//radio config
#define MESH_RADIO_ADDRESS_WIDTH        0x02 //SETUP_AW register - 4 byte address width.
//set rx address 0 to this value. The device should always receive this data. Write to this address to broadcast
#define MESH_RADIO_ADDRESS_GLOBAL    0xAFAFAFAFu
#define MESH_RADIO_ADDRESS_UNIQUE    0x01010100u

//Pass interrupts through to IRQ pin, enable 1 byte CRC, power up into PRX mode.
#define MESH_RADIO_RECEIVE_CONFIG    (RF1_CONFIG_EN_CRC | RF1_CONFIG_PWR_UP | RF1_CONFIG_PRIM_RX)
#define MESH_RADIO_TRANSMIT_CONFIG    (RF1_CONFIG_EN_CRC | RF1_CONFIG_PWR_UP)

#define MESH_CHANNEL_NUMBER         60
// structs ///////////////////
typedef enum
{
    pipe0,
    pipe1,
    pipe2,
    pipe3,
    pipe4,
    pipe5,
    invalid
} mesh_pipe;

//contains information about other NRF devices
typedef struct
{
    uint32_t module_address;
    uint32_t ping;
} clay_mesh_module;

// global vars ///////////////

// local vars ////////////////

// prototypes ////////////////

// implementations ///////////

extern void mesh_init();

extern void mesh_state_update();

extern void mesh_send_string(uint8_t * tx_buf, uint32_t length, uint32_t destinationAddress);

extern void mesh_broadcast_string(uint8_t * tx_buf, uint32_t length);

extern int mesh_receive_string(uint8_t * rx_buf, uint32_t length);

extern void mesh_interrupt_handler();

#endif /* APP_NRF24L01_H_ */
