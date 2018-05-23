/*
 * TemperatureSensorDataStorage.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "TemperatureSensorData.hpp"

TemperatureSensorData::TemperatureSensorData(double t, double h)
	: _temperature(t), _humidity(h)
{ }

formatter::Formatter::Values TemperatureSensorData::values() const
{
    formatter::Formatter::Values values;
    values.emplace(std::make_pair("temperature", _temperature));
    values.emplace(std::make_pair("humidity", _humidity));
    return values;
}
