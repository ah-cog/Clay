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
void Set_Access_Point(char * ssid, char * key)
{
	wifi_station_disconnect();

	struct station_config *config = (struct station_config *) zalloc(
			sizeof(struct station_config));

	sprintf(config->ssid, ssid);
	sprintf(config->password, key);

	/* need to sure that you are in station mode first,
	 * otherwise it will be failed. */
	wifi_station_set_config(config);
	free(config);

	wifi_station_connect();
}

////Local implementations ////////////////////////////////////////

