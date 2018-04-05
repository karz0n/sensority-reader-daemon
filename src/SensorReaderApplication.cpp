/*
 * SensorReaderApplication.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "SensorReaderApplication.h"

#include <iostream>

#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/HelpFormatter.h>

#include "SensorCommon.h"
#include "SensorReader.h"
#include "SensorDataStorage.h"
#include "SensorReadingStrategyFactory.h"

#include "HttpSensorReaderServer.h"

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

    unsigned short port = getServerPort();

    unsigned int pin = getDevicePin();
    SensorTypes type = getDeviceType();
    auto strategy = getDeviceReadingStrategy(type);

    auto reader = std::make_unique<SensorReader>(
                      pin,
                      type,
                      std::move(strategy),
                      std::make_shared<SensorDataStorage>());

    HttpSensorReaderServer server(std::move(reader), port);
    server.run();
    waitForTerminationRequest();
    server.shutdown();

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

unsigned int SensorReaderApplication::getDevicePin() const
{
    return config().getUInt("reader.devicePin", DEFAULT_DEVICE_PIN);
}

SensorTypes SensorReaderApplication::getDeviceType() const
{
    std::string value = config().getString("reader.deviceType", DEFAULT_DEVICE_TYPE);
    return translateSensorTypeFromString(value);
}

std::unique_ptr<SensorReadingStrategy> SensorReaderApplication::getDeviceReadingStrategy(SensorTypes deviceType) const
{
    return SensorReadingStrategyFactory::createReadingStrategy(deviceType);
}



