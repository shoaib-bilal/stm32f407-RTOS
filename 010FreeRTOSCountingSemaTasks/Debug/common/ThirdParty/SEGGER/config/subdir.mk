################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/shoaib\ data/workspace/RTOS_workspace/common/ThirdParty/SEGGER/config/SEGGER_SYSVIEW_Config_FreeRTOS.c 

OBJS += \
./common/ThirdParty/SEGGER/config/SEGGER_SYSVIEW_Config_FreeRTOS.o 

C_DEPS += \
./common/ThirdParty/SEGGER/config/SEGGER_SYSVIEW_Config_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
common/ThirdParty/SEGGER/config/SEGGER_SYSVIEW_Config_FreeRTOS.o: D:/shoaib\ data/workspace/RTOS_workspace/common/ThirdParty/SEGGER/config/SEGGER_SYSVIEW_Config_FreeRTOS.c common/ThirdParty/SEGGER/config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/shoaib data/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/include" -I"D:/shoaib data/workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"D:/shoaib data/workspace/RTOS_workspace/common/ThirdParty/SEGGER/config" -I"D:/shoaib data/workspace/RTOS_workspace/common/ThirdParty/SEGGER/OS" -I"D:/shoaib data/workspace/RTOS_workspace/common/ThirdParty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common-2f-ThirdParty-2f-SEGGER-2f-config

clean-common-2f-ThirdParty-2f-SEGGER-2f-config:
	-$(RM) ./common/ThirdParty/SEGGER/config/SEGGER_SYSVIEW_Config_FreeRTOS.d ./common/ThirdParty/SEGGER/config/SEGGER_SYSVIEW_Config_FreeRTOS.o

.PHONY: clean-common-2f-ThirdParty-2f-SEGGER-2f-config

