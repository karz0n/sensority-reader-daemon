/*!
* \file ConnectivitySubsystem.cpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Aug 12, 2018
*/

#include "ConnectivitySubsystem.hpp"

#include <Poco/Util/Application.h>

#include "data/FormatterCommon.hpp"
#include "connectivity/MqttLibrary.hpp"

#include "StorageSubsystem.hpp"

using Poco::Util::Application;

using data::OutputFormats;

static const std::string HTTP_CONF_PREFIX = "connectivity.http";
static const std::string MQTT_CONF_PREFIX = "connectivity.mqtt";

ConnectivitySubsystem::ConnectivitySubsystem()
{ }

ConnectivitySubsystem::~ConnectivitySubsystem()
{ }

const char* ConnectivitySubsystem::name() const
{
    static const char* NAME = "connectivity";
    return NAME;
}

void ConnectivitySubsystem::initialize(Application& app)
{
    if (isHttpServerEnabled(app.config()))
    {
        startHttpServer(app);
    }

    if (isMqttServerEnabled(app.config()))
    {
        startMqttServer(app);
    }
}

void ConnectivitySubsystem::uninitialize()
{

}

bool ConnectivitySubsystem::isHttpServerEnabled(const Poco::Util::LayeredConfiguration& config) const
{
    return config.getBool(HTTP_CONF_PREFIX + ".enable", false);
}

bool ConnectivitySubsystem::isMqttServerEnabled(const Poco::Util::LayeredConfiguration& config) const
{
    return config.getBool(MQTT_CONF_PREFIX + ".enable", false);
}

void ConnectivitySubsystem::startHttpServer(const Poco::Util::Application& app)
{
    std::string path = HTTP_CONF_PREFIX + ".format";
    OutputFormats format = connectivity::DEFAULT_HTTP_FORMAT;
    if (app.config().has(path)) {
        format = data::translateOutputFormat(app.config().getString(path));
    }

    path = HTTP_CONF_PREFIX + ".port";
    unsigned short port = app.config().getUInt(path, connectivity::DEFAULT_HTTP_PORT);

    auto manager = app.getSubsystem<StorageSubsystem>().manager();
    _httpServer = std::make_unique<connectivity::HttpDataServer>(manager, format, port);
    _httpServer->run();
}

void ConnectivitySubsystem::startMqttServer(const Poco::Util::Application& app)
{
    _mqttEndpoint = connectivity::MqttLibrary::instance().client();

    std::string path = MQTT_CONF_PREFIX + ".username";
    std::string username;
    if (app.config().has(path)) {
        username = app.config().getString(path);
    }
    path = MQTT_CONF_PREFIX + ".password";
    std::string password;
    if (app.config().has(path)) {
        password = app.config().getString(path);
    }
    if (!username.empty() && !password.empty()) {
        _mqttEndpoint->setCredentials(username, password);
    }

    path = MQTT_CONF_PREFIX + ".certs";
    std::string certs;
    if (app.config().has(path)) {
        certs = app.config().getString(path);
    }
    if (!certs.empty()) {
        _mqttEndpoint->configureTransportLayerSecurity(certs);
    }

    path = MQTT_CONF_PREFIX + ".format";
    OutputFormats format = connectivity::MQTT_DEFAULT_OUTPUT_FORMAt;
    if (app.config().has(path)) {
        format = data::translateOutputFormat(app.config().getString(path));
    }

    _mqttNotifier = std::make_unique<connectivity::MqttNotifier>(_mqttEndpoint, format);

    auto manager = app.getSubsystem<StorageSubsystem>().manager();
    std::size_t i = 0;
    do {
        path = MQTT_CONF_PREFIX + ".storages.storage[" + std::to_string(i++) + "]";
        if (!app.config().has(path)) {
            break;
        }

        std::string name = app.config().getString(path);
        if (!manager->has(name)) {
            continue;
        }
        auto storage = manager->get(name);

        _mqttNotifier->watch(storage);
    } while (true);

    path = MQTT_CONF_PREFIX + ".host";
    std::string host;
    if (app.config().has(path)) {
        host = app.config().getString(path);
    }
    if (host.empty()) {
        app.logger().error("Hostname for mqtt endpoint is absent");

        _mqttNotifier.reset();
        _mqttEndpoint.reset();

        return;
    }

    path = MQTT_CONF_PREFIX + ".port";
    unsigned short port = app.config().getUInt(path, connectivity::MQTT_DEFAULT_INSECURE_PORT);

    _mqttEndpoint->connect(host, port);
}
