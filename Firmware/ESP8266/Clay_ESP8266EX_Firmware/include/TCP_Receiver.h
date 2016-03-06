/*
 * TCP_Receiver.h
 *
 *  Created on: Mar 2, 2016
 *      Author: thebh_000
 */

#ifndef INCLUDE_TCP_RECEIVER_H_
#define INCLUDE_TCP_RECEIVER_H_

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
extern bool Exclusive_Rx_Access;
extern volatile bool IncomingQueueLock;

////Prototypes/////////////////////////////////////////////////////
extern bool TCP_Receiver_Init();
extern void TCP_Receiver_State_Step();

#endif /* INCLUDE_TCP_RECEIVER_H_ */
