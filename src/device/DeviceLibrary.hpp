/*!
 * \file DeviceLibrary.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 4, 2018
 */

#ifndef DEVICELIBRARY_HPP
#define DEVICELIBRARY_HPP

#include "DeviceCommon.hpp"
#include "DeviceGpio.hpp"

namespace device {

/*!
 * \addtogroup device
 * @{
 */

/*!
 * \brief The DeviceLibrary class.
 * \details Library class to work with device.
 */
class DeviceLibrary final {
public:
    /*!
     * \brief Return single instance of class.
     * \return instance of class.
     */
    static DeviceLibrary& instance();

    /*!
     * \brief Return init state of library.
     * \return init state value.
     */
    inline bool isInitialized() const
    {
        return _counter > 0;
    }

    /*!
     * \brief Initialize library.
     */
    void initialize();

    /*!
     * \brief Cleanup resources of library.
     */
    void cleanup();

    /*!
     * \brief Create instance of helper class to work with GPIO.
     * \param pin specified number of pin.
     * \return instance of helper class.
     */
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

/*! @} */

} // namespace device

#endif // DEVICELIBRARY_HPP
