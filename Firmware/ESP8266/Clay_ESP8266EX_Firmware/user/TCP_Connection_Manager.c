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
#include "UART.h"

int open_sockets[TCP_MAX_CONNECTIONS];
int i;
struct sockaddr_in temp_addr_list;
struct sockaddr_in temp_addr_query;

Message_Type temp_message_type;

uint32 temp_addr_length;
volatile bool socket_list_lock;


//TODO: (idea, anyway) update this class to actually open and close sockets. Live up to that 'Manager' name.

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
		open_sockets[i] = -1;
	}
}

int ICACHE_RODATA_ATTR SocketListAdd(int newSocket)
{
	int rval = -1;

	while (socket_list_lock)
	{
		vTaskDelay(1 / portTICK_RATE_MS);
	}

	socket_list_lock = true;

	taskENTER_CRITICAL();
	for (i = 0; i < TCP_MAX_CONNECTIONS; ++i)
	{
		if (open_sockets[i] == -1)
		{
			open_sockets[i] = newSocket;
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
	uint8 current_addr[50];

	int rval = -1;
	temp_addr_length = sizeof(temp_addr_list);

	//this whole lock mechanism is here because getpeername can't be in a critical section.
	while (socket_list_lock)
	{
		vTaskDelay(1 / portTICK_RATE_MS);
	}

	socket_list_lock = true;

	taskENTER_CRITICAL();
	Deserialize_Address(addrStr, &temp_addr_query, &temp_message_type);
//	printf("\r\nsearch for addr:[%s]\r\n", addrStr);

	for (i = 0; i < TCP_MAX_CONNECTIONS; ++i)
	{
		if (open_sockets[i] == -1)
		{
			continue;
		}

		//

		taskEXIT_CRITICAL();
		getpeername(open_sockets[i], (struct sockaddr* )&temp_addr_list,
				&temp_addr_length);
		taskENTER_CRITICAL();

		//

//		Serialize_Address(temp_addr_list.sin_addr.s_addr,
//				temp_addr_list.sin_port, current_addr, 50, MESSAGE_TYPE_TCP);
//		printf("%d:[%s]\r\n", i, current_addr);
//		taskEXIT_CRITICAL();
//		UART_WaitTxFifoEmpty(UART0);
//
//		taskENTER_CRITICAL();

		if (temp_addr_list.sin_port == temp_addr_query.sin_port
				&& temp_addr_list.sin_addr.s_addr
						== temp_addr_query.sin_addr.s_addr)
		{
			rval = open_sockets[i];

//			printf("found sock:%d\r\n", rval);

			break;
		}
	}
	taskEXIT_CRITICAL();
	socket_list_lock = false;

	return rval;
}

void ICACHE_RODATA_ATTR SocketListRemove(int targetSocket)
{
	while (socket_list_lock)
	{
		vTaskDelay(1 / portTICK_RATE_MS);
	}

	socket_list_lock = true;

	taskENTER_CRITICAL();
	for (i = 0; i < TCP_MAX_CONNECTIONS; ++i)
	{
		if (open_sockets[i] == targetSocket)
		{
//			printf("removed sock:%d\r\n", targetSocket);
			open_sockets[i] = -1;
		}
	}
	taskEXIT_CRITICAL();

	socket_list_lock = false;
}
