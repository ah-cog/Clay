################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Clay/Driver/Mesh/Mesh.cpp \
../Clay/Driver/Mesh/MeshTest.cpp \
../Clay/Driver/Mesh/mesh_statistics.cpp 

OBJS += \
./Clay/Driver/Mesh/Mesh.o \
./Clay/Driver/Mesh/MeshTest.o \
./Clay/Driver/Mesh/mesh_statistics.o 

CPP_DEPS += \
./Clay/Driver/Mesh/Mesh.d \
./Clay/Driver/Mesh/MeshTest.d \
./Clay/Driver/Mesh/mesh_statistics.d 


# Each subdirectory must supply rules for building sources it contributes
Clay/Driver/Mesh/%.o: ../Clay/Driver/Mesh/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MK64FN1M0VDC12" -DDEBUG -I../Clay/Driver/Clock -I../Clay/Driver/GPIO -I../Clay/Driver/Mesh -I../Clay/Utilities -I../Clay/Driver/Mesh/RadioHead -I../Clay/Driver/IMU -I../Clay/Driver/IMU/libmplmpu/core/driver/eMPL -I../Clay/Driver/IMU/libmplmpu/core/driver/include -I../Clay/Driver/IMU/libmplmpu/core/eMPL-hal -I../Clay/Driver/IMU/libmplmpu/core/mllite -I../Clay/Driver/IMU/libmplmpu/core/mpl -I../Clay/Driver/RGB_LED -I../freertos/Source/include -I../startup -I../board -I../utilities -I../freertos/Source/portable/GCC/ARM_CM4F -I../CMSIS -I../source -I../drivers -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


