/*
 * mpu_9250_driver.c
 *
 *  Created on: Sep 14, 2015
 *      Author: thebh_000
 */

// includes //////////////////
#ifndef MPU_9250_DRIVER_H_
#include "mpu_9250_driver.h"
#endif

#ifndef __I2C0_H
#include "I2C0.h"
#endif

#ifndef SYSTEM_TICK_H_
#include "system_tick.h"
#endif

// defines ///////////////////

// structs ///////////////////

// global vars ///////////////

// local vars ////////////////
static uint8 outgoing_msg_buf[32];
static uint8 incoming_msg_buf[32];

// prototypes ////////////////
static void send_message(uint8 * message, int32 size);
static void receive_message(uint8 * tx_buf, int32 tx_size, uint8 * rx_buf, int32 rx_size);
static void set_clock_source(uint8_t source);
static void set_full_scale_gyro_range(uint8_t range);
static void set_full_scale_accel_range(uint8_t range);
static void set_sleep_enabled(uint8_t enabled);
static void mpu9250_write_bit(uint8_t regAddr, uint8_t bitNum, uint8_t data);
static void mpu9250_write_bitfield(uint8_t reg_addr, uint8_t lsb_index, uint8_t field_length, uint8_t data);

// implementations ///////////
void mpu_9250_init()
{
    I2C0_SelectSlaveDevice(I2C0_DeviceData, LDD_I2C_ADDRTYPE_7BITS, MPU9250_ADDRESS);

    set_clock_source(MPU9250_CLOCK_PLL_XGYRO);
    set_full_scale_gyro_range(MPU9250_GYRO_FS_250);
    set_full_scale_accel_range(MPU9250_ACCEL_FS_2);
    set_sleep_enabled(FALSE);
}

void get_mpu_readings(mpu_values * data)
{
    outgoing_msg_buf[0] = MPU9250_RA_ACCEL_XOUT_H;
    receive_message(outgoing_msg_buf, 1, incoming_msg_buf, 6);

    //I2Cdev::readBytes(devAddr, MPU6050_RA_ACCEL_XOUT_H, 6, buffer);
    data->x_accel = (((int16_t) incoming_msg_buf[0]) << 8) | incoming_msg_buf[1];
    data->y_accel = (((int16_t) incoming_msg_buf[2]) << 8) | incoming_msg_buf[3];
    data->z_accel = (((int16_t) incoming_msg_buf[4]) << 8) | incoming_msg_buf[5];

    outgoing_msg_buf[0] = MPU9250_RA_GYRO_XOUT_H;
    receive_message(outgoing_msg_buf, 1, incoming_msg_buf, 6);

    data->x_gyro = (((int16_t) incoming_msg_buf[0]) << 8) | incoming_msg_buf[1];
    data->y_gyro = (((int16_t) incoming_msg_buf[2]) << 8) | incoming_msg_buf[3];
    data->z_gyro = (((int16_t) incoming_msg_buf[4]) << 8) | incoming_msg_buf[5];

    outgoing_msg_buf[0] = MPU9250_RA_MAG_XOUT_L;
    receive_message(outgoing_msg_buf, 1, incoming_msg_buf, 6);

    //Note: magnetometer buffers are little endian.
    data->x_mag = (((int16_t) incoming_msg_buf[1]) << 8) | incoming_msg_buf[0];
    data->y_mag = (((int16_t) incoming_msg_buf[3]) << 8) | incoming_msg_buf[2];
    data->z_mag = (((int16_t) incoming_msg_buf[5]) << 8) | incoming_msg_buf[4];
}

static void send_message(uint8 * message, int32 size)
{
    I2C0_SelectSlaveDevice(I2C0_DeviceData, LDD_I2C_ADDRTYPE_7BITS, MPU9250_ADDRESS);
    delay_n_msec(1);

    I2C0_MasterSendBlock(I2C0_DeviceData, (LDD_TData*) message, (LDD_I2C_TSize) size, LDD_I2C_SEND_STOP);
    delay_n_msec(1);
}

static void receive_message(uint8 * tx_buf, int32 tx_size, uint8 * rx_buf, int32 rx_size)
{
    send_message(tx_buf, tx_size);

    I2C0_MasterReceiveBlock(I2C0_DeviceData, rx_buf, rx_size, LDD_I2C_SEND_STOP);
    delay_n_msec(1);
}

static void set_clock_source(uint8_t source)
{
    mpu9250_write_bitfield(MPU9250_RA_PWR_MGMT_1, MPU9250_PWR1_CLKSEL_BIT, MPU9250_PWR1_CLKSEL_LENGTH, source);
}

static void set_full_scale_gyro_range(uint8_t range)
{
    mpu9250_write_bitfield(MPU9250_RA_GYRO_CONFIG, MPU9250_GCONFIG_FS_SEL_BIT, MPU9250_GCONFIG_FS_SEL_LENGTH, range);
}

static void set_full_scale_accel_range(uint8_t range)
{
    mpu9250_write_bitfield(MPU9250_RA_ACCEL_CONFIG, MPU9250_ACONFIG_AFS_SEL_BIT, MPU9250_ACONFIG_AFS_SEL_LENGTH, range);
}

static void set_sleep_enabled(uint8_t enabled)
{
    mpu9250_write_bit(MPU9250_RA_PWR_MGMT_1, MPU9250_PWR1_SLEEP_BIT, enabled);
}

static void mpu9250_write_bitfield(uint8_t reg_addr, uint8_t lsb_index, uint8_t field_length, uint8_t data)
{
    uint8_t current_value;

    uint8_t mask = (1 << (field_length + 1));
    uint8_t masked_data = data & mask;

    receive_message(&reg_addr, 1, &current_value, 1);

    outgoing_msg_buf[0] = reg_addr;
    outgoing_msg_buf[1] = (data ? (current_value | (masked_data << lsb_index)) : (current_value & ~(masked_data << lsb_index)));

    return send_message(outgoing_msg_buf, 2);
}

static void mpu9250_write_bit(uint8_t reg_addr, uint8_t bit_index, uint8_t data)
{
    uint8_t current_value;

    receive_message(&reg_addr, 1, &current_value, 1);

    outgoing_msg_buf[0] = reg_addr;
    outgoing_msg_buf[1] = (data ? (current_value | (1 << bit_index)) : (current_value & ~(1 << bit_index)));

    return send_message(outgoing_msg_buf, 2);
}
