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

#include "SensorReadingStrategy.hpp"
#include "SensorReadingStrategyFactory.hpp"

using Poco::Util::Application;

namespace sensor {

SensorReader::SensorReader(device::PinNum p, SensorTypes t)
    : _pin(p), _type(t)
{
    _storage = SensorDataStorage::create();
}

void SensorReader::doStart()
{
    SensorReadingStrategy::Ptr strategy = SensorReadingStrategyFactory::createReadingStrategy(_type);

    strategy->setup();
    while(isProceed()) {
        try {
            _storage->update(strategy->read(_pin, _type));
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

        if (strategy->needPause(_type)) {
            sleepFor(strategy->pauseLength(_type));
        }
    }
    strategy->cleanup();
}

void SensorReader::doStop()
{
    // TODO:
    //    Reset storage to empty state
}

} // namespace sensor
