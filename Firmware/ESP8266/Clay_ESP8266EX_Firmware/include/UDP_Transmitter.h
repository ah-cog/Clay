/*
 * UDP_Transmitter.h
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 */

#ifndef INCLUDE_UDP_TRANSMITTER_H_
#define INCLUDE_UDP_TRANSMITTER_H_
////Includes //////////////////////////////////////////////////////
#include "esp_common.h"

////Defines ///////////////////////////////////////////////////////
#define WAIT_FOR_OUTGOING_QUEUE()			while(OutgoingQueueLock){taskYIELD();} OutgoingQueueLock = TRUE;
#define LOCK_OUTGOING_QUEUE()			if(!OutgoingQueueLock){ OutgoingQueueLock = TRUE; }
#define RELEASE_OUTGOING_QUEUE()		OutgoingQueueLock = FALSE

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
extern volatile bool OutgoingQueueLock;

////Prototypes/////////////////////////////////////////////////////
extern bool UDP_Transmitter_Init();
extern void UDP_Transmitter_State_Step();

#endif /* INCLUDE_UDP_TRANSMITTER_H_ */
