/*
 * SensorCommon.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "SensorCommon.h"

#include <Poco/Exception.h>
#include <Poco/String.h>

SensorTypes translateSensorTypeFromString(const std::string& value)
{
    std::string s = Poco::trim(Poco::toLower(value));

    if (s == "dht11") {
        return SensorTypes::dht11;
    }
    if (s == "dht22") {
        return SensorTypes::dht22;
    }

    throw Poco::InvalidArgumentException("Unknown sensor type string value");
}

bool isTemperatureSensor(SensorTypes type)
{
   return (type == SensorTypes::dht11 || type == SensorTypes::dht22);
}
