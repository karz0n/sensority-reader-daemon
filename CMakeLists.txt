cmake_minimum_required(VERSION 3.5)

#------------------------------------------------------------------------------
# Project Configuration
#------------------------------------------------------------------------------

project(sensority-reader-daemon
    VERSION
        0.1
    DESCRIPTION
        "Sensority daemon project"
    LANGUAGES
        CXX)

#------------------------------------------------------------------------------
# Toolchain Configuration
#------------------------------------------------------------------------------

if(DEFINED ENV{ARM_SDK_PATH})
    include("${PROJECT_SOURCE_DIR}/cmake/toolchains/arm-toolchain.cmake")
endif()
if(DEFINED ENV{ARM_DEPLOY_PATH})
    include("${PROJECT_SOURCE_DIR}/cmake/macros/arm-deployment.cmake")
endif()

#------------------------------------------------------------------------------
# Dependency Configuration
#------------------------------------------------------------------------------

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

find_package(Threads REQUIRED)
find_package(Poco REQUIRED Util JSON XML Net Foundation)
find_package(Bcm2835 REQUIRED)

#------------------------------------------------------------------------------
# Target Configuration
#------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} "")

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${Bcm2835_INCLUDE_DIRS}
    ${Poco_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Bcm2835_LIBRARIES}
    ${Poco_LIBRARIES})

add_subdirectory(src)
