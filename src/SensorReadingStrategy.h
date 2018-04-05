/*
 * SensorReadingStrategy.h
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADINGSTRATEGY_H_
#define SENSORREADINGSTRATEGY_H_

#include <memory>

#include "SensorCommon.h"
#include "SensorData.h"

/**
 * @brief The SensorReadingStrategy class.
 * Base class of reading strategies.
 */
class SensorReadingStrategy {
public:
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
    virtual std::unique_ptr<SensorData> read(std::uint8_t pin, SensorTypes type) = 0;
};

#endif /* SENSORREADINGSTRATEGY_H_ */
