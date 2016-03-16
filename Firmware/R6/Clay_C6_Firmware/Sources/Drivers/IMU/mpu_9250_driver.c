/*
 * mpu_9250_driver.c
 *
 *  Created on: Sep 14, 2015
 *      Author: thebh_000
 */

// includes //////////////////
#include "mpu_9250_driver.h"
#include "I2C0.h"
#include "Clock.h"

// defines ///////////////////
#define SEND_TIMEOUT_MSEC   20

// structs ///////////////////

// global vars ///////////////
bool i2c_tx_complete;
bool i2c_rx_complete;

// local vars ////////////////
static uint32_t start_time;
static uint8_t outgoing_msg_buf[32];
static uint8_t incoming_msg_buf[32];

// prototypes ////////////////
static LDD_TError send_message(uint8_t * message, int32 size, uint8_t address);
static LDD_TError receive_message(uint8_t * tx_buf, int32 tx_size, uint8_t * rx_buf, int32 rx_size, uint8_t address);
static void set_clock_source(uint8_t source);
static void set_full_scale_gyro_range(uint8_t range);
static void set_full_scale_accel_range(uint8_t range);
static void set_sleep_enabled(uint8_t enabled);
static void set_magnetometer_mode(uint8_t mode);
static LDD_TError mpu9250_write_bitfield(uint8_t reg_addr, uint8_t lsb_index, uint8_t field_length, uint8_t data, uint8_t address);
static LDD_TError mpu9250_write_bit(uint8_t reg_addr, uint8_t bit_index, uint8_t data, uint8_t address);
static void mpu9250_write_accel_bit(uint8_t regAddr, uint8_t bitNum, uint8_t data);
static void mpu9250_write_accel_bitfield(uint8_t reg_addr, uint8_t lsb_index, uint8_t field_length, uint8_t data);
static void mpu9250_write_mag_bit(uint8_t regAddr, uint8_t bitNum, uint8_t data);
static void mpu9250_write_mag_bitfield(uint8_t reg_addr, uint8_t lsb_index, uint8_t field_length, uint8_t data);

// implementations ///////////
void mpu_9250_init()
{
   set_clock_source(MPU9250_CLOCK_PLL_XGYRO);
   set_full_scale_gyro_range(MPU9250_GYRO_FS_250);
   set_full_scale_accel_range(MPU9250_ACCEL_FS_2);
   set_sleep_enabled(FALSE);

   //set bypass mode so we can talk to the magnetometer
   mpu9250_write_accel_bit(MPU9250_RA_INT_PIN_CFG, 1, 1);

   set_magnetometer_mode(MPU9250_RA_MAG_MODE_CONTINUOUS_1);
}

//gets xyz data for accelerometer, gyro, and magnetometer
void get_mpu_readings(mpu_values * data)
{
   outgoing_msg_buf[0] = MPU9250_RA_ACCEL_XOUT_H;
   receive_message(outgoing_msg_buf, 1, incoming_msg_buf, 6, MPU9250_ACCEL_ADDRESS);

   //I2Cdev::readBytes(devAddr, MPU6050_RA_ACCEL_XOUT_H, 6, buffer);
   data->values.accel.val.x = (((int16_t) incoming_msg_buf[0]) << 8) | incoming_msg_buf[1];
   data->values.accel.val.y = (((int16_t) incoming_msg_buf[2]) << 8) | incoming_msg_buf[3];
   data->values.accel.val.z = (((int16_t) incoming_msg_buf[4]) << 8) | incoming_msg_buf[5];

   outgoing_msg_buf[0] = MPU9250_RA_GYRO_XOUT_H;
   receive_message(outgoing_msg_buf, 1, incoming_msg_buf, 6, MPU9250_ACCEL_ADDRESS);

   data->values.gyro.val.x = (((int16_t) incoming_msg_buf[0]) << 8) | incoming_msg_buf[1];
   data->values.gyro.val.y = (((int16_t) incoming_msg_buf[2]) << 8) | incoming_msg_buf[3];
   data->values.gyro.val.z = (((int16_t) incoming_msg_buf[4]) << 8) | incoming_msg_buf[5];

   outgoing_msg_buf[0] = MPU9250_RA_MAG_ST_1;
   receive_message(outgoing_msg_buf, 1, incoming_msg_buf, 9, MPU9250_MAG_ADDRESS);

   //Note: magnetometer buffers are little endian.
   data->values.mag.val.x = (((int16_t) incoming_msg_buf[2]) << 8) | incoming_msg_buf[1];
   data->values.mag.val.y = (((int16_t) incoming_msg_buf[4]) << 8) | incoming_msg_buf[3];
   data->values.mag.val.z = (((int16_t) incoming_msg_buf[6]) << 8) | incoming_msg_buf[5];
}

uint8_t local_inv_data[0x100];

