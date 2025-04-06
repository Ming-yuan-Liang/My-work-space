################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/Iravoid/app_iravoid.c \
../BSP/Iravoid/bsp_iravoid.c 

OBJS += \
./BSP/Iravoid/app_iravoid.o \
./BSP/Iravoid/bsp_iravoid.o 

C_DEPS += \
./BSP/Iravoid/app_iravoid.d \
./BSP/Iravoid/bsp_iravoid.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/Iravoid/%.o BSP/Iravoid/%.su BSP/Iravoid/%.cyclo: ../BSP/Iravoid/%.c BSP/Iravoid/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../BSP/encoder -I../BSP/motor -I../BSP/tim -I../BSP -I../BSP/ultrasonic -I../BSP/delay -I../BSP/USART -I../BSP/Iravoid -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP-2f-Iravoid

clean-BSP-2f-Iravoid:
	-$(RM) ./BSP/Iravoid/app_iravoid.cyclo ./BSP/Iravoid/app_iravoid.d ./BSP/Iravoid/app_iravoid.o ./BSP/Iravoid/app_iravoid.su ./BSP/Iravoid/bsp_iravoid.cyclo ./BSP/Iravoid/bsp_iravoid.d ./BSP/Iravoid/bsp_iravoid.o ./BSP/Iravoid/bsp_iravoid.su

.PHONY: clean-BSP-2f-Iravoid

