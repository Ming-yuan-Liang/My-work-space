################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/USART/bsp_usrt4.c 

OBJS += \
./BSP/USART/bsp_usrt4.o 

C_DEPS += \
./BSP/USART/bsp_usrt4.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/USART/%.o BSP/USART/%.su BSP/USART/%.cyclo: ../BSP/USART/%.c BSP/USART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../BSP/encoder -I../BSP/motor -I../BSP/tim -I../BSP -I../BSP/RGB -I../BSP/Two_Wheat -I../BSP/USART -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP-2f-USART

clean-BSP-2f-USART:
	-$(RM) ./BSP/USART/bsp_usrt4.cyclo ./BSP/USART/bsp_usrt4.d ./BSP/USART/bsp_usrt4.o ./BSP/USART/bsp_usrt4.su

.PHONY: clean-BSP-2f-USART

