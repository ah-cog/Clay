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

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR Set_Access_Point(char * ssid, char * key)
{

	bool rval = wifi_station_disconnect();

	taskENTER_CRITICAL();
	struct station_config *config = (struct station_config *) zalloc(
			sizeof(struct station_config));
	taskEXIT_CRITICAL();

	taskENTER_CRITICAL();
	sprintf(config->ssid, ssid);
	sprintf(config->password, key);
	taskEXIT_CRITICAL();

	rval &= wifi_station_set_config(config);

	free(config);

	rval &= wifi_station_connect();

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

