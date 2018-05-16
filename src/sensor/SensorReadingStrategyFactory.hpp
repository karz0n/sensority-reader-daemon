/*
 * SensorReadingStrategyFactory.hpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADINGSTRATEGYFACTORY_HPP_
#define SENSORREADINGSTRATEGYFACTORY_HPP_

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

#endif // SENSORREADINGSTRATEGYFACTORY_HPP_
