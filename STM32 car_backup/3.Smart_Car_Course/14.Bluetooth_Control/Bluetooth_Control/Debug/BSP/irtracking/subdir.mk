################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/irtracking/app_irtracking.c \
../BSP/irtracking/bsp_irtracking.c 

OBJS += \
./BSP/irtracking/app_irtracking.o \
./BSP/irtracking/bsp_irtracking.o 

C_DEPS += \
./BSP/irtracking/app_irtracking.d \
./BSP/irtracking/bsp_irtracking.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/irtracking/%.o BSP/irtracking/%.su BSP/irtracking/%.cyclo: ../BSP/irtracking/%.c BSP/irtracking/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../BSP/encoder -I../BSP/motor -I../BSP/tim -I../BSP -I../BSP/OLED -I../BSP/USART -I../BSP/Bluetooth -I../BSP/RGB -I../BSP/Buzzer -I../BSP/ultrasonic -I../BSP/VOL_detect -I../BSP/Iravoid -I../BSP/delay -I../BSP/irtracking -I../BSP/servo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP-2f-irtracking

clean-BSP-2f-irtracking:
	-$(RM) ./BSP/irtracking/app_irtracking.cyclo ./BSP/irtracking/app_irtracking.d ./BSP/irtracking/app_irtracking.o ./BSP/irtracking/app_irtracking.su ./BSP/irtracking/bsp_irtracking.cyclo ./BSP/irtracking/bsp_irtracking.d ./BSP/irtracking/bsp_irtracking.o ./BSP/irtracking/bsp_irtracking.su

.PHONY: clean-BSP-2f-irtracking

