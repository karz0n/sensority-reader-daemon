/*!
* \file App.cpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Mar 22, 2018
*/

#include "App.hpp"

#include <iostream>
#include <regex>
#include <exception>

#include <Poco/Format.h>
#include <Poco/Exception.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/HelpFormatter.h>

#include "hardware/DeviceCommon.hpp"
#include "hardware/SensorCommon.hpp"
#include "hardware/SensorReaderFactory.hpp"

#include "StorageSubsystem.hpp"
#include "HardwareSubsystem.hpp"
#include "ConnectivitySubsystem.hpp"

using Poco::Util::Application;
using Poco::Util::OptionSet;
using Poco::Util::Option;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;

using hardware::SensorReaderFactory;
using hardware::SensorReaderManager;

App::App()
	: _helpRequested(false)
{ }

App::~App()
{ }

void App::initialize(Application& self)
{
	loadConfiguration();

    addSubsystem(new StorageSubsystem);
    addSubsystem(new HardwareSubsystem);
    addSubsystem(new ConnectivitySubsystem);

	ServerApplication::initialize(self);
}

void App::defineOptions(OptionSet& options)
{
	ServerApplication::defineOptions(options);

    options.addOption(
        Option("help", "h", "Display argument help information")
            .required(false)
            .repeatable(false)
            .callback(
                OptionCallback<App>(this, &App::handleHelp)));
}

void App::handleHelp(const std::string&, const std::string&)
{
    _helpRequested = true;

    displayHelp();
    stopOptionsProcessing();
}

int App::main(const std::vector<std::string>&)
{
    if (_helpRequested) {
        return ServerApplication::EXIT_OK;
    }

    try {
        waitForTerminationRequest();
    } catch (const Poco::Exception& e) {
        logger().error(e.displayText());
        return Application::EXIT_SOFTWARE;
    } catch (const std::exception& e) {
        logger().error(e.what());
        return Application::EXIT_SOFTWARE;
    } catch (...) {
        logger().error("Unknown error");
        return Application::EXIT_SOFTWARE;
    }

    return Application::EXIT_OK;
}

void App::displayHelp()
{
    HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("Sensority Reader Server");
    helpFormatter.format(std::cout);
}

//
// Define main entry
//
POCO_SERVER_MAIN(App)
