################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/STM32F207ZGxx_Gpio_Driver.c \
../Drivers/Src/STM32F207ZGxx_SPI_Driver.c 

OBJS += \
./Drivers/Src/STM32F207ZGxx_Gpio_Driver.o \
./Drivers/Src/STM32F207ZGxx_SPI_Driver.o 

C_DEPS += \
./Drivers/Src/STM32F207ZGxx_Gpio_Driver.d \
./Drivers/Src/STM32F207ZGxx_SPI_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F2 -DSTM32F207ZGTx -c -I../Inc -I"D:/MD/Learning/Learning/STM32/002_Drivers/Drivers/Src" -I"D:/MD/Learning/Learning/STM32/002_Drivers/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/STM32F207ZGxx_Gpio_Driver.cyclo ./Drivers/Src/STM32F207ZGxx_Gpio_Driver.d ./Drivers/Src/STM32F207ZGxx_Gpio_Driver.o ./Drivers/Src/STM32F207ZGxx_Gpio_Driver.su ./Drivers/Src/STM32F207ZGxx_SPI_Driver.cyclo ./Drivers/Src/STM32F207ZGxx_SPI_Driver.d ./Drivers/Src/STM32F207ZGxx_SPI_Driver.o ./Drivers/Src/STM32F207ZGxx_SPI_Driver.su

.PHONY: clean-Drivers-2f-Src

