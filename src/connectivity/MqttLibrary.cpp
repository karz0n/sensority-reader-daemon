/*!
 * \file MqttLibrary.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Feb 21, 2018
 */

#include "MqttLibrary.hpp"

#include <mosquitto.h>

#include <Poco/Exception.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>

#include "MqttCommon.hpp"

using Poco::UUID;
using Poco::UUIDGenerator;

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

MqttLibraryVersion MqttLibrary::version()
{
    int maj{0}, min{0}, rev{0};
    mosquitto_lib_version(&maj, &min,&rev);
    return {maj, min, rev};
}

bool MqttLibrary::isInitialized() const
{
    return _counter > 0;
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
    poco_assert_msg(_counter > 0, "Library not inialized");

    if (--_counter > 0) {
        return;
    }

    int rc = mosquitto_lib_cleanup();
    if (rc != MOSQ_ERR_SUCCESS) {
        throw Poco::RuntimeException("Cleanup mqtt library");
    }
}

MqttEndpoint::Ptr MqttLibrary::endpoint(bool cleanSession)
{
    UUIDGenerator& g = UUIDGenerator::defaultGenerator();
    return endpoint(g.createRandom().toString(),
                    cleanSession);
}

MqttEndpoint::Ptr MqttLibrary::endpoint(const std::string& id, bool cleanSession)
{
    if (!isInitialized()) {
        initialize();
    }
    return MqttEndpoint::create(id, cleanSession);
}

} // namespace connectivity

