/*
 * UDP_Receive.h
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 */

#ifndef INCLUDE_UDP_RECEIVER_H_
#define INCLUDE_UDP_RECEIVER_H_
////Includes //////////////////////////////////////////////////////
#include "esp_common.h"

////Macros ////////////////////////////////////////////////////////
#define WAIT_FOR_INCOMING_QUEUE()			while(IncomingQueueLock){taskYIELD();} IncomingQueueLock = TRUE;
#define LOCK_INCOMING_QUEUE()			if(!IncomingQueueLock){ IncomingQueueLock = TRUE; }
#define RELEASE_INCOMING_QUEUE()		IncomingQueueLock = FALSE

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
extern bool Exclusive_Rx_Access;
extern volatile bool IncomingQueueLock;

////Prototypes/////////////////////////////////////////////////////
extern bool UDP_Receiver_Init();
extern void UDP_Receiver_State_Step();

#endif /* INCLUDE_UDP_RECEIVER_H_ */
