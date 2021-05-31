################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/freertos.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_hal_timebase_tim.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/utility.c 

OBJS += \
./Core/Src/freertos.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_hal_timebase_tim.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/utility.o 

C_DEPS += \
./Core/Src/freertos.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_hal_timebase_tim.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/utility.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/freertos.o: ../Core/Src/freertos.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/freertos.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f4xx_hal_msp.o: ../Core/Src/stm32f4xx_hal_msp.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f4xx_hal_timebase_tim.o: ../Core/Src/stm32f4xx_hal_timebase_tim.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f4xx_hal_timebase_tim.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f4xx_it.o: ../Core/Src/stm32f4xx_it.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32f4xx.o: ../Core/Src/system_stm32f4xx.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/utility.o: ../Core/Src/utility.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/include -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I/Users/larsmusaus/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/utility.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

