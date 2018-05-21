/*
 * DeviceLibrary.hpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef DEVICELIBRARY_HPP_
#define DEVICELIBRARY_HPP_

#include "DeviceCommon.hpp"
#include "DeviceGpio.hpp"

namespace device {

/**
 * @brief The DeviceLibrary class
 */
class DeviceLibrary final {
public:
    static DeviceLibrary& instance();

    inline bool isInitialized() const;
    void initialize();
    void cleanup();

    DeviceGpio::Ptr gpio(PinNum pin);

public:
    DeviceLibrary(const DeviceLibrary&) = delete;
    DeviceLibrary operator=(const DeviceLibrary&) = delete;

private:
    DeviceLibrary();
    ~DeviceLibrary();

private:
    unsigned long _counter;
};

//
// Inline
//

bool DeviceLibrary::isInitialized() const
{
    return _counter > 0;
}

} // namespace device

#endif /* DEVICELIBRARY_HPP_ */
