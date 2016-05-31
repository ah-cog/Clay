################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Application.c \
../Sources/Bootloader.c \
../Sources/Clock.c \
../Sources/Events.c \
../Sources/Message.c \
../Sources/Message_Queue.c \
../Sources/main.c 

OBJS += \
./Sources/Application.o \
./Sources/Bootloader.o \
./Sources/Clock.o \
./Sources/Events.o \
./Sources/Message.o \
./Sources/Message_Queue.o \
./Sources/main.o 

C_DEPS += \
./Sources/Application.d \
./Sources/Bootloader.d \
./Sources/Clock.d \
./Sources/Events.d \
./Sources/Message.d \
./Sources/Message_Queue.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Static_Code/System" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/LED" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/Program_Flash_" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/Button" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/Power_Manager" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/WiFi" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Utilities" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Static_Code/PDD" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Generated_Code" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


