/*!
* \file SensorReadingStrategyFactory.hpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Feb 21, 2018
*/

#ifndef SENSORREADINGSTRATEGYFACTORY_HPP
#define SENSORREADINGSTRATEGYFACTORY_HPP

#include "SensorCommon.hpp"
#include "SensorReadingStrategy.hpp"

namespace sensor {

/*!
 * \addtogroup sensor
 * @{
 */

/*!
 * \brief The SensorReadingStrategyFactory class
 */
class SensorReadingStrategyFactory
{
public:
    /*!
     * \brief Create reading strategy object.
     * \param type device type.
     * \return object of strategy.
     */
    static SensorReadingStrategy::Ptr createReadingStrategy(SensorTypes type);

private:
    static SensorReadingStrategy::Ptr createTemperatureReadingStrategy();
};

/*! @} */

} // namespace sensor

#endif // SENSORREADINGSTRATEGYFACTORY_HPP
