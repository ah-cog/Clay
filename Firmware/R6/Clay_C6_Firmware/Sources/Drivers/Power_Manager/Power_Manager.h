/*
 * Power_Manager.h
 *
 *  Created on: Mar 27, 2016
 *      Author: thebh_000
 */

#ifndef SOURCES_DRIVERS_POWER_MANAGER_POWER_MANAGER_H_
#define SOURCES_DRIVERS_POWER_MANAGER_POWER_MANAGER_H_

////Includes //////////////////////////////////////////////////////
#include "PE_Types.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Global prototypes ////////////////////////////////////////
extern bool Power_Manager_Enable();
extern void Power_Manager_Check_Startup();
extern void Power_Manager_Power_Off();
extern void Power_Manager_Check_For_Power_Off_Conditions();

#endif /* SOURCES_DRIVERS_POWER_MANAGER_POWER_MANAGER_H_ */
