/*
 * SensorReadingStrategyFactory.h
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADINGSTRATEGYFACTORY_H
#define SENSORREADINGSTRATEGYFACTORY_H

#include <memory>

#include "SensorCommon.hpp"
#include "SensorReadingStrategy.hpp"

/**
 * @brief The SensorReadingStrategyFactory class
 */
class SensorReadingStrategyFactory
{
public:
    static std::unique_ptr<SensorReadingStrategy> createReadingStrategy(SensorTypes type);

    static std::unique_ptr<SensorReadingStrategy> createTemperatureReadingStrategy();
};

#endif // SENSORREADINGSTRATEGYFACTORY_H