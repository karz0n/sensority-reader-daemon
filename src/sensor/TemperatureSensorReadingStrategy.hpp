/*!
* \file TemperatureSensorReadingStrategy.hpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Feb 21, 2018
*/

#ifndef TEMPERATURESENSORREADINGSTRATEGY_HPP
#define TEMPERATURESENSORREADINGSTRATEGY_HPP

#include "SensorData.hpp"
#include "SensorReadingStrategy.hpp"

namespace sensor {

/*!
 * \addtogroup sensor
 * @{
 */

/*!
 * \brief The TemperatureSensorReadingStrategy class
 */
class TemperatureSensorReadingStrategy : public SensorReadingStrategy {
public:
    void setup() override;
    void cleanup() override;
    std::chrono::milliseconds pauseLength(SensorTypes type) override;

    inline bool needPause(SensorTypes) const override
    {
        return true;
    }

    SensorData::Ptr read(device::PinNum pin, SensorTypes type) override;
};

/*! @} */

} // namespace sensor

#endif // TEMPERATURESENSORREADINGSTRATEGY_HPP
