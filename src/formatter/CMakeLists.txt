target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/JsonFormatter.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/JsonFormatter.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/StringFormatter.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/StringFormatter.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Formatter.hpp")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}")
