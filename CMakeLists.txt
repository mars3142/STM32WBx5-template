cmake_minimum_required(VERSION 3.20)
project(stm32wbxx
  VERSION 0.0.1
  LANGUAGES C ASM CXX
)
set(ELF_OUT firmware_v${PROJECT_VERSION}.elf)
set(BIN_OUT firmware_v${PROJECT_VERSION}.bin)
set(HEX_OUT firmware_v${PROJECT_VERSION}.hex)

include(cmake/format.cmake)

include_directories(include)

# Application library. Platform independent.
add_library(appLib
src/Module.cc)

if(CMAKE_CROSSCOMPILING)

# HAL Layer
set(HAL_SRC
  hal/cmsis-device-wb/Source/Templates/system_stm32wbxx.c
  hal/cmsis-device-wb/Source/Templates/gcc/startup_stm32wb55xx_cm4.s
  hal/stm32wbxx-hal-driver/Src/stm32wbxx_hal.c
  hal/stm32wbxx-hal-driver/Src/stm32wbxx_hal_cortex.c
  hal/stm32wbxx-hal-driver/Src/stm32wbxx_hal_gpio.c
  hal/stm32wbxx-hal-driver/Src/stm32wbxx_hal_rcc.c
)

add_library(stm32wbxx_hal ${HAL_SRC})
target_include_directories(stm32wbxx_hal PUBLIC
  hal/CMSIS_5/CMSIS/Core/Include # CMSIS: core_cm3.h  
  hal/cmsis-device-wb/Include # MCU: stm32wbxx.h
  hal/stm32wbxx-hal-driver/Inc # HAL
) 

# Common flags for MCU architecture agnostic compilers.
set(CompileFlags
  # -Wall
  # -ffreestanding
  -nostdlib
  -mthumb
  -mcpu=cortex-m4
  -fdata-sections
  -ffunction-sections
  -Werror
  -Warray-bounds 
  -fno-strict-aliasing
  -Wno-unused-const-variable
  -mfloat-abi=soft
  -mlittle-endian
  -specs=nano.specs
  -specs=nosys.specs
)
target_compile_definitions(stm32wbxx_hal PUBLIC STM32F401xC)
target_compile_options(stm32wbxx_hal PUBLIC ${CompileFlags})
target_compile_options(appLib PUBLIC ${CompileFlags})

# Linker flags must follow compiler flags. Specify linker script with instructions on the memory layout of the target device.
target_link_options(stm32wbxx_hal PUBLIC -T${CMAKE_SOURCE_DIR}/hal/STM32WBxx_FLASH.ld
  -Wl,--gc-sections,--print-memory-usage -mthumb -mcpu=cortex-m3 -specs=nosys.specs -specs=nano.specs
)

add_definitions(-DSTM32WB55xx)

# Main app
add_executable(${ELF_OUT}
  src/syscalls.c
  src/LED.cc
  src/main.cc
  src/Timing.cc
)
target_link_libraries(${ELF_OUT} stm32wbxx_hal appLib)
target_include_directories(${ELF_OUT} PUBLIC
  include
)

add_custom_target(${BIN_OUT} ALL
  COMMAND ${ARM_OBJCOPY} -Obinary ${ELF_OUT} ${BIN_OUT}
  DEPENDS ${ELF_OUT}
)

else()
  # Testing
  include(CTest)
  message(STATUS "## Building tests ##")
  if(BUILD_TESTING)
  add_subdirectory(test)
  endif()
endif()
