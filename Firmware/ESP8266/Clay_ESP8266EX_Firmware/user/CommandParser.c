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

#include "../include/System_Monitor.h"
#include "Clay_Config.h"

#include "Message_Queue.h"
#include "Message.h"
#include "ESP_Utilities.h"

#include "Wifi_Message_Serialization.h"
#include "UDP_Transmitter.h"
#include "UDP_Receiver.h"
#include "TCP_Combined.h"
#include "Queues.h"

////Defines ///////////////////////////////////////////////////////
#define WIFI_DISCONNECTED_RESPONSE		"wifi disconnected"
#define WIFI_CONNECTED_RESPONSE			"wifi connected"

#define SETAP_OK_RESPONSE			    "setap ok"
#define SETAP_FAIL_RESPONSE			    "setap fail"

#define WIFI_IP_RESPONSE			    "wifi address"
#define WIFI_GATEWAY_RESPONSE		    "wifi gateway"
#define WIFI_SUBNET_RESPONSE		    "wifi subnet mask"

#define TASK_START_OK_RESPONSE		    "task start ok"
#define TASK_START_FAIL_RESPONSE	    "task start fail"
#define TASK_STOP_OK_RESPONSE		    "task stop ok"

#define STARTUP_MESSAGE					"announce device wifi"

#define MESSAGE_TRIGGER_LEVEL			10

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
	CLAY_COMMAND_GET_CONNECTION_STATUS,
	CLAY_COMMAND_MAX
} CLAY_ESP_COMMANDS;

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////

// TODO: Implement these following example of Process_Event and Perform_Action in k64 code.
char* command_tokens[CLAY_COMMAND_MAX] =
{ "setap",        //
		"getap",        //
		"scanap",       //
		"get_ip",       //
		"get_gateway",  //
		"get_subnet",   //
		"stop_task",    //
		"start_task",   //
		"get_status"    //
		};

char * command_args;
char command_delimiter = ' ';
char args_delimiter = ',';

int i;
static Message * temp_msg_ptr;
static Command_Parser_States state;

static bool promoted;

////Local Prototypes///////////////////////////////////////////////
static CLAY_ESP_COMMANDS Command_String_Parse(char * commandStr,
		uint32_t commandStrLength, char ** argStr);
static bool Set_AP_Command(char * args);
static bool Get_AP_Command(char * args);
static bool Scan_AP_Command(char * args);
static bool Check_Needs_Promotion();

