/*
 * DeviceCommon.hpp
 *
 *  Created on: Mar 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef DEVICECOMMON_HPP_
#define DEVICECOMMON_HPP_

namespace device {

/**
 * Pin number
 */
using PinNum = unsigned char;

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
    low = 0, high = 1
};

} // namespace device

#endif // DEVICECOMMON_HPP_
