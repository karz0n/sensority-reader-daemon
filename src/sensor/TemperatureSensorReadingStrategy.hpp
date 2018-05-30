/*
 * TemperatureSensorReadingStrategy.hpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef TEMPERATURESENSORREADINGSTRATEGY_HPP_
#define TEMPERATURESENSORREADINGSTRATEGY_HPP_

#include "SensorData.hpp"
#include "SensorReadingStrategy.hpp"

namespace sensor {

class TemperatureSensorReadingStrategy : public SensorReadingStrategy {
public:
    void setup() override;
    void cleanup() override;
    std::chrono::milliseconds pauseLength(SensorTypes type) override;
    inline bool needPause(SensorTypes type) const override;
    SensorData::Ptr read(device::PinNum pin, SensorTypes type) override;
};

//
// Inlines
//

bool TemperatureSensorReadingStrategy::needPause(SensorTypes) const
{
    return true;
}

} // namespace sensor

#endif /* TEMPERATURESENSORREADINGSTRATEGY_HPP_ */
