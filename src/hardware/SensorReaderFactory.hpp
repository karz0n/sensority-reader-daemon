/*!
* \file SensorReaderFactory.hpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Feb 21, 2018
*/

#ifndef SENSORREADERFACTORY_HPP
#define SENSORREADERFACTORY_HPP

#include "data/Storage.hpp"

#include "DeviceCommon.hpp"
#include "SensorCommon.hpp"
#include "SensorReader.hpp"

namespace hardware {

/*!
 * \addtogroup hardware
 * @{
 */

/*!
 * \brief The SensorReaderFactory class
 */
class SensorReaderFactory {
public:
    /*!
     * \brief Create reading strategy object.
     * \param type device type.
     * \return object of strategy.
     */
    static SensorReader::Ptr createReader(data::Storage::Ptr storage,
                                                   DevicePinNum pin,
                                                   SensorTypes type);
};

/*! @} */

} // namespace hardware

#endif // SENSORREADERFACTORY_HPP
