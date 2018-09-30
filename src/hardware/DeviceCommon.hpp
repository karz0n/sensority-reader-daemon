/*!
 * \file DeviceCommon.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 21, 2018
 */

#ifndef DEVICECOMMON_HPP
#define DEVICECOMMON_HPP

namespace hardware {

/*!
 * \addtogroup hardware
 * @{
 */

/*!
 * \brief The Pin number type.
 */
using DevicePinNum = unsigned char;

/*!
 * \brief Represents directions of pin.
 */
enum class DevicePinDirs {
    out, in, outHigh, outLow
};

/*!
 * \brief Represents levels of pin state.
 */
enum class DevicePinLevels {
    low = 0, high = 1
};

/*! @} */

} // namespace hardware

#endif // DEVICECOMMON_HPP
