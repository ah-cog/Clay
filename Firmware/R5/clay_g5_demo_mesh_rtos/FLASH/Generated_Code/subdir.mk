################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/BitIoLdd1.c" \
"../Generated_Code/BitIoLdd2.c" \
"../Generated_Code/CE1.c" \
"../Generated_Code/CSN1.c" \
"../Generated_Code/Cpu.c" \
"../Generated_Code/ExtIntLdd1.c" \
"../Generated_Code/FRTOS1.c" \
"../Generated_Code/I2C0.c" \
"../Generated_Code/IMU_CS.c" \
"../Generated_Code/IMU_FSYNC.c" \
"../Generated_Code/IMU_INT.c" \
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
"../Generated_Code/IRQ1.c" \
"../Generated_Code/LED1.c" \
"../Generated_Code/LED2.c" \
"../Generated_Code/LED_DRIVER_0_RESET.c" \
"../Generated_Code/LED_DRIVER_1_RESET.c" \
"../Generated_Code/PE_LDD.c" \
"../Generated_Code/RApp.c" \
"../Generated_Code/RF1.c" \
"../Generated_Code/RMAC.c" \
"../Generated_Code/RMSG.c" \
"../Generated_Code/RNET1.c" \
"../Generated_Code/RNWK.c" \
"../Generated_Code/RPHY.c" \
"../Generated_Code/RStack.c" \
"../Generated_Code/Radio.c" \
"../Generated_Code/SM1.c" \
"../Generated_Code/SMasterLdd1.c" \
"../Generated_Code/TU1.c" \
"../Generated_Code/UTIL1.c" \
"../Generated_Code/Vectors.c" \
"../Generated_Code/WAIT1.c" \
"../Generated_Code/croutine.c" \
"../Generated_Code/event_groups.c" \
"../Generated_Code/heap_1.c" \
"../Generated_Code/heap_2.c" \
"../Generated_Code/heap_3.c" \
"../Generated_Code/heap_4.c" \
"../Generated_Code/heap_5.c" \
"../Generated_Code/list.c" \
"../Generated_Code/port.c" \
"../Generated_Code/queue.c" \
"../Generated_Code/tasks.c" \
"../Generated_Code/tick_1ms_timer.c" \
"../Generated_Code/timers.c" \

C_SRCS += \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/CE1.c \
../Generated_Code/CSN1.c \
../Generated_Code/Cpu.c \
../Generated_Code/ExtIntLdd1.c \
../Generated_Code/FRTOS1.c \
../Generated_Code/I2C0.c \
../Generated_Code/IMU_CS.c \
../Generated_Code/IMU_FSYNC.c \
../Generated_Code/IMU_INT.c \
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
../Generated_Code/IRQ1.c \
../Generated_Code/LED1.c \
../Generated_Code/LED2.c \
../Generated_Code/LED_DRIVER_0_RESET.c \
../Generated_Code/LED_DRIVER_1_RESET.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/RApp.c \
../Generated_Code/RF1.c \
../Generated_Code/RMAC.c \
../Generated_Code/RMSG.c \
../Generated_Code/RNET1.c \
../Generated_Code/RNWK.c \
../Generated_Code/RPHY.c \
../Generated_Code/RStack.c \
../Generated_Code/Radio.c \
../Generated_Code/SM1.c \
../Generated_Code/SMasterLdd1.c \
../Generated_Code/TU1.c \
../Generated_Code/UTIL1.c \
../Generated_Code/Vectors.c \
../Generated_Code/WAIT1.c \
../Generated_Code/croutine.c \
../Generated_Code/event_groups.c \
../Generated_Code/heap_1.c \
../Generated_Code/heap_2.c \
../Generated_Code/heap_3.c \
../Generated_Code/heap_4.c \
../Generated_Code/heap_5.c \
../Generated_Code/list.c \
../Generated_Code/port.c \
../Generated_Code/queue.c \
../Generated_Code/tasks.c \
../Generated_Code/tick_1ms_timer.c \
../Generated_Code/timers.c \

S_SRCS += \
../Generated_Code/portasm.s \

S_SRCS_QUOTED += \
"../Generated_Code/portasm.s" \

S_DEPS_QUOTED += \
"./Generated_Code/portasm.d" \

