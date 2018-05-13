target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/HttpSensorReaderRequestHandler.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/HttpSensorReaderRequestHandler.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/HttpSensorReaderRequestHandlerFactory.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/HttpSensorReaderRequestHandlerFactory.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/HttpSensorReaderServer.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/HttpSensorReaderServer.cpp")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}")
