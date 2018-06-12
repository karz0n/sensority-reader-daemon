/*!
 * \file SensorReader.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Feb 28, 2018
 */

#ifndef SENSORREADER_HPP
#define SENSORREADER_HPP

#include <memory>
#include <utility>

#include "common/ThreadTarget.hpp"

#include "device/DeviceCommon.hpp"

#include "SensorCommon.hpp"
#include "SensorReadableData.hpp"
#include "SensorDataStorage.hpp"

namespace sensor {

/*!
 * \addtogroup sensor
 * @{
 */

/**
 * Sensor reader class
 */
class SensorReader : public common::ThreadTarget {
public:
    using Ptr = std::unique_ptr<SensorReader>;  //!< Type of pointer to the class object.

    /*!
     * \brief Construct sensor reader class.
     * \param pin number of pin.
     * \param type type of device.
     */
    SensorReader(device::PinNum pin, SensorTypes type);

    /*!
     * \brief Return readable data.
     * \return pointer to the readable data object.
     */
    inline SensorReadableData::Ptr data() const
    {
        return _storage;
    }

public:
    /*!
     * Factory method
     */
    template<typename ...As>
    static inline Ptr create(As&&... args)
    {
        return std::make_unique<SensorReader>(std::forward<As>(args)...);
    }

protected:
    void doStart() override;
    void doStop() override;

private:
    device::PinNum _pin;
    SensorTypes _type;
    SensorDataStorage::Ptr _storage;
};

/*! @} */

} // namespace sensor

#endif // SENSORREADER_HPP
