/*
 * ESP_Utilities.h
 *
 *  Created on: Mar 19, 2016
 *      Author: thebh_000
 */

#ifndef INCLUDE_ESP_UTILITIES_H_
#define INCLUDE_ESP_UTILITIES_H_

#include "esp_common.h"

extern bool Set_Access_Point(char * ssid, char * key);
extern int Get_Subnet_Mask();
extern int Get_Gateway_Address();
extern int Get_IP_Address();

extern void ICACHE_RODATA_ATTR DEBUG_Print(char * msg);
extern void ICACHE_RODATA_ATTR DEBUG_Print_High_Water();

#endif /* INCLUDE_ESP_UTILITIES_H_ */
