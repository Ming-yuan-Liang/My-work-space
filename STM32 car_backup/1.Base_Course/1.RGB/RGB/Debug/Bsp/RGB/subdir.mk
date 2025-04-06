################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bsp/RGB/bsp_rgb.c 

OBJS += \
./Bsp/RGB/bsp_rgb.o 

C_DEPS += \
./Bsp/RGB/bsp_rgb.d 


# Each subdirectory must supply rules for building sources it contributes
Bsp/RGB/%.o Bsp/RGB/%.su Bsp/RGB/%.cyclo: ../Bsp/RGB/%.c Bsp/RGB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Bsp -I../Bsp/RGB -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Bsp-2f-RGB

clean-Bsp-2f-RGB:
	-$(RM) ./Bsp/RGB/bsp_rgb.cyclo ./Bsp/RGB/bsp_rgb.d ./Bsp/RGB/bsp_rgb.o ./Bsp/RGB/bsp_rgb.su

.PHONY: clean-Bsp-2f-RGB

