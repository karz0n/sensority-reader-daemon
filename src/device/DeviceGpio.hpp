/*!
 * \file DeviceGpio.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 4, 2018
 */

#ifndef DEVICEGPIO_HPP
#define DEVICEGPIO_HPP

#include <limits>
#include <memory>

#include "DeviceCommon.hpp"

namespace device {

/*!
 * \addtogroup device
 * @{
 */

/*!
 * \brief Default max count value.
 */
const unsigned long long DEVICE_MAX_COUNT = std::numeric_limits<unsigned long long>::max();

/*!
 * \brief The DeviceGpio class.
 * \details Helper class to work with GPIO.
 */
class DeviceGpio
{
public:
    using Ptr = std::shared_ptr<DeviceGpio>; //!< The pointer type of class.

    DeviceGpio(PinNum pin); //!< Construct class with specific number of pin.

    /*!
     * \brief Specify direction of pin.
     * \param dir specific direction.
     */
    void dir(PinDirs dir);

    /*!
     * \brief Perform delay in current thread.
     * \param millis length of delay in milliseconds.
     */
    void delay(unsigned int millis);

    /*!
     * \brief Perform delay in current thread.
     * \param micros length of delay in microseconds.
     */
    void delayMicroseconds(unsigned long long micros);

    /*!
     * \brief Get pin level value.
     * \return level of pin value.
     */
    PinLevels read();

    /*!
     * \brief Set pin level value.
     * \param level level of pin value.
     */
    void write(PinLevels level);

    /*!
     * \brief Count number of ticks till pin has specified level value.
     * \param level specific level value.
     * \param max maximum number of ticks.
     * \return number of ticks.
     */
    unsigned long long count(PinLevels level, unsigned long long max = DEVICE_MAX_COUNT);

public:
    /*!
     * Device gpio factory method
     */
    template<typename ...As>
    static Ptr create(As&&... args)
    {
        return std::make_shared<DeviceGpio>(std::forward<As>(args)...);
    }

private:
    PinNum _pin;
};

/*! @} */

} // namespace device

#endif // DEVICEGPIO_HPP
