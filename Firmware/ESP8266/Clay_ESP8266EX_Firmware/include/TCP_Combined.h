/*
 * TCP_Combined.h
 *
 *  Created on: Mar 31, 2016
 *      Author: thebh_000
 */

#ifndef INCLUDE_TCP_COMBINED_H_
#define INCLUDE_TCP_COMBINED_H_

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"
////Typedefs  /////////////////////////////////////////////////////
extern bool tcp_task_running;

////Globals   /////////////////////////////////////////////////////

////Global Prototypes ////////////////////////////////////////
extern bool TCP_Combined_Init();
extern void TCP_Combined_Deinit();
extern void TCP_Combined_Task();

#endif /* INCLUDE_TCP_COMBINED_H_ */
