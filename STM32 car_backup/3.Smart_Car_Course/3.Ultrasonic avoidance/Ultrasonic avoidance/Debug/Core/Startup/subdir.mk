################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f103zetx.s 

OBJS += \
./Core/Startup/startup_stm32f103zetx.o 

S_DEPS += \
./Core/Startup/startup_stm32f103zetx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -DDEBUG -c -I"C:/Users/liang/Desktop/STM32_CAR源码汇总/stm32_car/1.Base_Course/2.Buzzer/Buzzer/Bsp/Buzzer" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f103zetx.d ./Core/Startup/startup_stm32f103zetx.o

.PHONY: clean-Core-2f-Startup

