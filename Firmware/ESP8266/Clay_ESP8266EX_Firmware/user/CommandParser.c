/*
 * LocalCommandListener.c
 *
 *  Created on: Mar 19, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "../include/CommandParser.h"

#include "esp_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "uart.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "Clay_Config.h"

#include "Message_Queue.h"
#include "Message.h"
#include "ESP_Utilities.h"

#include "UDP_Transmitter.h"
#include "UDP_Receiver.h"
#include "TCP_Combined.h"

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable, Idle, ParseCommand, COMMAND_PARSER_STATE_MAX
} Command_Parser_States;

typedef enum
{
	CLAY_COMMAND_SET_AP,
	CLAY_COMMAND_GET_AP,
	CLAY_COMMAND_SCAN_AP,
	CLAY_COMMAND_GET_IP,
	CLAY_COMMAND_GET_GATEWAY,
	CLAY_COMMAND_GET_SUBNET,
	CLAY_COMMAND_STOP_TASK,
	CLAY_COMMAND_START_TASK,
	CLAY_COMMAND_MAX
} CLAY_ESP_COMMANDS;

typedef enum
{
	TASK_TYPE_UDP_TX = 1,
	TASK_TYPE_UDP_RX = 2,
	TASK_TYPE_TCP_TX = 4,
	TASK_TYPE_TCP_RX = 8,
	TASK_TYPE_MAX
} TASK_TYPE;

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////

// TODO: Implement these following example of Process_Event and Perform_Action in k64 code.
char* command_tokens[CLAY_COMMAND_MAX] =
{ "setap", "getap", "scanap", "get_ip", "get_gateway", "get_subnet",
		"stop_task", "start_task" };

char * command_args;
char command_delimiter = ' ';
char args_delimiter = ',';

int i;
static Message * m;
static Command_Parser_States state;
static xTaskHandle command_parser_task;

////Local Prototypes///////////////////////////////////////////////
static CLAY_ESP_COMMANDS Command_String_Parse(char * CommandStr, char ** ArgStr);
static bool Set_AP_Command(char * args);
static bool Get_AP_Command(char * args);
static bool Scan_AP_Command(char * args);
static bool Get_Subnet_Command(char * args);
static bool Get_Gateway_Command(char * args);
static bool Get_IP_Command(char * args);
static void Stop_Task(TASK_TYPE tt);

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR Command_Parser_Init()
{
	bool rval = false;

	taskENTER_CRITICAL();
	Initialize_Message_Queue(&incoming_command_queue);
	taskEXIT_CRITICAL();

	state = Idle;

	xTaskCreate(Command_Parser_State_Step, "cmdParser", 512, NULL, 2,
			command_parser_task);

	return rval;
}

void ICACHE_RODATA_ATTR Command_Parser_State_Step()
{
	for (;;)
	{
		switch (state)
		{
		case Disable:
		{
			if (wifi_station_get_connect_status() == STATION_GOT_IP)
			{
				state = Idle;
			}
			break;
		}

		case Idle:
		{
			taskENTER_CRITICAL();
			m = Peek_Message(&incoming_command_queue);
			taskEXIT_CRITICAL();

			if (m != NULL)
			{
				state = ParseCommand;
			}
			break;
		}

		case ParseCommand:
		{
#ifdef PRINT_HIGH_WATER
			taskENTER_CRITICAL();
			printf("cmdparse\r\n");
			taskEXIT_CRITICAL();

			portENTER_CRITICAL();
			UART_WaitTxFifoEmpty(UART0);
			portEXIT_CRITICAL();

			DEBUG_Print_High_Water();
#endif

			taskENTER_CRITICAL();
			m = Dequeue_Message(&incoming_command_queue);
			taskEXIT_CRITICAL();

			taskYIELD();

			switch (Command_String_Parse(m->content, &command_args))
			{
			case CLAY_COMMAND_SET_AP:
			{
				//DEBUG_Print("setap rx");
				Set_AP_Command(command_args);
				break;
			}

			case CLAY_COMMAND_GET_AP:
			{
				Get_AP_Command(command_args);
				break;
			}

			case CLAY_COMMAND_SCAN_AP:
			{
				Scan_AP_Command(command_args);
				break;
			}

			case CLAY_COMMAND_GET_IP:
			{
				Get_IP_Command(command_args);
				break;
			}

			case CLAY_COMMAND_GET_GATEWAY:
			{
				Get_Gateway_Command(command_args);
				break;
			}

			case CLAY_COMMAND_GET_SUBNET:
			{
				Get_Subnet_Command(command_args);
				break;
			}

			case CLAY_COMMAND_MAX:
			default:
			{
				state = Idle;
				break;
			}

			}

			//DEBUG_Print("free command");
			//dequeue alloc's a message.
			free(m);
			m = NULL;

			//DEBUG_Print("return to idle");

			state = Idle;
			break;
		}

		case COMMAND_PARSER_STATE_MAX:
		default:
		{
			break;
		}
		}
		taskYIELD();
	}
}

////Local implementations ////////////////////////////////////////

//Parses a command out of commandStr. The argStr will be updated to
//		point to the start of the arguments in commandStr
//Command strings should be of the following format:
//		"<Command Token> <arg1>,<arg2>...."
static ICACHE_RODATA_ATTR CLAY_ESP_COMMANDS Command_String_Parse(
		char * commandStr, char ** argStr)
{
	CLAY_ESP_COMMANDS rval = CLAY_COMMAND_MAX;

	*argStr = strchr(commandStr, command_delimiter);

	for (i = 0; i < CLAY_COMMAND_MAX; ++i)
	{
		if (strstr(commandStr, command_tokens[i]) != NULL)
		{
			rval = (CLAY_ESP_COMMANDS) i;
			break;
		}
	}

	return rval;
}

static ICACHE_RODATA_ATTR bool Set_AP_Command(char * args)
{
	bool rval = false;

	Stop_Task(TASK_TYPE_TCP_RX | TASK_TYPE_UDP_RX | TASK_TYPE_UDP_TX);

	taskENTER_CRITICAL();
	char * ssid = strtok(args, &args_delimiter);
	char * key = strtok(NULL, &args_delimiter);
	taskEXIT_CRITICAL();

	if (Set_Access_Point(ssid, key))
	{
		Send_Message_To_Master("setap_ok", MESSAGE_TYPE_INFO);
	}
	else
	{
		Send_Message_To_Master("setap_fail", MESSAGE_TYPE_INFO);
	}

	return rval;
}

static ICACHE_RODATA_ATTR bool Get_AP_Command(char * args)
{
	bool rval = false;

	return rval;
}

static ICACHE_RODATA_ATTR bool Scan_AP_Command(char * args)
{
	bool rval = false;

	return rval;
}

static ICACHE_RODATA_ATTR bool Get_IP_Command(char * args)
{
	bool rval = false;

	taskENTER_CRITICAL();
	char * response_buffer = zalloc(30);
	taskEXIT_CRITICAL();

	int ip = Get_IP_Address();

	taskENTER_CRITICAL();
	sprintf(response_buffer, "ip %s", inet_ntoa(ip));
	taskEXIT_CRITICAL();

	Send_Message_To_Master(response_buffer, MESSAGE_TYPE_INFO);

	rval = ip > 0;

	free(response_buffer);

	return rval;
}

bool Get_Gateway_Command(char * args)
{
	bool rval = false;

	taskENTER_CRITICAL();
	char * response_buffer = zalloc(30);
	taskEXIT_CRITICAL();

	int gw = Get_Gateway_Address();

	taskENTER_CRITICAL();
	sprintf(response_buffer, "gateway %s", inet_ntoa(gw));
	taskEXIT_CRITICAL();

	Send_Message_To_Master(response_buffer, MESSAGE_TYPE_INFO);

	rval = gw > 0;

	free(response_buffer);

	return rval;
}

bool Get_Subnet_Command(char * args)
{
	bool rval = false;

	taskENTER_CRITICAL();
	char * response_buffer = zalloc(30);
	taskEXIT_CRITICAL();

	int mask = Get_Subnet_Mask();

	taskENTER_CRITICAL();
	sprintf(response_buffer, "mask %s", inet_ntoa(mask));
	taskEXIT_CRITICAL();

	Send_Message_To_Master(response_buffer, MESSAGE_TYPE_INFO);

	rval = mask > 0;

	free(response_buffer);

	return rval;
}

static void Stop_Task(TASK_TYPE tt)
{
	if (tt && TASK_TYPE_UDP_RX)
	{
		UDP_Receiver_Deinit();
	}

	if (tt && TASK_TYPE_UDP_TX)
	{
		UDP_Transmitter_Deinit();
	}

	if (tt && (TASK_TYPE_TCP_RX | TASK_TYPE_TCP_RX))
	{
		TCP_Combined_Deinit();
	}

	Send_Message_To_Master("stop_ok", MESSAGE_TYPE_INFO);
}

static void Start_Task(TASK_TYPE tt)
{
	bool rval = false;

	if (tt && TASK_TYPE_UDP_RX)
	{
		UDP_Receiver_Init();
	}

	if (tt && TASK_TYPE_UDP_TX)
	{
		UDP_Transmitter_Init();
	}

	if (tt && (TASK_TYPE_TCP_RX | TASK_TYPE_TCP_RX))
	{
		TCP_Combined_Init();
	}

	Send_Message_To_Master(rval ? "task_start_ok" : "task_start_fail",
			MESSAGE_TYPE_INFO);
}
