/*!
* \file HardwareSubsystem.cpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Aug 12, 2018
*/

#include "HardwareSubsystem.hpp"

#include <Poco/Util/Application.h>

#include "hardware/SensorCommon.hpp"
#include "hardware/SensorReaderFactory.hpp"

#include "StorageSubsystem.hpp"

using Poco::Util::Application;

using hardware::SensorReaderFactory;
using hardware::SensorTypes;

using hardware::verifyTypeAsString;
using hardware::translateSensorTypeFromString;

HardwareSubsystem::HardwareSubsystem()
{ }

HardwareSubsystem::~HardwareSubsystem()
{ }

const char* HardwareSubsystem::name() const
{
    static const char* NAME = "hardware";
    return NAME;
}

hardware::SensorReaderManager& HardwareSubsystem::manager()
{
    return _manager;
}

const hardware::SensorReaderManager& HardwareSubsystem::manager() const
{
    return _manager;
}

void HardwareSubsystem::initialize(Application& app)
{
    readConfig(app);

    _manager.startAll();
}

void HardwareSubsystem::uninitialize()
{
//    _manager.stopAll();
}

void HardwareSubsystem::readConfig(const Poco::Util::Application& app)
{
    auto storageManager = app.getSubsystem<StorageSubsystem>().manager();
    std::size_t i = 0;
    do {
        std::string prefix = "hardware.sensors.sensor[" + std::to_string(i++) + "]";
        if (!app.config().has(prefix)) {
            break;
        }

        std::string path = prefix + ".storage";
        if (!app.config().has(path)) {
            app.logger().error("Missing '%s' option in config", path);
            continue;
        }
        std::string storageName = app.config().getString(prefix + ".storage");
        if (!storageManager->has(storageName)) {
            app.logger().error("Storage with '%s' name is absent", storageName);
            continue;
        }
        auto storage = storageManager->get(storageName);

        path = prefix + ".name";
        if (!app.config().has(path)) {
            app.logger().error("Missing '%s' option in config", path);
            continue;
        }
        std::string readerName = app.config().getString(path);

        path = prefix + ".pin";
        if (!app.config().has(path)) {
            app.logger().error("Missing '%s' option in config", path);
            continue;
        }
        unsigned int pin = app.config().getUInt(path);

        path = prefix + ".type";
        if (!app.config().has(path)) {
            app.logger().error("Missing '%s' option in config", path);
            continue;
        }
        std::string typeAsString = app.config().getString(path);
        if (!verifyTypeAsString(typeAsString)) {
            app.logger().error("Missing '%s' option in config", path);
            continue;
        }
        SensorTypes type = translateSensorTypeFromString(typeAsString);

        _manager.append(
            readerName,
            SensorReaderFactory::createReader(storage, pin, type));
    } while (true);
}
