################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/timers/timers.c 

OBJS += \
./src/timers/timers.o 

C_DEPS += \
./src/timers/timers.d 


# Each subdirectory must supply rules for building sources it contributes
src/timers/%.o: ../src/timers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD_VL -I"D:\PROGRAMMING\stm\stm-discovery_test_project\libs\StdPeripheralDriver\inc" -I"D:\PROGRAMMING\stm\stm-discovery_test_project\libs\CMSIS" -Os -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g -ggdb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


