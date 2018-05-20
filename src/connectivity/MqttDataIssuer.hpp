/*
 * MqttDataIssuer.hpp
 *
 *  Created on: May 20, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef MQTTDATAISSUER_HPP
#define MQTTDATAISSUER_HPP

#include <string>

#include "MqttDataEndpoint.hpp"

namespace connectivity {

/**
 * @brief The MqttDataIssuer class
 */
class MqttDataIssuer
{
public:
    MqttDataIssuer(const std::string& topic, MqttDataEndpoint::Ptr endpoint);

    void issue(const std::string& message,
               int qos = MQTT_DEFAULT_QOS_VALUE,
               bool retain = MQTT_DEFAULT_RETAIN_VALUE);

    void issue(const void* payload,
               std::size_t payloadSize,
               int qos = MQTT_DEFAULT_QOS_VALUE,
               bool retain = MQTT_DEFAULT_RETAIN_VALUE);

private:
    std::string _topic;
    MqttDataEndpoint::Ptr _endpoint;
};

} // namespace connectivity

#endif // MQTTDATAISSUER_HPP
