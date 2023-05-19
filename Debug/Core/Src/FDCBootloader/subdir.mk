################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/FDCBootloader/BootloaderTFTP.cpp \
../Core/Src/FDCBootloader/FDCBootloader.cpp 

OBJS += \
./Core/Src/FDCBootloader/BootloaderTFTP.o \
./Core/Src/FDCBootloader/FDCBootloader.o 

CPP_DEPS += \
./Core/Src/FDCBootloader/BootloaderTFTP.d \
./Core/Src/FDCBootloader/FDCBootloader.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/FDCBootloader/%.o Core/Src/FDCBootloader/%.su: ../Core/Src/FDCBootloader/%.cpp Core/Src/FDCBootloader/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++20 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -DDATA_IN_D2_SRAM -c -I"C:/Users/pablo/Desktop/Hyperloop UPV/H8/TESTING/ST-LIB" -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/pablo/Desktop/Hyperloop UPV/H8/TESTING/ST-LIB/Inc" -I"C:/Users/pablo/Desktop/Hyperloop UPV/H8/TESTING/ST-LIB/Inc/HALAL/Models" -I"C:/Users/pablo/Desktop/Hyperloop UPV/H8/TESTING/ST-LIB/Inc/HALAL/Services" -I"C:/Users/pablo/Desktop/Hyperloop UPV/H8/TESTING/ST-LIB/Inc/ST-LIB_LOW" -I"C:/Users/pablo/Desktop/Hyperloop UPV/H8/TESTING/ST-LIB/Inc/ST-LIB_HIGH" -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I"C:/Users/pablo/Desktop/Hyperloop UPV/H8/TESTING/ST-LIB/Inc/HALAL/Services/Communication" -I"C:/Users/pablo/Desktop/Hyperloop UPV/H8/TESTING/ST-LIB/Inc/HALAL/Services/Communication/Ethernet" -I"C:/Users/pablo/Desktop/Hyperloop UPV/H8/TESTING/ST-LIB/Inc/HALAL/Services/Communication/Ethernet/UDP" -I"C:/Users/pablo/Desktop/Hyperloop UPV/H8/TESTING/ST-LIB/Inc/HALAL/Services/Communication/Ethernet/TCP" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-FDCBootloader

clean-Core-2f-Src-2f-FDCBootloader:
	-$(RM) ./Core/Src/FDCBootloader/BootloaderTFTP.d ./Core/Src/FDCBootloader/BootloaderTFTP.o ./Core/Src/FDCBootloader/BootloaderTFTP.su ./Core/Src/FDCBootloader/FDCBootloader.d ./Core/Src/FDCBootloader/FDCBootloader.o ./Core/Src/FDCBootloader/FDCBootloader.su

.PHONY: clean-Core-2f-Src-2f-FDCBootloader

