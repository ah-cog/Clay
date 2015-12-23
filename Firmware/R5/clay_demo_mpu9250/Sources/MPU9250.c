/*
 * MPU9250.c
 *
 *  Created on: Aug 22, 2015
 *      Author: mokogobo
 */

#include "MPU9250.h"
#include "I2C2.h"

uint8_t buffer[14];

uint8_t MPU9250_ReadReg (uint8_t addr, uint8_t *data, short dataSize) {
  uint8_t res;
  
  /* Send I2C address plus register address to the I2C bus *without* a stop condition */
  res = I2C2_MasterSendBlock(deviceData.handle, &addr, 1U, LDD_I2C_NO_SEND_STOP);
  if (res!=ERR_OK) {
    return ERR_FAILED;
  }
  while (!deviceData.dataTransmittedFlg) {} /* Wait until data is sent */
  deviceData.dataTransmittedFlg = FALSE;

  /* Receive InpData (1 byte) from the I2C bus and generates a stop condition to end transmission */
  res = I2C2_MasterReceiveBlock(deviceData.handle, data, dataSize, LDD_I2C_SEND_STOP);
  if (res!=ERR_OK) {
	  return ERR_FAILED;
  }
  while (!deviceData.dataReceivedFlg) {} /* Wait until data is received received */
  deviceData.dataReceivedFlg = FALSE;
  return ERR_OK;
}

uint8_t MPU9250_WriteReg (uint8_t addr, uint8_t val) {
  uint8_t buf[2], res;

  buf[0] = addr;
  buf[1] = val;
	res = I2C2_MasterSendBlock(deviceData.handle, &buf, 2U, LDD_I2C_SEND_STOP); /* Send OutData (3 bytes with address) on the I2C bus and generates not a stop condition to end transmission */
	if (res!=ERR_OK) {
	  return ERR_FAILED;
	}
  while (!deviceData.dataTransmittedFlg) {}  /* Wait until date is sent */
	deviceData.dataTransmittedFlg = FALSE;
	return ERR_OK;
}

uint8_t mpu9250_read_bits (uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data, uint16_t timeout) {
    // 01101001 read byte
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    //    010   masked
    //   -> 010 shifted
    uint8_t count, b;
    if ((count = MPU9250_ReadReg (regAddr, &b, 1)) == ERR_OK) { // if ((count = readByte (devAddr, regAddr, &b, timeout)) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
    }
    return count;
}

uint8_t write_byte (uint8_t devAddr, uint8_t regAddr, uint8_t data) {
    MPU9250_WriteReg (MPU6050_DEFAULT_ADDRESS, data);
}

uint8_t mpu9250_write_bits (uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {
	
	//      010 value to write
	// 76543210 bit numbers
	//    xxx   args: bitStart=4, length=3
	// 00011100 mask byte
	// 10101111 original value (sample)
	// 10100011 original & ~mask
	// 10101011 masked | value
	uint8_t res;
	uint8_t b;
	res = MPU9250_ReadReg (regAddr, (uint8_t*) &b, 1);
	if (res == ERR_OK) {
	//if (readByte (devAddr, regAddr, &b) != 0) {
		uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
		data <<= (bitStart - length + 1); // shift data into correct position
		data &= mask; // zero all non-important bits in data
		b &= ~(mask); // zero all important bits in existing byte
		b |= data; // combine data with existing byte
		//return writeByte(devAddr, regAddr, b);
		return MPU9250_WriteReg (regAddr, b);
	} else {
		return FALSE;
	}
}

/** write a single bit in an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-7)
 * @param value New bit value to write
 * @return Status of operation (true = success)
 */
uint8_t mpu9250_write_bit (uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data) {

	uint8_t b;
	uint8_t res;
	res = MPU9250_ReadReg (regAddr, (uint8_t*) &b, 1);
	if (res == ERR_OK) {
		res = MPU9250_ReadReg (regAddr, (uint8_t*) &b, 1); // readByte(devAddr, regAddr, &b);
		b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
		return MPU9250_WriteReg (regAddr, b); // return writeByte(devAddr, regAddr, b);
	} else {
		return res;
	}
}

void mpu9250_initialize () {
	printf ("mpu9250_initialize\r\n");
	set_clock_source (MPU6050_CLOCK_PLL_XGYRO);
	set_full_scale_gyro_range (MPU6050_GYRO_FS_250);
	set_full_scale_accel_range (MPU6050_ACCEL_FS_2);
	set_sleep_enabled (FALSE);
}

void set_clock_source (uint8_t source) {
	printf ("set_clock_source\r\n");
	mpu9250_write_bits (MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
	//I2Cdev::writeBits(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}

void set_full_scale_gyro_range (uint8_t range) {
	printf ("set_full_scale_gyro_range\r\n");
	mpu9250_write_bits (MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

void set_full_scale_accel_range (uint8_t range) {
	printf ("mpu9250_write_bits\r\n");
	mpu9250_write_bits (MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

void set_sleep_enabled (uint8_t enabled) { // thanks to Jack Elston for pointing this one out!
	printf ("set_sleep_enabled\r\n");
	mpu9250_write_bit (MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}

void get_acceleration (int16_t* x, int16_t* y, int16_t* z) {
	
	uint8_t res = MPU9250_ReadReg (MPU6050_RA_ACCEL_XOUT_H, (uint8_t*) (&buffer), 6); // res = MPU9250_ReadReg(MPU9250_OUT_X_MSB, (uint8_t*)&xyz, 3);
	
    //I2Cdev::readBytes(devAddr, MPU6050_RA_ACCEL_XOUT_H, 6, buffer);
    *x = (((int16_t)buffer[0]) << 8) | buffer[1];
    *y = (((int16_t)buffer[2]) << 8) | buffer[3];
    *z = (((int16_t)buffer[4]) << 8) | buffer[5];
}

/** Get raw 6-axis motion sensor readings (accel/gyro).
 * Retrieves all currently available motion sensor values.
 * @param ax 16-bit signed integer container for accelerometer X-axis value
 * @param ay 16-bit signed integer container for accelerometer Y-axis value
 * @param az 16-bit signed integer container for accelerometer Z-axis value
 * @param gx 16-bit signed integer container for gyroscope X-axis value
 * @param gy 16-bit signed integer container for gyroscope Y-axis value
 * @param gz 16-bit signed integer container for gyroscope Z-axis value
 * @see getAcceleration()
 * @see getRotation()
 * @see MPU6050_RA_ACCEL_XOUT_H
 */
void mpu9250_get_motion_6 (int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz) {
	uint8_t res = MPU9250_ReadReg (MPU6050_RA_ACCEL_XOUT_H, (uint8_t*) (&buffer), 14); // I2Cdev::readBytes(devAddr, MPU6050_RA_ACCEL_XOUT_H, 14, buffer);
    *ax = (((int16_t)buffer[0]) << 8) | buffer[1];
    *ay = (((int16_t)buffer[2]) << 8) | buffer[3];
    *az = (((int16_t)buffer[4]) << 8) | buffer[5];
    *gx = (((int16_t)buffer[8]) << 8) | buffer[9];
    *gy = (((int16_t)buffer[10]) << 8) | buffer[11];
    *gz = (((int16_t)buffer[12]) << 8) | buffer[13];
}
