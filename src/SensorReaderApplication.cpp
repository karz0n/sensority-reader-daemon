/*
 * SensorReaderApplication.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "SensorReaderApplication.hpp"

#include <iostream>
#include <exception>

#include <Poco/Exception.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/HelpFormatter.h>

#include "sensor/SensorCommon.hpp"
#include "sensor/SensorReader.hpp"

#include "http/HttpSensorReaderServer.hpp"

using Poco::Util::Application;
using Poco::Util::OptionSet;
using Poco::Util::Option;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;

/**
 * @brief Default server port
 */
static const int DEFAULT_SERVER_PORT = 8080;

/**
 * @brief Default device pin value
 */
static const int DEFAULT_DEVICE_PIN = 22;

/**
 * @brief Default device type value
 */
static const std::string DEFAULT_DEVICE_TYPE = std::string("DHT22");

SensorReaderApplication::SensorReaderApplication()
	: _helpRequested(false)
{ }

SensorReaderApplication::~SensorReaderApplication()
{ }

void SensorReaderApplication::initialize(Application& self)
{
	loadConfiguration();
	ServerApplication::initialize(self);
}

void SensorReaderApplication::uninitialize()
{
	ServerApplication::uninitialize();
}

void SensorReaderApplication::reinitialize(Application& self)
{
	ServerApplication::reinitialize(self);
}

void SensorReaderApplication::defineOptions(OptionSet& options)
{
	ServerApplication::defineOptions(options);

	options.addOption(
        Option("help", "h", "Display argument help information")
            .required(false)
			.repeatable(false)
            .callback(   
                OptionCallback<SensorReaderApplication>(this, &SensorReaderApplication::handleHelp)));

    options.addOption(
        Option("port", "p", "Set HTTP server port")
            .required(false)
            .repeatable(false)
            .argument("value")
            .binding("server.port"));

    options.addOption(
        Option("devicePin", "", "Set reader device pin")
            .required(false)
            .repeatable(false)
            .argument("value")
            .binding("reader.devicePin"));

    options.addOption(
        Option("deviceType", "", "Set reader device type")
            .required(false)
            .repeatable(false)
            .argument("value")
            .binding("reader.deviceType"));
}

void SensorReaderApplication::handleOption(const std::string& name, const std::string& value)
{
	ServerApplication::handleOption(name, value);
}

void SensorReaderApplication::handleHelp(const std::string&, const std::string&)
{
    _helpRequested = true;

    displayHelp();
    stopOptionsProcessing();
}

int SensorReaderApplication::main(const std::vector<std::string>&)
{
    if (_helpRequested) {
        return ServerApplication::EXIT_OK;
    }

    try {
        SensorReader reader(getDevicePin(), getDeviceType());
        reader.run();

        HttpSensorReaderServer server(getServerPort(), reader.storage());
        server.run();
        waitForTerminationRequest();
        server.shutdown();

        reader.shutdown();
    } catch (const Poco::Exception& e) {
        logger().error(e.message());
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

void SensorReaderApplication::displayHelp()
{
    HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("Sensority Reader Server");
    helpFormatter.format(std::cout);
}

unsigned short SensorReaderApplication::getServerPort() const
{
    return static_cast<unsigned short>(
                config().getUInt("server.port", DEFAULT_SERVER_PORT));
}

std::uint8_t SensorReaderApplication::getDevicePin() const
{
    return static_cast<std::uint8_t>(
                config().getUInt("reader.devicePin", DEFAULT_DEVICE_PIN));
}

SensorTypes SensorReaderApplication::getDeviceType() const
{
    return translateSensorTypeFromString(
                config().getString("reader.deviceType", DEFAULT_DEVICE_TYPE));
}
