/*
 * DeviceLibrary.hpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef DEVICELIBRARY_HPP_
#define DEVICELIBRARY_HPP_

#define BCM2835_NO_DELAY_COMPATIBILITY

#include <bcm2835.h>

/**
 * @brief The PinDirs enum
 * Pin dirs
 */
enum class PinDirs {
	out, in, outHigh, outLow
};

/**
 * @brief The PinLevels enum
 * Pin levels
 */
enum class PinLevels {
	low = LOW, high = HIGH
};

#endif /* DEVICELIBRARY_HPP_ */
