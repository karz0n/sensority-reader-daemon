/*
 * TemperatureSensorReadingStrategy.h
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef TEMPERATURESENSORREADINGSTRATEGY_H_
#define TEMPERATURESENSORREADINGSTRATEGY_H_

#include <memory>

#include "SensorData.hpp"
#include "SensorReadingStrategy.hpp"

class TemperatureSensorReadingStrategy: public SensorReadingStrategy {
public:
	void setup() override;
	void cleanup() override;
	void pause(SensorTypes type) override;
    inline bool needPause(SensorTypes type) const override;
    std::unique_ptr<SensorData> read(std::uint8_t pin, SensorTypes type) override;
};

//
// Inlines
//

bool TemperatureSensorReadingStrategy::needPause(SensorTypes) const
{
    return true;
}

#endif /* TEMPERATURESENSORREADINGSTRATEGY_H_ */
