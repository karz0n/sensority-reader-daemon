/*
 * DeviceGpio.h
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef DEVICEGPIO_H_
#define DEVICEGPIO_H_

#include <cstdint>
#include <limits>

#include "DeviceLibrary.hpp"

/**
 * @brief The DeviceGpio class
 */
class DeviceGpio
{
public:
    DeviceGpio(std::uint8_t pin);

	void dir(PinDirs dir);
	void delay(std::uint32_t millis);
	void delayMicroseconds(std::uint64_t micros);

	PinLevels read();
	void write(PinLevels level);
	std::uint64_t count(PinLevels level, std::uint64_t max = std::numeric_limits<std::uint64_t>::max());

private:
    std::uint8_t _pin;
};

#endif /* DEVICEGPIO_H_ */
