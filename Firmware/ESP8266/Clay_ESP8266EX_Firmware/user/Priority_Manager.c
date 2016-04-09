/*
 * Priority_Manager.c
 *
 *  Created on: Apr 7, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"
#include "Priority_Manager.h"
#include "Message_Queue.h"
#include "queue.h"

////Macros ////////////////////////////////////////////////////////
#define DEFAULT_PRIORITY 		2

////Typedefs  /////////////////////////////////////////////////////
typedef struct
{
	int32 last_ran_time_us;
	xTaskHandle task_handle;
	Check_Task_Needs_Promotion task_needs_promotion;
	portBASE_TYPE current_priority;
	portBASE_TYPE default_priority;
} TASK_INFO;

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static TASK_INFO tasks[TASK_TYPE_MAX] =
{
//
		{ 0, NULL, NULL, DEFAULT_PRIORITY, DEFAULT_PRIORITY }, //TASK_TYPE_UDP_TX,
		{ 0, NULL, NULL, DEFAULT_PRIORITY, DEFAULT_PRIORITY }, //TASK_TYPE_UDP_RX,
		{ 0, NULL, NULL, DEFAULT_PRIORITY, DEFAULT_PRIORITY }, //TASK_TYPE_TCP_RX, tcp combined - tcp tx == tcp rx
		{ 0, NULL, NULL, DEFAULT_PRIORITY, DEFAULT_PRIORITY }, //TASK_TYPE_SERIAL_TX,
		{ 0, NULL, NULL, DEFAULT_PRIORITY, DEFAULT_PRIORITY }, //TASK_TYPE_SERIAL_RX,
		{ 0, NULL, NULL, DEFAULT_PRIORITY, DEFAULT_PRIORITY } //TASK_TYPE_COMMAND_PARSER,
};

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
void Register_Task(TASK_TYPE calling_task, xTaskHandle task_handle,
		Check_Task_Needs_Promotion promotion_callback)
{
	tasks[calling_task].task_handle = task_handle;
	tasks[calling_task].last_ran_time_us = 0;
	tasks[calling_task].task_needs_promotion = promotion_callback;
}

static int loops = 0;
static int consecutive_serial_promoted_count = 0;

void Priority_Check(TASK_TYPE calling_task)
{
	TASK_INFO * task = (tasks + ((int) calling_task));

	task->last_ran_time_us = system_get_time();

	if (task->task_needs_promotion != NULL && task->task_needs_promotion())
	{
		if (calling_task
				== TASK_TYPE_SERIAL_TX&& incoming_message_queue.count == MAXIMUM_MESSAGE_COUNT)
		{
			if (++consecutive_serial_promoted_count > 10)
			{
				consecutive_serial_promoted_count = 0;
				DEBUG_Print("reset tcp");
				taskENTER_CRITICAL();
				Stop_Task(TASK_TYPE_TCP_RX);
				TCP_Combined_Deinit();
				TCP_Combined_Init();
				taskEXIT_CRITICAL();
			}

		}

//		if (++loops > LOOPS_BEFORE_PRINT)
		{
			loops = 0;
			taskENTER_CRITICAL();
			printf("%d promoted\r\n", (int) calling_task);
			taskEXIT_CRITICAL();
		}

		if (task->current_priority <= task->default_priority)
		{
			++(task->current_priority);

			//context switch will happen here if task priority is higher than the current task..
			vTaskPrioritySet(task->task_handle, task->current_priority);
		}

	}
	else if (task->current_priority > task->default_priority)
	{
		--(task->current_priority);

		vTaskPrioritySet(task->task_handle, task->current_priority);
	}

	task->current_priority = uxTaskPriorityGet(task->task_handle);
}

int32 Get_Task_Priority(TASK_TYPE requested_task)
{
	return tasks[requested_task].current_priority;
}

void Stop_Task(TASK_TYPE kill_task)
{
	TASK_INFO * task = (tasks + ((int) kill_task));
	vTaskDelete(task->task_handle);
	task->task_handle = NULL;
	task->current_priority = task->default_priority;
	task->task_needs_promotion = NULL;
	task->last_ran_time_us = 0;
}

////Local implementations /////////////////////////////////////////

