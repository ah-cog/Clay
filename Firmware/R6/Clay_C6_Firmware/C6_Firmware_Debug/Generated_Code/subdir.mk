################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/ADC0.c \
../Generated_Code/ADC1.c \
../Generated_Code/BUTTON_IN.c \
../Generated_Code/BUZZER_PWM.c \
../Generated_Code/Cpu.c \
../Generated_Code/ESP8266_Serial.c \
../Generated_Code/FLASH1.c \
../Generated_Code/GPIO_PTB.c \
../Generated_Code/GPIO_PTC.c \
../Generated_Code/GPIO_PTE.c \
../Generated_Code/I2C0.c \
../Generated_Code/IMU_FSYNC.c \
../Generated_Code/IMU_IRQ.c \
../Generated_Code/LED1.c \
../Generated_Code/LED2.c \
../Generated_Code/LED_SDB.c \
../Generated_Code/MESH_CE.c \
../Generated_Code/MESH_CS.c \
../Generated_Code/MESH_IRQ.c \
../Generated_Code/MESH_SPI.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PWM_OUT_1.c \
../Generated_Code/PWM_OUT_3.c \
../Generated_Code/Pins1.c \
../Generated_Code/PowerOn.c \
../Generated_Code/TI1.c \
../Generated_Code/TU1.c \
../Generated_Code/WIFI_CHIP_EN.c \
../Generated_Code/WIFI_GPIO0.c \
../Generated_Code/WIFI_GPIO2.c \
../Generated_Code/WIFI_RESET.c \
../Generated_Code/WIFI_XPD_DCDC_INTERRUPT.c 

OBJS += \
./Generated_Code/ADC0.o \
./Generated_Code/ADC1.o \
./Generated_Code/BUTTON_IN.o \
./Generated_Code/BUZZER_PWM.o \
./Generated_Code/Cpu.o \
./Generated_Code/ESP8266_Serial.o \
./Generated_Code/FLASH1.o \
./Generated_Code/GPIO_PTB.o \
./Generated_Code/GPIO_PTC.o \
./Generated_Code/GPIO_PTE.o \
./Generated_Code/I2C0.o \
./Generated_Code/IMU_FSYNC.o \
./Generated_Code/IMU_IRQ.o \
./Generated_Code/LED1.o \
./Generated_Code/LED2.o \
./Generated_Code/LED_SDB.o \
./Generated_Code/MESH_CE.o \
./Generated_Code/MESH_CS.o \
./Generated_Code/MESH_IRQ.o \
./Generated_Code/MESH_SPI.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PWM_OUT_1.o \
./Generated_Code/PWM_OUT_3.o \
./Generated_Code/Pins1.o \
./Generated_Code/PowerOn.o \
./Generated_Code/TI1.o \
./Generated_Code/TU1.o \
./Generated_Code/WIFI_CHIP_EN.o \
./Generated_Code/WIFI_GPIO0.o \
./Generated_Code/WIFI_GPIO2.o \
./Generated_Code/WIFI_RESET.o \
./Generated_Code/WIFI_XPD_DCDC_INTERRUPT.o 

C_DEPS += \
./Generated_Code/ADC0.d \
./Generated_Code/ADC1.d \
./Generated_Code/BUTTON_IN.d \
./Generated_Code/BUZZER_PWM.d \
./Generated_Code/Cpu.d \
./Generated_Code/ESP8266_Serial.d \
./Generated_Code/FLASH1.d \
./Generated_Code/GPIO_PTB.d \
./Generated_Code/GPIO_PTC.d \
./Generated_Code/GPIO_PTE.d \
./Generated_Code/I2C0.d \
./Generated_Code/IMU_FSYNC.d \
./Generated_Code/IMU_IRQ.d \
./Generated_Code/LED1.d \
./Generated_Code/LED2.d \
./Generated_Code/LED_SDB.d \
./Generated_Code/MESH_CE.d \
./Generated_Code/MESH_CS.d \
./Generated_Code/MESH_IRQ.d \
./Generated_Code/MESH_SPI.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PWM_OUT_1.d \
./Generated_Code/PWM_OUT_3.d \
./Generated_Code/Pins1.d \
./Generated_Code/PowerOn.d \
./Generated_Code/TI1.d \
./Generated_Code/TU1.d \
./Generated_Code/WIFI_CHIP_EN.d \
./Generated_Code/WIFI_GPIO0.d \
./Generated_Code/WIFI_GPIO2.d \
./Generated_Code/WIFI_RESET.d \
./Generated_Code/WIFI_XPD_DCDC_INTERRUPT.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Battery" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Button" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Static_Code/System" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Static_Code/PDD" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Message" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Services" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Utilities" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Bootloader" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Generated_Code" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/RGB_LED" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/LEDs" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/I2C" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/WiFi" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Program_Flash_" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/IMU" -I"E:\git\clay\Firmware\R6\Clay_C6_Firmware\Sources\Drivers\IMU\libmplmpu\core\driver\include" -I"E:\git\clay\Firmware\R6\Clay_C6_Firmware\Sources\Drivers\IMU\libmplmpu\core\eMPL-hal" -I"E:\git\clay\Firmware\R6\Clay_C6_Firmware\Sources\Drivers\IMU\libmplmpu\core\mllite" -I"E:\git\clay\Firmware\R6\Clay_C6_Firmware\Sources\Drivers\IMU\libmplmpu\core\mpl" -I"E:\git\clay\Firmware\R6\Clay_C6_Firmware\Sources\Drivers\IMU\libmplmpu\core\driver\eMPL" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Buzzer" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/GPIO" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Clock" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Mesh" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Drivers/Power_Manager" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Services" -I"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Sources/Demo" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


