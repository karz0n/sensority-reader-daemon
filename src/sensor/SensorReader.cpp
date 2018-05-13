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

using Poco::Util::Application;

SensorReader::SensorReader(std::uint8_t p,
                           SensorTypes t,
                           std::unique_ptr<SensorReadingStrategy> srs,
                           std::shared_ptr<SensorDataStorage> sts)
    : _pin(p), _type(t), _strategy(std::move(srs)), _storage(sts), _runned(false)
{ }

void SensorReader::run()
{
    _runned = true;
    _thread = std::thread(&SensorReader::handler, this);
}

void SensorReader::shutdown()
{
	_thread.join();
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
            app.logger().error(e.message());
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
