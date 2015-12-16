/*
 * nvm_data.h
 *
 *  Created on: Dec 15, 2015
 *      Author: thebh_000
 */

//this file contains structs that will be stored in the NVM.
#ifndef NVM_DATA_H_
#define NVM_DATA_H_

#include "nvm.h"
#include "led_driver_pca9552.h"

#define LED_STATE_COUNT         12
//add your variables to this struct
typedef struct nvm_data
{
    //LED states
    color_rgb * rgb_states[LED_STATE_COUNT];
}nvm_data;

extern nvm_data nvm;
#endif /* NVM_DATA_H_ */
