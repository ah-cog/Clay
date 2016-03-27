/*
 * Serial_Transmitter.h
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 */

#ifndef INCLUDE_SERIAL_TRANSMITTER_H_
#define INCLUDE_SERIAL_TRANSMITTER_H_
////Includes //////////////////////////////////////////////////////
#include "esp_common.h"

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Prototypes/////////////////////////////////////////////////////
extern bool Serial_Transmitter_Init();
extern void Serial_Transmitter_State_Step();
extern void Send_Message_To_Master(char * message, Message_Type type);

#endif /* INCLUDE_SERIAL_TRANSMITTER_H_ */
