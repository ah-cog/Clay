################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 88
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Sources/Utilities/subdir.mk
-include Sources/RadioHead/subdir.mk
-include Sources/Drivers/subdir.mk
-include Sources/Drivers/libmplmpu/core/mllite/subdir.mk
-include Sources/Drivers/libmplmpu/core/eMPL-hal/subdir.mk
-include Sources/Drivers/libmplmpu/core/driver/eMPL/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Generated_Code/subdir.mk
-include .Analysis\ Data/subdir.mk
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
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
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
EXECUTABLES += \
Clay_5G_Firmware.elf \

EXECUTABLES_QUOTED += \
"Clay_5G_Firmware.elf" \

EXECUTABLES_OS_FORMAT += \
Clay_5G_Firmware.elf \

SECONDARY_FLASH += \
Clay_5G_Firmware.hex \

SECONDARY_FLASH_QUOTED += \
"Clay_5G_Firmware.hex" \

SECONDARY_FLASH_OS_FORMAT += \
Clay_5G_Firmware.hex \


# All Target
all: warning-messages explicit-dependencies Clay_5G_Firmware.elf secondary-outputs

# Tool invocations
Clay_5G_Firmware.elf: $(OBJS) $(USER_OBJS) ../Project_Settings/Linker_Files/ProcessorExpert.ld
	@echo 'Building target: $@'
	@echo 'Executing target #89 $@'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Linker'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++"  $(USER_OBJS_QUOTED)  @"Clay_5G_Firmware.args" -o"Clay_5G_Firmware.elf"
	@echo 'Finished building target: $@'
	@echo ' '

Clay_5G_Firmware.hex: Clay_5G_Firmware.elf
	@echo 'Executing target #90 $@'
	@echo 'Invoking: ARM Ltd Windows GNU Create Flash Image'
	"$(ARMSourceryDirEnv)/arm-none-eabi-objcopy"  -O binary Clay_5G_Firmware.elf "Clay_5G_Firmware.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) $(SECONDARY_FLASH_QUOTED) "./*/*.o" "./*/*/*.o" "./*/*/*/*/*/*/*.o" "./*/*/*/*/*/*.o"  "./*/*/*.d"  $(CC_DEPS_QUOTED) $(S_UPPER_DEPS_QUOTED) $(CXX_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(C_UPPER_DEPS_QUOTED) $(SX_DEPS_QUOTED) $(C++_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d" "./*/*/*.d" "./*/*/*/*/*/*/*.d" "./*/*/*/*/*/*.d"  $(ProjDirPath)/FLASH/Clay_5G_Firmware.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/ProcessorExpert.ld Clay_5G_Firmware.elf 

warning-messages: 

