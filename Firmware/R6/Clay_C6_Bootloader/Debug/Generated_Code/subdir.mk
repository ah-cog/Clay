################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/BUTTON_IN.c \
../Generated_Code/Cpu.c \
../Generated_Code/ESP8266_Serial.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Pins1.c \
../Generated_Code/PowerOn.c \
../Generated_Code/TU1.c \
../Generated_Code/Timer_1ms.c \
../Generated_Code/WIFI_CHIP_EN.c \
../Generated_Code/WIFI_GPIO0.c \
../Generated_Code/WIFI_GPIO2.c \
../Generated_Code/WIFI_RESET.c \
../Generated_Code/WIFI_XPD_DCDC_INTERRUPT.c 

OBJS += \
./Generated_Code/BUTTON_IN.o \
./Generated_Code/Cpu.o \
./Generated_Code/ESP8266_Serial.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Pins1.o \
./Generated_Code/PowerOn.o \
./Generated_Code/TU1.o \
./Generated_Code/Timer_1ms.o \
./Generated_Code/WIFI_CHIP_EN.o \
./Generated_Code/WIFI_GPIO0.o \
./Generated_Code/WIFI_GPIO2.o \
./Generated_Code/WIFI_RESET.o \
./Generated_Code/WIFI_XPD_DCDC_INTERRUPT.o 

C_DEPS += \
./Generated_Code/BUTTON_IN.d \
./Generated_Code/Cpu.d \
./Generated_Code/ESP8266_Serial.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Pins1.d \
./Generated_Code/PowerOn.d \
./Generated_Code/TU1.d \
./Generated_Code/Timer_1ms.d \
./Generated_Code/WIFI_CHIP_EN.d \
./Generated_Code/WIFI_GPIO0.d \
./Generated_Code/WIFI_GPIO2.d \
./Generated_Code/WIFI_RESET.d \
./Generated_Code/WIFI_XPD_DCDC_INTERRUPT.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Static_Code/System" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/Button" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/Power_Manager" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Drivers/WiFi" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources/Utilities" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Static_Code/PDD" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Sources" -I"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