OBJS += \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/CE1.o \
./Generated_Code/CSN1.o \
./Generated_Code/Cpu.o \
./Generated_Code/ExtIntLdd1.o \
./Generated_Code/FRTOS1.o \
./Generated_Code/I2C0.o \
./Generated_Code/IMU_CS.o \
./Generated_Code/IMU_FSYNC.o \
./Generated_Code/IMU_INT.o \
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
./Generated_Code/IRQ1.o \
./Generated_Code/LED1.o \
./Generated_Code/LED2.o \
./Generated_Code/LED_DRIVER_0_RESET.o \
./Generated_Code/LED_DRIVER_1_RESET.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/RApp.o \
./Generated_Code/RF1.o \
./Generated_Code/RMAC.o \
./Generated_Code/RMSG.o \
./Generated_Code/RNET1.o \
./Generated_Code/RNWK.o \
./Generated_Code/RPHY.o \
./Generated_Code/RStack.o \
./Generated_Code/Radio.o \
./Generated_Code/SM1.o \
./Generated_Code/SMasterLdd1.o \
./Generated_Code/TU1.o \
./Generated_Code/UTIL1.o \
./Generated_Code/Vectors.o \
./Generated_Code/WAIT1.o \
./Generated_Code/croutine.o \
./Generated_Code/event_groups.o \
./Generated_Code/heap_1.o \
./Generated_Code/heap_2.o \
./Generated_Code/heap_3.o \
./Generated_Code/heap_4.o \
./Generated_Code/heap_5.o \
./Generated_Code/list.o \
./Generated_Code/port.o \
./Generated_Code/portasm.o \
./Generated_Code/queue.o \
./Generated_Code/tasks.o \
./Generated_Code/tick_1ms_timer.o \
./Generated_Code/timers.o \

C_DEPS += \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/CE1.d \
./Generated_Code/CSN1.d \
./Generated_Code/Cpu.d \
./Generated_Code/ExtIntLdd1.d \
./Generated_Code/FRTOS1.d \
./Generated_Code/I2C0.d \
./Generated_Code/IMU_CS.d \
./Generated_Code/IMU_FSYNC.d \
./Generated_Code/IMU_INT.d \
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
./Generated_Code/IRQ1.d \
./Generated_Code/LED1.d \
./Generated_Code/LED2.d \
./Generated_Code/LED_DRIVER_0_RESET.d \
./Generated_Code/LED_DRIVER_1_RESET.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/RApp.d \
./Generated_Code/RF1.d \
./Generated_Code/RMAC.d \
./Generated_Code/RMSG.d \
./Generated_Code/RNET1.d \
./Generated_Code/RNWK.d \
./Generated_Code/RPHY.d \
./Generated_Code/RStack.d \
./Generated_Code/Radio.d \
./Generated_Code/SM1.d \
./Generated_Code/SMasterLdd1.d \
./Generated_Code/TU1.d \
./Generated_Code/UTIL1.d \
./Generated_Code/Vectors.d \
./Generated_Code/WAIT1.d \
./Generated_Code/croutine.d \
./Generated_Code/event_groups.d \
./Generated_Code/heap_1.d \
./Generated_Code/heap_2.d \
./Generated_Code/heap_3.d \
./Generated_Code/heap_4.d \
./Generated_Code/heap_5.d \
./Generated_Code/list.d \
./Generated_Code/port.d \
./Generated_Code/queue.d \
./Generated_Code/tasks.d \
./Generated_Code/tick_1ms_timer.d \
./Generated_Code/timers.d \

S_DEPS += \
./Generated_Code/portasm.d \

