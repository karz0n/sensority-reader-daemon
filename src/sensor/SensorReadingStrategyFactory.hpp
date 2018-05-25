/*
 * SensorReadingStrategyFactory.hpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADINGSTRATEGYFACTORY_HPP_
#define SENSORREADINGSTRATEGYFACTORY_HPP_

#include "SensorCommon.hpp"
#include "SensorReadingStrategy.hpp"

namespace sensor {

/**
 * @brief The SensorReadingStrategyFactory class
 */
class SensorReadingStrategyFactory
{
public:
    static SensorReadingStrategy::Ptr createReadingStrategy(SensorTypes type);

private:
    static SensorReadingStrategy::Ptr createTemperatureReadingStrategy();
};

} // namespace sensor

#endif // SENSORREADINGSTRATEGYFACTORY_HPP_