//TODO: these are both supposed to take char * and return bool;
static void Stop_Task_Command(TASK_TYPE tt);
static void Start_Task_Command(TASK_TYPE tt);

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR Command_Parser_Init()
{
	bool rval = false;
	promoted = false;

	taskENTER_CRITICAL();
	Initialize_Message_Queue(&incoming_command_queue);
	taskEXIT_CRITICAL();

	state = Idle;

	xTaskHandle command_parser_handle;

	xTaskCreate(Command_Parser_State_Step, "cmdParser", 512, NULL,
			Get_Task_Priority(TASK_TYPE_COMMAND_PARSER),
			&command_parser_handle);

	System_Register_Task(TASK_TYPE_COMMAND_PARSER, command_parser_handle,
			Check_Needs_Promotion);

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
			if (Has_Messages(&incoming_command_queue))
			{
				state = ParseCommand;
			}
			taskEXIT_CRITICAL();
			break;
		}

		case ParseCommand:
		{
#ifdef PRINT_HIGH_WATER
			taskENTER_CRITICAL();
			printf("cmdparse\r\n");
			taskEXIT_CRITICAL();

//			UART_WaitTxFifoEmpty(UART0);

			DEBUG_Print_High_Water();
#endif

			taskENTER_CRITICAL();
			temp_msg_ptr = Dequeue_Message(&incoming_command_queue);
			taskEXIT_CRITICAL();

			taskYIELD();

			switch (Command_String_Parse(temp_msg_ptr->content,
					temp_msg_ptr->content_length, &command_args))
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

			case CLAY_COMMAND_GET_CONNECTION_STATUS:
			{
				Get_Wifi_Status_Command(command_args);
				break;
			}

			case CLAY_COMMAND_START_TASK:
			case CLAY_COMMAND_STOP_TASK:
			case CLAY_COMMAND_MAX:
			default:
			{
				break;
			}

			}

			if(temp_msg_ptr != NULL)
			{
				Delete_Message(temp_msg_ptr);
			}

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
		char * commandStr, uint32_t commandStrLength, char ** argStr)
{
	char * cmd_str_ptr;
	CLAY_ESP_COMMANDS rval = CLAY_COMMAND_MAX;

	taskENTER_CRITICAL();
	*argStr = strchr(commandStr, command_delimiter);
	taskEXIT_CRITICAL();

	for (i = 0; i < CLAY_COMMAND_MAX; ++i)
	{
		taskENTER_CRITICAL();
		cmd_str_ptr = strstr(commandStr, command_tokens[i]);
		taskEXIT_CRITICAL();

		if (cmd_str_ptr != NULL)
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

	Stop_Task_Command(TASK_TYPE_TCP_RX);
	Stop_Task_Command(TASK_TYPE_UDP_RX);
	Stop_Task_Command(TASK_TYPE_UDP_TX);

	taskENTER_CRITICAL();
	char * ssid = strtok(args, &args_delimiter);
	char * key = strtok(NULL, &args_delimiter);
	taskEXIT_CRITICAL();

//	taskENTER_CRITICAL();
//	printf("\r\n\r\nsetap:%s,%s\r\n\r\n", ssid, key);
//	taskEXIT_CRITICAL();

	if (Set_Access_Point(ssid, key))
	{
		Send_Message_To_Master(SETAP_OK_RESPONSE, MESSAGE_TYPE_STATUS);
	}
	else
	{
		Send_Message_To_Master(SETAP_FAIL_RESPONSE, MESSAGE_TYPE_STATUS);
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

bool ICACHE_RODATA_ATTR Get_IP_Command(char * args)
{
	bool rval = false;

	taskENTER_CRITICAL();
	char * response_buffer = zalloc(30);
	taskEXIT_CRITICAL();

	int ip = Get_IP_Address();

	taskENTER_CRITICAL();
	sprintf(response_buffer, "%s %s", WIFI_IP_RESPONSE, inet_ntoa(ip));
	taskEXIT_CRITICAL();

	Send_Message_To_Master(response_buffer, MESSAGE_TYPE_STATUS);

	rval = ip > 0;

	free(response_buffer);

	return rval;
}

bool ICACHE_RODATA_ATTR Get_Gateway_Command(char * args)
{
	bool rval = false;

	taskENTER_CRITICAL();
	char * response_buffer = zalloc(30);
	taskEXIT_CRITICAL();

	int gw = Get_Gateway_Address();

	taskENTER_CRITICAL();
	sprintf(response_buffer, "%s %s", WIFI_GATEWAY_RESPONSE, inet_ntoa(gw));
	taskEXIT_CRITICAL();

	Send_Message_To_Master(response_buffer, MESSAGE_TYPE_STATUS);

	rval = gw > 0;

	free(response_buffer);

	return rval;
}

bool ICACHE_RODATA_ATTR Get_Subnet_Command(char * args)
{
	bool rval = false;

	taskENTER_CRITICAL();
	char * response_buffer = zalloc(30);
	taskEXIT_CRITICAL();

	int mask = Get_Subnet_Mask();

	taskENTER_CRITICAL();
	sprintf(response_buffer, "%s %s", WIFI_SUBNET_RESPONSE, inet_ntoa(mask));
	taskEXIT_CRITICAL();

	Send_Message_To_Master(response_buffer, MESSAGE_TYPE_STATUS);

	rval = mask > 0;

	free(response_buffer);

	return rval;
}

static void Stop_Task_Command(TASK_TYPE tt)
{
//TODO: there needs to be a version of this that the command parser supports. i.e. takes char * as arg.

	switch (tt)
	{
	case TASK_TYPE_UDP_RX:
	{
		UDP_Receiver_Deinit();
		break;
	}

	case TASK_TYPE_UDP_TX:
	{
		UDP_Transmitter_Deinit();
		break;
	}

	case TASK_TYPE_TCP_RX:
	{
		TCP_Combined_Deinit();
		break;
	}
	}

	Send_Message_To_Master(TASK_STOP_OK_RESPONSE, MESSAGE_TYPE_STATUS);
}

static void Start_Task_Command(TASK_TYPE tt)
{
//TODO: there needs to be a version of this that the command parser supports. i.e. takes char * as arg.

	bool rval = false;

	switch (tt)
	{
	case TASK_TYPE_UDP_RX:
	{
		UDP_Receiver_Init();
		break;
	}

	case TASK_TYPE_UDP_TX:
	{
		UDP_Transmitter_Init();
		break;
	}

	case TASK_TYPE_TCP_RX:
	{
		TCP_Combined_Init();
		break;
	}
	}

	Send_Message_To_Master(
			rval ? TASK_START_OK_RESPONSE : TASK_START_FAIL_RESPONSE,
			MESSAGE_TYPE_STATUS);
}

bool ICACHE_RODATA_ATTR Get_Wifi_Status_Command(char * args)
{
	bool connected = (wifi_station_get_connect_status() == STATION_GOT_IP);

	Send_Message_To_Master(
			connected ? WIFI_CONNECTED_RESPONSE : WIFI_DISCONNECTED_RESPONSE,
			MESSAGE_TYPE_STATUS);

	return connected;
}

void ICACHE_RODATA_ATTR Send_Startup_Message()
{
	Send_Message_To_Master(STARTUP_MESSAGE, MESSAGE_TYPE_STATUS);
}

static bool Check_Needs_Promotion()
{
	bool rval = false;

	//remain promoted until we empty the queue.
	taskENTER_CRITICAL();
	rval = (Has_Messages(&incoming_command_queue));
	taskEXIT_CRITICAL();

	promoted = rval;

	return rval;
}

