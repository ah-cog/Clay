/*
 * Mesh_Simple.h
 *
 *  Created on: Apr 20, 2016
 *      Author: thebh_000
 */

#ifndef SOURCES_DRIVERS_MESH_MESH_SIMPLE_H_
#define SOURCES_DRIVERS_MESH_MESH_SIMPLE_H_

////Includes //////////////////////////////////////////////////////
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////
typedef void (*Message_Complete_Callback)(int message_status);

////Globals   /////////////////////////////////////////////////////

////Function Prototypes ///////////////////////////////////////////
extern bool Mesh_Enable();

extern void Mesh_Periodic();

extern bool Mesh_Send(uint8_t * tx_buf,
                      uint32_t length,
                      uint32_t destination_address,
                      Message_Complete_Callback message_complete);

extern bool Mesh_Broadcast(uint8_t * tx_buf, uint32_t length, Message_Complete_Callback message_complete);

extern int Mesh_Receive(uint8_t * rx_buf, uint32_t length);

extern void Mesh_Interrupt_Handler();

#endif /* SOURCES_DRIVERS_MESH_MESH_SIMPLE_H_ */
