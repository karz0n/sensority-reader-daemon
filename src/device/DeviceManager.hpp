/*
 * DeviceManager.hpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef DEVICEMANAGER_HPP_
#define DEVICEMANAGER_HPP_

#include <cstdint>

#include "DeviceGpio.hpp"

/**
 * @brief The DeviceManager class
 */
class DeviceManager {
public:
    static DeviceManager& getInstance();

    void initialize();
    void close();
    inline bool isInitialized() const;

    DeviceGpio gpio(std::uint8_t pin) const;

	DeviceManager(const DeviceManager&) = delete;
	DeviceManager& operator=(const DeviceManager&) = delete;

private:
	DeviceManager();

private:
	bool _initialized;
};

//
// Inlines
//

bool DeviceManager::isInitialized() const
{
	return _initialized;
}

#endif /* DEVICEMANAGER_HPP_ */
