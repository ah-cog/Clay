/*
 * Priority_Manager.h
 *
 *  Created on: Apr 7, 2016
 *      Author: thebh_000
 */

#ifndef INCLUDE_PRIORITY_MANAGER_H_
#define INCLUDE_PRIORITY_MANAGER_H_

////Includes //////////////////////////////////////////////////////

////Macros ////////////////////////////////////////////////////////
#define LOOPS_BEFORE_PRINT		  10

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	TASK_TYPE_UDP_TX,
	TASK_TYPE_UDP_RX,
	TASK_TYPE_TCP_TX,
	TASK_TYPE_TCP_RX = TASK_TYPE_TCP_TX,
	TASK_TYPE_SERIAL_TX,
	TASK_TYPE_SERIAL_RX,
	TASK_TYPE_COMMAND_PARSER,
	TASK_TYPE_MAX
} TASK_TYPE;

//callback.
typedef bool (*Check_Task_Needs_Promotion)();

////Globals   /////////////////////////////////////////////////////
extern uint32 default_priority;

////Global Prototypes /////////////////////////////////////////////
void Register_Task(TASK_TYPE calling_task, xTaskHandle task_handle,
		Check_Task_Needs_Promotion promotion_callback);
void Priority_Check_Task();
int32 Get_Task_Priority(TASK_TYPE requested_task);
void Stop_Task(TASK_TYPE kill_task);

#endif /* INCLUDE_PRIORITY_MANAGER_H_ */
