################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/tim/bsp_tim.c 

OBJS += \
./BSP/tim/bsp_tim.o 

C_DEPS += \
./BSP/tim/bsp_tim.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/tim/%.o BSP/tim/%.su BSP/tim/%.cyclo: ../BSP/tim/%.c BSP/tim/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../BSP/encoder -I../BSP/motor -I../BSP/tim -I../BSP -I../BSP/OLED -I../BSP/USART -I../BSP/Bluetooth -I../BSP/RGB -I../BSP/Buzzer -I../BSP/ultrasonic -I../BSP/VOL_detect -I../BSP/Iravoid -I../BSP/delay -I../BSP/irtracking -I../BSP/servo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP-2f-tim

clean-BSP-2f-tim:
	-$(RM) ./BSP/tim/bsp_tim.cyclo ./BSP/tim/bsp_tim.d ./BSP/tim/bsp_tim.o ./BSP/tim/bsp_tim.su

.PHONY: clean-BSP-2f-tim

