#include "SensorReadingStrategyFactory.h"

#include <memory>

#include <Poco/Exception.h>

#include "TemperatureSensorReadingStrategy.h"

SensorReadingStrategy::Ptr SensorReadingStrategyFactory::createReadingStrategy(SensorTypes type)
{
    if (isTemperatureSensor(type)) {
        return SensorReadingStrategyFactory::createTemperatureReadingStrategy();
    }

    throw Poco::InvalidArgumentException("Unknown sensor type");
}

SensorReadingStrategy::Ptr SensorReadingStrategyFactory::createTemperatureReadingStrategy()
{
    return std::make_unique<TemperatureSensorReadingStrategy>();
}
