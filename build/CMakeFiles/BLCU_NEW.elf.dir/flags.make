# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# compile ASM with /usr/local/bin/arm-none-eabi-gcc
# compile C with /usr/local/bin/arm-none-eabi-gcc
# compile CXX with /usr/local/bin/arm-none-eabi-g++
ASM_DEFINES = -DDATA_IN_D2_SRAM -DDEBUG -DSTM32H723xx -DUSE_HAL_DRIVER

ASM_INCLUDES = -I"/home/predawnia/Desktop/Hyperloop UPV/H8/BLCU_NEW/Core/Inc" -I/opt/malva/ST-LIB/Drivers/CMSIS/Device/ST/STM32H7xx/Include -I/opt/malva/ST-LIB/Drivers/CMSIS/Include -I/opt/malva/ST-LIB/Drivers/STM32H7xx_HAL_Driver/Inc -I/opt/malva/ST-LIB/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/system -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/netif/ppp -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/lwip -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/lwip/apps -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/lwip/priv -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/lwip/prot -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/netif -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/posix -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/stdc -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/system/arch -I/opt/malva/ST-LIB/Drivers/BSP/Components -I/opt/malva/ST-LIB/Drivers/BSP/Components/lan8742 -I/opt/malva/ST-LIB/LWIP/App -I/opt/malva/ST-LIB/LWIP/Target -I/opt/malva/ST-LIB/Inc -I/opt/malva/ST-LIB/Inc/HALAL/Models -I/opt/malva/ST-LIB/Inc/HALAL/Services -I/opt/malva/ST-LIB/Inc/ST-LIB_LOW -I/opt/malva/ST-LIB/Inc/ST-LIB_HIGH

ASM_FLAGS =  -x assembler-with-cpp -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -g3 -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-use-cxa-atexit -Wall --specs=nosys.specs -Wno-psabi

C_DEFINES = -DDATA_IN_D2_SRAM -DDEBUG -DSTM32H723xx -DUSE_HAL_DRIVER

C_INCLUDES = -I"/home/predawnia/Desktop/Hyperloop UPV/H8/BLCU_NEW/Core/Inc" -I/opt/malva/ST-LIB/Drivers/CMSIS/Device/ST/STM32H7xx/Include -I/opt/malva/ST-LIB/Drivers/CMSIS/Include -I/opt/malva/ST-LIB/Drivers/STM32H7xx_HAL_Driver/Inc -I/opt/malva/ST-LIB/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/system -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/netif/ppp -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/lwip -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/lwip/apps -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/lwip/priv -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/lwip/prot -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/netif -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/posix -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/stdc -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/system/arch -I/opt/malva/ST-LIB/Drivers/BSP/Components -I/opt/malva/ST-LIB/Drivers/BSP/Components/lan8742 -I/opt/malva/ST-LIB/LWIP/App -I/opt/malva/ST-LIB/LWIP/Target -I/opt/malva/ST-LIB/Inc -I/opt/malva/ST-LIB/Inc/HALAL/Models -I/opt/malva/ST-LIB/Inc/HALAL/Services -I/opt/malva/ST-LIB/Inc/ST-LIB_LOW -I/opt/malva/ST-LIB/Inc/ST-LIB_HIGH

C_FLAGS = -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -g3 -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-use-cxa-atexit -Wall --specs=nosys.specs -Wno-psabi

CXX_DEFINES = -DDATA_IN_D2_SRAM -DDEBUG -DSTM32H723xx -DUSE_HAL_DRIVER

CXX_INCLUDES = -I"/home/predawnia/Desktop/Hyperloop UPV/H8/BLCU_NEW/Core/Inc" -I/opt/malva/ST-LIB/Drivers/CMSIS/Device/ST/STM32H7xx/Include -I/opt/malva/ST-LIB/Drivers/CMSIS/Include -I/opt/malva/ST-LIB/Drivers/STM32H7xx_HAL_Driver/Inc -I/opt/malva/ST-LIB/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/system -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/netif/ppp -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/lwip -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/lwip/apps -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/lwip/priv -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/lwip/prot -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/netif -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/posix -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/src/include/compat/stdc -I/opt/malva/ST-LIB/Middlewares/Third_Party/LwIP/system/arch -I/opt/malva/ST-LIB/Drivers/BSP/Components -I/opt/malva/ST-LIB/Drivers/BSP/Components/lan8742 -I/opt/malva/ST-LIB/LWIP/App -I/opt/malva/ST-LIB/LWIP/Target -I/opt/malva/ST-LIB/Inc -I/opt/malva/ST-LIB/Inc/HALAL/Models -I/opt/malva/ST-LIB/Inc/HALAL/Services -I/opt/malva/ST-LIB/Inc/ST-LIB_LOW -I/opt/malva/ST-LIB/Inc/ST-LIB_HIGH

CXX_FLAGS = -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -g3 -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-use-cxa-atexit -Wall --specs=nosys.specs -fno-rtti -Wno-psabi -std=gnu++20

