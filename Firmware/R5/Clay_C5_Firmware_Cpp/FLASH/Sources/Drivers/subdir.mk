################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/ESP8266.c" \
"../Sources/Drivers/LEDs.c" \
"../Sources/Drivers/MPU9250.c" \
"../Sources/Drivers/PCA9552.c" \
"../Sources/Drivers/mpu_9250_driver.c" \
"../Sources/Drivers/program_flash.c" \

C_SRCS += \
../Sources/Drivers/ESP8266.c \
../Sources/Drivers/LEDs.c \
../Sources/Drivers/MPU9250.c \
../Sources/Drivers/PCA9552.c \
../Sources/Drivers/mpu_9250_driver.c \
../Sources/Drivers/program_flash.c \

OBJS += \
./Sources/Drivers/ESP8266.o \
./Sources/Drivers/LEDs.o \
./Sources/Drivers/MPU9250.o \
./Sources/Drivers/PCA9552.o \
./Sources/Drivers/mpu_9250_driver.o \
./Sources/Drivers/program_flash.o \

OBJS_QUOTED += \
"./Sources/Drivers/ESP8266.o" \
"./Sources/Drivers/LEDs.o" \
"./Sources/Drivers/MPU9250.o" \
"./Sources/Drivers/PCA9552.o" \
"./Sources/Drivers/mpu_9250_driver.o" \
"./Sources/Drivers/program_flash.o" \

C_DEPS += \
./Sources/Drivers/ESP8266.d \
./Sources/Drivers/LEDs.d \
./Sources/Drivers/MPU9250.d \
./Sources/Drivers/PCA9552.d \
./Sources/Drivers/mpu_9250_driver.d \
./Sources/Drivers/program_flash.d \

C_DEPS_QUOTED += \
"./Sources/Drivers/ESP8266.d" \
"./Sources/Drivers/LEDs.d" \
"./Sources/Drivers/MPU9250.d" \
"./Sources/Drivers/PCA9552.d" \
"./Sources/Drivers/mpu_9250_driver.d" \
"./Sources/Drivers/program_flash.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/ESP8266.o \
./Sources/Drivers/LEDs.o \
./Sources/Drivers/MPU9250.o \
./Sources/Drivers/PCA9552.o \
./Sources/Drivers/mpu_9250_driver.o \
./Sources/Drivers/program_flash.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/ESP8266.o: ../Sources/Drivers/ESP8266.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/ESP8266.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/ESP8266.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/LEDs.o: ../Sources/Drivers/LEDs.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/LEDs.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/LEDs.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/MPU9250.o: ../Sources/Drivers/MPU9250.c
	@echo 'Building file: $<'
	@echo 'Executing target #36 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/MPU9250.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/MPU9250.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/PCA9552.o: ../Sources/Drivers/PCA9552.c
	@echo 'Building file: $<'
	@echo 'Executing target #37 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/PCA9552.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/PCA9552.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/mpu_9250_driver.o: ../Sources/Drivers/mpu_9250_driver.c
	@echo 'Building file: $<'
	@echo 'Executing target #38 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/mpu_9250_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/mpu_9250_driver.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/program_flash.o: ../Sources/Drivers/program_flash.c
	@echo 'Building file: $<'
	@echo 'Executing target #39 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/program_flash.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/program_flash.o"
	@echo 'Finished building: $<'
	@echo ' '


