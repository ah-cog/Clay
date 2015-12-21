################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Events.c" \
"../Sources/crc.c" \
"../Sources/main.c" \
"../Sources/program_flash.c" \
"../Sources/system_tick.c" \

C_SRCS += \
../Sources/Events.c \
../Sources/crc.c \
../Sources/main.c \
../Sources/program_flash.c \
../Sources/system_tick.c \

OBJS += \
./Sources/Events.o \
./Sources/crc.o \
./Sources/main.o \
./Sources/program_flash.o \
./Sources/system_tick.o \

C_DEPS += \
./Sources/Events.d \
./Sources/crc.d \
./Sources/main.d \
./Sources/program_flash.d \
./Sources/system_tick.d \

OBJS_QUOTED += \
"./Sources/Events.o" \
"./Sources/crc.o" \
"./Sources/main.o" \
"./Sources/program_flash.o" \
"./Sources/system_tick.o" \

C_DEPS_QUOTED += \
"./Sources/Events.d" \
"./Sources/crc.d" \
"./Sources/main.d" \
"./Sources/program_flash.d" \
"./Sources/system_tick.d" \

OBJS_OS_FORMAT += \
./Sources/Events.o \
./Sources/crc.o \
./Sources/main.o \
./Sources/program_flash.o \
./Sources/system_tick.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Events.o: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Events.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Events.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/crc.o: ../Sources/crc.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/crc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/crc.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/program_flash.o: ../Sources/program_flash.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/program_flash.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/program_flash.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/system_tick.o: ../Sources/system_tick.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/system_tick.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/system_tick.o"
	@echo 'Finished building: $<'
	@echo ' '


