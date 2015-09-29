################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Utilities/Ring_Buffer.c" \
"../Sources/Utilities/String.c" \

C_SRCS += \
../Sources/Utilities/Ring_Buffer.c \
../Sources/Utilities/String.c \

OBJS += \
./Sources/Utilities/Ring_Buffer.o \
./Sources/Utilities/String.o \

C_DEPS += \
./Sources/Utilities/Ring_Buffer.d \
./Sources/Utilities/String.d \

OBJS_QUOTED += \
"./Sources/Utilities/Ring_Buffer.o" \
"./Sources/Utilities/String.o" \

C_DEPS_QUOTED += \
"./Sources/Utilities/Ring_Buffer.d" \
"./Sources/Utilities/String.d" \

OBJS_OS_FORMAT += \
./Sources/Utilities/Ring_Buffer.o \
./Sources/Utilities/String.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Utilities/Ring_Buffer.o: ../Sources/Utilities/Ring_Buffer.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Utilities/Ring_Buffer.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Utilities/Ring_Buffer.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Utilities/String.o: ../Sources/Utilities/String.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Utilities/String.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Utilities/String.o"
	@echo 'Finished building: $<'
	@echo ' '


