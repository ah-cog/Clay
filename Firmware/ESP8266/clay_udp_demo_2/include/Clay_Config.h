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
#include "Clay_Config.h"

////Macros ////////////////////////////////////////////////////////
#define UDP_RX_TIMEOUT_MSEC               100
#define UDP_TX_TIMEOUT_MSEC               100

#define UDP_RX_PORT                       1200
#define UDP_TX_PORT                       1200

#define UDP_RX_BUFFER_SIZE_BYTES          1024
#define UDP_TX_BUFFER_SIZE_BYTES          1024

#define CLAY_RX_MESSAGE_QUEUE_SIZE        15        //Messages pending to the uC
#define CLAY_TX_MESSAGE_QUEUE_SIZE        15        //Messages pending for transmission

#define CLAY_MESSAGE_LENGTH_MAX_BYTES     512

//TODO: define SSID/PW here.
//TODO: timeouts on serial comms?

//TODO: check UDP ports
//TODO: my port and a broadcast port, tx and rx
//TODO: discovery port

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Prototypes/////////////////////////////////////////////////////

#endif /* INCLUDE_CLAY_CONFIG_H_ */
