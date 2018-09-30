/*!
* \file ConnectivitySubsystem.cpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Aug 12, 2018
*/

#include "ConnectivitySubsystem.hpp"

#include <Poco/Util/Application.h>

using Poco::Util::Application;

ConnectivitySubsystem::ConnectivitySubsystem()
{

}

ConnectivitySubsystem::~ConnectivitySubsystem()
{

}

const char* ConnectivitySubsystem::name() const
{
    static const char* NAME = "connectivity";
    return NAME;
}

void ConnectivitySubsystem::initialize(Application& app)
{
    readConfig(app);
}

void ConnectivitySubsystem::uninitialize()
{

}

void ConnectivitySubsystem::readConfig(const Poco::Util::Application& app)
{

}


