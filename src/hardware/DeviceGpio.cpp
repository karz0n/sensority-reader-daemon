/*!
 * \file DeviceGpio.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 4, 2018
 */

#include "DeviceGpio.hpp"

#define BCM2835_NO_DELAY_COMPATIBILITY

#include <bcm2835.h>

#include <Poco/Exception.h>

namespace hardware {

DeviceGpio::DeviceGpio(DevicePinNum pin)
    : _pin(pin)
{ }

void DeviceGpio::dir(DevicePinDirs dir)
{
    switch (dir) {
    case DevicePinDirs::in:
        bcm2835_gpio_fsel(_pin, BCM2835_GPIO_FSEL_INPT);
        break;
    case DevicePinDirs::out:
        bcm2835_gpio_fsel(_pin, BCM2835_GPIO_FSEL_OUTP);
        break;
    case DevicePinDirs::outHigh:
        bcm2835_gpio_fsel(_pin, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_write(_pin, HIGH);
        break;
    case DevicePinDirs::outLow:
        bcm2835_gpio_fsel(_pin, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_write(_pin, LOW);
        break;
    }
}

void DeviceGpio::delay(unsigned int millis)
{
    bcm2835_delay(millis);
}

void DeviceGpio::delayMicroseconds(unsigned long long micros)
{
    bcm2835_delayMicroseconds(micros);
}

DevicePinLevels DeviceGpio::read()
{
    return static_cast<DevicePinLevels>(bcm2835_gpio_lev(_pin));
}

void DeviceGpio::write(DevicePinLevels level)
{
    bcm2835_gpio_write(_pin, static_cast<uint8_t>(level));
}

unsigned long long DeviceGpio::count(DevicePinLevels level, unsigned long long max)
{
    volatile unsigned long long count = 0;
    while (read() == level) {
        if (count++ == max) {
            throw Poco::LogicException("Max count reached");
        }
    }
    return count;
}

} // namespace hardware
