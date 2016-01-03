################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application.c" \
"../Sources/Behavior.c" \
"../Sources/Clock.c" \
"../Sources/Events.c" \
"../Sources/Events_ESP8266.c" \
"../Sources/GPIO.c" \
"../Sources/Mesh.c" \
"../Sources/Messenger.c" \
"../Sources/main.c" \
"../Sources/meshTest.c" \
"../Sources/mesh_statistics.c" \

C_SRCS += \
../Sources/Application.c \
../Sources/Behavior.c \
../Sources/Clock.c \
../Sources/Events.c \
../Sources/Events_ESP8266.c \
../Sources/GPIO.c \
../Sources/Mesh.c \
../Sources/Messenger.c \
../Sources/main.c \
../Sources/meshTest.c \
../Sources/mesh_statistics.c \

OBJS += \
./Sources/Application.o \
./Sources/Behavior.o \
./Sources/Clock.o \
./Sources/Events.o \
./Sources/Events_ESP8266.o \
./Sources/GPIO.o \
./Sources/Mesh.o \
./Sources/Messenger.o \
./Sources/main.o \
./Sources/meshTest.o \
./Sources/mesh_statistics.o \

OBJS_QUOTED += \
"./Sources/Application.o" \
"./Sources/Behavior.o" \
"./Sources/Clock.o" \
"./Sources/Events.o" \
"./Sources/Events_ESP8266.o" \
"./Sources/GPIO.o" \
"./Sources/Mesh.o" \
"./Sources/Messenger.o" \
"./Sources/main.o" \
"./Sources/meshTest.o" \
"./Sources/mesh_statistics.o" \

C_DEPS += \
./Sources/Application.d \
./Sources/Behavior.d \
./Sources/Clock.d \
./Sources/Events.d \
./Sources/Events_ESP8266.d \
./Sources/GPIO.d \
./Sources/Mesh.d \
./Sources/Messenger.d \
./Sources/main.d \
./Sources/meshTest.d \
./Sources/mesh_statistics.d \

C_DEPS_QUOTED += \
"./Sources/Application.d" \
"./Sources/Behavior.d" \
"./Sources/Clock.d" \
"./Sources/Events.d" \
"./Sources/Events_ESP8266.d" \
"./Sources/GPIO.d" \
"./Sources/Mesh.d" \
"./Sources/Messenger.d" \
"./Sources/main.d" \
"./Sources/meshTest.d" \
"./Sources/mesh_statistics.d" \

OBJS_OS_FORMAT += \
./Sources/Application.o \
./Sources/Behavior.o \
./Sources/Clock.o \
./Sources/Events.o \
./Sources/Events_ESP8266.o \
./Sources/GPIO.o \
./Sources/Mesh.o \
./Sources/Messenger.o \
./Sources/main.o \
./Sources/meshTest.o \
./Sources/mesh_statistics.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application.o: ../Sources/Application.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Application.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Behavior.o: ../Sources/Behavior.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Behavior.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Behavior.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Clock.o: ../Sources/Clock.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Clock.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Clock.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Events.o: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Events.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Events.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Events_ESP8266.o: ../Sources/Events_ESP8266.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Events_ESP8266.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Events_ESP8266.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/GPIO.o: ../Sources/GPIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/GPIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/GPIO.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Mesh.o: ../Sources/Mesh.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Mesh.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Mesh.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Messenger.o: ../Sources/Messenger.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Messenger.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Messenger.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/meshTest.o: ../Sources/meshTest.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/meshTest.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/meshTest.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mesh_statistics.o: ../Sources/mesh_statistics.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/mesh_statistics.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mesh_statistics.o"
	@echo 'Finished building: $<'
	@echo ' '


