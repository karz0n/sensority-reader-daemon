/*
 * SensorData.hpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORDATA_HPP_
#define SENSORDATA_HPP_

#include <memory>
#include <utility>

#include "Formatter.hpp"
#include "SensorReadableData.hpp"

namespace sensor {

/**
 * @brief The SensorData class
 */
class SensorData : public SensorReadableData {
public:
    using Ptr = std::unique_ptr<SensorData>;

    virtual ~SensorData() = default;

    /**
     * @brief format values of data object
     * @param formatter specified formatter
     * @return formatted string of values
     */
    inline std::string format(const formatter::Formatter& formatter) const;

    /**
     * @brief return values of data object
     * @return values
     */
    virtual formatter::Formatter::Values values() const = 0;

public:
    /**
     * Sensor data factory method
     */
    template <typename T, typename ...As>
    static Ptr create(As... args)
    {
        return std::make_unique<T>(std::forward<As>(args)...);
    }
};

//
// Inlines
//

std::string SensorData::format(const formatter::Formatter& formatter) const
{
    return formatter.format(values());
}

} // namespace sensor

#endif /* SENSORDATA_HPP_ */
