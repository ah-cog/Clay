################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 23
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Generated_Code/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
clay_g5_demo_gpio.elf \

EXECUTABLES_QUOTED += \
"clay_g5_demo_gpio.elf" \

EXECUTABLES_OS_FORMAT += \
clay_g5_demo_gpio.elf \

SECONDARY_FLASH += \
clay_g5_demo_gpio.hex \

SECONDARY_FLASH_QUOTED += \
"clay_g5_demo_gpio.hex" \

SECONDARY_FLASH_OS_FORMAT += \
clay_g5_demo_gpio.hex \

SECONDARY_SIZE += \
clay_g5_demo_gpio.siz \

SECONDARY_SIZE_QUOTED += \
"clay_g5_demo_gpio.siz" \

SECONDARY_SIZE_OS_FORMAT += \
clay_g5_demo_gpio.siz \


# All Target
all: warning-messages explicit-dependencies clay_g5_demo_gpio.elf secondary-outputs

# Tool invocations
clay_g5_demo_gpio.elf: $(OBJS) $(USER_OBJS) ../Project_Settings/Linker_Files/ProcessorExpert.ld
	@echo 'Building target: $@'
	@echo 'Executing target #24 $@'
	@echo 'Invoking: ARM Ltd Windows GCC C Linker'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED) @"clay_g5_demo_gpio.args" -o"clay_g5_demo_gpio.elf"
	@echo 'Finished building target: $@'
	@echo ' '

clay_g5_demo_gpio.hex: clay_g5_demo_gpio.elf
	@echo 'Executing target #25 $@'
	@echo 'Invoking: ARM Ltd Windows GNU Create Flash Image'
	"$(ARMSourceryDirEnv)/arm-none-eabi-objcopy"  -O binary clay_g5_demo_gpio.elf "clay_g5_demo_gpio.hex"
	@echo 'Finished building: $@'
	@echo ' '

clay_g5_demo_gpio.siz: clay_g5_demo_gpio.elf
	@echo 'Executing target #26 $@'
	@echo 'Invoking: ARM Ltd Windows GNU Print Size'
	"$(ARMSourceryDirEnv)/arm-none-eabi-size"  --format=berkeley clay_g5_demo_gpio.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) $(SECONDARY_FLASH_QUOTED) "./*/*.o" "./*/*/*.o"  $(S_UPPER_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(SECONDARY_SIZE_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(SX_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d" "./*/*/*.d"  $(ProjDirPath)/FLASH/clay_g5_demo_gpio.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/ProcessorExpert.ld clay_g5_demo_gpio.elf clay_g5_demo_gpio.elf 

warning-messages: 

