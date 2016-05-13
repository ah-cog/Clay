/*
 * Priority_Manager.h
 *
 *  Created on: Apr 7, 2016
 *      Author: thebh_000
 */

#ifndef INCLUDE_SYSTEM_MONITOR_H_
#define INCLUDE_SYSTEM_MONITOR_H_

////Includes //////////////////////////////////////////////////////

////Macros ////////////////////////////////////////////////////////
#define LOOPS_BEFORE_PRINT		  		   10
#define DEFAULT_PRIORITY 		           2
#define SYSTEM_MONITOR_PRIORITY            DEFAULT_PRIORITY + 2
#define FREE_HEAP_MINIMUM_LEVEL 		   4000

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
extern void System_Register_Task(TASK_TYPE calling_task,
		xTaskHandle task_handle, Check_Task_Needs_Promotion promotion_callback);
extern void System_Monitor_Task();
extern int32 System_Get_Task_Priority(TASK_TYPE requested_task);
extern void System_Stop_Task(TASK_TYPE kill_task);

extern void System_Start_Tasks();

#endif /* INCLUDE_SYSTEM_MONITOR_H_ */
