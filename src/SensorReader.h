/*
 * SensorReader.h
 *
 *  Created on: Feb 28, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADER_H_
#define SENSORREADER_H_

#include <thread>
#include <atomic>
#include <memory>

#include "SensorCommon.h"
#include "SensorReadingStrategy.h"
#include "SensorDataStorage.h"

/**
 * Sensor reader class
 */
class SensorReader {
public:
    SensorReader(std::uint8_t pin,
                 SensorTypes type,
                 std::unique_ptr<SensorReadingStrategy> strategy,
                 std::shared_ptr<SensorDataStorage> storage);

	inline bool isRunned() const;
    inline std::shared_ptr<SensorDataStorage> storage() const;

	void run();
	void shutdown();

private:
    void handler();

private:
    std::uint8_t _pin;
	SensorTypes _type;
    std::unique_ptr<SensorReadingStrategy> _strategy;
    std::shared_ptr<SensorDataStorage> _storage;
	std::thread _thread;
    std::atomic<bool> _runned;
};

//
// Inlines
//

bool SensorReader::isRunned() const
{
    return _runned;
}

std::shared_ptr<SensorDataStorage> SensorReader::storage() const
{
    return _storage;
}

#endif /* SENSORREADER_H_ */
