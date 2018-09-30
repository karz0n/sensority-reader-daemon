if (NOT USE_CROSS_TOOLCHAIN)
    message(FATAL_ERROR "Variable USE_CROSS_TOOLCHAIN not set")
endif()

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

if (NOT DEFINED ENV{CROSS_TOOLCHAIN_TUPLE})
    message(FATAL_ERROR "Variable CROSS_TOOLCHAIN_TUPLE not set")
endif()
if(DEFINED ENV{CROSS_TOOLCHAIN_BIN})
    set(GCC $ENV{CROSS_TOOLCHAIN_BIN}/$ENV{CROSS_TOOLCHAIN_TUPLE}-gcc)
    set(G++ $ENV{CROSS_TOOLCHAIN_BIN}/$ENV{CROSS_TOOLCHAIN_TUPLE}-g++)
else()
    set(GCC $ENV{CROSS_TOOLCHAIN_TUPLE}-gcc)
    set(G++ $ENV{CROSS_TOOLCHAIN_TUPLE}-g++)
endif()

set(CMAKE_C_COMPILER ${GCC})
set(CMAKE_CXX_COMPILER ${G++})

if (NOT DEFINED ENV{CROSS_TOOLCHAIN_FIND_PATH})
    message(FATAL_ERROR "Variable CROSS_TOOLCHAIN_FIND_PATH not set")
endif()
set(CMAKE_FIND_ROOT_PATH $ENV{CROSS_TOOLCHAIN_FIND_PATH})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)