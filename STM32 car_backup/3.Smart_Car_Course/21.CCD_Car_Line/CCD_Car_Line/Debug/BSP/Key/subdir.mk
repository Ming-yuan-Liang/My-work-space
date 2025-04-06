################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/Key/bsp_key.c 

OBJS += \
./BSP/Key/bsp_key.o 

C_DEPS += \
./BSP/Key/bsp_key.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/Key/%.o BSP/Key/%.su BSP/Key/%.cyclo: ../BSP/Key/%.c BSP/Key/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../BSP/encoder -I../BSP/motor -I../BSP/tim -I../BSP -I../BSP/CCD -I../BSP/OLED -I../BSP/Key -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP-2f-Key

clean-BSP-2f-Key:
	-$(RM) ./BSP/Key/bsp_key.cyclo ./BSP/Key/bsp_key.d ./BSP/Key/bsp_key.o ./BSP/Key/bsp_key.su

.PHONY: clean-BSP-2f-Key

