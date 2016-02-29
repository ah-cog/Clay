/*
 * UDP_Config.h
 *
 *  Created on: Feb 23, 2016
 *      Author: thebh
 */

#ifndef INCLUDE_CLAY_CONFIG_H_
#define INCLUDE_CLAY_CONFIG_H_

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"

#include "lwip/sockets.h"

#include "Clay_Config.h"

////Macros ////////////////////////////////////////////////////////
///Buffer size information below:
//           struct sockaddr_in {
//             u8_t            sin_len;
//             sa_family_t     sin_family;
//             in_port_t       sin_port;
//             struct in_addr  sin_addr;
//           #define SIN_ZERO_LEN 8
//             char            sin_zero[SIN_ZERO_LEN];
//           };

//sa_family is u8_t typedefs.
//

//TODO: double-check this size...
//sizes as they are printed
#define DELIMITER_SIZE                    1         //each char is 1 byte, there are 13 in the serialized string.
#define DELIMITER_COUNT                   11
#define NEWLINE_SIZE                      1
#define U8_T_SIZE_BYTES                   2
#define IN_PORT_T_SIZE_BYTES              4
#define IN_ADDR_SIZE_BYTES                8          //4                    //4
#define SOCKADDR_IN_SIZE_BYTES            ((2 * U8_T_SIZE_BYTES) + IN_PORT_T_SIZE_BYTES \
                                             + SIN_ZERO_LEN * 2 + IN_ADDR_SIZE_BYTES + DELIMITER_SIZE * DELIMITER_COUNT + NEWLINE_SIZE)               //total size is 16
//                                                 //8                //8                           //11

#define UINT32_SIZE_BYTES                 4

#define CLAY_MESSAGE_LENGTH_MAX_BYTES     512                                   //4                     //16
#define CLAY_MESSAGE_STRUCT_SIZE_BYTES    (CLAY_MESSAGE_LENGTH_MAX_BYTES + UINT32_SIZE_BYTES + SOCKADDR_IN_SIZE_BYTES) //total size 532

////
#define UDP_RX_TIMEOUT_MSEC               100
#define UDP_TX_TIMEOUT_MSEC               100

////
#define UDP_RX_PORT                       1200
#define UDP_TX_PORT                       1201

////
#define UDP_RX_MESSAGE_CAPACITY           2
#define UDP_TX_MESSAGE_CAPACITY           2
#define UDP_RX_BUFFER_SIZE_BYTES          (CLAY_MESSAGE_STRUCT_SIZE_BYTES * UDP_RX_MESSAGE_CAPACITY)
#define UDP_TX_BUFFER_SIZE_BYTES          (CLAY_MESSAGE_STRUCT_SIZE_BYTES * UDP_TX_MESSAGE_CAPACITY)
#define SERIAL_TX_MESSAGE_CAPACITY        2
#define SERIAL_RX_MESSAGE_CAPACITY        2
#define SERIAL_TX_BUFFER_SIZE_BYTES       (CLAY_MESSAGE_STRUCT_SIZE_BYTES * SERIAL_TX_MESSAGE_CAPACITY)
#define SERIAL_RX_BUFFER_SIZE_BYTES       (CLAY_MESSAGE_STRUCT_SIZE_BYTES * SERIAL_RX_MESSAGE_CAPACITY)

///
#define CLAY_RX_MESSAGE_QUEUE_SIZE        15        //Messages pending to the uC
#define CLAY_TX_MESSAGE_QUEUE_SIZE        15        //Messages pending for transmission

#define CLAY_SERIAL_MESSAGE_NEWLINE_COUNT 2

#define CLAY_INTERRUPT_OUT_PIN		      16		//send interrupt to uC
#define CLAY_INTERRUPT_IN_PIN		      2			//receive interrupt from uC

//TODO: define SSID/PW here.
//TODO: timeouts on serial comms?

//TODO: check UDP ports
//TODO: my port and a broadcast port, tx and rx
//TODO: discovery port

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Prototypes/////////////////////////////////////////////////////

#endif /* INCLUDE_CLAY_CONFIG_H_ */
