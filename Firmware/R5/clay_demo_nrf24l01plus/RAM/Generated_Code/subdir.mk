################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/BitIoLdd1.c" \
"../Generated_Code/BitIoLdd2.c" \
"../Generated_Code/CE.c" \
"../Generated_Code/CSN.c" \
"../Generated_Code/ExtIntLdd1.c" \
"../Generated_Code/IRQ.c" \
"../Generated_Code/PE_LDD.c" \
"../Generated_Code/SM1.c" \
"../Generated_Code/SMasterLdd1.c" \
"../Generated_Code/Tower.c" \
"../Generated_Code/Vectors.c" \
"../Generated_Code/WAIT1.c" \

C_SRCS += \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/CE.c \
../Generated_Code/CSN.c \
../Generated_Code/ExtIntLdd1.c \
../Generated_Code/IRQ.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/SM1.c \
../Generated_Code/SMasterLdd1.c \
../Generated_Code/Tower.c \
../Generated_Code/Vectors.c \
../Generated_Code/WAIT1.c \

OBJS += \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/CE.o \
./Generated_Code/CSN.o \
./Generated_Code/ExtIntLdd1.o \
./Generated_Code/IRQ.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/SM1.o \
./Generated_Code/SMasterLdd1.o \
./Generated_Code/Tower.o \
./Generated_Code/Vectors.o \
./Generated_Code/WAIT1.o \

C_DEPS += \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/CE.d \
./Generated_Code/CSN.d \
./Generated_Code/ExtIntLdd1.d \
./Generated_Code/IRQ.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/SM1.d \
./Generated_Code/SMasterLdd1.d \
./Generated_Code/Tower.d \
./Generated_Code/Vectors.d \
./Generated_Code/WAIT1.d \

OBJS_QUOTED += \
"./Generated_Code/BitIoLdd1.o" \
"./Generated_Code/BitIoLdd2.o" \
"./Generated_Code/CE.o" \
"./Generated_Code/CSN.o" \
"./Generated_Code/ExtIntLdd1.o" \
"./Generated_Code/IRQ.o" \
"./Generated_Code/PE_LDD.o" \
"./Generated_Code/SM1.o" \
"./Generated_Code/SMasterLdd1.o" \
"./Generated_Code/Tower.o" \
"./Generated_Code/Vectors.o" \
"./Generated_Code/WAIT1.o" \

C_DEPS_QUOTED += \
"./Generated_Code/BitIoLdd1.d" \
"./Generated_Code/BitIoLdd2.d" \
"./Generated_Code/CE.d" \
"./Generated_Code/CSN.d" \
"./Generated_Code/ExtIntLdd1.d" \
"./Generated_Code/IRQ.d" \
"./Generated_Code/PE_LDD.d" \
"./Generated_Code/SM1.d" \
"./Generated_Code/SMasterLdd1.d" \
"./Generated_Code/Tower.d" \
"./Generated_Code/Vectors.d" \
"./Generated_Code/WAIT1.d" \

OBJS_OS_FORMAT += \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/CE.o \
./Generated_Code/CSN.o \
./Generated_Code/ExtIntLdd1.o \
./Generated_Code/IRQ.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/SM1.o \
./Generated_Code/SMasterLdd1.o \
./Generated_Code/Tower.o \
./Generated_Code/Vectors.o \
./Generated_Code/WAIT1.o \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/BitIoLdd1.o: ../Generated_Code/BitIoLdd1.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/BitIoLdd1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/BitIoLdd1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/BitIoLdd2.o: ../Generated_Code/BitIoLdd2.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/BitIoLdd2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/BitIoLdd2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/CE.o: ../Generated_Code/CE.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/CE.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/CE.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/CSN.o: ../Generated_Code/CSN.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/CSN.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/CSN.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ExtIntLdd1.o: ../Generated_Code/ExtIntLdd1.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ExtIntLdd1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ExtIntLdd1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IRQ.o: ../Generated_Code/IRQ.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IRQ.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IRQ.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_LDD.o: ../Generated_Code/PE_LDD.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PE_LDD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PE_LDD.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/SM1.o: ../Generated_Code/SM1.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/SM1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/SM1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/SMasterLdd1.o: ../Generated_Code/SMasterLdd1.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/SMasterLdd1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/SMasterLdd1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Tower.o: ../Generated_Code/Tower.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Tower.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Tower.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors.o: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Vectors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Vectors.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/WAIT1.o: ../Generated_Code/WAIT1.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/WAIT1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/WAIT1.o"
	@echo 'Finished building: $<'
	@echo ' '


