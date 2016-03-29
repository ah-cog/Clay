################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Clay/Driver/IMU/libmplmpu/core/mllite/data_builder.c \
../Clay/Driver/IMU/libmplmpu/core/mllite/hal_outputs.c \
../Clay/Driver/IMU/libmplmpu/core/mllite/message_layer.c \
../Clay/Driver/IMU/libmplmpu/core/mllite/ml_math_func.c \
../Clay/Driver/IMU/libmplmpu/core/mllite/mlmath.c \
../Clay/Driver/IMU/libmplmpu/core/mllite/mpl.c \
../Clay/Driver/IMU/libmplmpu/core/mllite/results_holder.c \
../Clay/Driver/IMU/libmplmpu/core/mllite/start_manager.c \
../Clay/Driver/IMU/libmplmpu/core/mllite/storage_manager.c 

OBJS += \
./Clay/Driver/IMU/libmplmpu/core/mllite/data_builder.o \
./Clay/Driver/IMU/libmplmpu/core/mllite/hal_outputs.o \
./Clay/Driver/IMU/libmplmpu/core/mllite/message_layer.o \
./Clay/Driver/IMU/libmplmpu/core/mllite/ml_math_func.o \
./Clay/Driver/IMU/libmplmpu/core/mllite/mlmath.o \
./Clay/Driver/IMU/libmplmpu/core/mllite/mpl.o \
./Clay/Driver/IMU/libmplmpu/core/mllite/results_holder.o \
./Clay/Driver/IMU/libmplmpu/core/mllite/start_manager.o \
./Clay/Driver/IMU/libmplmpu/core/mllite/storage_manager.o 

C_DEPS += \
./Clay/Driver/IMU/libmplmpu/core/mllite/data_builder.d \
./Clay/Driver/IMU/libmplmpu/core/mllite/hal_outputs.d \
./Clay/Driver/IMU/libmplmpu/core/mllite/message_layer.d \
./Clay/Driver/IMU/libmplmpu/core/mllite/ml_math_func.d \
./Clay/Driver/IMU/libmplmpu/core/mllite/mlmath.d \
./Clay/Driver/IMU/libmplmpu/core/mllite/mpl.d \
./Clay/Driver/IMU/libmplmpu/core/mllite/results_holder.d \
./Clay/Driver/IMU/libmplmpu/core/mllite/start_manager.d \
./Clay/Driver/IMU/libmplmpu/core/mllite/storage_manager.d 


# Each subdirectory must supply rules for building sources it contributes
Clay/Driver/IMU/libmplmpu/core/mllite/%.o: ../Clay/Driver/IMU/libmplmpu/core/mllite/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MK64FN1M0VDC12" -I../Clay/Driver/Button -I../Clay/Driver/Buzzer -I../Clay/Driver/Clock -I../Clay/Driver/GPIO -I../Clay/Driver/I2C -I../Clay/Driver/IMU -I../Clay/Driver/IMU/libmplmpu/core/driver/eMPL -I../Clay/Driver/IMU/libmplmpu/core/driver/include -I../Clay/Driver/IMU/libmplmpu/core/eMPL-hal -I../Clay/Driver/IMU/libmplmpu/core/mllite -I../Clay/Driver/IMU/libmplmpu/core/mpl -I../Clay/Driver/LEDs -I../Clay/Driver/Mesh -I../Clay/Driver/Mesh/RadioHead -I../Clay/Driver/Power_Manager -I../Clay/Driver/RGB_LED -I../Clay/Driver/WiFi -I../Clay/Application -I../Clay/Bootloader -I../Clay/Message -I../Clay/Utilities -I../freertos/Source/include -I../startup -I../board -I../utilities -I../freertos/Source/portable/GCC/ARM_CM4F -I../CMSIS -I../source -I../drivers -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


