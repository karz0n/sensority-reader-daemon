/*!
* \file StorageSubsystem.hpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Aug 12, 2018
*/

#ifndef STORAGESUBSYSTEM_HPP
#define STORAGESUBSYSTEM_HPP

#include <unordered_map>

#include <Poco/Util/Subsystem.h>

#include "data/StorageManager.hpp"

class StorageSubsystem : public Poco::Util::Subsystem
{
public:
    StorageSubsystem();
    ~StorageSubsystem() override;

    const char* name() const override;

    data::StorageManager::Ptr manager() const;

protected:
    void initialize(Poco::Util::Application& app) override;
    void uninitialize() override;

private:
    void readConfig(const Poco::Util::Application&);

private:
    data::StorageManager::Ptr _manager;
};

#endif // STORAGESUBSYSTEM_HPP
