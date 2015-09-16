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
"../Generated_Code/ESP8266_XPD_DCDC.c" \
"../Generated_Code/I2C0.c" \
"../Generated_Code/IO_1.c" \
"../Generated_Code/IO_10.c" \
"../Generated_Code/IO_11.c" \
"../Generated_Code/IO_12.c" \
"../Generated_Code/IO_2.c" \
"../Generated_Code/IO_3.c" \
"../Generated_Code/IO_4.c" \
"../Generated_Code/IO_5.c" \
"../Generated_Code/IO_6.c" \
"../Generated_Code/IO_7.c" \
"../Generated_Code/IO_8.c" \
"../Generated_Code/IO_9.c" \
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
../Generated_Code/ESP8266_XPD_DCDC.c \
../Generated_Code/I2C0.c \
../Generated_Code/IO_1.c \
../Generated_Code/IO_10.c \
../Generated_Code/IO_11.c \
../Generated_Code/IO_12.c \
../Generated_Code/IO_2.c \
../Generated_Code/IO_3.c \
../Generated_Code/IO_4.c \
../Generated_Code/IO_5.c \
../Generated_Code/IO_6.c \
../Generated_Code/IO_7.c \
../Generated_Code/IO_8.c \
../Generated_Code/IO_9.c \
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
./Generated_Code/ESP8266_XPD_DCDC.o \
./Generated_Code/I2C0.o \
./Generated_Code/IO_1.o \
./Generated_Code/IO_10.o \
./Generated_Code/IO_11.o \
./Generated_Code/IO_12.o \
./Generated_Code/IO_2.o \
./Generated_Code/IO_3.o \
./Generated_Code/IO_4.o \
./Generated_Code/IO_5.o \
./Generated_Code/IO_6.o \
./Generated_Code/IO_7.o \
./Generated_Code/IO_8.o \
./Generated_Code/IO_9.o \
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
./Generated_Code/ESP8266_XPD_DCDC.d \
./Generated_Code/I2C0.d \
./Generated_Code/IO_1.d \
./Generated_Code/IO_10.d \
./Generated_Code/IO_11.d \
./Generated_Code/IO_12.d \
./Generated_Code/IO_2.d \
./Generated_Code/IO_3.d \
./Generated_Code/IO_4.d \
./Generated_Code/IO_5.d \
./Generated_Code/IO_6.d \
./Generated_Code/IO_7.d \
./Generated_Code/IO_8.d \
./Generated_Code/IO_9.d \
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
"./Generated_Code/ESP8266_XPD_DCDC.o" \
"./Generated_Code/I2C0.o" \
"./Generated_Code/IO_1.o" \
"./Generated_Code/IO_10.o" \
"./Generated_Code/IO_11.o" \
"./Generated_Code/IO_12.o" \
"./Generated_Code/IO_2.o" \
"./Generated_Code/IO_3.o" \
"./Generated_Code/IO_4.o" \
"./Generated_Code/IO_5.o" \
"./Generated_Code/IO_6.o" \
"./Generated_Code/IO_7.o" \
"./Generated_Code/IO_8.o" \
"./Generated_Code/IO_9.o" \
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
"./Generated_Code/ESP8266_XPD_DCDC.d" \
"./Generated_Code/I2C0.d" \
"./Generated_Code/IO_1.d" \
"./Generated_Code/IO_10.d" \
"./Generated_Code/IO_11.d" \
"./Generated_Code/IO_12.d" \
"./Generated_Code/IO_2.d" \
"./Generated_Code/IO_3.d" \
"./Generated_Code/IO_4.d" \
"./Generated_Code/IO_5.d" \
"./Generated_Code/IO_6.d" \
"./Generated_Code/IO_7.d" \
"./Generated_Code/IO_8.d" \
"./Generated_Code/IO_9.d" \
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
./Generated_Code/ESP8266_XPD_DCDC.o \
./Generated_Code/I2C0.o \
./Generated_Code/IO_1.o \
./Generated_Code/IO_10.o \
./Generated_Code/IO_11.o \
./Generated_Code/IO_12.o \
./Generated_Code/IO_2.o \
./Generated_Code/IO_3.o \
./Generated_Code/IO_4.o \
./Generated_Code/IO_5.o \
./Generated_Code/IO_6.o \
./Generated_Code/IO_7.o \
./Generated_Code/IO_8.o \
./Generated_Code/IO_9.o \
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

Generated_Code/ESP8266_XPD_DCDC.o: ../Generated_Code/ESP8266_XPD_DCDC.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ESP8266_XPD_DCDC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ESP8266_XPD_DCDC.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/I2C0.o: ../Generated_Code/I2C0.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/I2C0.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/I2C0.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_1.o: ../Generated_Code/IO_1.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO_1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO_1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_10.o: ../Generated_Code/IO_10.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO_10.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO_10.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_11.o: ../Generated_Code/IO_11.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO_11.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO_11.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_12.o: ../Generated_Code/IO_12.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO_12.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO_12.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_2.o: ../Generated_Code/IO_2.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO_2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO_2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_3.o: ../Generated_Code/IO_3.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO_3.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO_3.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_4.o: ../Generated_Code/IO_4.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO_4.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO_4.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_5.o: ../Generated_Code/IO_5.c
	@echo 'Building file: $<'
	@echo 'Executing target #25 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO_5.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO_5.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_6.o: ../Generated_Code/IO_6.c
	@echo 'Building file: $<'
	@echo 'Executing target #26 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO_6.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO_6.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_7.o: ../Generated_Code/IO_7.c
	@echo 'Building file: $<'
	@echo 'Executing target #27 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO_7.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO_7.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_8.o: ../Generated_Code/IO_8.c
	@echo 'Building file: $<'
	@echo 'Executing target #28 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO_8.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO_8.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_9.o: ../Generated_Code/IO_9.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO_9.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO_9.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED_DRIVER_0_RESET.o: ../Generated_Code/LED_DRIVER_0_RESET.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/LED_DRIVER_0_RESET.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/LED_DRIVER_0_RESET.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED_DRIVER_1_RESET.o: ../Generated_Code/LED_DRIVER_1_RESET.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/LED_DRIVER_1_RESET.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/LED_DRIVER_1_RESET.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_LDD.o: ../Generated_Code/PE_LDD.c
	@echo 'Building file: $<'
	@echo 'Executing target #32 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PE_LDD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PE_LDD.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TU1.o: ../Generated_Code/TU1.c
	@echo 'Building file: $<'
	@echo 'Executing target #33 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TU1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TU1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Timer_1ms.o: ../Generated_Code/Timer_1ms.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Timer_1ms.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Timer_1ms.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors.o: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Vectors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Vectors.o"
	@echo 'Finished building: $<'
	@echo ' '


