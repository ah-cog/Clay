################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Drivers/WiFi/HTTP_Messages.c \
../Sources/Drivers/WiFi/WiFi.c \
../Sources/Drivers/WiFi/Wifi_Message_Serialization.c 

OBJS += \
./Sources/Drivers/WiFi/HTTP_Messages.o \
./Sources/Drivers/WiFi/WiFi.o \
./Sources/Drivers/WiFi/Wifi_Message_Serialization.o 

C_DEPS += \
./Sources/Drivers/WiFi/HTTP_Messages.d \
./Sources/Drivers/WiFi/WiFi.d \
./Sources/Drivers/WiFi/Wifi_Message_Serialization.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/WiFi/%.o: ../Sources/Drivers/WiFi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DDEBUG_APP=1 -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Static_Code/System" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/LED" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/Program_Flash_" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/Button" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/Power_Manager" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/WiFi" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Utilities" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Static_Code/PDD" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Generated_Code" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


