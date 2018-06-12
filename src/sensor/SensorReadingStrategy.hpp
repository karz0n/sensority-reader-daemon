/*!
* \file SensorReadingStrategy.hpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Feb 21, 2018
*/

#ifndef SENSORREADINGSTRATEGY_HPP
#define SENSORREADINGSTRATEGY_HPP

#include <memory>
#include <chrono>
#include <utility>

#include "device/DeviceCommon.hpp"

#include "SensorCommon.hpp"
#include "SensorData.hpp"

namespace sensor {

/*!
 * \addtogroup sensor
 * @{
 */

/**
 * @brief The SensorReadingStrategy class.
 * Base class of reading strategies.
 */
class SensorReadingStrategy {
public:
    using Ptr = std::unique_ptr<SensorReadingStrategy>; //!< Type of pointer to the class object.

    virtual ~SensorReadingStrategy() = default;

    /*!
     * \brief Setup environment.
     * \details Called once before reading will start.
     */
    virtual void setup() = 0;

    /*!
     * \brief Cleanup environment.
     * \details Called once after reading has finished.
     */
    virtual void cleanup() = 0;

    /*!
     * \brief Return amount of time in milliseconds.
     * \details Called to obtain amount of time which need to pause after each read cycle.
     * \param type device type.
     * \return amount of time.
     */
    virtual std::chrono::milliseconds pauseLength(SensorTypes type) = 0;

    /**
     * @brief Indicate if pause is necessary.
     * @param type device type.
     * @return The flag that indicate if pause is necessary.
     */

    /*!
     * \brief Indicate if pause is necessary.
     * \param type device type.
     * \return flag which indicate that pause is necessary.
     */
    virtual bool needPause(SensorTypes type) const = 0;

    /*!
     * \brief Read data.
     * \details Called on each step of reading cycle.
     * \param pin pin number.
     * \param type device type.
     * \return the pointer to the data object.
     */
    virtual SensorData::Ptr read(device::PinNum pin, SensorTypes type) = 0;

 public:
    /*!
     * Sensor reading strategy factory method
     */
    template <typename T, typename ...As>
    static Ptr create(As&&... args)
    {
        return std::make_unique<T>(std::forward<As>(args)...);
    }
};

/*! @} */

} // namespace sensor

#endif // SENSORREADINGSTRATEGY_HPP
