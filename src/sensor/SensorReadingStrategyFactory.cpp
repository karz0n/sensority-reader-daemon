/*!
* \file SensorReadingStrategyFactory.cpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Feb 21, 2018
*/

#include "SensorReadingStrategyFactory.hpp"

#include <Poco/Exception.h>

#include "TemperatureSensorReadingStrategy.hpp"

namespace sensor {

SensorReadingStrategy::Ptr SensorReadingStrategyFactory::createReadingStrategy(SensorTypes type)
{
    if (isTemperatureSensor(type)) {
        return SensorReadingStrategyFactory::createTemperatureReadingStrategy();
    }

    throw Poco::InvalidArgumentException("Unknown sensor type");
}

SensorReadingStrategy::Ptr SensorReadingStrategyFactory::createTemperatureReadingStrategy()
{
    return SensorReadingStrategy::create<TemperatureSensorReadingStrategy>();
}

} // namespace sensor
