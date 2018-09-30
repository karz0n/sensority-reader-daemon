/*!
 * \file StorageManager.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Sep 05, 2018
 */

#include "StorageManager.hpp"

#include <algorithm>

#include <Poco/Exception.h>
#include <Poco/Format.h>

namespace data {

/*!
 * \addtogroup data
 * @{
 */

void StorageManager::append(Storage::Ptr storage)
{
    const auto& name = storage->name();
    if (has(name)) {
        throw Poco::RuntimeException(Poco::format("Storage with '%s' name is already exists", name));
    }
    _storages[name] = storage;
}

void StorageManager::remove(const std::string& name)
{
    auto it = _storages.find(name);
    if (it == _storages.end()) {
        throw Poco::RuntimeException(Poco::format("Storage with '%s' name is absent", name));
    }
    _storages.erase(it);
}

bool StorageManager::has(const std::string& name) const
{
    return (_storages.count(name) > 0);
}

Storage::Ptr StorageManager::get(const std::string& name) const
{
    auto it = _storages.find(name);
    if (it == _storages.end()) {
        throw Poco::RuntimeException(Poco::format("Storage with '%s' name is absent", name));
    }
    return it->second;
}

std::vector<std::string> StorageManager::names() const
{
    if (_storages.empty()) {
        return {};
    }

    std::vector<std::string> output;
    output.reserve(_storages.size());
    std::for_each(_storages.cbegin(), _storages.cend(), [&] (const Storages::value_type& p) {
        output.push_back(p.first);
    });
    return output;
}

std::string StorageManager::format(const Formatter& formatter) const
{
    if (_storages.empty()) {
        return {};
    }

    StorageValueItemsGroup group;
    std::for_each(_storages.cbegin(), _storages.cend(), [&] (const Storages::value_type& p) {
        group.emplace(p.first, p.second->extract());
    });
    return formatter.format(group);
}

/*! @} */

} // namespace data
