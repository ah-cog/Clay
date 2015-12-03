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
#define MESH_RADIO_ADDRESS_WIDTH     0x02 //SETUP_AW register - 4 byte address width.
//
#define MESH_RADIO_ADDRESS_BASE      0xA5A50000
#define MESH_RADIO_ADDRESS_GLOBAL    (MESH_RADIO_ADDRESS_BASE + 0x0000u)

//
#define MESH_RADIO_ADDRESS_0         (MESH_RADIO_ADDRESS_BASE + 0xB000u)
#define MESH_RADIO_ADDRESS_1         (MESH_RADIO_ADDRESS_BASE + 0xB001u)
#define MESH_RADIO_ADDRESS_2         (MESH_RADIO_ADDRESS_BASE + 0xB002u)

//
#define MESH_PACKET_SIZE             32

//Pass interrupts through to IRQ pin, enable 1 byte CRC, power up into PRX mode.
#define MESH_RADIO_RECEIVE_CONFIG    (RF1_CONFIG_EN_CRC | RF1_CONFIG_PWR_UP | RF1_CONFIG_PRIM_RX)
#define MESH_RADIO_TRANSMIT_CONFIG   (RF1_CONFIG_EN_CRC | RF1_CONFIG_PWR_UP)

#define MESH_CHANNEL_NUMBER          60

#define MESH_MODULE_MAX_COUNT        10
#define TX_MESSAGE_BUFFER_LENGTH     10
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
    uint32_t moduleAddress;        //the address of the module
    uint32_t ping;                  //round trip time for a message

    //TODO: is this dumb? How should messages be sent? Non-directly communicable devices found and removed?
    bool direct;                    //true if the module should be addressed directly
} clay_mesh_module;

typedef enum
{
    OK,
    TIMED_OUT,
    EXCEEDED_MAX_RETRY,
    ERROR
} message_status;

typedef void (*messageCompleteCallback)(message_status);

typedef struct
{
    uint8_t * data;
    uint32_t length;
    uint32_t destination;
    uint32_t lastPacket;
    uint32_t messageId;
    bool transmissionComplete;
    uint8_t retryCount;
    messageCompleteCallback onMessageComplete;
} mesh_message;

// global vars ///////////////
extern clay_mesh_module clayModules[MESH_MODULE_MAX_COUNT];

// local vars ////////////////

// prototypes ////////////////

// implementations ///////////

extern void meshInit();

extern void meshStateUpdate();

extern bool meshSend(uint8_t * tx_buf, uint32_t length, uint32_t destinationAddress, messageCompleteCallback messageComplete);

extern bool meshBroadcast(uint8_t * tx_buf, uint32_t length, messageCompleteCallback messageComplete);

extern int meshReceiveString(uint8_t * rx_buf, uint32_t length);

extern void meshInterruptHandler();

#endif /* APP_NRF24L01_H_ */
