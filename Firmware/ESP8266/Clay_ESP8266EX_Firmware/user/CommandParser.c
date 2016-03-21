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
	Disable, Idle, ParseCommand, RespondToMaster, COMMAND_PARSER_STATE_MAX
} Command_Parser_States;

typedef enum
{
	CLAY_COMMAND_SET_AP,
	CLAY_COMMAND_GET_AP,
	CLAY_COMMAND_SCAN_AP,
	CLAY_COMMAND_MAX
} CLAY_ESP_COMMANDS;
////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
char* command_tokens[CLAY_COMMAND_MAX] =
{ "SETAP", "GETAP", "SCANAP" };

char * command_args;
char command_delimiter = ' ';
char args_delimiter = ',';

int i;
static Message * m;
Command_Parser_States state;

////Local Prototypes///////////////////////////////////////////////
CLAY_ESP_COMMANDS Command_String_Parse(char * CommandStr, char ** ArgStr);
bool Set_AP_Command(char * args);
bool Get_AP_Command(char * args);
bool Scan_AP_Command(char * args);

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR Command_Parser_Init()
{
	bool rval = false;

	state = Idle;

	Initialize_Message_Queue(&incomingCommandMessageQueue);

	xTaskCreate(Command_Parser_State_Step, "cmdParser", 512, NULL, 2, NULL);

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
			m = Peek_Message(&incomingCommandMessageQueue);
			taskEXIT_CRITICAL();

			if (m != NULL)
			{
				state = ParseCommand;
			}
			break;
		}

		case ParseCommand:
		{
			taskENTER_CRITICAL();
			m = Dequeue_Message(&incomingCommandMessageQueue);
			taskEXIT_CRITICAL();

			//set state based on whether or not a response is necessary.
			state = RespondToMaster;

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

			case CLAY_COMMAND_MAX:
			default:
			{
				state = Idle;
				break;
			}

			}

			break;
		}

		case RespondToMaster:
		{
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
CLAY_ESP_COMMANDS Command_String_Parse(char * commandStr, char ** argStr)
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

bool Set_AP_Command(char * args)
{
	bool rval = false;

	char * ssid = strtok(args, &args_delimiter);
	char * key = strtok(NULL, &args_delimiter);

	Set_Access_Point(ssid, key);

	return rval;
}

bool Get_AP_Command(char * args)
{
	bool rval = false;

	return rval;
}

bool Scan_AP_Command(char * args)
{
	bool rval = false;

	return rval;
}

