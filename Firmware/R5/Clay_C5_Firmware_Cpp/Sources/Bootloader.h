/*
 * Bootloader.h
 *
 *  Created on: Jan 9, 2016
 *      Author: thebh
 */

#ifndef BOOTLOADER_H
#define BOOTLOADER_H

//includes
#include "PE_Types.h"

//defines

//data types
typedef struct shared_bootloader_data
{
    uint32_t ApplicationKey;
    bool UpdateApplication;
    bool ApplicationUpdateAvailable;
    uint16_t pad;
}shared_bootloader_data;

//global vars
extern shared_bootloader_data SharedData;

//prototypes

//Returns true if an update is available and writes the ApplicationKey value so 
//        the bootloader will know that the application has run.
extern bool Update_Available ();

//Call to jump to the bootloader and update the application.
extern void Jump_To_Bootloader_And_Update_Application();


#endif /* BOOTLOADER_H */
