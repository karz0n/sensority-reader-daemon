/*!
 * \file TemperatureSensorReader.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 18, 2018
 */

#ifndef TEMPERATURESENSORREADER_HPP
#define TEMPERATURESENSORREADER_HPP

#include "data/Storage.hpp"

#include "DeviceCommon.hpp"
#include "SensorCommon.hpp"
#include "SensorReader.hpp"

namespace hardware {

/*!
 * \addtogroup hardware
 * @{
 */

class TemperatureSensorReader : public SensorReader
{
public:
    TemperatureSensorReader(data::Storage::Ptr storage,
                            DevicePinNum pin,
                            SensorTypes type);

protected:
    void run() override;

private:
    void read();

private:
    DevicePinNum _pin;
    SensorTypes _type;
};

/*! @} */

} // namespace hardware

#endif // TEMPERATURESENSORREADER_HPP
