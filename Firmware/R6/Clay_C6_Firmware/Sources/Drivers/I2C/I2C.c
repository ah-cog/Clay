/*
 * I2C.c
 *
 *  Created on: Feb 13, 2016
 *      Author: thebh
 */

////includes
#include "PE_Types.h"
#include "Clock.h"
#include "I2C0.h"
#include "I2C.h"

////defines
#define SEND_TIMEOUT_MSEC   20

////typedefs

////global vars
bool i2c_tx_complete;
bool i2c_rx_complete;
////local vars
static uint32_t start_time;

////local function prototypes

//TODO: init methods

////global function implementations
//
//tx_buf contains data that will be sent to the device.
//tx_size is the number of bytes in tx_buf
//address is the I2C address of the device which is to be read
LDD_TError I2C_Send_Message(uint8_t * message, int32 size, uint8_t address)
{
   LDD_TError rval = I2C0_SelectSlaveDevice(I2C0_DeviceData, LDD_I2C_ADDRTYPE_7BITS, address);

   if (!rval)
   {

      i2c_tx_complete = FALSE;
      start_time = Millis();

      rval = I2C0_MasterSendBlock(I2C0_DeviceData, (LDD_TData*) message, (LDD_I2C_TSize) size, LDD_I2C_SEND_STOP);
      while (!i2c_tx_complete && (Millis() - start_time) < SEND_TIMEOUT_MSEC)
         ;
   }

   Wait(1);

   return rval;
}

//tx_buf contains command that will prepare the device for the read
//tx_size is the number of bytes in tx_buf
//rx_buf is the location where the returned data will be stored
//rx_size is the number of bytes to read
//address is the I2C address of the device which is to be read
LDD_TError I2C_Receive_Message(uint8_t * tx_buf, int32 tx_size, uint8_t * rx_buf, int32 rx_size, uint8_t address)
{
   LDD_TError rval = I2C_Send_Message(tx_buf, tx_size, address);

   if (!rval)
   {
      Wait(1);

      i2c_rx_complete = FALSE;
      start_time = Millis();

      rval = I2C0_MasterReceiveBlock(I2C0_DeviceData, rx_buf, rx_size, LDD_I2C_SEND_STOP);

      while (!i2c_rx_complete && (Millis() - start_time) < SEND_TIMEOUT_MSEC)
         ;
   }

   return rval;
}

////local function implementations
