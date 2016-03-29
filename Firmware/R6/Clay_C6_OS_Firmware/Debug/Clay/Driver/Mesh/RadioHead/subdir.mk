################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Clay/Driver/Mesh/RadioHead/HardwareSPI.cpp \
../Clay/Driver/Mesh/RadioHead/HardwareSerial.cpp \
../Clay/Driver/Mesh/RadioHead/RHCRC.cpp \
../Clay/Driver/Mesh/RadioHead/RHDatagram.cpp \
../Clay/Driver/Mesh/RadioHead/RHGenericDriver.cpp \
../Clay/Driver/Mesh/RadioHead/RHGenericSPI.cpp \
../Clay/Driver/Mesh/RadioHead/RHHardwareSPI.cpp \
../Clay/Driver/Mesh/RadioHead/RHMesh.cpp \
../Clay/Driver/Mesh/RadioHead/RHNRFSPIDriver.cpp \
../Clay/Driver/Mesh/RadioHead/RHReliableDatagram.cpp \
../Clay/Driver/Mesh/RadioHead/RHRouter.cpp \
../Clay/Driver/Mesh/RadioHead/RHSPIDriver.cpp \
../Clay/Driver/Mesh/RadioHead/RHSoftwareSPI.cpp \
../Clay/Driver/Mesh/RadioHead/RH_NRF24.cpp \
../Clay/Driver/Mesh/RadioHead/RH_Serial.cpp \
../Clay/Driver/Mesh/RadioHead/RH_TCP.cpp \
../Clay/Driver/Mesh/RadioHead/wirish.cpp 

OBJS += \
./Clay/Driver/Mesh/RadioHead/HardwareSPI.o \
./Clay/Driver/Mesh/RadioHead/HardwareSerial.o \
./Clay/Driver/Mesh/RadioHead/RHCRC.o \
./Clay/Driver/Mesh/RadioHead/RHDatagram.o \
./Clay/Driver/Mesh/RadioHead/RHGenericDriver.o \
./Clay/Driver/Mesh/RadioHead/RHGenericSPI.o \
./Clay/Driver/Mesh/RadioHead/RHHardwareSPI.o \
./Clay/Driver/Mesh/RadioHead/RHMesh.o \
./Clay/Driver/Mesh/RadioHead/RHNRFSPIDriver.o \
./Clay/Driver/Mesh/RadioHead/RHReliableDatagram.o \
./Clay/Driver/Mesh/RadioHead/RHRouter.o \
./Clay/Driver/Mesh/RadioHead/RHSPIDriver.o \
./Clay/Driver/Mesh/RadioHead/RHSoftwareSPI.o \
./Clay/Driver/Mesh/RadioHead/RH_NRF24.o \
./Clay/Driver/Mesh/RadioHead/RH_Serial.o \
./Clay/Driver/Mesh/RadioHead/RH_TCP.o \
./Clay/Driver/Mesh/RadioHead/wirish.o 

CPP_DEPS += \
./Clay/Driver/Mesh/RadioHead/HardwareSPI.d \
./Clay/Driver/Mesh/RadioHead/HardwareSerial.d \
./Clay/Driver/Mesh/RadioHead/RHCRC.d \
./Clay/Driver/Mesh/RadioHead/RHDatagram.d \
./Clay/Driver/Mesh/RadioHead/RHGenericDriver.d \
./Clay/Driver/Mesh/RadioHead/RHGenericSPI.d \
./Clay/Driver/Mesh/RadioHead/RHHardwareSPI.d \
./Clay/Driver/Mesh/RadioHead/RHMesh.d \
./Clay/Driver/Mesh/RadioHead/RHNRFSPIDriver.d \
./Clay/Driver/Mesh/RadioHead/RHReliableDatagram.d \
./Clay/Driver/Mesh/RadioHead/RHRouter.d \
./Clay/Driver/Mesh/RadioHead/RHSPIDriver.d \
./Clay/Driver/Mesh/RadioHead/RHSoftwareSPI.d \
./Clay/Driver/Mesh/RadioHead/RH_NRF24.d \
./Clay/Driver/Mesh/RadioHead/RH_Serial.d \
./Clay/Driver/Mesh/RadioHead/RH_TCP.d \
./Clay/Driver/Mesh/RadioHead/wirish.d 


# Each subdirectory must supply rules for building sources it contributes
Clay/Driver/Mesh/RadioHead/%.o: ../Clay/Driver/Mesh/RadioHead/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MK64FN1M0VDC12" -DDEBUG -I../Clay/Driver/Clock -I../Clay/Driver/GPIO -I../Clay/Driver/Mesh -I../Clay/Utilities -I../Clay/Driver/Mesh/RadioHead -I../Clay/Driver/IMU -I../Clay/Driver/IMU/libmplmpu/core/driver/eMPL -I../Clay/Driver/IMU/libmplmpu/core/driver/include -I../Clay/Driver/IMU/libmplmpu/core/eMPL-hal -I../Clay/Driver/IMU/libmplmpu/core/mllite -I../Clay/Driver/IMU/libmplmpu/core/mpl -I../Clay/Driver/RGB_LED -I../freertos/Source/include -I../startup -I../board -I../utilities -I../freertos/Source/portable/GCC/ARM_CM4F -I../CMSIS -I../source -I../drivers -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


