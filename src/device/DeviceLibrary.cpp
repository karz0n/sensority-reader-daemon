/*
 * DeviceLibrary.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "DeviceLibrary.hpp"

#include <bcm2835.h>

#include <Poco/Exception.h>

namespace device {

DeviceLibrary& DeviceLibrary::instance()
{
    static DeviceLibrary library;
    return library;
}

DeviceLibrary::DeviceLibrary()
    : _counter(0)
{ }

DeviceLibrary::~DeviceLibrary()
{
    if (isInitialized()) {
        cleanup();
    }
}

void DeviceLibrary::initialize()
{
    if (_counter++ > 0) {
        return;
    }

    int rc = bcm2835_init();
    if (!rc) {
        throw Poco::RuntimeException("Initialize BCM2835 library");
    }
}

void DeviceLibrary::cleanup()
{
    if (--_counter > 0) {
        return;
    }

    int rc = bcm2835_close();
    if (!rc) {
        throw Poco::RuntimeException("Close BCM2835 library");
    }
}

DeviceGpio::Ptr DeviceLibrary::gpio(PinNum pin)
{
    if (!isInitialized()) {
        initialize();
    }

    return DeviceGpio::create(pin);
}

} // namespace device
