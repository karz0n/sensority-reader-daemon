add_subdirectory(common)
add_subdirectory(connectivity)
add_subdirectory(device)
add_subdirectory(formatter)
add_subdirectory(sensor)

target_sources(${PROJECT_NAME}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/App.cpp"
        "${PROJECT_SOURCE_DIR}/src/App.hpp")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}")
