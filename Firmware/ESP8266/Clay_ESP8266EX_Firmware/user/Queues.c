/*
 * Queues.c
 *
 *  Created on: May 3, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"

#include "Queues.h"
#include "Message.h"

////Macros ////////////////////////////////////////////////////////
////Typedefs  /////////////////////////////////////////////////////
////Globals   /////////////////////////////////////////////////////
////Local vars/////////////////////////////////////////////////////
////Local Prototypes///////////////////////////////////////////////
////Global implementations ////////////////////////////////////////
////Local implementations /////////////////////////////////////////
Message * incoming_message_queue = NULL;
Message * outgoing_tcp_message_queue = NULL;
Message * outgoing_udp_message_queue = NULL;
Message * incoming_command_queue = NULL;

void Initialize_Message_Queues()
{
	Initialize_Message_Queue(&incoming_message_queue);
	Initialize_Message_Queue(&outgoing_tcp_message_queue);
	Initialize_Message_Queue(&outgoing_udp_message_queue);
	Initialize_Message_Queue(&incoming_command_queue);
}

void Free_Message_Queues()
{

}
