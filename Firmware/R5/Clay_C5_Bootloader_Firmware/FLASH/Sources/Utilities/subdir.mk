################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Utilities/Debug.c" \
"../Sources/Utilities/Ring_Buffer.c" \
"../Sources/Utilities/String.c" \
"../Sources/Utilities/UUID.c" \

C_SRCS += \
../Sources/Utilities/Debug.c \
../Sources/Utilities/Ring_Buffer.c \
../Sources/Utilities/String.c \
../Sources/Utilities/UUID.c \

OBJS += \
./Sources/Utilities/Debug.o \
./Sources/Utilities/Ring_Buffer.o \
./Sources/Utilities/String.o \
./Sources/Utilities/UUID.o \

C_DEPS += \
./Sources/Utilities/Debug.d \
./Sources/Utilities/Ring_Buffer.d \
./Sources/Utilities/String.d \
./Sources/Utilities/UUID.d \

OBJS_QUOTED += \
"./Sources/Utilities/Debug.o" \
"./Sources/Utilities/Ring_Buffer.o" \
"./Sources/Utilities/String.o" \
"./Sources/Utilities/UUID.o" \

C_DEPS_QUOTED += \
"./Sources/Utilities/Debug.d" \
"./Sources/Utilities/Ring_Buffer.d" \
"./Sources/Utilities/String.d" \
"./Sources/Utilities/UUID.d" \

OBJS_OS_FORMAT += \
./Sources/Utilities/Debug.o \
./Sources/Utilities/Ring_Buffer.o \
./Sources/Utilities/String.o \
./Sources/Utilities/UUID.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Utilities/Debug.o: ../Sources/Utilities/Debug.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Utilities/Debug.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Utilities/Debug.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Utilities/Ring_Buffer.o: ../Sources/Utilities/Ring_Buffer.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Utilities/Ring_Buffer.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Utilities/Ring_Buffer.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Utilities/String.o: ../Sources/Utilities/String.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Utilities/String.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Utilities/String.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Utilities/UUID.o: ../Sources/Utilities/UUID.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Utilities/UUID.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Utilities/UUID.o"
	@echo 'Finished building: $<'
	@echo ' '


