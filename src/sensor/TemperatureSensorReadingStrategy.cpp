/*
 * TemperatureSensorReadingStrategy.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "TemperatureSensorReadingStrategy.hpp"

#include <cstdint>
#include <array>
#include <thread>
#include <chrono>

#include <Poco/Exception.h>

#include "System.hpp"
#include "DeviceCommon.hpp"
#include "DeviceLibrary.hpp"
#include "DeviceGpio.hpp"
#include "TemperatureSensorData.hpp"

static const int DHT_MAXCOUNT = 32000;
static const int DHT_PULSES = 41;

using device::DeviceLibrary;
using device::DeviceGpio;
using common::System;

void TemperatureSensorReadingStrategy::setup()
{
    DeviceLibrary::instance().initialize();
}

void TemperatureSensorReadingStrategy::cleanup()
{
    DeviceLibrary::instance().cleanup();
}

void TemperatureSensorReadingStrategy::pause(SensorTypes)
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

std::unique_ptr<SensorData> TemperatureSensorReadingStrategy::read(std::uint8_t pin, SensorTypes type)
{
    bool isRoot = System::isRoot();
    if (isRoot) {
        System::setCurrentThreadHighPriority();
    }

    std::array<std::uint64_t, DHT_PULSES * 2> pulseCounts = {{0}};

	try {
        DeviceGpio::Ptr gpio = DeviceLibrary::instance().gpio(pin);
        gpio->dir(device::PinDirs::outHigh);
        gpio->delay(500);
        gpio->write(device::PinLevels::low);
        gpio->delay(type == SensorTypes::dht11 ? 18 : 15);
        gpio->dir(device::PinDirs::in);
		for (volatile int i = 0; i < 50; ++i);

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

	std::uint64_t threshold = 0;
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
			return std::make_unique<TemperatureSensorData>(temperature, humidity);
	    }

		if (type == SensorTypes::dht22) {
            double humidity = (data[0] * 256 + data[1]) / 10.0;
            double temperature = ((data[2] & 0x7F) * 256 + data[3]) / 10.0;
			if (data[2] & 0x80) {
                temperature *= -1.0;
	    	}
			return std::make_unique<TemperatureSensorData>(temperature, humidity);
	    }

        throw Poco::RuntimeException("Unknown sensor type");
	}

    throw Poco::RuntimeException("Value checksum error");
}
