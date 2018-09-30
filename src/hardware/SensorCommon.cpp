/*!
 * \file SensorCommon.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Feb 21, 2018
 */

#include "SensorCommon.hpp"

#include <regex>

#include <Poco/Exception.h>
#include <Poco/String.h>

namespace hardware {

bool verifyTypeAsString(const std::string& value)
{
    static std::regex re("^dht(11|22)$", std::regex_constants::icase);
    return std::regex_match(value, re);
}

SensorTypes translateSensorTypeFromString(const std::string& value)
{
    std::string s = Poco::toLower(Poco::trim(value));

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

} // namespace hardware
