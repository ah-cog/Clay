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
"../Generated_Code/ESP8266_XPD_DCDC.c" \
"../Generated_Code/PE_LDD.c" \
"../Generated_Code/TI1.c" \
"../Generated_Code/TU1.c" \
"../Generated_Code/Vectors.c" \

C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/ESP8266_CHIP_EN.c \
../Generated_Code/ESP8266_GPIO0.c \
../Generated_Code/ESP8266_GPIO2.c \
../Generated_Code/ESP8266_RST.c \
../Generated_Code/ESP8266_XPD_DCDC.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/TI1.c \
../Generated_Code/TU1.c \
../Generated_Code/Vectors.c \

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/ESP8266_CHIP_EN.o \
./Generated_Code/ESP8266_GPIO0.o \
./Generated_Code/ESP8266_GPIO2.o \
./Generated_Code/ESP8266_RST.o \
./Generated_Code/ESP8266_XPD_DCDC.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/TI1.o \
./Generated_Code/TU1.o \
./Generated_Code/Vectors.o \

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/ESP8266_CHIP_EN.d \
./Generated_Code/ESP8266_GPIO0.d \
./Generated_Code/ESP8266_GPIO2.d \
./Generated_Code/ESP8266_RST.d \
./Generated_Code/ESP8266_XPD_DCDC.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/TI1.d \
./Generated_Code/TU1.d \
./Generated_Code/Vectors.d \

OBJS_QUOTED += \
"./Generated_Code/Cpu.o" \
"./Generated_Code/ESP8266_CHIP_EN.o" \
"./Generated_Code/ESP8266_GPIO0.o" \
"./Generated_Code/ESP8266_GPIO2.o" \
"./Generated_Code/ESP8266_RST.o" \
"./Generated_Code/ESP8266_XPD_DCDC.o" \
"./Generated_Code/PE_LDD.o" \
"./Generated_Code/TI1.o" \
"./Generated_Code/TU1.o" \
"./Generated_Code/Vectors.o" \

C_DEPS_QUOTED += \
"./Generated_Code/Cpu.d" \
"./Generated_Code/ESP8266_CHIP_EN.d" \
"./Generated_Code/ESP8266_GPIO0.d" \
"./Generated_Code/ESP8266_GPIO2.d" \
"./Generated_Code/ESP8266_RST.d" \
"./Generated_Code/ESP8266_XPD_DCDC.d" \
"./Generated_Code/PE_LDD.d" \
"./Generated_Code/TI1.d" \
"./Generated_Code/TU1.d" \
"./Generated_Code/Vectors.d" \

OBJS_OS_FORMAT += \
./Generated_Code/Cpu.o \
./Generated_Code/ESP8266_CHIP_EN.o \
./Generated_Code/ESP8266_GPIO0.o \
./Generated_Code/ESP8266_GPIO2.o \
./Generated_Code/ESP8266_RST.o \
./Generated_Code/ESP8266_XPD_DCDC.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/TI1.o \
./Generated_Code/TU1.o \
./Generated_Code/Vectors.o \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/Cpu.o: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Cpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Cpu.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ESP8266_CHIP_EN.o: ../Generated_Code/ESP8266_CHIP_EN.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ESP8266_CHIP_EN.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ESP8266_CHIP_EN.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ESP8266_GPIO0.o: ../Generated_Code/ESP8266_GPIO0.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ESP8266_GPIO0.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ESP8266_GPIO0.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ESP8266_GPIO2.o: ../Generated_Code/ESP8266_GPIO2.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ESP8266_GPIO2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ESP8266_GPIO2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ESP8266_RST.o: ../Generated_Code/ESP8266_RST.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ESP8266_RST.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ESP8266_RST.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ESP8266_XPD_DCDC.o: ../Generated_Code/ESP8266_XPD_DCDC.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ESP8266_XPD_DCDC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ESP8266_XPD_DCDC.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_LDD.o: ../Generated_Code/PE_LDD.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PE_LDD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PE_LDD.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TI1.o: ../Generated_Code/TI1.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TI1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TI1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TU1.o: ../Generated_Code/TU1.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TU1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TU1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors.o: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Vectors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Vectors.o"
	@echo 'Finished building: $<'
	@echo ' '


