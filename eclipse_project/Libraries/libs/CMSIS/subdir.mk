################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/CMSIS/core_cm3.c \
../libs/CMSIS/system_stm32f10x.c 

S_UPPER_SRCS += \
../libs/CMSIS/startup_stm32f10x_md_vl.S 

OBJS += \
./libs/CMSIS/core_cm3.o \
./libs/CMSIS/startup_stm32f10x_md_vl.o \
./libs/CMSIS/system_stm32f10x.o 

C_DEPS += \
./libs/CMSIS/core_cm3.d \
./libs/CMSIS/system_stm32f10x.d 

S_UPPER_DEPS += \
./libs/CMSIS/startup_stm32f10x_md_vl.d 


# Each subdirectory must supply rules for building sources it contributes
libs/CMSIS/%.o: ../libs/CMSIS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD_VL -I"D:\PROGRAMMING\stm\StdPeripheralDrivers\inc" -I"D:\PROGRAMMING\stm\stm-discovery_test_project\libs\CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g -ggdb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libs/CMSIS/%.o: ../libs/CMSIS/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g -ggdb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


