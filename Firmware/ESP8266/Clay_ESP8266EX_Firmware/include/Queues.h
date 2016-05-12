/*
 * Queues.h
 *
 *  Created on: May 3, 2016
 *      Author: thebh_000
 */

#ifndef INCLUDE_QUEUES_H_
#define INCLUDE_QUEUES_H_

////Includes //////////////////////////////////////////////////////
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"

#include "Multibyte_Ring_Buffer.h"
#include "Message.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
extern Multibyte_Ring_Buffer serial_rx_multibyte;

extern Message * incoming_message_queue;
extern uint32_t incoming_message_count;

extern Message * outgoing_tcp_message_queue;
extern uint32_t outgoing_tcp_message_count;

extern Message * outgoing_udp_message_queue;
extern uint32_t outgoing_udp_message_count;

extern Message * incoming_command_queue;
extern uint32_t incoming_command_message_count;

////Function Prototypes ///////////////////////////////////////////
extern void Initialize_Message_Queues();
extern void Free_Message_Queue();

#endif /* INCLUDE_QUEUES_H_ */
