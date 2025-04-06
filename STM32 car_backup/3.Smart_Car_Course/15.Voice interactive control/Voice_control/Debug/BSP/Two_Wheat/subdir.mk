################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/Two_Wheat/bsp_two_wheat.c 

OBJS += \
./BSP/Two_Wheat/bsp_two_wheat.o 

C_DEPS += \
./BSP/Two_Wheat/bsp_two_wheat.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/Two_Wheat/%.o BSP/Two_Wheat/%.su BSP/Two_Wheat/%.cyclo: ../BSP/Two_Wheat/%.c BSP/Two_Wheat/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../BSP/encoder -I../BSP/motor -I../BSP/tim -I../BSP -I../BSP/RGB -I../BSP/Two_Wheat -I../BSP/USART -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP-2f-Two_Wheat

clean-BSP-2f-Two_Wheat:
	-$(RM) ./BSP/Two_Wheat/bsp_two_wheat.cyclo ./BSP/Two_Wheat/bsp_two_wheat.d ./BSP/Two_Wheat/bsp_two_wheat.o ./BSP/Two_Wheat/bsp_two_wheat.su

.PHONY: clean-BSP-2f-Two_Wheat

