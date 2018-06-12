/*!
* \file TemperatureSensorData.hpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Feb 21, 2018
*/

#ifndef TEMPERATURESENSORDATA_HPP
#define TEMPERATURESENSORDATA_HPP

#include "Formatter.hpp"
#include "SensorData.hpp"

namespace sensor {

/*!
 * \addtogroup sensor
 * @{
 */

/*!
 * \brief The TemperatureSensorData class
 */
class TemperatureSensorData : public SensorData {
public:
    /*!
     * \brief Construct temperature sensor data class.
     * \param temperature value of temperature.
     * \param humidity value of humidity.
     */
    TemperatureSensorData(double temperature, double humidity);

    /*!
     * \brief Return temperature value.
     * \return temperature value.
     */
    inline double getTemperature()
    {
        return _temperature;
    }

    /*!
     * \brief Return humidity value.
     * \return humidity value.
     */
    inline double getHumidity()
    {
        return _humidity;
    }

    formatter::Formatter::Values values() const override;

private:
    double _temperature;
    double _humidity;
};

/*! @} */

} // namespace sensor

#endif // TEMPERATURESENSORDATA_HPP
