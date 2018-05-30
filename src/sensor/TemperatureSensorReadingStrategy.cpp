/*
 * TemperatureSensorReadingStrategy.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "TemperatureSensorReadingStrategy.hpp"

#include <array>

#include <Poco/Exception.h>

#include "common/System.hpp"
#include "device/DeviceLibrary.hpp"
#include "device/DeviceGpio.hpp"

#include "TemperatureSensorData.hpp"

using common::System;
using device::DeviceLibrary;
using device::DeviceGpio;

/**
 * @brief DHT_MAXCOUNT
 */
static const int DHT_MAXCOUNT = 32000;

/**
 * @brief DHT_PULSES
 */
static const int DHT_PULSES = 41;

namespace sensor {

void TemperatureSensorReadingStrategy::setup()
{
    DeviceLibrary::instance().initialize();
}

void TemperatureSensorReadingStrategy::cleanup()
{
    DeviceLibrary::instance().cleanup();
}

std::chrono::milliseconds TemperatureSensorReadingStrategy::pauseLength(SensorTypes)
{
    return std::chrono::milliseconds(2000);
}

SensorData::Ptr TemperatureSensorReadingStrategy::read(device::PinNum pin, SensorTypes type)
{
    bool isRoot = System::isRoot();
    if (isRoot) {
        System::setCurrentThreadHighPriority();
    }

    std::array<unsigned long long, DHT_PULSES * 2> pulseCounts = {{0}};

    try {
        DeviceGpio::Ptr gpio = DeviceLibrary::instance().gpio(pin);
        gpio->dir(device::PinDirs::outHigh);
        gpio->delay(500);
        gpio->write(device::PinLevels::low);
        gpio->delay(type == SensorTypes::dht11 ? 18 : 15);
        gpio->dir(device::PinDirs::in);

        gpio->count(device::PinLevels::high, DHT_MAXCOUNT);

        for (std::size_t i = 0; i < DHT_PULSES * 2; i += 2) {
            pulseCounts[i] = gpio->count(device::PinLevels::low, DHT_MAXCOUNT);
            pulseCounts[i + 1] = gpio->count(device::PinLevels::high, DHT_MAXCOUNT);
        }

        if (isRoot) {
            System::setCurrentThreadDefaultPriority();
        }
    } catch (...) {
        if (isRoot) {
            System::setCurrentThreadDefaultPriority();
        }
        throw;
    }

    unsigned long long threshold = 0;
    for (std::size_t i = 2; i < DHT_PULSES * 2; i += 2) {
        threshold += pulseCounts[i];
    }
    threshold /= DHT_PULSES - 1;

    std::array<unsigned char, 5> data;
    for (std::size_t i = 3; i < DHT_PULSES * 2; i += 2) {
        std::size_t index = (i - 3) / 16;
        data[index] <<= 1;
        if (pulseCounts[i] >= threshold) {
            data[index] |= 1;
        }
    }

    if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
        if (type == SensorTypes::dht11) {
            double temperature = data[2];
            double humidity = data[0];
            return SensorData::create<TemperatureSensorData>(temperature, humidity);
        }

        if (type == SensorTypes::dht22) {
            double humidity = (data[0] * 256 + data[1]) / 10.0;
            double temperature = ((data[2] & 0x7F) * 256 + data[3]) / 10.0;
            if (data[2] & 0x80) {
                temperature *= -1.0;
            }
            return SensorData::create<TemperatureSensorData>(temperature, humidity);
        }

        throw Poco::RuntimeException("Unknown sensor type");
    }

    throw Poco::RuntimeException("Value checksum error");
}

} // namespace sensor
