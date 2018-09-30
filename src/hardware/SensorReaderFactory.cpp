/*!
* \file SensorReaderFactory.cpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Feb 21, 2018
*/

#include "SensorReaderFactory.hpp"

#include <Poco/Exception.h>

#include "TemperatureSensorReader.hpp"

namespace hardware {

SensorReader::Ptr SensorReaderFactory::createReader(
        data::Storage::Ptr storage,
        DevicePinNum pin,
        SensorTypes type)
{
    if (isTemperatureSensor(type)) {
        return std::make_unique<TemperatureSensorReader>(storage, pin, type);
    }

    throw Poco::InvalidArgumentException("Unknown sensor type");
}

} // namespace hardware
