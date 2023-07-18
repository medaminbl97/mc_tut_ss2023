cmake_minimum_required(VERSION 3.21)

# Project name and language configuration
project(tiva_sdk)
enable_language(C ASM)

# Interface library for build definitions
add_library(builddefs INTERFACE)

# Compiler options
target_compile_options(builddefs INTERFACE
    -mthumb
    -mcpu=cortex-m4
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -g3
    -O0
    -fomit-frame-pointer
)

# Preprocessor definitions
target_compile_definitions(builddefs INTERFACE
    -Dgcc
    -DTM4C123GH6PM
    -DUSE_CORE_CLK_PLL
    -DPART_TM4C123GH6PM
)

# Linker options
target_link_options(builddefs INTERFACE
    --specs=nosys.specs
    -mcpu=cortex-m4
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -T${CMAKE_CURRENT_SOURCE_DIR}/tm4c123gh6pm.ld
)   

# System sources
set(SYSTEM_CODE 
    system/system_tm4c123gh6pm.c
    system/syscalls.c
    system/sysmem.c
)

# External libraries
set(LIBS "")

# Name of the executable 
add_executable(boot.elf)
target_include_directories(boot.elf PUBLIC . ./system)

# Path to SDK
set(SDKROOT ${CMAKE_CURRENT_SOURCE_DIR}/../.. CACHE INTERNAL "")

# CMSIS Driver
target_include_directories(boot.elf
    PUBLIC
    ${SDKROOT}/CMSIS
)

# TivaWare SDK Driverlib
#   We build as static library, so only used objects are
#   included in boot.elf.
add_library(driverlib)

file(GLOB DRIVERLIB_SRC ${SDKROOT}/tivaware/driverlib/*.c)
target_sources(driverlib PRIVATE ${DRIVERLIB_SRC})

target_include_directories(driverlib
    PUBLIC
    ${SDKROOT}/tivaware/
    ${SDKROOT}/tivaware/driverlib    
)

target_link_libraries(driverlib PRIVATE builddefs)

# Project source files

file(GLOB CSRC ./*.c)
file(GLOB ASRC ./*.s)

target_sources(boot.elf
    PRIVATE
    ${CSRC}
    ${ASRC}
    ${SYSTEM_CODE}
)

# Link against libraries
target_link_libraries(boot.elf
    PRIVATE
    ${LIBS}
    m
    driverlib
    builddefs
)