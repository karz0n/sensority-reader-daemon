/*
 * SensorReadingStrategy.h
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "SensorReadingStrategyFactory.hpp"

#include <memory>

#include <Poco/Exception.h>

#include "TemperatureSensorReadingStrategy.hpp"

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