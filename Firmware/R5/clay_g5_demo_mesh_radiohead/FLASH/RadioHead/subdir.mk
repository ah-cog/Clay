################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../RadioHead/HardwareSPI.cpp \
../RadioHead/HardwareSerial.cpp \
../RadioHead/RHCRC.cpp \
../RadioHead/RHDatagram.cpp \
../RadioHead/RHGenericDriver.cpp \
../RadioHead/RHGenericSPI.cpp \
../RadioHead/RHHardwareSPI.cpp \
../RadioHead/RHMesh.cpp \
../RadioHead/RHNRFSPIDriver.cpp \
../RadioHead/RHReliableDatagram.cpp \
../RadioHead/RHRouter.cpp \
../RadioHead/RHSPIDriver.cpp \
../RadioHead/RHSoftwareSPI.cpp \
../RadioHead/RH_ASK.cpp \
../RadioHead/RH_NRF24.cpp \
../RadioHead/RH_Serial.cpp \
../RadioHead/RH_TCP.cpp \
../RadioHead/wirish.cpp \

CPP_SRCS_QUOTED += \
"../RadioHead/HardwareSPI.cpp" \
"../RadioHead/HardwareSerial.cpp" \
"../RadioHead/RHCRC.cpp" \
"../RadioHead/RHDatagram.cpp" \
"../RadioHead/RHGenericDriver.cpp" \
"../RadioHead/RHGenericSPI.cpp" \
"../RadioHead/RHHardwareSPI.cpp" \
"../RadioHead/RHMesh.cpp" \
"../RadioHead/RHNRFSPIDriver.cpp" \
"../RadioHead/RHReliableDatagram.cpp" \
"../RadioHead/RHRouter.cpp" \
"../RadioHead/RHSPIDriver.cpp" \
"../RadioHead/RHSoftwareSPI.cpp" \
"../RadioHead/RH_ASK.cpp" \
"../RadioHead/RH_NRF24.cpp" \
"../RadioHead/RH_Serial.cpp" \
"../RadioHead/RH_TCP.cpp" \
"../RadioHead/wirish.cpp" \

OBJS += \
./RadioHead/HardwareSPI.o \
./RadioHead/HardwareSerial.o \
./RadioHead/RHCRC.o \
./RadioHead/RHDatagram.o \
./RadioHead/RHGenericDriver.o \
./RadioHead/RHGenericSPI.o \
./RadioHead/RHHardwareSPI.o \
./RadioHead/RHMesh.o \
./RadioHead/RHNRFSPIDriver.o \
./RadioHead/RHReliableDatagram.o \
./RadioHead/RHRouter.o \
./RadioHead/RHSPIDriver.o \
./RadioHead/RHSoftwareSPI.o \
./RadioHead/RH_ASK.o \
./RadioHead/RH_NRF24.o \
./RadioHead/RH_Serial.o \
./RadioHead/RH_TCP.o \
./RadioHead/wirish.o \

OBJS_QUOTED += \
"./RadioHead/HardwareSPI.o" \
"./RadioHead/HardwareSerial.o" \
"./RadioHead/RHCRC.o" \
"./RadioHead/RHDatagram.o" \
"./RadioHead/RHGenericDriver.o" \
"./RadioHead/RHGenericSPI.o" \
"./RadioHead/RHHardwareSPI.o" \
"./RadioHead/RHMesh.o" \
"./RadioHead/RHNRFSPIDriver.o" \
"./RadioHead/RHReliableDatagram.o" \
"./RadioHead/RHRouter.o" \
"./RadioHead/RHSPIDriver.o" \
"./RadioHead/RHSoftwareSPI.o" \
"./RadioHead/RH_ASK.o" \
"./RadioHead/RH_NRF24.o" \
"./RadioHead/RH_Serial.o" \
"./RadioHead/RH_TCP.o" \
"./RadioHead/wirish.o" \

CPP_DEPS_QUOTED += \
"./RadioHead/HardwareSPI.d" \
"./RadioHead/HardwareSerial.d" \
"./RadioHead/RHCRC.d" \
"./RadioHead/RHDatagram.d" \
"./RadioHead/RHGenericDriver.d" \
"./RadioHead/RHGenericSPI.d" \
"./RadioHead/RHHardwareSPI.d" \
"./RadioHead/RHMesh.d" \
"./RadioHead/RHNRFSPIDriver.d" \
"./RadioHead/RHReliableDatagram.d" \
"./RadioHead/RHRouter.d" \
"./RadioHead/RHSPIDriver.d" \
"./RadioHead/RHSoftwareSPI.d" \
"./RadioHead/RH_ASK.d" \
"./RadioHead/RH_NRF24.d" \
"./RadioHead/RH_Serial.d" \
"./RadioHead/RH_TCP.d" \
"./RadioHead/wirish.d" \