//used for invensense driver
uint8_t write_mpu9250(uint8_t device_addr, uint8_t reg_addr, uint8_t length, uint8_t * data)
{
   local_inv_data[0] = reg_addr;

   for (int i = 0; i < length; ++i)
   {
      local_inv_data[i + 1] = data[i];
   }

   Wait(1);

   return send_message(local_inv_data, length + 1, device_addr);
}

//used for invensense driver
uint8_t read_mpu9250(uint8_t device_addr, uint8_t reg_addr, uint8_t length, uint8_t * data)
{
   Wait(1);
   return receive_message(&reg_addr, 1, data, length, device_addr);
}

//TODO: these live in I2C.c/h now
//tx_buf contains data that will be sent to the device.
//tx_size is the number of bytes in tx_buf
//address is the I2C address of the device which is to be read
static LDD_TError send_message(uint8_t * message, int32 size, uint8_t address)
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

   return rval;
}

//TODO: these live in I2C.c/h now
//tx_buf contains command that will prepare the device for the read
//tx_size is the number of bytes in tx_buf
//rx_buf is the location where the returned data will be stored
//rx_size is the number of bytes to read
//address is the I2C address of the device which is to be read
static LDD_TError receive_message(uint8_t * tx_buf, int32 tx_size, uint8_t * rx_buf, int32 rx_size, uint8_t address)
{
   LDD_TError rval = send_message(tx_buf, tx_size, address);

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

static void set_clock_source(uint8_t source)
{
   mpu9250_write_accel_bitfield(MPU9250_RA_PWR_MGMT_1, MPU9250_PWR1_CLKSEL_BIT, MPU9250_PWR1_CLKSEL_LENGTH, source);
}

static void set_full_scale_gyro_range(uint8_t range)
{
   mpu9250_write_accel_bitfield(MPU9250_RA_GYRO_CONFIG, MPU9250_GCONFIG_FS_SEL_BIT, MPU9250_GCONFIG_FS_SEL_LENGTH, range);
}

static void set_full_scale_accel_range(uint8_t range)
{
   mpu9250_write_accel_bitfield(MPU9250_RA_ACCEL_CONFIG, MPU9250_ACONFIG_AFS_SEL_BIT, MPU9250_ACONFIG_AFS_SEL_LENGTH, range);
}

static void set_sleep_enabled(uint8_t enabled)
{
   mpu9250_write_accel_bit(MPU9250_RA_PWR_MGMT_1, MPU9250_PWR1_SLEEP_BIT, enabled);
}

static void set_magnetometer_mode(uint8_t mode)
{
   mpu9250_write_mag_bit(MPU9250_RA_MAG_CONTROL_1, 4, 1);
   mpu9250_write_mag_bitfield(MPU9250_RA_MAG_CONTROL_1, 0, 4, mode);
}

static void mpu9250_write_accel_bitfield(uint8_t reg_addr, uint8_t lsb_index, uint8_t field_length, uint8_t data)
{
   mpu9250_write_bitfield(reg_addr, lsb_index, field_length, data, MPU9250_ACCEL_ADDRESS);
}

static void mpu9250_write_accel_bit(uint8_t reg_addr, uint8_t bit_index, uint8_t data)
{
   mpu9250_write_bit(reg_addr, bit_index, data, MPU9250_ACCEL_ADDRESS);
}

static void mpu9250_write_mag_bit(uint8_t reg_addr, uint8_t bit_index, uint8_t data)
{
   mpu9250_write_bit(reg_addr, bit_index, data, MPU9250_MAG_ADDRESS);
}

static void mpu9250_write_mag_bitfield(uint8_t reg_addr, uint8_t lsb_index, uint8_t field_length, uint8_t data)
{
   mpu9250_write_bitfield(reg_addr, lsb_index, field_length, data, MPU9250_MAG_ADDRESS);
}

static LDD_TError mpu9250_write_bitfield(uint8_t reg_addr, uint8_t lsb_index, uint8_t field_length, uint8_t data, uint8_t address)
{
   uint8_t current_value;

   uint8_t mask = (1 << field_length) - 1;
   uint8_t masked_data = data & mask;

   receive_message(&reg_addr, 1, &current_value, 1, address);

   current_value &= ~mask;

   outgoing_msg_buf[0] = reg_addr;
   outgoing_msg_buf[1] = current_value | (masked_data << lsb_index);

   return send_message(outgoing_msg_buf, 2, address);
}

static LDD_TError mpu9250_write_bit(uint8_t reg_addr, uint8_t bit_index, uint8_t data, uint8_t address)
{
   uint8_t current_value;

   receive_message(&reg_addr, 1, &current_value, 1, address);

   outgoing_msg_buf[0] = reg_addr;
   outgoing_msg_buf[1] = (data ? (current_value | (1 << bit_index)) : (current_value & ~(1 << bit_index)));

   return send_message(outgoing_msg_buf, 2, address);
}
