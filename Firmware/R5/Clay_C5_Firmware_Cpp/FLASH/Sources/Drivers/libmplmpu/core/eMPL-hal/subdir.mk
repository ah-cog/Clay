################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/libmplmpu/core/eMPL-hal/eMPL_outputs.c" \

C_SRCS += \
../Sources/Drivers/libmplmpu/core/eMPL-hal/eMPL_outputs.c \

OBJS += \
./Sources/Drivers/libmplmpu/core/eMPL-hal/eMPL_outputs.o \

OBJS_QUOTED += \
"./Sources/Drivers/libmplmpu/core/eMPL-hal/eMPL_outputs.o" \

C_DEPS += \
./Sources/Drivers/libmplmpu/core/eMPL-hal/eMPL_outputs.d \

C_DEPS_QUOTED += \
"./Sources/Drivers/libmplmpu/core/eMPL-hal/eMPL_outputs.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/libmplmpu/core/eMPL-hal/eMPL_outputs.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/libmplmpu/core/eMPL-hal/eMPL_outputs.o: ../Sources/Drivers/libmplmpu/core/eMPL-hal/eMPL_outputs.c
	@echo 'Building file: $<'
	@echo 'Executing target #48 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/libmplmpu/core/eMPL-hal/eMPL_outputs.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/libmplmpu/core/eMPL-hal/eMPL_outputs.o"
	@echo 'Finished building: $<'
	@echo ' '


