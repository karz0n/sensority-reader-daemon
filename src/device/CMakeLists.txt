target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/DeviceCommon.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/DeviceGpio.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/DeviceGpio.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/DeviceLibrary.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/DeviceLibrary.cpp")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}")
