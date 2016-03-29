/*
 * Power_Manager.c
 *
 *  Created on: Mar 27, 2016
 *      Author: thebh_000
 */

//enable ADC and register button.
void Power_Manager_Init();

//call on startup; watch button and make sure user holds it for a certain period of time. We should do this to prevent unintentional power-on
void Power_Manager_Check_Startup();

//pulls the UVLO line low to turn off the regulator.
void Power_Manager_Power_Off();

//looks at ADC to see if user wants to shut down.
void Power_Manager_Check_For_Power_Off_Conditions();
