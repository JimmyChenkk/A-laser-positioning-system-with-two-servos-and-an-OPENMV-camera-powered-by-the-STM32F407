################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/SysTick.c \
../Core/Src/beep.c \
../Core/Src/key.c \
../Core/Src/led.c \
../Core/Src/main.c \
../Core/Src/servo.c \
../Core/Src/servopwm.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tftlcd.c \
../Core/Src/time.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/SysTick.o \
./Core/Src/beep.o \
./Core/Src/key.o \
./Core/Src/led.o \
./Core/Src/main.o \
./Core/Src/servo.o \
./Core/Src/servopwm.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tftlcd.o \
./Core/Src/time.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/SysTick.d \
./Core/Src/beep.d \
./Core/Src/key.d \
./Core/Src/led.d \
./Core/Src/main.d \
./Core/Src/servo.d \
./Core/Src/servopwm.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tftlcd.d \
./Core/Src/time.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/SysTick.cyclo ./Core/Src/SysTick.d ./Core/Src/SysTick.o ./Core/Src/SysTick.su ./Core/Src/beep.cyclo ./Core/Src/beep.d ./Core/Src/beep.o ./Core/Src/beep.su ./Core/Src/key.cyclo ./Core/Src/key.d ./Core/Src/key.o ./Core/Src/key.su ./Core/Src/led.cyclo ./Core/Src/led.d ./Core/Src/led.o ./Core/Src/led.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/servo.cyclo ./Core/Src/servo.d ./Core/Src/servo.o ./Core/Src/servo.su ./Core/Src/servopwm.cyclo ./Core/Src/servopwm.d ./Core/Src/servopwm.o ./Core/Src/servopwm.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tftlcd.cyclo ./Core/Src/tftlcd.d ./Core/Src/tftlcd.o ./Core/Src/tftlcd.su ./Core/Src/time.cyclo ./Core/Src/time.d ./Core/Src/time.o ./Core/Src/time.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

