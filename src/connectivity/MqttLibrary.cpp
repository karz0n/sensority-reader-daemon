/*
 * MqttLibrary.cpp
 *
 *  Created on: May 20, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "MqttLibrary.hpp"

#include <mosquitto.h>

#include <Poco/Exception.h>

namespace connectivity {

MqttLibrary::MqttLibrary()
    : _counter(0)
{ }

MqttLibrary::~MqttLibrary()
{
    if (isInitialized()) {
        cleanup();
    }
}

MqttLibrary& MqttLibrary::instance()
{
    static MqttLibrary mqttLibrary;
    return mqttLibrary;
}

void MqttLibrary::initialize()
{
    if (_counter++ > 0) {
        return;
    }

    int rc = mosquitto_lib_init();
    if (rc != MOSQ_ERR_SUCCESS) {
        throw Poco::RuntimeException("Initialize mqtt library");
    }
}

void MqttLibrary::cleanup()
{
    if (--_counter > 0) {
        return;
    }

    int rc = mosquitto_lib_cleanup();
    if (rc != MOSQ_ERR_SUCCESS) {
        throw Poco::RuntimeException("Cleanup mqtt library");
    }
}

MqttDataEndpoint::Ptr MqttLibrary::endpoint(const std::string& id, bool cleanSession)
{
    if (!isInitialized()) {
        initialize();
    }

    return MqttDataEndpoint::create(id, cleanSession);
}

} // namespace connectivity

