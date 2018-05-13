target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/DeviceGpio.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/DeviceGpio.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/DeviceManager.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/DeviceManager.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/DeviceLibrary.hpp")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}")
