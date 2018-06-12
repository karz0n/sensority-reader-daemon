/*!
 * \file SensorReadableData.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 23, 2018
 */

#ifndef SENSORREADABLEDATA_HPP
#define SENSORREADABLEDATA_HPP

#include <memory>
#include <string>

#include "Formatter.hpp"

namespace sensor {

/*!
 * \addtogroup sensor
 * @{
 */

/*!
 * \brief The SensorReadableData class.
 */
class SensorReadableData {
public:
    using Ptr = std::shared_ptr<SensorReadableData>;    //!< Type of pointer to the class.

    virtual ~SensorReadableData() = default;

    /**
     * @brief format data by specified formatter
     * @param formatter used formatter
     * @return formatted data
     */
    virtual std::string format(const formatter::Formatter& formatter) const = 0;
};

/*! @} */

} // namespace sensor

#endif // SENSORREADABLEDATA_HPP
