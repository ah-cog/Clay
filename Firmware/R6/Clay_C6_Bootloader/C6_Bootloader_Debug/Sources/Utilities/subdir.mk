################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Utilities/Multibyte_Ring_Buffer.c \
../Sources/Utilities/Ring_Buffer.c \
../Sources/Utilities/UUID.c \
../Sources/Utilities/clayString.c 

OBJS += \
./Sources/Utilities/Multibyte_Ring_Buffer.o \
./Sources/Utilities/Ring_Buffer.o \
./Sources/Utilities/UUID.o \
./Sources/Utilities/clayString.o 

C_DEPS += \
./Sources/Utilities/Multibyte_Ring_Buffer.d \
./Sources/Utilities/Ring_Buffer.d \
./Sources/Utilities/UUID.d \
./Sources/Utilities/clayString.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Utilities/%.o: ../Sources/Utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Static_Code/System" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/Button" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/Power_Manager" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/WiFi" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Utilities" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Static_Code/PDD" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Generated_Code" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