OBJS_QUOTED += \
"./Generated_Code/BitIoLdd1.o" \
"./Generated_Code/BitIoLdd2.o" \
"./Generated_Code/CE1.o" \
"./Generated_Code/CSN1.o" \
"./Generated_Code/Cpu.o" \
"./Generated_Code/ExtIntLdd1.o" \
"./Generated_Code/FRTOS1.o" \
"./Generated_Code/I2C0.o" \
"./Generated_Code/IMU_CS.o" \
"./Generated_Code/IMU_FSYNC.o" \
"./Generated_Code/IMU_INT.o" \
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
"./Generated_Code/IRQ1.o" \
"./Generated_Code/LED1.o" \
"./Generated_Code/LED2.o" \
"./Generated_Code/LED_DRIVER_0_RESET.o" \
"./Generated_Code/LED_DRIVER_1_RESET.o" \
"./Generated_Code/PE_LDD.o" \
"./Generated_Code/RApp.o" \
"./Generated_Code/RF1.o" \
"./Generated_Code/RMAC.o" \
"./Generated_Code/RMSG.o" \
"./Generated_Code/RNET1.o" \
"./Generated_Code/RNWK.o" \
"./Generated_Code/RPHY.o" \
"./Generated_Code/RStack.o" \
"./Generated_Code/Radio.o" \
"./Generated_Code/SM1.o" \
"./Generated_Code/SMasterLdd1.o" \
"./Generated_Code/TU1.o" \
"./Generated_Code/UTIL1.o" \
"./Generated_Code/Vectors.o" \
"./Generated_Code/WAIT1.o" \
"./Generated_Code/croutine.o" \
"./Generated_Code/event_groups.o" \
"./Generated_Code/heap_1.o" \
"./Generated_Code/heap_2.o" \
"./Generated_Code/heap_3.o" \
"./Generated_Code/heap_4.o" \
"./Generated_Code/heap_5.o" \
"./Generated_Code/list.o" \
"./Generated_Code/port.o" \
"./Generated_Code/portasm.o" \
"./Generated_Code/queue.o" \
"./Generated_Code/tasks.o" \
"./Generated_Code/tick_1ms_timer.o" \
"./Generated_Code/timers.o" \

C_DEPS_QUOTED += \
"./Generated_Code/BitIoLdd1.d" \
"./Generated_Code/BitIoLdd2.d" \
"./Generated_Code/CE1.d" \
"./Generated_Code/CSN1.d" \
"./Generated_Code/Cpu.d" \
"./Generated_Code/ExtIntLdd1.d" \
"./Generated_Code/FRTOS1.d" \
"./Generated_Code/I2C0.d" \
"./Generated_Code/IMU_CS.d" \
"./Generated_Code/IMU_FSYNC.d" \
"./Generated_Code/IMU_INT.d" \
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
"./Generated_Code/IRQ1.d" \
"./Generated_Code/LED1.d" \
"./Generated_Code/LED2.d" \
"./Generated_Code/LED_DRIVER_0_RESET.d" \
"./Generated_Code/LED_DRIVER_1_RESET.d" \
"./Generated_Code/PE_LDD.d" \
"./Generated_Code/RApp.d" \
"./Generated_Code/RF1.d" \
"./Generated_Code/RMAC.d" \
"./Generated_Code/RMSG.d" \
"./Generated_Code/RNET1.d" \
"./Generated_Code/RNWK.d" \
"./Generated_Code/RPHY.d" \
"./Generated_Code/RStack.d" \
"./Generated_Code/Radio.d" \
"./Generated_Code/SM1.d" \
"./Generated_Code/SMasterLdd1.d" \
"./Generated_Code/TU1.d" \
"./Generated_Code/UTIL1.d" \
"./Generated_Code/Vectors.d" \
"./Generated_Code/WAIT1.d" \
"./Generated_Code/croutine.d" \
"./Generated_Code/event_groups.d" \
"./Generated_Code/heap_1.d" \
"./Generated_Code/heap_2.d" \
"./Generated_Code/heap_3.d" \
"./Generated_Code/heap_4.d" \
"./Generated_Code/heap_5.d" \
"./Generated_Code/list.d" \
"./Generated_Code/port.d" \
"./Generated_Code/queue.d" \
"./Generated_Code/tasks.d" \
"./Generated_Code/tick_1ms_timer.d" \
"./Generated_Code/timers.d" \

