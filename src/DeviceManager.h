/*
 * DeviceManager.h
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef DEVICEMANAGER_H_
#define DEVICEMANAGER_H_

#include <cstdint>

#include "DeviceGpio.h"

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

#endif /* DEVICEMANAGER_H_ */
