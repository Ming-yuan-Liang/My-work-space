################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/CCD/app_ccd.c \
../BSP/CCD/bsp_ccd.c 

OBJS += \
./BSP/CCD/app_ccd.o \
./BSP/CCD/bsp_ccd.o 

C_DEPS += \
./BSP/CCD/app_ccd.d \
./BSP/CCD/bsp_ccd.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/CCD/%.o BSP/CCD/%.su BSP/CCD/%.cyclo: ../BSP/CCD/%.c BSP/CCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../BSP/encoder -I../BSP/motor -I../BSP/tim -I../BSP -I../BSP/CCD -I../BSP/OLED -I../BSP/Key -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP-2f-CCD

clean-BSP-2f-CCD:
	-$(RM) ./BSP/CCD/app_ccd.cyclo ./BSP/CCD/app_ccd.d ./BSP/CCD/app_ccd.o ./BSP/CCD/app_ccd.su ./BSP/CCD/bsp_ccd.cyclo ./BSP/CCD/bsp_ccd.d ./BSP/CCD/bsp_ccd.o ./BSP/CCD/bsp_ccd.su

.PHONY: clean-BSP-2f-CCD

