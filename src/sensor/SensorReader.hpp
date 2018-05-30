/*
 * SensorReader.hpp
 *
 *  Created on: Feb 28, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADER_HPP_
#define SENSORREADER_HPP_

#include <memory>
#include <utility>

#include "common/ThreadTarget.hpp"

#include "device/DeviceCommon.hpp"

#include "SensorCommon.hpp"
#include "SensorReadableData.hpp"
#include "SensorDataStorage.hpp"

namespace sensor {

/**
 * Sensor reader class
 */
class SensorReader : public common::ThreadTarget {
public:
    using Ptr = std::unique_ptr<SensorReader>;

    SensorReader(device::PinNum pin, SensorTypes type);

    /**
     * @brief return readable data
     * @return readable data object
     */
    inline SensorReadableData::Ptr data() const;

public:
    /**
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

//
// Inlines
//

SensorReadableData::Ptr SensorReader::data() const
{
    return _storage;
}

} // namespace sensor

#endif /* SENSORREADER_HPP_ */
