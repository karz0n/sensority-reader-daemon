target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/HttpDataRequestHandler.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/HttpDataRequestHandler.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/HttpDataRequestHandlerFactory.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/HttpDataRequestHandlerFactory.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/HttpDataServer.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/HttpDataServer.cpp")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}")
