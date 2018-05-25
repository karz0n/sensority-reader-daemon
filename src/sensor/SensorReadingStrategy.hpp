/*
 * SensorReadingStrategy.hpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADINGSTRATEGY_HPP_
#define SENSORREADINGSTRATEGY_HPP_

#include <memory>
#include <utility>

#include "SensorCommon.hpp"
#include "SensorData.hpp"

namespace sensor {

/**
 * @brief The SensorReadingStrategy class.
 * Base class of reading strategies.
 */
class SensorReadingStrategy {
public:
    using Ptr = std::unique_ptr<SensorReadingStrategy>;

    virtual ~SensorReadingStrategy() = default;

    /**
     * @brief Setup environment.
     * Called once before reading will start.
     */
    virtual void setup() = 0;

    /**
     * @brief Cleanup environment.
     * Called once after reading has finished.
     */
    virtual void cleanup() = 0;

    /**
     * @brief Pause before reading.
     * Called after each read cycle has performed.
     * @param type device type.
     */
    virtual void pause(SensorTypes type) = 0;

    /**
     * @brief Indicate if pause is necessary.
     * @param type device type.
     * @return The flag that indicate if pause is necessary.
     */
    virtual bool needPause(SensorTypes type) const = 0;

    /**
     * Read data
     * (called on each step of reading cycle)
     */
    /**
     * @brief Read data.
     * Called on each step of reading cycle.
     * @param pin pin number.
     * @param type device type.
     * @return The pointer of reading result.
     */
    virtual SensorData::Ptr read(std::uint8_t pin, SensorTypes type) = 0;

 public:
    /**
     * Sensor reading strategy factory method
     */
    template <typename T, typename ...As>
    static Ptr create(As... args)
    {
        return std::make_unique<T>(std::forward<As>(args)...);
    }
};

} // namespace sensor

#endif /* SENSORREADINGSTRATEGY_HPP_ */
