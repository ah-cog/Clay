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

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Prototypes/////////////////////////////////////////////////////
extern bool UDP_Transmitter_Init();
extern void UDP_Transmitter_State_Step();

#endif /* INCLUDE_UDP_TRANSMITTER_H_ */
