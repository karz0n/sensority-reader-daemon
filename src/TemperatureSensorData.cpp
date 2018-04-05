/*
 * TemperatureSensorDataStorage.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "TemperatureSensorData.h"

TemperatureSensorData::TemperatureSensorData(double t, double h)
	: _temperature(t), _humidity(h)
{ }

Formatter::Values TemperatureSensorData::values() const
{
    return {
        {std::string("temperature"), Formatter::Value(_temperature)},
        {std::string("humidity"), Formatter::Value(_humidity)}
    };
}
