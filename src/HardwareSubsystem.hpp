/*!
* \file HardwareSubsystem.hpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Aug 12, 2018
*/

#ifndef HARDWARESUBSYSTEM_HPP
#define HARDWARESUBSYSTEM_HPP

#include <Poco/Util/Subsystem.h>

#include "hardware/SensorReaderManager.hpp"

class HardwareSubsystem : public Poco::Util::Subsystem
{
public:
    HardwareSubsystem();
    ~HardwareSubsystem() override;

    const char* name() const override;

    hardware::SensorReaderManager& manager();

    const hardware::SensorReaderManager& manager() const;

protected:
    void initialize(Poco::Util::Application&) override;
    void uninitialize() override;

private:
    void readConfig(const Poco::Util::Application& app);

private:
    hardware::SensorReaderManager _manager;
};

#endif // HARDWARESUBSYSTEM_HPP
