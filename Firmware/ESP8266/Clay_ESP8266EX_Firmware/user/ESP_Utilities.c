/*
 * ESP_Utilities.c
 *
 *  Created on: Mar 19, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "../include/ESP_Utilities.h"

#include "esp_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "uart.h"

#include "Clay_Config.h"

////Defines	///////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR Set_Access_Point(char * ssid, char * key)
{
	DEBUG_Print("setap");

	bool rval = wifi_station_disconnect();

	DEBUG_Print("disconnect");

	taskENTER_CRITICAL();
	struct station_config *config = (struct station_config *) zalloc(
			sizeof(struct station_config));
	taskEXIT_CRITICAL();

	DEBUG_Print("config created");

	taskENTER_CRITICAL();
	sprintf(config->ssid, ssid);
	sprintf(config->password, key);
	taskEXIT_CRITICAL();

	DEBUG_Print("set ssid and key");

	rval &= wifi_station_set_config(config);

	DEBUG_Print("config set");

	free(config);

	DEBUG_Print("freed config");

	rval &= wifi_station_connect();

	taskENTER_CRITICAL();
	printf("setap:%s\r\n", rval ? "ok" : "nfg");
	taskEXIT_CRITICAL();

	return rval;
}

int ICACHE_RODATA_ATTR Get_IP_Address()
{
	struct ip_info ip;
	wifi_get_ip_info(STATION_IF, &ip);

	return ip.ip.addr;
}

int ICACHE_RODATA_ATTR Get_Gateway_Address()
{
	struct ip_info ip;
	wifi_get_ip_info(STATION_IF, &ip);

	return ip.gw.addr;
}

int ICACHE_RODATA_ATTR Get_Subnet_Mask()
{
	struct ip_info ip;
	wifi_get_ip_info(STATION_IF, &ip);

	return ip.netmask.addr;
}

#if ENABLE_DEBUG_PRINT
void ICACHE_RODATA_ATTR DEBUG_Print(char * msg)
{
	taskENTER_CRITICAL();
	printf("%s\r\n", msg);
	taskEXIT_CRITICAL();
}
#endif

void ICACHE_RODATA_ATTR DEBUG_Print_Address(struct sockaddr_in * addr,
		char * tag)
{
	char addr_string[50];

	taskENTER_CRITICAL();
	Serialize_Address(addr->sin_addr.s_addr, addr->sin_port, addr_string, 50);
	taskEXIT_CRITICAL();

	taskENTER_CRITICAL();
	printf("%s: %s", tag, addr_string);
	taskEXIT_CRITICAL();
}

void ICACHE_RODATA_ATTR DEBUG_Print_High_Water()
{
	xTaskHandle task_handle = xTaskGetCurrentTaskHandle();

	taskENTER_CRITICAL();
	printf("task %d: high water:%d\r\n\r\n\r\n", *((int*) task_handle),
			uxTaskGetStackHighWaterMark(task_handle));
	taskEXIT_CRITICAL();

	portENTER_CRITICAL();
	UART_WaitTxFifoEmpty(UART0);
	portEXIT_CRITICAL();
}

////Local implementations ////////////////////////////////////////

