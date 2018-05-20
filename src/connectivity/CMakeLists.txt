target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/MqttDataEndpoint.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/MqttDataEndpoint.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/MqttDataIssuer.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/MqttDataIssuer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/MqttLibrary.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/MqttLibrary.cpp")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}")
