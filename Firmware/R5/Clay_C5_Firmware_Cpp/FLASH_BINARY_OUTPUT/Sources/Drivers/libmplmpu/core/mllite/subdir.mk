################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/libmplmpu/core/mllite/data_builder.c" \
"../Sources/Drivers/libmplmpu/core/mllite/hal_outputs.c" \
"../Sources/Drivers/libmplmpu/core/mllite/message_layer.c" \
"../Sources/Drivers/libmplmpu/core/mllite/ml_math_func.c" \
"../Sources/Drivers/libmplmpu/core/mllite/mlmath.c" \
"../Sources/Drivers/libmplmpu/core/mllite/mpl.c" \
"../Sources/Drivers/libmplmpu/core/mllite/results_holder.c" \
"../Sources/Drivers/libmplmpu/core/mllite/start_manager.c" \
"../Sources/Drivers/libmplmpu/core/mllite/storage_manager.c" \

C_SRCS += \
../Sources/Drivers/libmplmpu/core/mllite/data_builder.c \
../Sources/Drivers/libmplmpu/core/mllite/hal_outputs.c \
../Sources/Drivers/libmplmpu/core/mllite/message_layer.c \
../Sources/Drivers/libmplmpu/core/mllite/ml_math_func.c \
../Sources/Drivers/libmplmpu/core/mllite/mlmath.c \
../Sources/Drivers/libmplmpu/core/mllite/mpl.c \
../Sources/Drivers/libmplmpu/core/mllite/results_holder.c \
../Sources/Drivers/libmplmpu/core/mllite/start_manager.c \
../Sources/Drivers/libmplmpu/core/mllite/storage_manager.c \

OBJS += \
./Sources/Drivers/libmplmpu/core/mllite/data_builder.o \
./Sources/Drivers/libmplmpu/core/mllite/hal_outputs.o \
./Sources/Drivers/libmplmpu/core/mllite/message_layer.o \
./Sources/Drivers/libmplmpu/core/mllite/ml_math_func.o \
./Sources/Drivers/libmplmpu/core/mllite/mlmath.o \
./Sources/Drivers/libmplmpu/core/mllite/mpl.o \
./Sources/Drivers/libmplmpu/core/mllite/results_holder.o \
./Sources/Drivers/libmplmpu/core/mllite/start_manager.o \
./Sources/Drivers/libmplmpu/core/mllite/storage_manager.o \

OBJS_QUOTED += \
"./Sources/Drivers/libmplmpu/core/mllite/data_builder.o" \
"./Sources/Drivers/libmplmpu/core/mllite/hal_outputs.o" \
"./Sources/Drivers/libmplmpu/core/mllite/message_layer.o" \
"./Sources/Drivers/libmplmpu/core/mllite/ml_math_func.o" \
"./Sources/Drivers/libmplmpu/core/mllite/mlmath.o" \
"./Sources/Drivers/libmplmpu/core/mllite/mpl.o" \
"./Sources/Drivers/libmplmpu/core/mllite/results_holder.o" \
"./Sources/Drivers/libmplmpu/core/mllite/start_manager.o" \
"./Sources/Drivers/libmplmpu/core/mllite/storage_manager.o" \

C_DEPS += \
./Sources/Drivers/libmplmpu/core/mllite/data_builder.d \
./Sources/Drivers/libmplmpu/core/mllite/hal_outputs.d \
./Sources/Drivers/libmplmpu/core/mllite/message_layer.d \
./Sources/Drivers/libmplmpu/core/mllite/ml_math_func.d \
./Sources/Drivers/libmplmpu/core/mllite/mlmath.d \
./Sources/Drivers/libmplmpu/core/mllite/mpl.d \
./Sources/Drivers/libmplmpu/core/mllite/results_holder.d \
./Sources/Drivers/libmplmpu/core/mllite/start_manager.d \
./Sources/Drivers/libmplmpu/core/mllite/storage_manager.d \

