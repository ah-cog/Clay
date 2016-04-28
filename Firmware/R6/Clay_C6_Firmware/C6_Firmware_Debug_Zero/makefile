################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Static_Code/System/subdir.mk
-include Sources/Utilities/subdir.mk
-include Sources/Services/subdir.mk
-include Sources/Drivers/WiFi/subdir.mk
-include Sources/Drivers/RGB_LED/subdir.mk
-include Sources/Drivers/Power_Manager/subdir.mk
-include Sources/Drivers/Mesh/subdir.mk
-include Sources/Drivers/LEDs/subdir.mk
-include Sources/Drivers/IMU/libmplmpu/core/mllite/subdir.mk
-include Sources/Drivers/IMU/libmplmpu/core/eMPL-hal/subdir.mk
-include Sources/Drivers/IMU/libmplmpu/core/driver/eMPL/subdir.mk
-include Sources/Drivers/IMU/subdir.mk
-include Sources/Drivers/I2C/subdir.mk
-include Sources/Drivers/GPIO/subdir.mk
-include Sources/Drivers/Clock/subdir.mk
-include Sources/Drivers/Buzzer/subdir.mk
-include Sources/Drivers/Button/subdir.mk
-include Sources/Demo/subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Generated_Code/subdir.mk
-include Debug/Static_Code/System/subdir.mk
-include Debug/Sources/Utilities/subdir.mk
-include Debug/Sources/Services/subdir.mk
-include Debug/Sources/Drivers/WiFi/subdir.mk
-include Debug/Sources/Drivers/RGB_LED/subdir.mk
-include Debug/Sources/Drivers/Power_Manager/subdir.mk
-include Debug/Sources/Drivers/Mesh/subdir.mk
-include Debug/Sources/Drivers/LEDs/subdir.mk
-include Debug/Sources/Drivers/IMU/libmplmpu/core/mllite/subdir.mk
-include Debug/Sources/Drivers/IMU/libmplmpu/core/eMPL-hal/subdir.mk
-include Debug/Sources/Drivers/IMU/libmplmpu/core/driver/eMPL/subdir.mk
-include Debug/Sources/Drivers/IMU/subdir.mk
-include Debug/Sources/Drivers/I2C/subdir.mk
-include Debug/Sources/Drivers/GPIO/subdir.mk
-include Debug/Sources/Drivers/Clock/subdir.mk
-include Debug/Sources/Drivers/Buzzer/subdir.mk
-include Debug/Sources/Drivers/Button/subdir.mk
-include Debug/Sources/Demo/subdir.mk
-include Debug/Sources/subdir.mk
-include Debug/Project_Settings/Startup_Code/subdir.mk
-include Debug/Generated_Code/subdir.mk
-include Debug/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Clay_C6_Firmware.bin \


# All Target
all: Clay_C6_Firmware.elf secondary-outputs

# Tool invocations
Clay_C6_Firmware.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "E:/git/clay/Firmware/R6/Clay_C6_Firmware/Project_Settings/Linker_Files/clay_debug_zero.ld" -Xlinker --gc-sections -L"E:/git/clay/Firmware/R6/Clay_C6_Firmware/Project_Settings/Linker_Files" -L"E:\git\clay\Firmware\R6\Clay_C6_Firmware\Sources\Drivers\IMU\libmplmpu\core\mpl" -Wl,-Map,"Clay_C6_Firmware.map" --specs=nano.specs -specs=nosys.specs -o "Clay_C6_Firmware.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Clay_C6_Firmware.bin: Clay_C6_Firmware.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "Clay_C6_Firmware.elf"  "Clay_C6_Firmware.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(SECONDARY_FLASH)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) Clay_C6_Firmware.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
