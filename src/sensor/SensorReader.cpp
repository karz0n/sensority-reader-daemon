/*
 * SensorReader.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "SensorReader.hpp"

#include <exception>

#include <Poco/Exception.h>
#include <Poco/Util/Application.h>

#include "sensor/SensorDataStorage.hpp"
#include "sensor/SensorReadingStrategyFactory.hpp"

using Poco::Util::Application;

namespace sensor {

SensorReader::SensorReader(device::PinNum p, SensorTypes t)
    : _pin(p), _type(t), _runned(false)
{
    _strategy = SensorReadingStrategyFactory::createReadingStrategy(t);
    _storage = SensorDataStorage::create();
}

SensorReader::~SensorReader()
{
    if (isRunned()) {
        shutdown();
    }
}

void SensorReader::run()
{
    _thread = std::thread(&SensorReader::handler, this);
    _runned = true;
}

void SensorReader::shutdown()
{
    if (_thread.joinable()) {
        _thread.join();
    }
    _runned = false;
}

void SensorReader::handler()
{
    _strategy->setup();
    while(_runned) {
        try {
            auto data = _strategy->read(_pin, _type);
            _storage->update(std::move(data));
        }
        catch (const Poco::Exception& e) {
            Application& app = Application::instance();
            app.logger().error(e.displayText());
        }
        catch (const std::exception& e) {
            Application& app = Application::instance();
            app.logger().error(e.what());
        }
        catch (...) {
            Application& app = Application::instance();
            app.logger().error("Unknown error");
        }

        if (_strategy->needPause(_type)) {
            _strategy->pause(_type);
        }
    }
    _strategy->cleanup();
}

} // namespace sensor
