################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/lcd_1100/nokia1100_lcd_lib.c 

OBJS += \
./libs/lcd_1100/nokia1100_lcd_lib.o 

C_DEPS += \
./libs/lcd_1100/nokia1100_lcd_lib.d 


# Each subdirectory must supply rules for building sources it contributes
libs/lcd_1100/%.o: ../libs/lcd_1100/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD_VL -I"D:\PROGRAMMING\stm\stm-discovery_test_project\libs\StdPeripheralDriver\inc" -I"D:\PROGRAMMING\stm\stm-discovery_test_project\libs\lcd_1100" -I"D:\PROGRAMMING\stm\stm-discovery_test_project\libs\CMSIS" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -v -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g -ggdb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


