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
struct sockaddr_in tempAddrList;
struct sockaddr_in tempAddrQuery;

Message_Type mt;

uint32 tempAddrLength;

//TODO: in add socket, check for inactive connections
//		-add a time of last activity, updated when receiving from or sending to
//		-close the socket
//		-stop the task that's listening to it
//		-remove socket from list.

void ICACHE_RODATA_ATTR SocketListInitialize()
{
	for (i = 0; i < TCP_MAX_CONNECTIONS; ++i)
	{
		Open_Sockets[i] = -1;
	}
}

int ICACHE_RODATA_ATTR SocketListAdd(int newSocket)
{
	int rval = -1;

	taskENTER_CRITICAL();
	for (i = 0; i < TCP_MAX_CONNECTIONS; ++i)
	{
		if (Open_Sockets[i] == -1)
		{
			Open_Sockets[i] = newSocket;
			rval = i;
			break;
		}
	}
	taskEXIT_CRITICAL();

	return rval;
}

int ICACHE_RODATA_ATTR SocketListQuery(uint8* addrStr)
{
	int rval = -1;
	tempAddrLength = sizeof(tempAddrList);

	taskENTER_CRITICAL();
	Deserialize_Address(addrStr, &tempAddrQuery, &mt);

	for (i = 0; i < TCP_MAX_CONNECTIONS; ++i)
	{
		if (i == -1)
		{
			continue;
		}

		taskEXIT_CRITICAL();
		//TODO: fix possible race condition with this.
		//      getpeername causes crash if we're in a critical section. likely needs another task to run.
		getpeername(Open_Sockets[i], (struct sockaddr* )&tempAddrList,
				&tempAddrLength);
		taskENTER_CRITICAL();

		if (tempAddrList.sin_port == tempAddrQuery.sin_port
				&& tempAddrList.sin_addr.s_addr
						== tempAddrQuery.sin_addr.s_addr)
		{
			rval = Open_Sockets[i];
			break;
		}
	}
	taskEXIT_CRITICAL();

	return rval;
}

void ICACHE_RODATA_ATTR SocketListRemove(int targetSocket)
{
	taskENTER_CRITICAL();
	for (i = 0; i < TCP_MAX_CONNECTIONS; ++i)
	{
		if (Open_Sockets[i] == targetSocket)
		{
			Open_Sockets[i] = -1;
		}
	}
	taskEXIT_CRITICAL();
}
