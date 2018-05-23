/*
 * TemperatureSensorData.hpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef TEMPERATURESENSORDATA_HPP_
#define TEMPERATURESENSORDATA_HPP_

#include <string>

#include "Formatter.hpp"
#include "SensorData.hpp"

/**
 * @brief The TemperatureSensorData class
 */
class TemperatureSensorData: public SensorData {
public:
    TemperatureSensorData(double temperature, double humidity);

    inline double getTemperature();
    inline double getHumidity();

    formatter::Formatter::Values values() const override;

private:
    double _temperature;
    double _humidity;
};

//
// Inlines
//

double TemperatureSensorData::getTemperature()
{
	return _temperature;
}

double TemperatureSensorData::getHumidity()
{
	return _humidity;
}

#endif /* TEMPERATURESENSORDATA_HPP_ */
