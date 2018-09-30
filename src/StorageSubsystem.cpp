/*!
* \file StorageSubsystem.cpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Aug 12, 2018
*/

#include "StorageSubsystem.hpp"

#include <Poco/Exception.h>
#include <Poco/Util/Application.h>

#include "data/MemoryStorage.hpp"

using Poco::Util::Application;

using data::Storage;
using data::MemoryStorage;
using data::StorageManager;

StorageSubsystem::StorageSubsystem()
{
    _manager = std::make_shared<StorageManager>();
}

StorageSubsystem::~StorageSubsystem()
{ }

const char* StorageSubsystem::name() const
{
    static const char* NAME = "storage";
    return NAME;
}

StorageManager::Ptr StorageSubsystem::manager() const
{
    return _manager;
}

void StorageSubsystem::initialize(Application& app)
{
    readConfig(app);
}

void StorageSubsystem::uninitialize()
{

}

void StorageSubsystem::readConfig(const Poco::Util::Application& app)
{
    std::size_t i = 0;
    do {
        std::string prefix = "data.storages.storage[" + std::to_string(i++) + "]";
        if (!app.config().has(prefix)) {
            break;
        }

        std::string path = prefix + ".name";
        if (!app.config().has(path)) {
            app.logger().error("Missing '%s' option in config", path);
            continue;
        }
        std::string name = app.config().getString(path);

        _manager->append(std::make_shared<MemoryStorage>(name));
    } while (true);
}
