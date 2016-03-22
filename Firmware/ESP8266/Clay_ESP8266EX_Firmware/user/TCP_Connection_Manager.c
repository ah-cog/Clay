/*
 * TCP_Connection_Manager.c
 *
 *  Created on: Mar 12, 2016
 *      Author: thebh_000
 */

#include "esp_common.h"
#include "lwip/sockets.h"
#include "AddressSerialization.h"
#include "Clay_Config.h"
#include "TCP_Connection_Manager.h"

int Open_Sockets[TCP_MAX_CONNECTIONS];
int i;
struct sockaddr_in temp_addr_list;
struct sockaddr_in temp_addr_query;

Message_Type temp_message_type;

uint32 temp_addr_length;
volatile bool socket_list_lock;

//TODO: in add socket, check for inactive connections
//		-add a time of last activity, updated when receiving from or sending to
//		-close the socket
//		-stop the task that's listening to it
//		-remove socket from list.

void ICACHE_RODATA_ATTR SocketListInitialize()
{
	socket_list_lock = false;
	for (i = 0; i < TCP_MAX_CONNECTIONS; ++i)
	{
		Open_Sockets[i] = -1;
	}
}

int ICACHE_RODATA_ATTR SocketListAdd(int newSocket)
{
	int rval = -1;

	while (socket_list_lock)
	{
		printf("yield add\r\n");
		vTaskDelay(5 / portTICK_RATE_MS);
//		taskYIELD();
	}

	socket_list_lock = true;

	taskENTER_CRITICAL();
	for (i = 0; i < TCP_MAX_CONNECTIONS; ++i)
	{
		if (Open_Sockets[i] == -1)
		{
			printf("added socket:%d\r\n", newSocket);
			Open_Sockets[i] = newSocket;
			rval = i;
			break;
		}
	}
	taskEXIT_CRITICAL();

	socket_list_lock = false;

	return rval;
}

int ICACHE_RODATA_ATTR SocketListQuery(uint8* addrStr)
{
	int rval = -1;
	temp_addr_length = sizeof(temp_addr_list);

	taskENTER_CRITICAL();
	Deserialize_Address(addrStr, &temp_addr_query, &temp_message_type);

	for (i = 0; i < TCP_MAX_CONNECTIONS; ++i)
	{
		if (i == -1)
		{
			continue;
		}

		taskEXIT_CRITICAL();

		//this is here because getpeername can't be in a critical section.
		while (socket_list_lock)
		{
			printf("yield query\r\n");
			vTaskDelay(5 / portTICK_RATE_MS);
//			taskYIELD();
		}
		socket_list_lock = true;

		getpeername(Open_Sockets[i], (struct sockaddr* )&temp_addr_list,
				&temp_addr_length);

		socket_list_lock = false;

		taskENTER_CRITICAL();

		if (temp_addr_list.sin_port == temp_addr_query.sin_port
				&& temp_addr_list.sin_addr.s_addr
						== temp_addr_query.sin_addr.s_addr)
		{
			rval = Open_Sockets[i];
			printf("found socket:%d\r\n", rval);
			break;
		}
	}
	taskEXIT_CRITICAL();

	return rval;
}

void ICACHE_RODATA_ATTR SocketListRemove(int targetSocket)
{
	while (socket_list_lock)
	{
		vTaskDelay(5 / portTICK_RATE_MS);
		printf("yield remove\r\n");
//		taskYIELD();
	}

	socket_list_lock = true;

	taskENTER_CRITICAL();
	for (i = 0; i < TCP_MAX_CONNECTIONS; ++i)
	{
		if (Open_Sockets[i] == targetSocket)
		{
			printf("removing socket :%d\r\n", targetSocket);
			Open_Sockets[i] = -1;
		}
	}
	taskEXIT_CRITICAL();

	socket_list_lock = false;
}
