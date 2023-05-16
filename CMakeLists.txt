cmake_minimum_required (VERSION 3.4)
project (BLCU_NEW ASM C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(STLIB_DIR /opt/malva/ST-LIB)
set(EXECUTABLE ${PROJECT_NAME}.elf)

add_subdirectory(${STLIB_DIR} ${STLIB_DIR}/build)
add_executable(${EXECUTABLE} 
  Core/Src/main.cpp 
  Core/Src/syscalls.c 
  Core/Src/stm32h7xx_hal_msp.c
  Core/Src/stm32h7xx_it.c
  Core/Src/sysmem.c
  Core/Src/system_stm32h7xx.c
  Core/Startup/startup_stm32h723zgtx.s
  )

target_link_libraries(${EXECUTABLE} st-lib)

target_compile_definitions(${EXECUTABLE} PUBLIC
  -DUSE_HAL_DRIVER
  -DSTM32H723xx
  -DDATA_IN_D2_SRAM
)

target_include_directories(${EXECUTABLE} PUBLIC
  Core/Inc
)


target_compile_options(${EXECUTABLE} PUBLIC
  -mcpu=cortex-m7
  -mfpu=fpv5-d16
  -mfloat-abi=hard
  -mthumb
  
  ${PROFILE}
  ${OPTIMIZATION}
  -ffunction-sections
  -fdata-sections
  -fno-exceptions
  -fno-use-cxa-atexit
  -fno-use-cxa-atexit

  -Wall

  --specs=nosys.specs
)
target_link_options(${EXECUTABLE} PUBLIC 
        -T${CMAKE_SOURCE_DIR}/STM32H723ZGTX_FLASH.ld
        -mcpu=cortex-m7
        -mthumb
        -mfpu=fpv5-d16
        -mfloat-abi=hard
        -specs=nosys.specs
        -lc
        -lm
        -lnosys
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
        )
