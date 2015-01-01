################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/timers/subdir.mk
-include src/led/subdir.mk
-include src/encoder/subdir.mk
-include src/display/subdir.mk
-include src/common/subdir.mk
-include src/adc/subdir.mk
-include src/subdir.mk
-include libs/lcd_1100/subdir.mk
-include libs/StdPeripheralDriver/src/subdir.mk
-include libs/CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
stm-discovery_test_project.hex \

SECONDARY_LIST += \
stm-discovery_test_project.lst \

SECONDARY_SIZE += \
stm-discovery_test_project.siz \


# All Target
all: stm-discovery_test_project.elf secondary-outputs

# Tool invocations
stm-discovery_test_project.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"D:\PROGRAMMING\stm\stm-discovery_test_project\build\stm32f100rb.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,stm-discovery_test_project.map -mcpu=cortex-m3 -mthumb -g -ggdb -o "stm-discovery_test_project.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

stm-discovery_test_project.hex: stm-discovery_test_project.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary stm-discovery_test_project.elf  "stm-discovery_test_project.hex"
	@echo 'Finished building: $@'
	@echo ' '

stm-discovery_test_project.lst: stm-discovery_test_project.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S stm-discovery_test_project.elf > "stm-discovery_test_project.lst"
	@echo 'Finished building: $@'
	@echo ' '

stm-discovery_test_project.siz: stm-discovery_test_project.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley stm-discovery_test_project.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) stm-discovery_test_project.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
