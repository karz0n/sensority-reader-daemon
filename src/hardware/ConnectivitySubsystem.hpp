/*!
* \file ConnectivitySubsystem.hpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Aug 12, 2018
*/

#ifndef CONNECTIVITYSUBSYSTEM_HPP
#define CONNECTIVITYSUBSYSTEM_HPP

#include <Poco/Util/Subsystem.h>

#include "connectivity/HttpDataServer.hpp"

class ConnectivitySubsystem : public Poco::Util::Subsystem
{
public:
    ConnectivitySubsystem();
    ~ConnectivitySubsystem();

    const char* name() const override;

protected:
    void initialize(Poco::Util::Application&) override;
    void uninitialize() override;

private:
    void readConfig(const Poco::Util::Application&);

private:
    connectivity::HttpDataServer::Ptr _httpServer;
};

#endif // CONNECTIVITYSUBSYSTEM_HPP
