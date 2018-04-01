/*
 * DeviceGpio.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "DeviceGpio.h"

#include <Poco/Exception.h>

DeviceGpio::DeviceGpio(std::uint8_t pin)
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

void DeviceGpio::delay(std::uint32_t millis)
{
	bcm2835_delay(millis);
}

void DeviceGpio::delayMicroseconds(std::uint64_t micros)
{
	bcm2835_delayMicroseconds(micros);
}

PinLevels DeviceGpio::read()
{
	std::uint8_t value = bcm2835_gpio_lev(_pin);
	return PinLevels(value);
}

void DeviceGpio::write(PinLevels level)
{
	std::uint8_t value = std::uint8_t(level);
	bcm2835_gpio_write(_pin, value);
}

std::uint64_t DeviceGpio::count(PinLevels level, std::uint64_t max)
{
	std::uint64_t count = 0;
	while (read() == level) {
        if (count++ == max) {
            throw Poco::LogicException("Max count reached");
        }
	}
	return count;
}


