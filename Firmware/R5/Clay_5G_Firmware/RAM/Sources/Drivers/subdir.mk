################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/ESP8266.c" \
"../Sources/Drivers/PCA9552.c" \

C_SRCS += \
../Sources/Drivers/ESP8266.c \
../Sources/Drivers/PCA9552.c \

OBJS += \
./Sources/Drivers/ESP8266.o \
./Sources/Drivers/PCA9552.o \

C_DEPS += \
./Sources/Drivers/ESP8266.d \
./Sources/Drivers/PCA9552.d \

OBJS_QUOTED += \
"./Sources/Drivers/ESP8266.o" \
"./Sources/Drivers/PCA9552.o" \

C_DEPS_QUOTED += \
"./Sources/Drivers/ESP8266.d" \
"./Sources/Drivers/PCA9552.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/ESP8266.o \
./Sources/Drivers/PCA9552.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/ESP8266.o: ../Sources/Drivers/ESP8266.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/ESP8266.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/ESP8266.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/PCA9552.o: ../Sources/Drivers/PCA9552.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/PCA9552.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/PCA9552.o"
	@echo 'Finished building: $<'
	@echo ' '


