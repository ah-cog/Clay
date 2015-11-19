################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/main.cpp \

C_SRCS_QUOTED += \
"../Sources/Events.c" \
"../Sources/led_driver_pca9552.c" \
"../Sources/main.c" \
"../Sources/mpu_9250_driver.c" \
"../Sources/system_tick.c" \

C_SRCS += \
../Sources/Events.c \
../Sources/led_driver_pca9552.c \
../Sources/main.c \
../Sources/mpu_9250_driver.c \
../Sources/system_tick.c \

CPP_SRCS_QUOTED += \
"../Sources/main.cpp" \

OBJS += \
./Sources/Events.o \
./Sources/led_driver_pca9552.o \
./Sources/main_c.o \
./Sources/main_cpp.o \
./Sources/mpu_9250_driver.o \
./Sources/system_tick.o \

OBJS_QUOTED += \
"./Sources/Events.o" \
"./Sources/led_driver_pca9552.o" \
"./Sources/main_c.o" \
"./Sources/main_cpp.o" \
"./Sources/mpu_9250_driver.o" \
"./Sources/system_tick.o" \

CPP_DEPS_QUOTED += \
"./Sources/main_cpp.d" \

CPP_DEPS += \
./Sources/main_cpp.d \

C_DEPS += \
./Sources/Events.d \
./Sources/led_driver_pca9552.d \
./Sources/main_c.d \
./Sources/mpu_9250_driver.d \
./Sources/system_tick.d \

C_DEPS_QUOTED += \
"./Sources/Events.d" \
"./Sources/led_driver_pca9552.d" \
"./Sources/main_c.d" \
"./Sources/mpu_9250_driver.d" \
"./Sources/system_tick.d" \

OBJS_OS_FORMAT += \
./Sources/Events.o \
./Sources/led_driver_pca9552.o \
./Sources/main_c.o \
./Sources/main_cpp.o \
./Sources/mpu_9250_driver.o \
./Sources/system_tick.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Events.o: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Events.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Events.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/led_driver_pca9552.o: ../Sources/led_driver_pca9552.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/led_driver_pca9552.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/led_driver_pca9552.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main_c.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_cpp.o: ../Sources/main.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/main_1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main_cpp.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mpu_9250_driver.o: ../Sources/mpu_9250_driver.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/mpu_9250_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mpu_9250_driver.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/system_tick.o: ../Sources/system_tick.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/system_tick.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/system_tick.o"
	@echo 'Finished building: $<'
	@echo ' '


