################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/BLCU/BLCU.cpp \
../Core/Src/BLCU/Orders.cpp \
../Core/Src/BLCU/StateMachine.cpp 

OBJS += \
./Core/Src/BLCU/BLCU.o \
./Core/Src/BLCU/Orders.o \
./Core/Src/BLCU/StateMachine.o 

CPP_DEPS += \
./Core/Src/BLCU/BLCU.d \
./Core/Src/BLCU/Orders.d \
./Core/Src/BLCU/StateMachine.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/BLCU/%.o Core/Src/BLCU/%.su: ../Core/Src/BLCU/%.cpp Core/Src/BLCU/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++20 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -DDATA_IN_D2_SRAM -c -I"/home/predawnia/Desktop/Hyperloop UPV/H8/ST-LIB" -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/home/predawnia/Desktop/Hyperloop UPV/H8/ST-LIB/Inc" -I"/home/predawnia/Desktop/Hyperloop UPV/H8/ST-LIB/Inc/HALAL/Models" -I"/home/predawnia/Desktop/Hyperloop UPV/H8/ST-LIB/Inc/HALAL/Services" -I"/home/predawnia/Desktop/Hyperloop UPV/H8/ST-LIB/Inc/ST-LIB_LOW" -I"/home/predawnia/Desktop/Hyperloop UPV/H8/ST-LIB/Inc/ST-LIB_HIGH" -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I"/home/predawnia/Desktop/Hyperloop UPV/H8/ST-LIB/Inc/HALAL/Services/Communication" -I"/home/predawnia/Desktop/Hyperloop UPV/H8/ST-LIB/Inc/HALAL/Services/Communication/Ethernet" -I"/home/predawnia/Desktop/Hyperloop UPV/H8/ST-LIB/Inc/HALAL/Services/Communication/Ethernet/UDP" -I"/home/predawnia/Desktop/Hyperloop UPV/H8/ST-LIB/Inc/HALAL/Services/Communication/Ethernet/TCP" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-BLCU

clean-Core-2f-Src-2f-BLCU:
	-$(RM) ./Core/Src/BLCU/BLCU.d ./Core/Src/BLCU/BLCU.o ./Core/Src/BLCU/BLCU.su ./Core/Src/BLCU/Orders.d ./Core/Src/BLCU/Orders.o ./Core/Src/BLCU/Orders.su ./Core/Src/BLCU/StateMachine.d ./Core/Src/BLCU/StateMachine.o ./Core/Src/BLCU/StateMachine.su

.PHONY: clean-Core-2f-Src-2f-BLCU

