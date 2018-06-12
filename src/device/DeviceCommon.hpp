/*!
 * \file DeviceCommon.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 21, 2018
 */

#ifndef DEVICECOMMON_HPP
#define DEVICECOMMON_HPP

namespace device {

/*!
 * \addtogroup device
 * @{
 */

/*!
 * \brief The Pin number type.
 */
using PinNum = unsigned char;

/*!
 * \brief The PinDirs enum.
 * \details Represents directions of pin.
 */
enum class PinDirs {
    out, in, outHigh, outLow
};

/*!
 * \brief The PinLevels enum.
 * \details Represents levels of pin state.
 */
enum class PinLevels {
    low = 0, high = 1
};

/*! @} */

} // namespace device

#endif // DEVICECOMMON_HPP
