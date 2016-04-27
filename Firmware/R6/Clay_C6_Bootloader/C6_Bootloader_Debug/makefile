################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Static_Code/System/subdir.mk
-include Sources/Utilities/subdir.mk
-include Sources/Drivers/program_flash/subdir.mk
-include Sources/Drivers/WiFi/subdir.mk
-include Sources/Drivers/Power_Manager/subdir.mk
-include Sources/Drivers/LED/subdir.mk
-include Sources/Drivers/Button/subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Generated_Code/subdir.mk
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
Clay_C6_Bootloader.bin \

SECONDARY_LIST += \
Clay_C6_Bootloader.lst \


# All Target
all: Clay_C6_Bootloader.elf secondary-outputs

# Tool invocations
Clay_C6_Bootloader.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Project_Settings/Linker_Files/clay_bootloader.ld" -Xlinker --gc-sections -L"E:/git/clay/Firmware/R6/Clay_C6_Bootloader/Project_Settings/Linker_Files" -Wl,-Map,"Clay_C6_Bootloader.map" -specs=nano.specs -specs=nosys.specs -o "Clay_C6_Bootloader.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Clay_C6_Bootloader.bin: Clay_C6_Bootloader.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "Clay_C6_Bootloader.elf"  "Clay_C6_Bootloader.bin"
	@echo 'Finished building: $@'
	@echo ' '

Clay_C6_Bootloader.lst: Clay_C6_Bootloader.elf
	@echo 'Invoking: Cross ARM GNU Create Listing'
	arm-none-eabi-objdump --source --all-headers --demangle --line-numbers --wide "Clay_C6_Bootloader.elf" > "Clay_C6_Bootloader.lst"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(SECONDARY_FLASH)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(SECONDARY_LIST)$(S_UPPER_DEPS) Clay_C6_Bootloader.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
