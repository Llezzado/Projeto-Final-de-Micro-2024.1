################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/I2C.c \
../Src/Oled.c \
../Src/Usart1_Bare_Metal_Custom_Lib.c \
../Src/dht11.c \
../Src/fonts.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/tim2.c 

OBJS += \
./Src/I2C.o \
./Src/Oled.o \
./Src/Usart1_Bare_Metal_Custom_Lib.o \
./Src/dht11.o \
./Src/fonts.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/tim2.o 

C_DEPS += \
./Src/I2C.d \
./Src/Oled.d \
./Src/Usart1_Bare_Metal_Custom_Lib.d \
./Src/dht11.d \
./Src/fonts.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/tim2.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB=STM32F103xB -c -I"/home/juan/STM32CubeIDE/workspace_1.15.1/Projeto micro modularizado/Inc" -I"/home/juan/STM32CubeIDE/workspace_1.15.1/Projeto micro modularizado/F1_Header/Device/ST/STM32F1xx/Include" -I"/home/juan/STM32CubeIDE/workspace_1.15.1/Projeto micro modularizado/F1_Header/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/I2C.cyclo ./Src/I2C.d ./Src/I2C.o ./Src/I2C.su ./Src/Oled.cyclo ./Src/Oled.d ./Src/Oled.o ./Src/Oled.su ./Src/Usart1_Bare_Metal_Custom_Lib.cyclo ./Src/Usart1_Bare_Metal_Custom_Lib.d ./Src/Usart1_Bare_Metal_Custom_Lib.o ./Src/Usart1_Bare_Metal_Custom_Lib.su ./Src/dht11.cyclo ./Src/dht11.d ./Src/dht11.o ./Src/dht11.su ./Src/fonts.cyclo ./Src/fonts.d ./Src/fonts.o ./Src/fonts.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/tim2.cyclo ./Src/tim2.d ./Src/tim2.o ./Src/tim2.su

.PHONY: clean-Src

