################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Settings/Startup_Code/startup.c 

OBJS += \
./Project_Settings/Startup_Code/startup.o 

C_DEPS += \
./Project_Settings/Startup_Code/startup.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Battery" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Button" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Static_Code/System" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Static_Code/PDD" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Message" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Services" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Utilities" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Bootloader" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Generated_Code" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/RGB_LED" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/LEDs" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/I2C" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/WiFi" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Program_Flash_" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/IMU" -I"E:\git\clay\Firmware\R6\Clay_C6_Firmware\Sources\Drivers\IMU\libmplmpu\core\driver\include" -I"E:\git\clay\Firmware\R6\Clay_C6_Firmware\Sources\Drivers\IMU\libmplmpu\core\eMPL-hal" -I"E:\git\clay\Firmware\R6\Clay_C6_Firmware\Sources\Drivers\IMU\libmplmpu\core\mllite" -I"E:\git\clay\Firmware\R6\Clay_C6_Firmware\Sources\Drivers\IMU\libmplmpu\core\mpl" -I"E:\git\clay\Firmware\R6\Clay_C6_Firmware\Sources\Drivers\IMU\libmplmpu\core\driver\eMPL" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Buzzer" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/GPIO" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Clock" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Mesh" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Power_Manager" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Services" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Demo" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


