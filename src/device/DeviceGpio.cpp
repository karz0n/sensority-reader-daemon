/*
 * DeviceGpio.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "DeviceGpio.hpp"

#define BCM2835_NO_DELAY_COMPATIBILITY

#include <bcm2835.h>

#include <Poco/Exception.h>

namespace device {

DeviceGpio::DeviceGpio(PinNum pin)
    : _pin(pin)
{ }

void DeviceGpio::dir(PinDirs dir)
{
    switch (dir) {
    case PinDirs::in:
        bcm2835_gpio_fsel(_pin, BCM2835_GPIO_FSEL_INPT);
        break;
    case PinDirs::out:
        bcm2835_gpio_fsel(_pin, BCM2835_GPIO_FSEL_OUTP);
        break;
    case PinDirs::outHigh:
        bcm2835_gpio_fsel(_pin, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_write(_pin, HIGH);
        break;
    case PinDirs::outLow:
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

PinLevels DeviceGpio::read()
{
    return static_cast<PinLevels>(bcm2835_gpio_lev(_pin));
}

void DeviceGpio::write(PinLevels level)
{
    bcm2835_gpio_write(_pin, static_cast<uint8_t>(level));
}

unsigned long long DeviceGpio::count(PinLevels level, unsigned long long max)
{
    volatile unsigned long long count = 0;
    while (read() == level) {
        if (count++ == max) {
            throw Poco::LogicException("Max count reached");
        }
    }
    return count;
}

} // namespace device
