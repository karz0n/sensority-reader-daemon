#ifndef SENSORREADINGSTRATEGYFACTORY_H
#define SENSORREADINGSTRATEGYFACTORY_H

#include <memory>

#include "SensorCommon.h"
#include "SensorReadingStrategy.h"

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
