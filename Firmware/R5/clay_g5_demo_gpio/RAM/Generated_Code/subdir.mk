################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/Cpu.c" \
"../Generated_Code/IO1.c" \
"../Generated_Code/IO10.c" \
"../Generated_Code/IO11.c" \
"../Generated_Code/IO12.c" \
"../Generated_Code/IO2.c" \
"../Generated_Code/IO3.c" \
"../Generated_Code/IO4.c" \
"../Generated_Code/IO5.c" \
"../Generated_Code/IO6.c" \
"../Generated_Code/IO7.c" \
"../Generated_Code/IO8.c" \
"../Generated_Code/IO9.c" \
"../Generated_Code/PE_LDD.c" \
"../Generated_Code/Vectors.c" \

C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/IO1.c \
../Generated_Code/IO10.c \
../Generated_Code/IO11.c \
../Generated_Code/IO12.c \
../Generated_Code/IO2.c \
../Generated_Code/IO3.c \
../Generated_Code/IO4.c \
../Generated_Code/IO5.c \
../Generated_Code/IO6.c \
../Generated_Code/IO7.c \
../Generated_Code/IO8.c \
../Generated_Code/IO9.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Vectors.c \

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/IO1.o \
./Generated_Code/IO10.o \
./Generated_Code/IO11.o \
./Generated_Code/IO12.o \
./Generated_Code/IO2.o \
./Generated_Code/IO3.o \
./Generated_Code/IO4.o \
./Generated_Code/IO5.o \
./Generated_Code/IO6.o \
./Generated_Code/IO7.o \
./Generated_Code/IO8.o \
./Generated_Code/IO9.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Vectors.o \

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/IO1.d \
./Generated_Code/IO10.d \
./Generated_Code/IO11.d \
./Generated_Code/IO12.d \
./Generated_Code/IO2.d \
./Generated_Code/IO3.d \
./Generated_Code/IO4.d \
./Generated_Code/IO5.d \
./Generated_Code/IO6.d \
./Generated_Code/IO7.d \
./Generated_Code/IO8.d \
./Generated_Code/IO9.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Vectors.d \

OBJS_QUOTED += \
"./Generated_Code/Cpu.o" \
"./Generated_Code/IO1.o" \
"./Generated_Code/IO10.o" \
"./Generated_Code/IO11.o" \
"./Generated_Code/IO12.o" \
"./Generated_Code/IO2.o" \
"./Generated_Code/IO3.o" \
"./Generated_Code/IO4.o" \
"./Generated_Code/IO5.o" \
"./Generated_Code/IO6.o" \
"./Generated_Code/IO7.o" \
"./Generated_Code/IO8.o" \
"./Generated_Code/IO9.o" \
"./Generated_Code/PE_LDD.o" \
"./Generated_Code/Vectors.o" \

C_DEPS_QUOTED += \
"./Generated_Code/Cpu.d" \
"./Generated_Code/IO1.d" \
"./Generated_Code/IO10.d" \
"./Generated_Code/IO11.d" \
"./Generated_Code/IO12.d" \
"./Generated_Code/IO2.d" \
"./Generated_Code/IO3.d" \
"./Generated_Code/IO4.d" \
"./Generated_Code/IO5.d" \
"./Generated_Code/IO6.d" \
"./Generated_Code/IO7.d" \
"./Generated_Code/IO8.d" \
"./Generated_Code/IO9.d" \
"./Generated_Code/PE_LDD.d" \
"./Generated_Code/Vectors.d" \

OBJS_OS_FORMAT += \
./Generated_Code/Cpu.o \
./Generated_Code/IO1.o \
./Generated_Code/IO10.o \
./Generated_Code/IO11.o \
./Generated_Code/IO12.o \
./Generated_Code/IO2.o \
./Generated_Code/IO3.o \
./Generated_Code/IO4.o \
./Generated_Code/IO5.o \
./Generated_Code/IO6.o \
./Generated_Code/IO7.o \
./Generated_Code/IO8.o \
./Generated_Code/IO9.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Vectors.o \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/Cpu.o: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Cpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Cpu.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO1.o: ../Generated_Code/IO1.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO10.o: ../Generated_Code/IO10.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO10.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO10.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO11.o: ../Generated_Code/IO11.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO11.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO11.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO12.o: ../Generated_Code/IO12.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO12.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO12.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO2.o: ../Generated_Code/IO2.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO3.o: ../Generated_Code/IO3.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO3.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO3.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO4.o: ../Generated_Code/IO4.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO4.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO4.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO5.o: ../Generated_Code/IO5.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO5.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO5.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO6.o: ../Generated_Code/IO6.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO6.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO6.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO7.o: ../Generated_Code/IO7.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO7.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO7.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO8.o: ../Generated_Code/IO8.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO8.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO8.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO9.o: ../Generated_Code/IO9.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO9.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO9.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_LDD.o: ../Generated_Code/PE_LDD.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PE_LDD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PE_LDD.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors.o: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Vectors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Vectors.o"
	@echo 'Finished building: $<'
	@echo ' '