CPP_DEPS += \
./RadioHead/HardwareSPI.d \
./RadioHead/HardwareSerial.d \
./RadioHead/RHCRC.d \
./RadioHead/RHDatagram.d \
./RadioHead/RHGenericDriver.d \
./RadioHead/RHGenericSPI.d \
./RadioHead/RHHardwareSPI.d \
./RadioHead/RHMesh.d \
./RadioHead/RHNRFSPIDriver.d \
./RadioHead/RHReliableDatagram.d \
./RadioHead/RHRouter.d \
./RadioHead/RHSPIDriver.d \
./RadioHead/RHSoftwareSPI.d \
./RadioHead/RH_ASK.d \
./RadioHead/RH_NRF24.d \
./RadioHead/RH_Serial.d \
./RadioHead/RH_TCP.d \
./RadioHead/wirish.d \

OBJS_OS_FORMAT += \
./RadioHead/HardwareSPI.o \
./RadioHead/HardwareSerial.o \
./RadioHead/RHCRC.o \
./RadioHead/RHDatagram.o \
./RadioHead/RHGenericDriver.o \
./RadioHead/RHGenericSPI.o \
./RadioHead/RHHardwareSPI.o \
./RadioHead/RHMesh.o \
./RadioHead/RHNRFSPIDriver.o \
./RadioHead/RHReliableDatagram.o \
./RadioHead/RHRouter.o \
./RadioHead/RHSPIDriver.o \
./RadioHead/RHSoftwareSPI.o \
./RadioHead/RH_ASK.o \
./RadioHead/RH_NRF24.o \
./RadioHead/RH_Serial.o \
./RadioHead/RH_TCP.o \
./RadioHead/wirish.o \


# Each subdirectory must supply rules for building sources it contributes
RadioHead/HardwareSPI.o: ../RadioHead/HardwareSPI.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/HardwareSPI.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/HardwareSPI.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/HardwareSerial.o: ../RadioHead/HardwareSerial.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/HardwareSerial.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/HardwareSerial.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RHCRC.o: ../RadioHead/RHCRC.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RHCRC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RHCRC.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RHDatagram.o: ../RadioHead/RHDatagram.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RHDatagram.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RHDatagram.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RHGenericDriver.o: ../RadioHead/RHGenericDriver.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RHGenericDriver.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RHGenericDriver.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RHGenericSPI.o: ../RadioHead/RHGenericSPI.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RHGenericSPI.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RHGenericSPI.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RHHardwareSPI.o: ../RadioHead/RHHardwareSPI.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RHHardwareSPI.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RHHardwareSPI.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RHMesh.o: ../RadioHead/RHMesh.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RHMesh.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RHMesh.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RHNRFSPIDriver.o: ../RadioHead/RHNRFSPIDriver.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RHNRFSPIDriver.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RHNRFSPIDriver.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RHReliableDatagram.o: ../RadioHead/RHReliableDatagram.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RHReliableDatagram.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RHReliableDatagram.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RHRouter.o: ../RadioHead/RHRouter.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RHRouter.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RHRouter.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RHSPIDriver.o: ../RadioHead/RHSPIDriver.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RHSPIDriver.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RHSPIDriver.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RHSoftwareSPI.o: ../RadioHead/RHSoftwareSPI.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RHSoftwareSPI.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RHSoftwareSPI.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RH_ASK.o: ../RadioHead/RH_ASK.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RH_ASK.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RH_ASK.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RH_NRF24.o: ../RadioHead/RH_NRF24.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RH_NRF24.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RH_NRF24.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RH_Serial.o: ../RadioHead/RH_Serial.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RH_Serial.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RH_Serial.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/RH_TCP.o: ../RadioHead/RH_TCP.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/RH_TCP.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/RH_TCP.o"
	@echo 'Finished building: $<'
	@echo ' '

RadioHead/wirish.o: ../RadioHead/wirish.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"RadioHead/wirish.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"RadioHead/wirish.o"
	@echo 'Finished building: $<'
	@echo ' '


