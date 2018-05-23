/*
 * SensorData.hpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORDATA_HPP_
#define SENSORDATA_HPP_

#include <memory>

#include "Formatter.hpp"
#include "SensorReadableData.hpp"

/**
 * @brief The SensorData class
 */
class SensorData: public SensorReadableData {
public:
    virtual ~SensorData() = default;

    /**
     * @brief format
     * @param formatter
     * @return
     */
    inline std::string format(const formatter::Formatter& formatter) const;

    /**
     * @brief values
     * @return
     */
    virtual formatter::Formatter::Values values() const = 0;
};

//
// Inlines
//

std::string SensorData::format(const formatter::Formatter& formatter) const
{
    return formatter.format(values());
}

#endif /* SENSORDATA_HPP_ */
