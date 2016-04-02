/*
 * TCP_Connection_Manager.h
 *
 *  Created on: Mar 12, 2016
 *      Author: thebh_000
 */

#ifndef INCLUDE_TCP_CONNECTION_MANAGER_H_
#define INCLUDE_TCP_CONNECTION_MANAGER_H_

#include "Clay_Config.h"

extern int open_sockets[];

extern void SocketListInitialize();

//adds a socket to the list. Returns the index of the socket. Returns -1 if no space available.
extern int SocketListAdd(int newSocket);

//attempts to match connectionStr to a socket in the list. returns -1 if no socket found.
extern int SocketListQuery(uint8* connectionStr);

//looks for targetSocket in the list of open sockets and sets that value to -1 when it finds it.
extern void SocketListRemove(int targetSocket);

#endif /* INCLUDE_TCP_CONNECTION_MANAGER_H_ */
