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

#include "common/Thread.hpp"

using Poco::Util::Application;
using Poco::Util::OptionSet;
using Poco::Util::Option;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;

using connectivity::HttpDataServer;
using sensor::SensorTypes;
using sensor::SensorReader;
using sensor::SensorReadableData;

/**
 * @brief Default device pin value
 */
static const int DEFAULT_DEVICE_PIN = 22;

/**
 * @brief Default device type value
 */
static const std::string DEFAULT_DEVICE_TYPE {"DHT22"};

/**
 * @brief Default http enable state
 */
static const bool DEFAULT_HTTP_ENABLE = false;

/**
 * @brief Default http server port
 */
static const int DEFAULT_HTTP_PORT = 8080;

/**
 * @brief Default HTTP data format
 */
static const std::string DEFAULT_HTTP_FORMAT {"json"};

App::App()
	: _helpRequested(false)
{ }

App::~App()
{ }

void App::initialize(Application& self)
{
	loadConfiguration();
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

    options.addOption(
        Option("devicePin", "s", "Set reader device pin")
            .required(false)
            .repeatable(false)
            .argument("value")
            .binding("reader.devicePin"));

    options.addOption(
        Option("deviceType", "t", "Set reader device type")
            .required(false)
            .repeatable(false)
            .argument("value")
            .binding("reader.deviceType"));

    options.addOption(
        Option("http", "", "Enable http publisher")
            .required(false)
            .repeatable(false)
            .argument("value")
            .binding("http.enable"));

    options.addOption(
        Option("httpPort", "", "Set HTTP server port. Valid value is a number from 1024 to 65535.")
            .required(false)
            .repeatable(false)
            .argument("value")
            .binding("http.port"));

    options.addOption(
        Option("httpFormat", "", "Set HTTP server data format. Valid value is 'json' or 'string'")
            .required(false)
            .repeatable(false)
            .argument("value")
            .binding("http.format"));
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
        std::unique_ptr<SensorReader> reader = createSensorReader();

        common::Thread thread(*reader);

        std::unique_ptr<HttpDataServer> server;
        bool httpEnabled = isHttpEnabled();
        if (httpEnabled) {
            server = createHttpServer(reader->data());
        }

        if (server) {
            server->run();
        }

        waitForTerminationRequest();

        if (server) {
            server->shutdown();
        }

        reader->stop();
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

SensorReader::Ptr App::createSensorReader()
{
    return SensorReader::create(getDevicePin(), getDeviceType());
}

HttpDataServer::Ptr App::createHttpServer(SensorReadableData::Ptr data)
{
    return HttpDataServer::create(getHttpPort(), getHttpFormat(), data);
}

bool App::isHttpEnabled() const
{
    const Option& option = options().getOption("http");
    try {
        return config().getBool(option.binding(), DEFAULT_HTTP_ENABLE);
    }
    catch (Poco::SyntaxException&) {
        throw Poco::InvalidArgumentException(
            Poco::format("argument for '%s' (%s) must be boolean",
                         option.fullName(), option.binding()));
    }
}

unsigned short App::getHttpPort() const
{
    const Option& option = options().getOption("httpPort");
    try {
        return static_cast<unsigned short>(config().getUInt(option.binding(), DEFAULT_HTTP_PORT));
    }
    catch (Poco::SyntaxException&) {
        throw Poco::InvalidArgumentException(
            Poco::format("argument for '%s' (%s) must be an integer",
                         option.fullName(), option.binding()));
    }
}

std::string App::getHttpFormat() const
{
    const Option& option = options().getOption("httpFormat");
    std::string value = config().getString(option.binding(), DEFAULT_HTTP_FORMAT);
    std::regex re("^json|string$", std::regex_constants::icase);
    if (!std::regex_match(value, re)) {
        throw Poco::InvalidArgumentException(
            Poco::format("argument for '%s' (%s) must equals 'json' or 'string'",
                         option.fullName(), option.binding()));
    }
    return value;
}

device::PinNum App::getDevicePin() const
{
    const Option& option = options().getOption("devicePin");
    try {
        return static_cast<device::PinNum>(config().getUInt(option.binding(), DEFAULT_DEVICE_PIN));
    } catch (Poco::SyntaxException&) {
        throw Poco::InvalidArgumentException(
            Poco::format("argument for '%s' (%s) must be an integer",
                         option.fullName(), option.binding()));
    }
}

SensorTypes App::getDeviceType() const
{
    const Option& option = options().getOption("deviceType");
    std::string value = config().getString(option.binding(), DEFAULT_DEVICE_TYPE);
    std::regex re("^dht(11|22)$", std::regex_constants::icase);
    if (!std::regex_match(value, re)) {
        throw Poco::InvalidArgumentException(
            Poco::format("argument for '%s' (%s) must equals valid device type",
                         option.fullName(), option.binding()));
    }
    return sensor::translateSensorTypeFromString(value);
}

//
// Define main entry
//
POCO_SERVER_MAIN(App)
