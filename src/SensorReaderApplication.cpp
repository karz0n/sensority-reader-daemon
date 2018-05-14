/*
 * SensorReaderApplication.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "SensorReaderApplication.hpp"

#include "sensor/SensorReader.hpp"
#include "http/HttpDataServer.hpp"

#include <string>
#include <iostream>
#include <exception>

#include <Poco/NumberParser.h>
#include <Poco/Exception.h>
#include <Poco/Util/Validator.h>
#include <Poco/Util/IntValidator.h>
#include <Poco/Util/RegExpValidator.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/HelpFormatter.h>

using Poco::Util::Validator;
using Poco::Util::Application;
using Poco::Util::OptionSet;
using Poco::Util::Option;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Util::IntValidator;
using Poco::Util::RegExpValidator;

/**
 * @brief Default server port
 */
static const std::string DEFAULT_SERVER_PORT {"8080"};

/**
 * @brief Default device pin value
 */
static const std::string DEFAULT_DEVICE_PIN {"22"};

/**
 * @brief Default device type value
 */
static const std::string DEFAULT_DEVICE_TYPE {"DHT22"};

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
        Option("port", "p", "Set HTTP server port. Valid value is a number from 1024 to 65535.")
            .required(false)
            .repeatable(false)
            .argument("value")
            .validator(new IntValidator(1024, 65535))
            .binding("server.port"));

    options.addOption(
        Option("devicePin", "s", "Set reader device pin")
            .required(false)
            .repeatable(false)
            .argument("value")
            .validator(new IntValidator(0, 31))
            .binding("reader.devicePin"));

    options.addOption(
        Option("deviceType", "t", "Set reader device type")
            .required(false)
            .repeatable(false)
            .argument("value")
            .validator(new RegExpValidator("(?i)dht(11|22)"))
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
        std::uint8_t devicePin = getDevicePin();
        SensorTypes deviceType = getDeviceType();
        SensorReader reader(devicePin, deviceType);

        unsigned short port = getServerPort();
        HttpDataServer server(port, reader.storage());

        reader.run();
        server.run();

        waitForTerminationRequest();

        server.shutdown();
        reader.shutdown();
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
    const Option& option = options().getOption("port");

    Validator* validator = option.validator();
    poco_check_ptr(validator);

    std::string value = config().getString(option.binding(), DEFAULT_SERVER_PORT);
    validator->validate(option, value);

    return static_cast<unsigned short>(Poco::NumberParser::parseUnsigned(value));
}

std::uint8_t SensorReaderApplication::getDevicePin() const
{
    const Option& option = options().getOption("devicePin");

    Validator* validator = option.validator();
    poco_check_ptr(validator);

    std::string value = config().getString(option.binding(), DEFAULT_DEVICE_PIN);
    validator->validate(option, value);

    return static_cast<std::uint8_t>(Poco::NumberParser::parseUnsigned(value));
}

SensorTypes SensorReaderApplication::getDeviceType() const
{
    const Option& option = options().getOption("deviceType");

    Validator* validator = option.validator();
    poco_check_ptr(validator);

    std::string value = config().getString(option.binding(), DEFAULT_DEVICE_TYPE);
    validator->validate(option, value);

    return translateSensorTypeFromString(value);
}
