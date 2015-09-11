#include "Application.h"
#include "I2C2.h"
#include "MPU9250.h"

int16_t ax, ay, az; // Accelerometer // unsigned short = unit16_t
int16_t gx, gy, gz; // Gyroscope     // unsigned short = unit16_t
int16_t mx, my, mz; // Magnetometer  // unsigned short = unit16_t

void APP_Run () {
  uint8_t res;
  
  deviceData.handle = I2C2_Init (&deviceData); // Initialize with the I2C device (e.g., MPU9250) with the address specified in Processor Expert.
  
  mpu9250_initialize ();
  
  /* F_READ: Fast read mode, data format limited to single byte (auto increment counter will skip LSB)
   * ACTIVE: Full scale selection
   */
  //     [ _ _ _ _ _ _ _ _ ]
  // MSB [ 7 6 5 4 3 2 1 0 ] LSB
  //                 ^ MPU6050_PWR1_CLKSEL_BIT    = 2
  //                   MPU6050_PWR1_CLKSEL_LENGTH = 3
  //     [ _ _ _ _ _[0 0 1]] (i.e., MPU6050_CLOCK_PLL_XGYRO = 0x01)
  //res = MPU9250_WriteReg (MPU6050_RA_PWR_MGMT_1, MPU6050_CLOCK_PLL_XGYRO); //res = MPU9250_WriteReg (MPU9250_CTRL_REG_1,  MPU9250_F_READ_BIT_MASK|MPU9250_ACTIVE_BIT_MASK);
//  if (res == ERR_OK) {
	  printf ("Starting\r\n");
    for(;;) {
    	//res = MPU9250_ReadReg(MPU6050_RA_WHO_AM_I, (uint8_t*) (&xyz), 1); // res = MPU9250_ReadReg(MPU9250_OUT_X_MSB, (uint8_t*)&xyz, 3);
//    	xyz[1] = '\0';
//    	printf ("MPU6050_RA_WHO_AM_I = 0x%1x\r\n", (uint8_t) (&xyz)[0]);
    	
    	//get_acceleration (&ax, &ay, &az);
    	mpu9250_get_motion_6 (&ax, &ay, &az, &gx, &gy, &gz);
    	
    	printf ("A: ax = %d, ay = %d, az = %d, gx = %d, gy = %d, gz = %d\r\n", ax, ay, az, gx, gy, gz);

//    	res = MPU9250_ReadReg (MPU6050_RA_GYRO_CONFIG, (uint8_t*)&xyz, 1); // res = MPU9250_ReadReg(MPU9250_OUT_X_MSB, (uint8_t*)&xyz, 3);
//    	xyz[1] = '\0';
//    	printf ("MPU6050_RA_GYRO_CONFIG (before) = 0x%1x\r\n", (uint8_t) (&xyz)[0]);
//    	mpu9250_write_bits (0x00, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, MPU6050_GYRO_FS_250);
//    	res = MPU9250_ReadReg (MPU6050_RA_GYRO_CONFIG, (uint8_t*)&xyz, 1); // res = MPU9250_ReadReg(MPU9250_OUT_X_MSB, (uint8_t*)&xyz, 3);
//    	if (res == ERR_OK) {
//			xyz[1] = '\0';
//			printf ("MPU6050_RA_GYRO_CONFIG (after) = 0x%1x\r\n", (uint8_t) (&xyz)[0]);
//    	}
    }
//  }
  I2C2_Deinit(deviceData.handle);
}
