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

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR Set_Access_Point(char * ssid, char * key)
{

	bool rval = wifi_station_disconnect();

	struct station_config *config = (struct station_config *) zalloc(
			sizeof(struct station_config));

	sprintf(config->ssid, ssid);
	sprintf(config->password, key);

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

////Local implementations ////////////////////////////////////////

