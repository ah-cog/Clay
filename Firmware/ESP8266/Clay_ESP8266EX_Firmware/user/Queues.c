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
#include "Message_Queue.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
Multibyte_Ring_Buffer serial_rx_multibyte;
Message * incoming_message_queue = NULL;
uint32_t incoming_message_count;

Message * outgoing_tcp_message_queue = NULL;
uint32_t outgoing_tcp_message_count;

Message * outgoing_udp_message_queue = NULL;
uint32_t outgoing_udp_message_count;

Message * incoming_command_queue = NULL;
uint32_t incoming_command_message_count;

////Local vars/////////////////////////////////////////////////////

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////

////Local implementations /////////////////////////////////////////

void Initialize_Message_Queues()
{
	Initialize_Message_Queue(&incoming_message_queue);
	Initialize_Message_Queue(&outgoing_tcp_message_queue);
	Initialize_Message_Queue(&outgoing_udp_message_queue);
	Initialize_Message_Queue(&incoming_command_queue);

	incoming_message_count = 0;
	outgoing_tcp_message_count = 0;
	outgoing_udp_message_count = 0;
	incoming_command_message_count = 0;

}

void Free_Message_Queue(Message * * queue)
{
	Message * m;
	while ((m = Dequeue_Message(queue)) != NULL)
	{
		Delete_Message(m);
	}
}
