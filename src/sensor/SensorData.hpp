/*!
 * \file SensorData.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 4, 2018
 */

#ifndef SENSORDATA_HPP
#define SENSORDATA_HPP

#include <memory>
#include <utility>

#include "Formatter.hpp"
#include "SensorReadableData.hpp"

namespace sensor {

/*!
 * \addtogroup sensor
 * @{
 */

/*!
 * \brief The SensorData class.
 */
class SensorData : public SensorReadableData {
public:
    using Ptr = std::unique_ptr<SensorData>; //!< Type of pointer to the class

    virtual ~SensorData() = default;

    /*!
     * \brief Format data using specified formatter.
     * \param formatter specific formatter.
     * \return result of formatting.
     */
    inline std::string format(const formatter::Formatter& formatter) const
    {
        return formatter.format(values());
    }

    /*!
     * \brief Return values of sensor data.
     * \return values of sensor data.
     */
    virtual formatter::Formatter::Values values() const = 0;

public:
    /*!
     * Sensor data factory method
     */
    template <typename T, typename ...As>
    static Ptr create(As... args)
    {
        return std::make_unique<T>(std::forward<As>(args)...);
    }
};

/*! @} */

} // namespace sensor

#endif // SENSORDATA_HPP
