if(DEFINED ENV{ARM_SDK_PATH})
    set(ARM_SDK_PATH $ENV{ARM_SDK_PATH})
    message(STATUS "ARM SDK path is ${ARM_SDK_PATH}")
else()
    message(FATAL_ERROR "ARM SDK path not sets")
    return()
endif()

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_SYSROOT "${ARM_SDK_PATH}/sysroot")
set(CMAKE_STAGING_PREFIX "${ARM_SDK_PATH}/staging")

set(CMAKE_C_COMPILER "${ARM_SDK_PATH}/prebuilt/bin/armv8-rpi3-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "${ARM_SDK_PATH}/prebuilt/bin/armv8-rpi3-linux-gnueabihf-g++")

set(CMAKE_FIND_ROOT_PATH "${ARM_SDK_PATH}/staging")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