OBJS_OS_FORMAT += \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/CE1.o \
./Generated_Code/CSN1.o \
./Generated_Code/Cpu.o \
./Generated_Code/ExtIntLdd1.o \
./Generated_Code/FRTOS1.o \
./Generated_Code/I2C0.o \
./Generated_Code/IMU_CS.o \
./Generated_Code/IMU_FSYNC.o \
./Generated_Code/IMU_INT.o \
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
./Generated_Code/IRQ1.o \
./Generated_Code/LED1.o \
./Generated_Code/LED2.o \
./Generated_Code/LED_DRIVER_0_RESET.o \
./Generated_Code/LED_DRIVER_1_RESET.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/RApp.o \
./Generated_Code/RF1.o \
./Generated_Code/RMAC.o \
./Generated_Code/RMSG.o \
./Generated_Code/RNET1.o \
./Generated_Code/RNWK.o \
./Generated_Code/RPHY.o \
./Generated_Code/RStack.o \
./Generated_Code/Radio.o \
./Generated_Code/SM1.o \
./Generated_Code/SMasterLdd1.o \
./Generated_Code/TU1.o \
./Generated_Code/UTIL1.o \
./Generated_Code/Vectors.o \
./Generated_Code/WAIT1.o \
./Generated_Code/croutine.o \
./Generated_Code/event_groups.o \
./Generated_Code/heap_1.o \
./Generated_Code/heap_2.o \
./Generated_Code/heap_3.o \
./Generated_Code/heap_4.o \
./Generated_Code/heap_5.o \
./Generated_Code/list.o \
./Generated_Code/port.o \
./Generated_Code/portasm.o \
./Generated_Code/queue.o \
./Generated_Code/tasks.o \
./Generated_Code/tick_1ms_timer.o \
./Generated_Code/timers.o \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/BitIoLdd1.o: ../Generated_Code/BitIoLdd1.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/BitIoLdd1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/BitIoLdd1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/BitIoLdd2.o: ../Generated_Code/BitIoLdd2.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/BitIoLdd2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/BitIoLdd2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/CE1.o: ../Generated_Code/CE1.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/CE1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/CE1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/CSN1.o: ../Generated_Code/CSN1.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/CSN1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/CSN1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Cpu.o: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Cpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Cpu.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ExtIntLdd1.o: ../Generated_Code/ExtIntLdd1.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ExtIntLdd1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ExtIntLdd1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/FRTOS1.o: ../Generated_Code/FRTOS1.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/FRTOS1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/FRTOS1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/I2C0.o: ../Generated_Code/I2C0.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/I2C0.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/I2C0.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IMU_CS.o: ../Generated_Code/IMU_CS.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IMU_CS.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IMU_CS.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IMU_FSYNC.o: ../Generated_Code/IMU_FSYNC.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IMU_FSYNC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IMU_FSYNC.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IMU_INT.o: ../Generated_Code/IMU_INT.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IMU_INT.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IMU_INT.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO1.o: ../Generated_Code/IO1.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO10.o: ../Generated_Code/IO10.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO10.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO10.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO11.o: ../Generated_Code/IO11.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO11.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO11.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO12.o: ../Generated_Code/IO12.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO12.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO12.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO2.o: ../Generated_Code/IO2.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO3.o: ../Generated_Code/IO3.c
	@echo 'Building file: $<'
	@echo 'Executing target #25 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO3.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO3.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO4.o: ../Generated_Code/IO4.c
	@echo 'Building file: $<'
	@echo 'Executing target #26 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO4.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO4.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO5.o: ../Generated_Code/IO5.c
	@echo 'Building file: $<'
	@echo 'Executing target #27 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO5.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO5.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO6.o: ../Generated_Code/IO6.c
	@echo 'Building file: $<'
	@echo 'Executing target #28 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO6.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO6.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO7.o: ../Generated_Code/IO7.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO7.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO7.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO8.o: ../Generated_Code/IO8.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO8.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO8.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO9.o: ../Generated_Code/IO9.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO9.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO9.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IRQ1.o: ../Generated_Code/IRQ1.c
	@echo 'Building file: $<'
	@echo 'Executing target #32 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IRQ1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IRQ1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED1.o: ../Generated_Code/LED1.c
	@echo 'Building file: $<'
	@echo 'Executing target #33 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/LED1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/LED1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED2.o: ../Generated_Code/LED2.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/LED2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/LED2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED_DRIVER_0_RESET.o: ../Generated_Code/LED_DRIVER_0_RESET.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/LED_DRIVER_0_RESET.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/LED_DRIVER_0_RESET.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED_DRIVER_1_RESET.o: ../Generated_Code/LED_DRIVER_1_RESET.c
	@echo 'Building file: $<'
	@echo 'Executing target #36 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/LED_DRIVER_1_RESET.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/LED_DRIVER_1_RESET.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_LDD.o: ../Generated_Code/PE_LDD.c
	@echo 'Building file: $<'
	@echo 'Executing target #37 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PE_LDD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PE_LDD.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/RApp.o: ../Generated_Code/RApp.c
	@echo 'Building file: $<'
	@echo 'Executing target #38 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/RApp.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/RApp.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/RF1.o: ../Generated_Code/RF1.c
	@echo 'Building file: $<'
	@echo 'Executing target #39 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/RF1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/RF1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/RMAC.o: ../Generated_Code/RMAC.c
	@echo 'Building file: $<'
	@echo 'Executing target #40 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/RMAC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/RMAC.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/RMSG.o: ../Generated_Code/RMSG.c
	@echo 'Building file: $<'
	@echo 'Executing target #41 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/RMSG.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/RMSG.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/RNET1.o: ../Generated_Code/RNET1.c
	@echo 'Building file: $<'
	@echo 'Executing target #42 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/RNET1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/RNET1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/RNWK.o: ../Generated_Code/RNWK.c
	@echo 'Building file: $<'
	@echo 'Executing target #43 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/RNWK.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/RNWK.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/RPHY.o: ../Generated_Code/RPHY.c
	@echo 'Building file: $<'
	@echo 'Executing target #44 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/RPHY.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/RPHY.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/RStack.o: ../Generated_Code/RStack.c
	@echo 'Building file: $<'
	@echo 'Executing target #45 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/RStack.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/RStack.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Radio.o: ../Generated_Code/Radio.c
	@echo 'Building file: $<'
	@echo 'Executing target #46 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Radio.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Radio.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/SM1.o: ../Generated_Code/SM1.c
	@echo 'Building file: $<'
	@echo 'Executing target #47 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/SM1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/SM1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/SMasterLdd1.o: ../Generated_Code/SMasterLdd1.c
	@echo 'Building file: $<'
	@echo 'Executing target #48 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/SMasterLdd1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/SMasterLdd1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TU1.o: ../Generated_Code/TU1.c
	@echo 'Building file: $<'
	@echo 'Executing target #49 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TU1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TU1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/UTIL1.o: ../Generated_Code/UTIL1.c
	@echo 'Building file: $<'
	@echo 'Executing target #50 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/UTIL1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/UTIL1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors.o: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #51 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Vectors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Vectors.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/WAIT1.o: ../Generated_Code/WAIT1.c
	@echo 'Building file: $<'
	@echo 'Executing target #52 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/WAIT1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/WAIT1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/croutine.o: ../Generated_Code/croutine.c
	@echo 'Building file: $<'
	@echo 'Executing target #53 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/croutine.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/croutine.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/event_groups.o: ../Generated_Code/event_groups.c
	@echo 'Building file: $<'
	@echo 'Executing target #54 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/event_groups.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/event_groups.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/heap_1.o: ../Generated_Code/heap_1.c
	@echo 'Building file: $<'
	@echo 'Executing target #55 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/heap_1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/heap_1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/heap_2.o: ../Generated_Code/heap_2.c
	@echo 'Building file: $<'
	@echo 'Executing target #56 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/heap_2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/heap_2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/heap_3.o: ../Generated_Code/heap_3.c
	@echo 'Building file: $<'
	@echo 'Executing target #57 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/heap_3.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/heap_3.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/heap_4.o: ../Generated_Code/heap_4.c
	@echo 'Building file: $<'
	@echo 'Executing target #58 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/heap_4.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/heap_4.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/heap_5.o: ../Generated_Code/heap_5.c
	@echo 'Building file: $<'
	@echo 'Executing target #59 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/heap_5.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/heap_5.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/list.o: ../Generated_Code/list.c
	@echo 'Building file: $<'
	@echo 'Executing target #60 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/list.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/list.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/port.o: ../Generated_Code/port.c
	@echo 'Building file: $<'
	@echo 'Executing target #61 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/port.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/port.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/portasm.o: ../Generated_Code/portasm.s
	@echo 'Building file: $<'
	@echo 'Executing target #62 $<'
	@echo 'Invoking: ARM Ltd Windows GCC Assembler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/portasm.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/portasm.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/queue.o: ../Generated_Code/queue.c
	@echo 'Building file: $<'
	@echo 'Executing target #63 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/queue.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/queue.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/tasks.o: ../Generated_Code/tasks.c
	@echo 'Building file: $<'
	@echo 'Executing target #64 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/tasks.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/tasks.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/tick_1ms_timer.o: ../Generated_Code/tick_1ms_timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #65 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/tick_1ms_timer.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/tick_1ms_timer.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/timers.o: ../Generated_Code/timers.c
	@echo 'Building file: $<'
	@echo 'Executing target #66 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/timers.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/timers.o"
	@echo 'Finished building: $<'
	@echo ' '


