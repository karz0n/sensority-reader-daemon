/*
 * DeviceGpio.hpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef DEVICEGPIO_HPP_
#define DEVICEGPIO_HPP_

#include <limits>
#include <memory>

#include "DeviceCommon.hpp"

namespace device {

const unsigned long long DEVICE_MAX_COUNT = std::numeric_limits<unsigned long long>::max();

/**
 * @brief The DeviceGpio class
 */
class DeviceGpio
{
public:
    using Ptr = std::shared_ptr<DeviceGpio>;

    DeviceGpio(PinNum pin);

    void dir(PinDirs dir);
    void delay(unsigned int millis);
    void delayMicroseconds(unsigned long long micros);

    PinLevels read();
    void write(PinLevels level);
    unsigned long long count(PinLevels level, unsigned long long max = DEVICE_MAX_COUNT);

public:
    /**
     * Device gpio factory method
     */
    template<typename ...As>
    static Ptr create(As&&... args)
    {
        return std::make_shared<DeviceGpio>(std::forward<As>(args)...);
    }

private:
    PinNum _pin;
};

} // namespace device

#endif /* DEVICEGPIO_HPP_ */
