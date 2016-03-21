/*
 * LocalCommandListener.h
 *
 *  Created on: Mar 19, 2016
 *      Author: thebh_000
 */

#ifndef INCLUDE_COMMANDPARSER_H_
#define INCLUDE_COMMANDPARSER_H_

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Prototypes/////////////////////////////////////////////////////
extern bool Command_Parser_Init();
extern void Command_Parser_State_Step();

#endif /* INCLUDE_COMMANDPARSER_H_ */
