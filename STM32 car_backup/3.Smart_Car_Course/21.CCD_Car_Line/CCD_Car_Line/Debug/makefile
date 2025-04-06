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
-include BSP/tim/subdir.mk
-include BSP/motor/subdir.mk
-include BSP/encoder/subdir.mk
-include BSP/OLED/subdir.mk
-include BSP/Key/subdir.mk
-include BSP/CCD/subdir.mk
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


BUILD_ARTIFACT_NAME := CCD_Car_Line
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
CCD_Car_Line.elf \

MAP_FILES += \
CCD_Car_Line.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
CCD_Car_Line.list \

OBJCOPY_HEX += \
CCD_Car_Line.hex \


# All Target
all: main-build

# Main-build Target
main-build: CCD_Car_Line.elf secondary-outputs

# Tool invocations
CCD_Car_Line.elf CCD_Car_Line.map: $(OBJS) $(USER_OBJS) C:\Users\liang\Desktop\STM32_CAR源码汇总\stm32_car\3.Smart_Car_Course\21.CCD_Car_Line\CCD_Car_Line\STM32F103ZETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "CCD_Car_Line.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\liang\Desktop\STM32_CAR源码汇总\stm32_car\3.Smart_Car_Course\21.CCD_Car_Line\CCD_Car_Line\STM32F103ZETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="CCD_Car_Line.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

CCD_Car_Line.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "CCD_Car_Line.list"
	@echo 'Finished building: $@'
	@echo ' '

CCD_Car_Line.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "CCD_Car_Line.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) CCD_Car_Line.elf CCD_Car_Line.hex CCD_Car_Line.list CCD_Car_Line.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
