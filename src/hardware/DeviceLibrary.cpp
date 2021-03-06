/*!
 * \file DeviceLibrary.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 4, 2018
 */

#include "DeviceLibrary.hpp"

#include <bcm2835.h>

#include <Poco/Exception.h>

namespace hardware {

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
    poco_assert_msg(_counter > 0, "Library not inialized");

    if (--_counter > 0) {
        return;
    }

    int rc = bcm2835_close();
    if (!rc) {
        throw Poco::RuntimeException("Close BCM2835 library");
    }
}

DeviceGpio::Ptr DeviceLibrary::gpio(DevicePinNum pin)
{
    if (!isInitialized()) {
        initialize();
    }

    return DeviceGpio::create(pin);
}

} // namespace device
