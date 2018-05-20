/*
 * MqttDataIssuer.cpp
 *
 *  Created on: May 20, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "MqttDataIssuer.hpp"

namespace connectivity {

MqttDataIssuer::MqttDataIssuer(const std::string& t, MqttDataEndpoint::Ptr e)
    : _topic(t)
    , _endpoint(std::move(e))
{ }

void MqttDataIssuer::issue(const std::string& message,
                           int qos /*= MQTT_DEFAULT_QOS_VALUE*/,
                           bool retain /*= MQTT_DEFAULT_RETAIN_VALUE*/)
{
    issue(message.c_str(), message.size(), qos, retain);
}

void MqttDataIssuer::issue(const void* payload,
                           std::size_t payloadSize,
                           int qos /*= MQTT_DEFAULT_QOS_VALUE*/,
                           bool retain /*= MQTT_DEFAULT_RETAIN_VALUE*/)
{
    _endpoint->publish(_topic.c_str(), payload, payloadSize, qos, retain);
}

} // namespace connectivity
