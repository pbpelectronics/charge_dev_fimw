################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/StdPeripheralDriver/src/misc.c \
../libs/StdPeripheralDriver/src/stm32f10x_adc.c \
../libs/StdPeripheralDriver/src/stm32f10x_bkp.c \
../libs/StdPeripheralDriver/src/stm32f10x_can.c \
../libs/StdPeripheralDriver/src/stm32f10x_cec.c \
../libs/StdPeripheralDriver/src/stm32f10x_crc.c \
../libs/StdPeripheralDriver/src/stm32f10x_dac.c \
../libs/StdPeripheralDriver/src/stm32f10x_dbgmcu.c \
../libs/StdPeripheralDriver/src/stm32f10x_dma.c \
../libs/StdPeripheralDriver/src/stm32f10x_exti.c \
../libs/StdPeripheralDriver/src/stm32f10x_flash.c \
../libs/StdPeripheralDriver/src/stm32f10x_fsmc.c \
../libs/StdPeripheralDriver/src/stm32f10x_gpio.c \
../libs/StdPeripheralDriver/src/stm32f10x_i2c.c \
../libs/StdPeripheralDriver/src/stm32f10x_iwdg.c \
../libs/StdPeripheralDriver/src/stm32f10x_pwr.c \
../libs/StdPeripheralDriver/src/stm32f10x_rcc.c \
../libs/StdPeripheralDriver/src/stm32f10x_rtc.c \
../libs/StdPeripheralDriver/src/stm32f10x_sdio.c \
../libs/StdPeripheralDriver/src/stm32f10x_spi.c \
../libs/StdPeripheralDriver/src/stm32f10x_tim.c \
../libs/StdPeripheralDriver/src/stm32f10x_usart.c \
../libs/StdPeripheralDriver/src/stm32f10x_wwdg.c 

OBJS += \
./libs/StdPeripheralDriver/src/misc.o \
./libs/StdPeripheralDriver/src/stm32f10x_adc.o \
./libs/StdPeripheralDriver/src/stm32f10x_bkp.o \
./libs/StdPeripheralDriver/src/stm32f10x_can.o \
./libs/StdPeripheralDriver/src/stm32f10x_cec.o \
./libs/StdPeripheralDriver/src/stm32f10x_crc.o \
./libs/StdPeripheralDriver/src/stm32f10x_dac.o \
./libs/StdPeripheralDriver/src/stm32f10x_dbgmcu.o \
./libs/StdPeripheralDriver/src/stm32f10x_dma.o \
./libs/StdPeripheralDriver/src/stm32f10x_exti.o \
./libs/StdPeripheralDriver/src/stm32f10x_flash.o \
./libs/StdPeripheralDriver/src/stm32f10x_fsmc.o \
./libs/StdPeripheralDriver/src/stm32f10x_gpio.o \
./libs/StdPeripheralDriver/src/stm32f10x_i2c.o \
./libs/StdPeripheralDriver/src/stm32f10x_iwdg.o \
./libs/StdPeripheralDriver/src/stm32f10x_pwr.o \
./libs/StdPeripheralDriver/src/stm32f10x_rcc.o \
./libs/StdPeripheralDriver/src/stm32f10x_rtc.o \
./libs/StdPeripheralDriver/src/stm32f10x_sdio.o \
./libs/StdPeripheralDriver/src/stm32f10x_spi.o \
./libs/StdPeripheralDriver/src/stm32f10x_tim.o \
./libs/StdPeripheralDriver/src/stm32f10x_usart.o \
./libs/StdPeripheralDriver/src/stm32f10x_wwdg.o 

C_DEPS += \
./libs/StdPeripheralDriver/src/misc.d \
./libs/StdPeripheralDriver/src/stm32f10x_adc.d \
./libs/StdPeripheralDriver/src/stm32f10x_bkp.d \
./libs/StdPeripheralDriver/src/stm32f10x_can.d \
./libs/StdPeripheralDriver/src/stm32f10x_cec.d \
./libs/StdPeripheralDriver/src/stm32f10x_crc.d \
./libs/StdPeripheralDriver/src/stm32f10x_dac.d \
./libs/StdPeripheralDriver/src/stm32f10x_dbgmcu.d \
./libs/StdPeripheralDriver/src/stm32f10x_dma.d \
./libs/StdPeripheralDriver/src/stm32f10x_exti.d \
./libs/StdPeripheralDriver/src/stm32f10x_flash.d \
./libs/StdPeripheralDriver/src/stm32f10x_fsmc.d \
./libs/StdPeripheralDriver/src/stm32f10x_gpio.d \
./libs/StdPeripheralDriver/src/stm32f10x_i2c.d \
./libs/StdPeripheralDriver/src/stm32f10x_iwdg.d \
./libs/StdPeripheralDriver/src/stm32f10x_pwr.d \
./libs/StdPeripheralDriver/src/stm32f10x_rcc.d \
./libs/StdPeripheralDriver/src/stm32f10x_rtc.d \
./libs/StdPeripheralDriver/src/stm32f10x_sdio.d \
./libs/StdPeripheralDriver/src/stm32f10x_spi.d \
./libs/StdPeripheralDriver/src/stm32f10x_tim.d \
./libs/StdPeripheralDriver/src/stm32f10x_usart.d \
./libs/StdPeripheralDriver/src/stm32f10x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
libs/StdPeripheralDriver/src/%.o: ../libs/StdPeripheralDriver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD_VL -I"D:\PROGRAMMING\stm\stm-discovery_test_project\libs\StdPeripheralDriver\inc" -I"D:\PROGRAMMING\stm\stm-discovery_test_project\libs\CMSIS" -Os -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g -ggdb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


