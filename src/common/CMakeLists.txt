target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Thread.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Thread.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ThreadTarget.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ThreadTarget.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/System.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/System.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Runnable.hpp")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}")
