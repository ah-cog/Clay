################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu.c" \
"../Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu_dmp_motion_driver.c" \

C_SRCS += \
../Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu.c \
../Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu_dmp_motion_driver.c \

OBJS += \
./Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu.o \
./Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu_dmp_motion_driver.o \

OBJS_QUOTED += \
"./Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu.o" \
"./Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu_dmp_motion_driver.o" \

C_DEPS += \
./Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu.d \
./Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu_dmp_motion_driver.d \

C_DEPS_QUOTED += \
"./Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu.d" \
"./Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu_dmp_motion_driver.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu.o \
./Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu_dmp_motion_driver.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu.o: ../Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #50 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu_dmp_motion_driver.o: ../Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu_dmp_motion_driver.c
	@echo 'Building file: $<'
	@echo 'Executing target #51 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu_dmp_motion_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/libmplmpu/core/driver/eMPL/inv_mpu_dmp_motion_driver.o"
	@echo 'Finished building: $<'
	@echo ' '


