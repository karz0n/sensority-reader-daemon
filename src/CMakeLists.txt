add_subdirectory(common)
add_subdirectory(connectivity)
add_subdirectory(data)
add_subdirectory(hardware)

target_sources(${PROJECT_NAME}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/StorageSubsystem.hpp"
        "${PROJECT_SOURCE_DIR}/src/StorageSubsystem.cpp"
        "${PROJECT_SOURCE_DIR}/src/HardwareSubsystem.hpp"
        "${PROJECT_SOURCE_DIR}/src/HardwareSubsystem.cpp"
        "${PROJECT_SOURCE_DIR}/src/ConnectivitySubsystem.hpp"
        "${PROJECT_SOURCE_DIR}/src/ConnectivitySubsystem.cpp"
        "${PROJECT_SOURCE_DIR}/src/App.hpp"
        "${PROJECT_SOURCE_DIR}/src/App.cpp")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}")
