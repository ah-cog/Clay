/*
 * flash.c
 *
 *  Created on: Dec 19, 2015
 *      Author: Ben
 */

#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"

//TODO: update flash driver.
//#include "FLASH1.h"
#include "program_flash.h"

#define CRC16_POLY 0x8005U

bool checksum_initialized = false;
volatile bool flash_operation_completed;
/**
 * Erases the entire program flash.
 * 
 * Erases the entire segment of flash memory dedicated to the main application 
 * firmware.
 */
uint16_t Erase_Program_Flash() {
   uint32_t address = APP_START_ADDR;
   uint16_t rval = 0;

   while (!rval && address < APP_END_ADDR) {
      rval = Erase_Program_Flash_Page(address);

      if (rval > 0) break;

      address += FLASH_MEMORY_PAGE_SIZE;
   }

   return rval;
}

/**
 * Erases the page of program flash containing the address.
 */
uint16_t Erase_Program_Flash_Page(uint32_t address) {
   // Set up erase block operation
//   uint16_t rval = FLASH1_Erase(FLASH1_DeviceData, address, FLASH_MEMORY_PAGE_SIZE);
   uint16_t rval = 0;

   flash_operation_completed = false;

   while (!rval && !flash_operation_completed) {
      // Run operation by calling flash1_main
      //TODO: update flash driver
//      FLASH1_Main(FLASH1_DeviceData);
   }

   return rval;
}

/**
 * Writes data to the program flash.
 */
uint16_t Write_Program_Block(uint32_t destination, uint8_t *data, uint32_t length) {
   // Set up flash operation
   uint16_t rval = 0;

   //TODO: update flash driver.
//   uint16_t rval = FLASH1_Write(FLASH1_DeviceData, data, destination, length);

   flash_operation_completed = false;
   while (!rval && !flash_operation_completed) {
      // Run operation by calling flash1_main

      //TODO: update flash driver.
//      FLASH1_Main(FLASH1_DeviceData);
   }

   return rval;
}

/**
 * Writes the specified data to flash memory. Since the checksum only requires 
 * two bytes, only the first two bytes of the specified data will be coped to 
 * flash.
 */
uint16_t Write_Program_Checksum(uint16_t checksum) {
   // Get pointer to the checksum data
//   uint8_t *data = (uint8_t *) &checksum;

   // Set up flash operation
   //TODO: update flash driver
//   uint16_t rval = FLASH1_Write(FLASH1_DeviceData, data, APP_CHECKSUM_ADDRESS, APP_CHECKSUM_SIZE);
   uint16_t rval = 0;

   flash_operation_completed = false;
   while (!rval && !flash_operation_completed) {
      // Run operation by calling flash1_main
      //TODO: update flash driver
//      FLASH1_Main(FLASH1_DeviceData);
   }

   return rval;
}

uint16_t Read_Program_Checksum() {
   uint16_t result = NULL;     // Return value. Default to NULL.
   uint16_t *checksum = NULL;     // Pointer to the checksum address in the flash memory.

   // Point to the checksum memory location.
   checksum = (uint16_t *) APP_CHECKSUM_ADDRESS;

   // Copy the stored checksum into the return value.
   result = *checksum;

   return result;
}

/**
 * Writes the specified data to flash memory. Since the application size requires  
 * four bytes, only the first four bytes of the specified data will be coped to 
 * flash.
 */
uint16_t Write_Program_Size(uint32_t size) {
   // Get pointer to the application size bytes
//   uint8_t *data = (uint8_t *) &size;

   // Set up flash operation
   //TODO: update flash driver
//	uint16_t rval = FLASH1_Write (FLASH1_DeviceData, data, APP_SIZE_ADDRESS, APP_SIZE_SIZE);
   uint16_t rval = 0;

   flash_operation_completed = false;
   while (!rval && !flash_operation_completed) {
      // Run operation by calling flash1_main
      //TODO: update flash driver.
//      FLASH1_Main(FLASH1_DeviceData);
   }

   return rval;
}

uint32_t Read_Program_Size() {
   uint32_t result = NULL;     // Return value. Default to NULL.
   uint32_t *size = NULL;     // Pointer to the checksum address in the flash memory.

   // Point to the checksum memory location.
   size = (uint32_t *) APP_SIZE_ADDRESS;

   // Copy the stored checksum into the return value.
   result = *size;

   return result;
}
