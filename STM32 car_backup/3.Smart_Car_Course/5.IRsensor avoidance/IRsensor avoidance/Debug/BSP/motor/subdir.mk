################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/motor/app_motor.c \
../BSP/motor/bsp_PID_motor.c \
../BSP/motor/bsp_motor.c 

OBJS += \
./BSP/motor/app_motor.o \
./BSP/motor/bsp_PID_motor.o \
./BSP/motor/bsp_motor.o 

C_DEPS += \
./BSP/motor/app_motor.d \
./BSP/motor/bsp_PID_motor.d \
./BSP/motor/bsp_motor.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/motor/%.o BSP/motor/%.su BSP/motor/%.cyclo: ../BSP/motor/%.c BSP/motor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../BSP/encoder -I../BSP/motor -I../BSP/tim -I../BSP -I../BSP/ultrasonic -I../BSP/delay -I../BSP/USART -I../BSP/Iravoid -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP-2f-motor

clean-BSP-2f-motor:
	-$(RM) ./BSP/motor/app_motor.cyclo ./BSP/motor/app_motor.d ./BSP/motor/app_motor.o ./BSP/motor/app_motor.su ./BSP/motor/bsp_PID_motor.cyclo ./BSP/motor/bsp_PID_motor.d ./BSP/motor/bsp_PID_motor.o ./BSP/motor/bsp_PID_motor.su ./BSP/motor/bsp_motor.cyclo ./BSP/motor/bsp_motor.d ./BSP/motor/bsp_motor.o ./BSP/motor/bsp_motor.su

.PHONY: clean-BSP-2f-motor

