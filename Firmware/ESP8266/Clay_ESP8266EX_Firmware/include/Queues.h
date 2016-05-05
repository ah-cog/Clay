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
extern Message * outgoing_tcp_message_queue;
extern Message * outgoing_udp_message_queue;
extern Message * incoming_command_queue;

////Function Prototypes ///////////////////////////////////////////
extern void Initialize_Message_Queues();
extern void Free_Message_Queues();

#endif /* INCLUDE_QUEUES_H_ */
