/*
 * SensorCommon.h
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORCOMMON_H_
#define SENSORCOMMON_H_

#include <string>

/**
 * @brief The SensorTypes enum.
 * Sensor types.
 */
enum class SensorTypes {
	dht11, dht22
};

/**
 * @brief Get sensor type represenation from string.
 * @param value string sensor type represenation.
 * @return The value in sensor type represenation.
 */
SensorTypes translateSensorTypeFromString(const std::string& value);

/**
 * @brief Check if type refers to temperature sensor.
 * @param type sensor type.
 * @return The flag that indicate if we have temperature sensor.
 */
bool isTemperatureSensor(SensorTypes type);

#endif /* SENSORCOMMON_H_ */
