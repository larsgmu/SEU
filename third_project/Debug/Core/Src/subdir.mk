################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/main.c \
../Core/Src/stm32l0xx_hal_msp.c \
../Core/Src/stm32l0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l0xx.c 

OBJS += \
./Core/Src/main.o \
./Core/Src/stm32l0xx_hal_msp.o \
./Core/Src/stm32l0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l0xx.o 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/stm32l0xx_hal_msp.d \
./Core/Src/stm32l0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/main.o: ../Core/Src/main.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L053xx -c -I../Core/Inc -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/STM32L0xx_HAL_Driver/Inc -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/stm32l0xx_hal_msp.o: ../Core/Src/stm32l0xx_hal_msp.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L053xx -c -I../Core/Inc -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/STM32L0xx_HAL_Driver/Inc -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32l0xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/stm32l0xx_it.o: ../Core/Src/stm32l0xx_it.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L053xx -c -I../Core/Inc -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/STM32L0xx_HAL_Driver/Inc -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32l0xx_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L053xx -c -I../Core/Inc -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/STM32L0xx_HAL_Driver/Inc -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L053xx -c -I../Core/Inc -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/STM32L0xx_HAL_Driver/Inc -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/system_stm32l0xx.o: ../Core/Src/system_stm32l0xx.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L053xx -c -I../Core/Inc -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/STM32L0xx_HAL_Driver/Inc -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/home/kveriksen/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.0/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32l0xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

