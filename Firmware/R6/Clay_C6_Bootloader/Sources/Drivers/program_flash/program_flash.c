/*
 * flash.c
 *
 *  Created on: Dec 19, 2015
 *      Author: Ben
 */

#include "PE_Types.h"
#include "FLASH1.h"
#include "program_flash.h"

#define CRC16_POLY 0x8005U

bool checksum_initialized = FALSE;
volatile bool flash_operation_completed;

static uint32_t Read_Value_From_Address(uint32_t address, uint32_t size);
static uint32_t Write_Value_To_Address(uint32_t address, uint32_t size, uint8_t * data);

/**
 * Erases the entire program flash.
 * 
 * Erases the entire segment of flash memory dedicated to the main application 
 * firmware.
 */
uint16_t Erase_Program_Flash() {
   uint32_t address = APP_START_ADDR;
   uint16_t rval = 0;

   while (!rval && address <= APP_END_ADDR) {
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

   //erase operations must be 128-bit aligned (as in address & 0xF == 0)
   flash_operation_completed = FALSE;

   // Set up erase block operation
   uint16_t rval = FLASH1_Erase(FLASH1_DeviceData, address, FLASH_MEMORY_PAGE_SIZE);

   while (!rval && !flash_operation_completed) {
      // Run operation by calling flash1_main
      FLASH1_Main(FLASH1_DeviceData);
   }

   return rval;
}

/**
 * Writes data to the program flash.
 */
uint16_t Write_Program_Block(uint32_t destination, const uint8_t *data, uint32_t length) {
   // Set up flash operation
   flash_operation_completed = FALSE;
   LDD_FLASH_TOperationStatus status;

   uint16_t rval = FLASH1_Write(FLASH1_DeviceData, (char *) data, destination, length);

   while (!rval && !flash_operation_completed) {
      // Run operation by calling flash1_main
      FLASH1_Main(FLASH1_DeviceData);

      status = FLASH1_GetOperationStatus(FLASH1_DeviceData);

      flash_operation_completed = status != LDD_FLASH_RUNNING && status != LDD_FLASH_START && status != LDD_FLASH_STOP_REQ;
   }

   return rval;
}

/**
 * Writes the specified data to flash memory. Since the checksum only requires 
 * two bytes, only the first two bytes of the specified data will be coped to 
 * flash.
 */
uint16_t Write_Program_Checksum(uint32_t checksum) {

   checksum &= 0xFFFF;
   return Write_Value_To_Address(APP_CHECKSUM_ADDRESS, APP_CHECKSUM_SIZE, (uint8_t*) &checksum);
}

uint32_t Read_Program_Checksum() {
   return 0xFFFFU & Read_Value_From_Address(APP_CHECKSUM_ADDRESS, APP_CHECKSUM_SIZE);
}

/**
 * Writes the specified data to flash memory. Since the application size requires  
 * four bytes, only the first four bytes of the specified data will be coped to 
 * flash.
 */
uint16_t Write_Program_Size(uint32_t size) {
   return Write_Value_To_Address(APP_SIZE_ADDRESS, APP_SIZE_SIZE, (uint8_t*) &size);
}

uint32_t Read_Program_Size() {
   return Read_Value_From_Address(APP_SIZE_ADDRESS, APP_SIZE_SIZE);
}

/**
 * Writes the specified data to flash memory. Since the application size requires
 * four bytes, only the first four bytes of the specified data will be coped to
 * flash.
 */
uint16_t Write_Program_Version(uint32_t version) {
   return Write_Value_To_Address(APP_VERSION_ADDRESS, APP_VERSION_SIZE, (uint8_t*) &version);
}

uint32_t Read_Program_Version() {
   return Read_Value_From_Address(APP_VERSION_ADDRESS, APP_VERSION_SIZE);
}

//read up to an int.
uint32_t Read_Value_From_Address(uint32_t address, uint32_t size) {
   uint32_t result = NULL;     // Return value. Default to NULL.

   flash_operation_completed = FALSE;

   uint32_t read_result = FLASH1_Read(FLASH1_DeviceData, address, (void*) &result, size);

   while (!read_result && !flash_operation_completed) {
      // Run operation by calling flash1_main
      FLASH1_Main(FLASH1_DeviceData);
   }

   return result;
}

uint32_t Write_Value_To_Address(uint32_t address, uint32_t size, uint8_t * data) {

   flash_operation_completed = FALSE;

   // Set up flash operation
   uint16_t rval = FLASH1_Write(FLASH1_DeviceData, data, address, size);

   while (!rval && !flash_operation_completed) {
      // Run operation by calling flash1_main
      FLASH1_Main(FLASH1_DeviceData);
   }

//   rval = FLASH1_GetOperationStatus(FLASH1_DeviceData);
//
//   if (rval != 0) {
//      rval = 0;
//   }

   return rval;
}
