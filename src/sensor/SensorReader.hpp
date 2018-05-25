/*
 * SensorReader.hpp
 *
 *  Created on: Feb 28, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADER_HPP_
#define SENSORREADER_HPP_

#include <thread>
#include <atomic>
#include <memory>

#include "device/DeviceCommon.hpp"

#include "SensorCommon.hpp"
#include "SensorReadingStrategy.hpp"
#include "SensorReadableData.hpp"
#include "SensorDataStorage.hpp"

namespace sensor {

/**
 * Sensor reader class
 */
class SensorReader {
public:
    SensorReader(device::PinNum pin, SensorTypes type);
    virtual ~SensorReader();

    inline SensorReadableData::Ptr data() const;

    inline bool isRunned() const;
    void run();
    void shutdown();

private:
    void handler();

private:
    device::PinNum _pin;
    SensorTypes _type;
    std::unique_ptr<SensorReadingStrategy> _strategy;
    SensorDataStorage::Ptr _storage;
    std::thread _thread;
    std::atomic<bool> _runned;
};

//
// Inlines
//

bool SensorReader::isRunned() const
{
    return _runned;
}

SensorReadableData::Ptr SensorReader::data() const
{
    return _storage;
}

} // namespace sensor

#endif /* SENSORREADER_HPP_ */
