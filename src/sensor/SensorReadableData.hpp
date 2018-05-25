/*
 * SensorReadableData.hpp
 *
 *  Created on: Mar 23, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADABLEDATA_HPP_
#define SENSORREADABLEDATA_HPP_

#include <memory>
#include <string>

#include "Formatter.hpp"

namespace sensor {

/**
 * @brief The SensorReadableData class
 */
class SensorReadableData {
public:
    using Ptr = std::shared_ptr<SensorReadableData>;

    virtual ~SensorReadableData() = default;

    /**
     * @brief format data by specified formatter
     * @param formatter used formatter
     * @return formatted data
     */
    virtual std::string format(const formatter::Formatter& formatter) const = 0;
};

} // namespace sensor

#endif // SENSORREADABLEDATA_HPP_
