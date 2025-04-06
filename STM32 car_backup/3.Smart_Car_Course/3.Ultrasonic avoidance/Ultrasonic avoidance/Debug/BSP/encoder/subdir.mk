################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/encoder/bsp_encoder.c 

OBJS += \
./BSP/encoder/bsp_encoder.o 

C_DEPS += \
./BSP/encoder/bsp_encoder.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/encoder/%.o BSP/encoder/%.su BSP/encoder/%.cyclo: ../BSP/encoder/%.c BSP/encoder/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../BSP/encoder -I../BSP/motor -I../BSP/tim -I../BSP -I../BSP/ultrasonic -I../BSP/delay -I../BSP/USART -I../BSP/Buzzer -I../BSP/RGB -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP-2f-encoder

clean-BSP-2f-encoder:
	-$(RM) ./BSP/encoder/bsp_encoder.cyclo ./BSP/encoder/bsp_encoder.d ./BSP/encoder/bsp_encoder.o ./BSP/encoder/bsp_encoder.su

.PHONY: clean-BSP-2f-encoder

