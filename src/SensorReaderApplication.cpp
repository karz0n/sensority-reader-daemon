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

    unsigned int pin = getDevicePin();
    SensorTypes type = getDeviceType();
    auto strategy = getReadingStrategy(type);

    auto reader = std::make_unique<SensorReader>(
                      pin,
                      type,
                      std::move(strategy),
                      std::make_shared<SensorDataStorage>());

    HttpSensorReaderServer server(std::move(reader));
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

unsigned int SensorReaderApplication::getDevicePin()
{
    return config().getUInt("reader.devicePin", DEFAULT_DEVICE_PIN);
}

SensorTypes SensorReaderApplication::getDeviceType()
{
    std::string value = config().getString("reader.deviceType", DEFAULT_DEVICE_TYPE);
    return translateSensorTypeFromString(value);
}

SensorReadingStrategy::Ptr SensorReaderApplication::getReadingStrategy(SensorTypes deviceType)
{
    return SensorReadingStrategyFactory::createReadingStrategy(deviceType);
}



