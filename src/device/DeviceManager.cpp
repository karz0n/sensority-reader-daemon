/*
 * DeviceManager.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "DeviceManager.hpp"
#include "DeviceLibrary.hpp"

#include <Poco/Exception.h>

DeviceManager& DeviceManager::getInstance()
{
	static DeviceManager deviceManager;
	return deviceManager;
}

DeviceManager::DeviceManager()
	: _initialized(false)
{ }

void DeviceManager::initialize()
{
    poco_assert_msg(!_initialized, "Device has already initialized");

	int retVal = bcm2835_init();
	if (!retVal) {
        throw Poco::RuntimeException("Initialize BCM2835 library");
	}

	_initialized = true;
}

void DeviceManager::close()
{
    poco_assert_msg(_initialized, "Device not initialized");

	int retVal = bcm2835_close();
	if (!retVal) {
        throw Poco::RuntimeException("Close BCM2835 library");
	}

	_initialized = false;
}

DeviceGpio DeviceManager::gpio(std::uint8_t pin) const
{
    poco_assert_msg(_initialized, "Device not initialized");

	return DeviceGpio(pin);
}
