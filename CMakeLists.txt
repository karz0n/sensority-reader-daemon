cmake_minimum_required(VERSION 3.5)

#-------------------------------------------------------------------------------
# Project Definition
#-------------------------------------------------------------------------------

project(sensority-reader-daemon
    VERSION 0.1
    DESCRIPTION "Sensority daemon project")

#-------------------------------------------------------------------------------
# Project Options
#-------------------------------------------------------------------------------

#
option(BUILD_DOC "Build project documentation" OFF)

# Enable using cross-toolchain
#
# CROSS_TOOLCHAIN_BIN [optional] - path to cross-toochain binary
#   files (compilers, etc.). If not defined use tuple of target platform and find
#   in system defined directories (see PATH environment variable).
# CROSS_TOOLCHAIN_TUPLE [required] - name of tuple of target platform
#   (e.g. armv8-rpi3-linux-gnueabihf).
# CROSS_TOOLCHAIN_FIND_PATH [required] - list of paths where to find
#   dependencies using cmake modules. Paths should be separated by semicolon.
#
option(USE_CROSS_TOOLCHAIN "Using cross-toolchain" OFF)

#-------------------------------------------------------------------------------
# Project Configuration
#-------------------------------------------------------------------------------

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/common")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

include(Flags)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING FORCE)
    message(STATUS "Build type not defined. Using 'Debug' as default")
endif()

if (USE_CROSS_TOOLCHAIN)
    include(CrossToolchain)
endif()

#-------------------------------------------------------------------------------
# Dependency Configuration
#-------------------------------------------------------------------------------

find_package(Threads REQUIRED)
find_package(Bcm2835 REQUIRED)
find_package(Cares REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Poco
    REQUIRED
    COMPONENTS Util JSON XML Net Foundation)
find_package(Mosquitto REQUIRED)
if(BUILD_DOC)
    find_package(Doxygen COMPONENTS dot)
endif()

#-------------------------------------------------------------------------------
# Target Configuration
#-------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} "")

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        "$<$<CONFIG:Debug>:${debug_flags}>"
        "$<$<NOT:$<CONFIG:Debug>>:${release_flags}>"
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${Bcm2835_INCLUDE_DIRS}
        ${Poco_INCLUDE_DIRS}
        ${Mosquitto_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_THREAD_LIBS_INIT}
        ${Bcm2835_LIBRARIES}
        ${Cares_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${Poco_LIBRARIES}
        ${Mosquitto_LIBRARIES}
)

#-------------------------------------------------------------------------------
# Structure Configuration
#-------------------------------------------------------------------------------

add_subdirectory(src)
if(BUILD_DOC)
    add_subdirectory(doc)
endif()

