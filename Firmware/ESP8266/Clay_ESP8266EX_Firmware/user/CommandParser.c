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
	CLAY_COMMAND_MAX
} CLAY_ESP_COMMANDS;
////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
char* command_tokens[CLAY_COMMAND_MAX] =
{ "SETAP", "GETAP", "SCANAP", "GET_IP", "GET_GATEWAY", "GET_SUBNET" };

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

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR Command_Parser_Init()
{
	bool rval = false;

	taskENTER_CRITICAL();
	Initialize_Message_Queue(&incoming_command_queue);
	taskEXIT_CRITICAL();

	state = Idle;

	xTaskCreate(Command_Parser_State_Step, "cmdParser", 128, NULL, 2,
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

			switch (Command_String_Parse(m->content, &command_args))
			{
			case CLAY_COMMAND_SET_AP:
			{
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

			//dequeue alloc's a message.
			free(m);
			m = NULL;

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

	taskENTER_CRITICAL();
	char * ssid = strtok(args, &args_delimiter);
	char * key = strtok(NULL, &args_delimiter);
	taskEXIT_CRITICAL();

	if (Set_Access_Point(ssid, key))
	{
		Send_Message_To_Master("SETAP_OK", MESSAGE_TYPE_INFO);
	}
	else
	{
		Send_Message_To_Master("SETAP_FAIL", MESSAGE_TYPE_INFO);
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

	int ip = Get_IP_Address();
	Send_Message_To_Master(inet_ntoa(ip), MESSAGE_TYPE_INFO);

	rval = ip > 0;

	return rval;
}

bool Get_Gateway_Command(char * args)
{
	bool rval = false;

	int gw = Get_Gateway_Address();
	Send_Message_To_Master(inet_ntoa(gw), MESSAGE_TYPE_INFO);

	rval = gw > 0;

	return rval;
}

bool Get_Subnet_Command(char * args)
{
	bool rval = false;
	int mask = Get_Subnet_Mask();
	Send_Message_To_Master(inet_ntoa(mask), MESSAGE_TYPE_INFO);

	rval = mask > 0;

	return rval;
}
