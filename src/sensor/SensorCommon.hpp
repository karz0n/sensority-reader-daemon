/*!
 * \file SensorCommon.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Feb 21, 2018
 */

#ifndef SENSORCOMMON_HPP
#define SENSORCOMMON_HPP

#include <string>

namespace sensor {

/*!
 * \addtogroup sensor
 * @{
 */

/*!
 * \brief The SensorTypes enum.
 * \details Sensor types.
 */
enum class SensorTypes {
    dht11, dht22
};

/*!
 * \brief Convert sensor type from string to the enum type.
 * \param value sensor type in string form.
 * \return sensor type in enum type.
 */
SensorTypes translateSensorTypeFromString(const std::string& value);

/**
 * @brief Check if type refers to temperature sensor.
 * @param type sensor type.
 * @return flag which indicate that we have temperature sensor.
 */

/*!
 * \brief Check if type refers to temperature sensor.
 * \param type sensor type.
 * \return flag which indicate that we have temperature sensor.
 */
bool isTemperatureSensor(SensorTypes type);

/*! @} */

} // namespace sensor

#endif // SENSORCOMMON_HPP
