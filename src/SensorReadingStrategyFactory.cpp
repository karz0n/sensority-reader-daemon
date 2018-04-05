#include "SensorReadingStrategyFactory.h"

#include <memory>

#include <Poco/Exception.h>

#include "TemperatureSensorReadingStrategy.h"

std::unique_ptr<SensorReadingStrategy> SensorReadingStrategyFactory::createReadingStrategy(SensorTypes type)
{
    if (isTemperatureSensor(type)) {
        return SensorReadingStrategyFactory::createTemperatureReadingStrategy();
    }

    throw Poco::InvalidArgumentException("Unknown sensor type");
}

std::unique_ptr<SensorReadingStrategy> SensorReadingStrategyFactory::createTemperatureReadingStrategy()
{
    return std::make_unique<TemperatureSensorReadingStrategy>();
}
