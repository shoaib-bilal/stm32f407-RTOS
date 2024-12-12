################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/shoai/Downloads/MasteringRTOS-master/MasteringRTOS-master/RTOS_workspace/common/ThirdParty/SEGGER/SEGGER/Syscalls/SEGGER_RTT_Syscalls_GCC.c 

OBJS += \
./common/ThirdParty/SEGGER/SEGGER/Syscalls/SEGGER_RTT_Syscalls_GCC.o 

C_DEPS += \
./common/ThirdParty/SEGGER/SEGGER/Syscalls/SEGGER_RTT_Syscalls_GCC.d 


# Each subdirectory must supply rules for building sources it contributes
common/ThirdParty/SEGGER/SEGGER/Syscalls/SEGGER_RTT_Syscalls_GCC.o: C:/Users/shoai/Downloads/MasteringRTOS-master/MasteringRTOS-master/RTOS_workspace/common/ThirdParty/SEGGER/SEGGER/Syscalls/SEGGER_RTT_Syscalls_GCC.c common/ThirdParty/SEGGER/SEGGER/Syscalls/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I"D:/Workspace/RTOS_workspace/common/ThirdParty/SEGGER/Config" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"D:/Workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"D:/Workspace/RTOS_workspace/common/ThirdParty/FreeRTOS/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"D:/Workspace/RTOS_workspace/common/ThirdParty/SEGGER/OS" -I"D:/Workspace/RTOS_workspace/common/ThirdParty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common-2f-ThirdParty-2f-SEGGER-2f-SEGGER-2f-Syscalls

clean-common-2f-ThirdParty-2f-SEGGER-2f-SEGGER-2f-Syscalls:
	-$(RM) ./common/ThirdParty/SEGGER/SEGGER/Syscalls/SEGGER_RTT_Syscalls_GCC.d ./common/ThirdParty/SEGGER/SEGGER/Syscalls/SEGGER_RTT_Syscalls_GCC.o

.PHONY: clean-common-2f-ThirdParty-2f-SEGGER-2f-SEGGER-2f-Syscalls

