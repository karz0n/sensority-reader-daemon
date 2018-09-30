/*!
* \file ConnectivitySubsystem.hpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Aug 12, 2018
*/

#ifndef CONNECTIVITYSUBSYSTEM_HPP
#define CONNECTIVITYSUBSYSTEM_HPP

#include <Poco/Util/Subsystem.h>
#include <Poco/Util/LayeredConfiguration.h>

#include "connectivity/HttpDataServer.hpp"
#include "connectivity/MqttClient.hpp"
#include "connectivity/MqttNotifier.hpp"

class ConnectivitySubsystem : public Poco::Util::Subsystem
{
public:
    ConnectivitySubsystem();
    ~ConnectivitySubsystem() override;

    const char* name() const override;

protected:
    void initialize(Poco::Util::Application&) override;
    void uninitialize() override;

private:
    bool isHttpServerEnabled(const Poco::Util::LayeredConfiguration&) const;
    bool isMqttServerEnabled(const Poco::Util::LayeredConfiguration&) const;

    void startHttpServer(const Poco::Util::Application&);
    void startMqttServer(const Poco::Util::Application&);

private:
    connectivity::HttpDataServer::Ptr _httpServer;
    connectivity::MqttEndpoint::Ptr _mqttEndpoint;
    connectivity::MqttNotifier::Ptr _mqttNotifier;
};

#endif // CONNECTIVITYSUBSYSTEM_HPP
