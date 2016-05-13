/*
 * Priority_Manager.c
 *
 *  Created on: Apr 7, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"
#include "Message_Queue.h"
#include "queue.h"
#include "queues.h"
#include "System_Monitor.h"
#include "UART.h"
#include "Clay_Config.h"

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
static xTaskHandle system_monitor_handle;

static uint32 free_heap_size;

static TASK_TYPE current_task;

static portTickType previous_run_time;
static portTickType priority_monitor_interval = (100 / portTICK_RATE_MS);

static TASK_INFO * current_task_ptr;

static bool tasks_started;

////Local Prototypes///////////////////////////////////////////////
static void Monitor_Priority();
static void Monitor_Memory();

////Global implementations ////////////////////////////////////////
void ICACHE_RODATA_ATTR Start_System_Monitor()
{
	tasks_started = false;
	idle_handle = xTaskGetIdleTaskHandle();
	current_task = TASK_TYPE_UDP_TX;

//	for (current_task = 0; current_task < TASK_TYPE_MAX; ++current_task)
//	{
//		vTaskDelay(1000 / portTICK_RATE_MS);
//
//		taskENTER_CRITICAL();
//		printf("task:%d cp:%d dp:%d lr:%d th:%d np:%d\r\n", current_task,
//				tasks[current_task].current_priority,
//				tasks[current_task].default_priority,
//				tasks[current_task].last_ran_time_us,
//				tasks[current_task].task_handle,
//				tasks[current_task].task_needs_promotion);
//		taskEXIT_CRITICAL();
//	}

	xTaskCreate(System_Monitor_Task, "system monitor", 256, NULL,
			SYSTEM_MONITOR_PRIORITY, &system_monitor_handle);

}

void ICACHE_RODATA_ATTR System_Register_Task(TASK_TYPE calling_task,
		xTaskHandle task_handle, Check_Task_Needs_Promotion promotion_callback)
{
	tasks[calling_task].task_handle = task_handle;
	tasks[calling_task].last_ran_time_us = 0;
	tasks[calling_task].task_needs_promotion = promotion_callback;
}

void ICACHE_RODATA_ATTR System_Monitor_Task()
{
	for (;;)
	{
		if (tasks_started)
		{
			Monitor_Priority();
		}
		else
		{
			System_Start_Tasks();
		}

		Monitor_Memory();

//		if (incoming_command_message_count || incoming_message_count
//				|| outgoing_tcp_message_count || outgoing_udp_message_count)
//		{
//			taskENTER_CRITICAL();
//			printf("ic:%d im:%d ot:%d ou:%d\r\n\r\n",
//					incoming_command_message_count, incoming_message_count,
//					outgoing_tcp_message_count, outgoing_udp_message_count);
//			taskEXIT_CRITICAL();
//		}

		//run every priority_monitor_interval ticks.
		previous_run_time = xTaskGetTickCount();
		vTaskDelayUntil(&previous_run_time, priority_monitor_interval);
	}
}

int32 ICACHE_RODATA_ATTR System_Get_Task_Priority(TASK_TYPE requested_task)
{
	return tasks[requested_task].current_priority;
}

void ICACHE_RODATA_ATTR System_Stop_Task(TASK_TYPE kill_task)
{
	TASK_INFO * task = (tasks + ((int) kill_task));
	if (task->task_handle != NULL)
	{
		vTaskDelete(task->task_handle);
		task->task_handle = NULL;
		task->current_priority = task->default_priority;
		task->task_needs_promotion = NULL;
		task->last_ran_time_us = 0;
	}
}

void System_Start_Tasks()
{
//	DEBUG_Print("start tasks");
	tasks_started = (wifi_station_get_connect_status() == STATION_GOT_IP);

#if ENABLE_UDP_SENDER
	if (tasks_started && tasks[TASK_TYPE_UDP_TX].task_handle == NULL)
	{
		UDP_Transmitter_Init();
	}
#endif
#if ENABLE_UDP_RECEIVER
	if (tasks_started && tasks[TASK_TYPE_UDP_RX].task_handle == NULL)
	{
		UDP_Receiver_Init();
	}
#endif

#if ENABLE_TCP_SENDER
	TCP_Transmitter_Init();
#endif

#if ENABLE_TCP_RECEIVER
	TCP_Receiver_Init();
#endif

#if ENABLE_TCP_COMBINED_TX || ENABLE_TCP_COMBINED_RX
	if (tasks_started && tasks[TASK_TYPE_TCP_RX].task_handle == NULL)
	{
		TCP_Combined_Init();
	}
#endif
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
			if (current_task_ptr->current_priority
					<= current_task_ptr->default_priority)
			{
//				taskENTER_CRITICAL();
//				printf(
//						"\r\n\r\n%d promoted old:%d default:%d sysmon:%d\r\n\r\n",
//						(int) current_task, current_task_ptr->current_priority,
//						current_task_ptr->default_priority,
//						SYSTEM_MONITOR_PRIORITY);
//				UART_WaitTxFifoEmpty(UART0);
//				taskEXIT_CRITICAL();

				++(current_task_ptr->current_priority);

				//context switch will happen here if task priority is higher than the current task..
				vTaskPrioritySet(current_task_ptr->task_handle,
						current_task_ptr->current_priority);
			}

		}
		else if (current_task_ptr->current_priority
				> current_task_ptr->default_priority)
		{
//			taskENTER_CRITICAL();
//			printf("\r\n%d demoted old:%d default:%d sysmon:%d\r\n\r\n",
//					(int) current_task, current_task_ptr->current_priority,
//					current_task_ptr->default_priority,
//					SYSTEM_MONITOR_PRIORITY);
//			UART_WaitTxFifoEmpty(UART0);
//			taskEXIT_CRITICAL();

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
//	printf("\r\ntick:%d heap free: %d\r\n", xTaskGetTickCount(),
//			free_heap_size);
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
