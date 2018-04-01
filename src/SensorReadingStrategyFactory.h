#ifndef SENSORREADINGSTRATEGYFACTORY_H
#define SENSORREADINGSTRATEGYFACTORY_H

#include "SensorCommon.h"
#include "SensorReadingStrategy.h"

/**
 * @brief The SensorReadingStrategyFactory class
 */
class SensorReadingStrategyFactory
{
public:
    static SensorReadingStrategy::Ptr createReadingStrategy(SensorTypes type);
    static SensorReadingStrategy::Ptr createTemperatureReadingStrategy();
};

#endif // SENSORREADINGSTRATEGYFACTORY_H