C_DEPS_QUOTED += \
"./Sources/Drivers/libmplmpu/core/mllite/data_builder.d" \
"./Sources/Drivers/libmplmpu/core/mllite/hal_outputs.d" \
"./Sources/Drivers/libmplmpu/core/mllite/message_layer.d" \
"./Sources/Drivers/libmplmpu/core/mllite/ml_math_func.d" \
"./Sources/Drivers/libmplmpu/core/mllite/mlmath.d" \
"./Sources/Drivers/libmplmpu/core/mllite/mpl.d" \
"./Sources/Drivers/libmplmpu/core/mllite/results_holder.d" \
"./Sources/Drivers/libmplmpu/core/mllite/start_manager.d" \
"./Sources/Drivers/libmplmpu/core/mllite/storage_manager.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/libmplmpu/core/mllite/data_builder.o \
./Sources/Drivers/libmplmpu/core/mllite/hal_outputs.o \
./Sources/Drivers/libmplmpu/core/mllite/message_layer.o \
./Sources/Drivers/libmplmpu/core/mllite/ml_math_func.o \
./Sources/Drivers/libmplmpu/core/mllite/mlmath.o \
./Sources/Drivers/libmplmpu/core/mllite/mpl.o \
./Sources/Drivers/libmplmpu/core/mllite/results_holder.o \
./Sources/Drivers/libmplmpu/core/mllite/start_manager.o \
./Sources/Drivers/libmplmpu/core/mllite/storage_manager.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/libmplmpu/core/mllite/data_builder.o: ../Sources/Drivers/libmplmpu/core/mllite/data_builder.c
	@echo 'Building file: $<'
	@echo 'Executing target #39 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/libmplmpu/core/mllite/data_builder.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/libmplmpu/core/mllite/data_builder.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/libmplmpu/core/mllite/hal_outputs.o: ../Sources/Drivers/libmplmpu/core/mllite/hal_outputs.c
	@echo 'Building file: $<'
	@echo 'Executing target #40 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/libmplmpu/core/mllite/hal_outputs.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/libmplmpu/core/mllite/hal_outputs.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/libmplmpu/core/mllite/message_layer.o: ../Sources/Drivers/libmplmpu/core/mllite/message_layer.c
	@echo 'Building file: $<'
	@echo 'Executing target #41 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/libmplmpu/core/mllite/message_layer.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/libmplmpu/core/mllite/message_layer.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/libmplmpu/core/mllite/ml_math_func.o: ../Sources/Drivers/libmplmpu/core/mllite/ml_math_func.c
	@echo 'Building file: $<'
	@echo 'Executing target #42 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/libmplmpu/core/mllite/ml_math_func.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/libmplmpu/core/mllite/ml_math_func.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/libmplmpu/core/mllite/mlmath.o: ../Sources/Drivers/libmplmpu/core/mllite/mlmath.c
	@echo 'Building file: $<'
	@echo 'Executing target #43 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/libmplmpu/core/mllite/mlmath.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/libmplmpu/core/mllite/mlmath.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/libmplmpu/core/mllite/mpl.o: ../Sources/Drivers/libmplmpu/core/mllite/mpl.c
	@echo 'Building file: $<'
	@echo 'Executing target #44 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/libmplmpu/core/mllite/mpl.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/libmplmpu/core/mllite/mpl.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/libmplmpu/core/mllite/results_holder.o: ../Sources/Drivers/libmplmpu/core/mllite/results_holder.c
	@echo 'Building file: $<'
	@echo 'Executing target #45 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/libmplmpu/core/mllite/results_holder.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/libmplmpu/core/mllite/results_holder.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/libmplmpu/core/mllite/start_manager.o: ../Sources/Drivers/libmplmpu/core/mllite/start_manager.c
	@echo 'Building file: $<'
	@echo 'Executing target #46 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/libmplmpu/core/mllite/start_manager.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/libmplmpu/core/mllite/start_manager.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/libmplmpu/core/mllite/storage_manager.o: ../Sources/Drivers/libmplmpu/core/mllite/storage_manager.c
	@echo 'Building file: $<'
	@echo 'Executing target #47 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/Drivers/libmplmpu/core/mllite/storage_manager.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/libmplmpu/core/mllite/storage_manager.o"
	@echo 'Finished building: $<'
	@echo ' '


