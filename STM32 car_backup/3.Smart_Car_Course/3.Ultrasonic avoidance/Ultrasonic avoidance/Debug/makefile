################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include BSP/ultrasonic/subdir.mk
-include BSP/tim/subdir.mk
-include BSP/motor/subdir.mk
-include BSP/encoder/subdir.mk
-include BSP/delay/subdir.mk
-include BSP/USART/subdir.mk
-include BSP/RGB/subdir.mk
-include BSP/Buzzer/subdir.mk
-include BSP/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Ultrasonic avoidance
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Ultrasonic\ avoidance.elf \

MAP_FILES += \
Ultrasonic\ avoidance.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Ultrasonic\ avoidance.list \

OBJCOPY_HEX += \
Ultrasonic\ avoidance.hex \


# All Target
all: main-build

# Main-build Target
main-build: Ultrasonic\ avoidance.elf secondary-outputs

# Tool invocations
Ultrasonic\ avoidance.elf Ultrasonic\ avoidance.map: $(OBJS) $(USER_OBJS) C:\Users\liang\Desktop\STM32_CAR源码汇总\stm32_car\3.Smart_Car_Course\3.Ultrasonic\ avoidance\Ultrasonic\ avoidance\STM32F103ZETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Ultrasonic avoidance.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\liang\Desktop\STM32_CAR源码汇总\stm32_car\3.Smart_Car_Course\3.Ultrasonic avoidance\Ultrasonic avoidance\STM32F103ZETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Ultrasonic avoidance.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Ultrasonic\ avoidance.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Ultrasonic avoidance.list"
	@echo 'Finished building: $@'
	@echo ' '

Ultrasonic\ avoidance.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Ultrasonic avoidance.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Ultrasonic\ avoidance.elf Ultrasonic\ avoidance.hex Ultrasonic\ avoidance.list Ultrasonic\ avoidance.map Ultrasonic\\ avoidance.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
