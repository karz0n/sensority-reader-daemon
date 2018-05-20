/*
 * MqttDataEndpoint.cpp
 *
 *  Created on: May 20, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "MqttDataEndpoint.hpp"

#include <mosquitto.h>

#include <Poco/Format.h>
#include <Poco/Exception.h>

namespace connectivity {

MqttDataEndpoint::MqttDataEndpoint(const std::string& id /*= ""*/,
                                   bool cleanSession /*= true*/)
    : _mosq(nullptr)
    , _connected(false)
{
    _mosq = mosquitto_new(
                id.empty()
                    ? nullptr
                    : id.c_str(),
                cleanSession, this);
    if (_mosq == nullptr) {
        throw Poco::RuntimeException("Create endpoint");
    }
}

MqttDataEndpoint::~MqttDataEndpoint()
{
    mosquitto_destroy(_mosq);
}

void MqttDataEndpoint::connect(const std::string& host,
                               unsigned short port /*= MQTT_DEFAULT_INSECURE_PORT*/,
                               int keepalive /*= MQTT_DEFAULT_KEEPALIVE*/)
{
    poco_assert_msg(!_connected, "Connection has been already established");

    int rc = mosquitto_connect(_mosq, host.c_str(), port, keepalive);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw Poco::RuntimeException(
                    Poco::format("Attempt connect to %s:%d", host, port),
                    rc);
    }

    _connected = true;
}

void MqttDataEndpoint::disconnect()
{
    poco_assert_msg(_connected, "First need to make a connection");

    int rc = mosquitto_disconnect(_mosq);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw Poco::RuntimeException("Attempt disconnect", rc);
    }

    _connected = false;
}

void MqttDataEndpoint::setCertificatesPath(const std::string& path)
{
    poco_assert_msg(!_connected, "Forbidden after connection was established");

    int rc = mosquitto_tls_set(_mosq, nullptr, path.c_str(), nullptr, nullptr, nullptr);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw Poco::RuntimeException("Set certificates path", rc);
    }
}

void MqttDataEndpoint::setCredentials(const std::string& username,
                                      const std::string& password)
{
    poco_assert_msg(!_connected, "Forbidden after connection was established");

    int rc = mosquitto_username_pw_set(_mosq, username.c_str(), password.c_str());
    if (rc != MOSQ_ERR_SUCCESS) {
        throw Poco::RuntimeException("Set credential", rc);
    }
}

void MqttDataEndpoint::publish(const std::string& topic,
                               const void* payload,
                               std::size_t size,
                               int qos /*= MQTT_DEFAULT_QOS_VALUE*/,
                               bool retain /*= MQTT_DEFAULT_RETAIN_VALUE*/)
{
    poco_assert_msg(_connected, "First need to make a connection");

    int rc = mosquitto_publish(_mosq, nullptr, topic.c_str(),
                               int(size), payload,
                               qos, retain);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw Poco::RuntimeException("Attempt publish data", rc);
    }
}

} // namespace connectivity
