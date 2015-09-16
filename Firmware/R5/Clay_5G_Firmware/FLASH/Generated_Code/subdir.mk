################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/Cpu.c" \
"../Generated_Code/ESP8266_CHIP_EN.c" \
"../Generated_Code/ESP8266_GPIO0.c" \
"../Generated_Code/ESP8266_GPIO2.c" \
"../Generated_Code/ESP8266_RST.c" \
"../Generated_Code/ESP8266_Serial.c" \
"../Generated_Code/I2C0.c" \
"../Generated_Code/LED_DRIVER_0_RESET.c" \
"../Generated_Code/LED_DRIVER_1_RESET.c" \
"../Generated_Code/PE_LDD.c" \
"../Generated_Code/TU1.c" \
"../Generated_Code/Timer_1ms.c" \
"../Generated_Code/Vectors.c" \

C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/ESP8266_CHIP_EN.c \
../Generated_Code/ESP8266_GPIO0.c \
../Generated_Code/ESP8266_GPIO2.c \
../Generated_Code/ESP8266_RST.c \
../Generated_Code/ESP8266_Serial.c \
../Generated_Code/I2C0.c \
../Generated_Code/LED_DRIVER_0_RESET.c \
../Generated_Code/LED_DRIVER_1_RESET.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/TU1.c \
../Generated_Code/Timer_1ms.c \
../Generated_Code/Vectors.c \

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/ESP8266_CHIP_EN.o \
./Generated_Code/ESP8266_GPIO0.o \
./Generated_Code/ESP8266_GPIO2.o \
./Generated_Code/ESP8266_RST.o \
./Generated_Code/ESP8266_Serial.o \
./Generated_Code/I2C0.o \
./Generated_Code/LED_DRIVER_0_RESET.o \
./Generated_Code/LED_DRIVER_1_RESET.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/TU1.o \
./Generated_Code/Timer_1ms.o \
./Generated_Code/Vectors.o \

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/ESP8266_CHIP_EN.d \
./Generated_Code/ESP8266_GPIO0.d \
./Generated_Code/ESP8266_GPIO2.d \
./Generated_Code/ESP8266_RST.d \
./Generated_Code/ESP8266_Serial.d \
./Generated_Code/I2C0.d \
./Generated_Code/LED_DRIVER_0_RESET.d \
./Generated_Code/LED_DRIVER_1_RESET.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/TU1.d \
./Generated_Code/Timer_1ms.d \
./Generated_Code/Vectors.d \

OBJS_QUOTED += \
"./Generated_Code/Cpu.o" \
"./Generated_Code/ESP8266_CHIP_EN.o" \
"./Generated_Code/ESP8266_GPIO0.o" \
"./Generated_Code/ESP8266_GPIO2.o" \
"./Generated_Code/ESP8266_RST.o" \
"./Generated_Code/ESP8266_Serial.o" \
"./Generated_Code/I2C0.o" \
"./Generated_Code/LED_DRIVER_0_RESET.o" \
"./Generated_Code/LED_DRIVER_1_RESET.o" \
"./Generated_Code/PE_LDD.o" \
"./Generated_Code/TU1.o" \
"./Generated_Code/Timer_1ms.o" \
"./Generated_Code/Vectors.o" \

C_DEPS_QUOTED += \
"./Generated_Code/Cpu.d" \
"./Generated_Code/ESP8266_CHIP_EN.d" \
"./Generated_Code/ESP8266_GPIO0.d" \
"./Generated_Code/ESP8266_GPIO2.d" \
"./Generated_Code/ESP8266_RST.d" \
"./Generated_Code/ESP8266_Serial.d" \
"./Generated_Code/I2C0.d" \
"./Generated_Code/LED_DRIVER_0_RESET.d" \
"./Generated_Code/LED_DRIVER_1_RESET.d" \
"./Generated_Code/PE_LDD.d" \
"./Generated_Code/TU1.d" \
"./Generated_Code/Timer_1ms.d" \
"./Generated_Code/Vectors.d" \

OBJS_OS_FORMAT += \
./Generated_Code/Cpu.o \
./Generated_Code/ESP8266_CHIP_EN.o \
./Generated_Code/ESP8266_GPIO0.o \
./Generated_Code/ESP8266_GPIO2.o \
./Generated_Code/ESP8266_RST.o \
./Generated_Code/ESP8266_Serial.o \
./Generated_Code/I2C0.o \
./Generated_Code/LED_DRIVER_0_RESET.o \
./Generated_Code/LED_DRIVER_1_RESET.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/TU1.o \
./Generated_Code/Timer_1ms.o \
./Generated_Code/Vectors.o \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/Cpu.o: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Cpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Cpu.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ESP8266_CHIP_EN.o: ../Generated_Code/ESP8266_CHIP_EN.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ESP8266_CHIP_EN.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ESP8266_CHIP_EN.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ESP8266_GPIO0.o: ../Generated_Code/ESP8266_GPIO0.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ESP8266_GPIO0.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ESP8266_GPIO0.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ESP8266_GPIO2.o: ../Generated_Code/ESP8266_GPIO2.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ESP8266_GPIO2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ESP8266_GPIO2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ESP8266_RST.o: ../Generated_Code/ESP8266_RST.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ESP8266_RST.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ESP8266_RST.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ESP8266_Serial.o: ../Generated_Code/ESP8266_Serial.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ESP8266_Serial.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ESP8266_Serial.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/I2C0.o: ../Generated_Code/I2C0.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/I2C0.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/I2C0.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED_DRIVER_0_RESET.o: ../Generated_Code/LED_DRIVER_0_RESET.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/LED_DRIVER_0_RESET.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/LED_DRIVER_0_RESET.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED_DRIVER_1_RESET.o: ../Generated_Code/LED_DRIVER_1_RESET.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/LED_DRIVER_1_RESET.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/LED_DRIVER_1_RESET.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_LDD.o: ../Generated_Code/PE_LDD.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PE_LDD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PE_LDD.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TU1.o: ../Generated_Code/TU1.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TU1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TU1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Timer_1ms.o: ../Generated_Code/Timer_1ms.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Timer_1ms.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Timer_1ms.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors.o: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Vectors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Vectors.o"
	@echo 'Finished building: $<'
	@echo ' '


