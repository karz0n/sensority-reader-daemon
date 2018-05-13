add_subdirectory(device)
add_subdirectory(formatter)
add_subdirectory(http)
add_subdirectory(os)
add_subdirectory(sensor)

target_sources(${PROJECT_NAME}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
        "${PROJECT_SOURCE_DIR}/src/SensorReaderApplication.cpp"
        "${PROJECT_SOURCE_DIR}/src/SensorReaderApplication.hpp")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}")
