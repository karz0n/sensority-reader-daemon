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

std::string TemperatureSensorData::format(const Formatter& formatter) const
{
	Formatter::Values values;
	values.emplace(std::string("temperature"), Formatter::Value(_temperature));
	values.emplace(std::string("humidity"), Formatter::Value(_humidity));
	return formatter.format(values);
}
