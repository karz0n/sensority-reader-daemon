/*
 * SensorReadableData.hpp
 *
 *  Created on: Mar 23, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADABLEDATA_HPP_
#define SENSORREADABLEDATA_HPP_

#include <string>

#include "Formatter.hpp"

/**
 * @brief The SensorReadableData class
 */
class SensorReadableData {
public:
    virtual ~SensorReadableData() = default;

    virtual std::string format(const Formatter& formatter) const = 0;
};

#endif // SENSORREADABLEDATA_HPP
