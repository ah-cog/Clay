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
#define DEFAULT_PRIORITY 		           2
#define SYSTEM_MONITOR_PRIORITY            DEFAULT_PRIORITY + 2
#define FREE_HEAP_MINIMUM_LEVEL 		   4000

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

static xTaskHandle idle_handle;
static xTaskHandle priority_check_handle;

static uint32 free_heap_size;
static int loops = 0;

static TASK_TYPE current_task;

static portTickType previous_run_time;
static portTickType priority_monitor_interval = (100 / portTICK_RATE_MS);

static TASK_INFO * current_task_ptr;

////Local Prototypes///////////////////////////////////////////////
static void Monitor_Priority();
static void Monitor_Memory();
static void Monitor_TCP_Timeout();

////Global implementations ////////////////////////////////////////
void ICACHE_RODATA_ATTR Start_Priority_Monitor()
{
	idle_handle = xTaskGetIdleTaskHandle();
	current_task = TASK_TYPE_UDP_TX;
	xTaskCreate(Priority_Check_Task, "priority monitor", 128, NULL,
			SYSTEM_MONITOR_PRIORITY, &priority_check_handle);
}

void ICACHE_RODATA_ATTR Register_Task(TASK_TYPE calling_task,
		xTaskHandle task_handle, Check_Task_Needs_Promotion promotion_callback)
{
	tasks[calling_task].task_handle = task_handle;
	tasks[calling_task].last_ran_time_us = 0;
	tasks[calling_task].task_needs_promotion = promotion_callback;
}

void ICACHE_RODATA_ATTR Priority_Check_Task()
{
	previous_run_time = xTaskGetTickCount();

	for (;;)
	{
		//TODO: figure out how long an iteration of this task runs.

		Monitor_Priority();
		Monitor_Memory();
		Monitor_TCP_Timeout();

		//run every priority_monitor_interval ticks.
		vTaskDelayUntil(&previous_run_time, priority_monitor_interval);
	}
}

int32 ICACHE_RODATA_ATTR Get_Task_Priority(TASK_TYPE requested_task)
{
	return tasks[requested_task].current_priority;
}

void ICACHE_RODATA_ATTR Stop_Task(TASK_TYPE kill_task)
{
	TASK_INFO * task = (tasks + ((int) kill_task));
	vTaskDelete(task->task_handle);
	task->task_handle = NULL;
	task->current_priority = task->default_priority;
	task->task_needs_promotion = NULL;
	task->last_ran_time_us = 0;
}

////Local implementations /////////////////////////////////////////
static void ICACHE_RODATA_ATTR Monitor_Priority()
{
	for (current_task = 0; current_task < TASK_TYPE_MAX; ++current_task)
	{
		current_task_ptr = (tasks + ((int) current_task));
		current_task_ptr->last_ran_time_us = system_get_time();

		if (current_task_ptr->task_needs_promotion != NULL
				&& current_task_ptr->task_needs_promotion())
		{
//			if (++loops > LOOPS_BEFORE_PRINT)
//			{
//				loops = 0;
//				taskENTER_CRITICAL();
//				printf("%d promoted\r\n", (int) current_task);
//				taskEXIT_CRITICAL();
//			}

			if (current_task_ptr->current_priority
					<= current_task_ptr->default_priority)
			{
				++(current_task_ptr->current_priority);

				//context switch will happen here if task priority is higher than the current task..
				vTaskPrioritySet(current_task_ptr->task_handle,
						current_task_ptr->current_priority);
			}

		}
		else if (current_task_ptr->current_priority
				> current_task_ptr->default_priority)
		{
			--(current_task_ptr->current_priority);

			vTaskPrioritySet(current_task_ptr->task_handle,
					current_task_ptr->current_priority);
		}

		current_task_ptr->current_priority = uxTaskPriorityGet(
				current_task_ptr->task_handle);
	}
}

static void ICACHE_RODATA_ATTR Monitor_Memory()
{
	free_heap_size = system_get_free_heap_size();

//	taskENTER_CRITICAL();
//	printf("heap free: %d\r\n", free_heap_size);
//	taskEXIT_CRITICAL();

	if (free_heap_size < FREE_HEAP_MINIMUM_LEVEL)
	{
//		DEBUG_Print("low on memory!");

		//raise priority so we make sure tasks get cleaned up.
		vTaskPrioritySet(idle_handle, DEFAULT_PRIORITY);
		vTaskDelay(25 / portTICK_RATE_MS);
		vTaskPrioritySet(idle_handle, 0);
	}
}

static void ICACHE_RODATA_ATTR Monitor_TCP_Timeout()
{
	//TODO: check to see if tcp tx is hanging.
}
