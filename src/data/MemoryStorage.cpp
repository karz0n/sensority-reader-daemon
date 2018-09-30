/*!
 * \file MemoryStorage.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 16, 2018
 */

#include "MemoryStorage.hpp"

namespace data
{

MemoryStorage::MemoryStorage(const std::string& name)
    : Storage{name}
{ }

StorageValue MemoryStorage::extract(const std::string& key) const
{
    std::shared_lock<std::shared_mutex> lock(_mutex);
    return _storage.at(key);
}

StorageValueItems MemoryStorage::extract(std::initializer_list<std::string> keys) const
{
    std::shared_lock<std::shared_mutex> lock(_mutex);
    StorageValueItems items;
    items.reserve(keys.size());
    auto it = std::back_insert_iterator(items);
    for (const auto& name : keys) {
        const auto& data = _storage.at(name);
        it = {name, data};

    }
    return items;
}

StorageValueItems MemoryStorage::extract() const
{
    std::shared_lock<std::shared_mutex> lock(_mutex);
    StorageValueItems items;
    items.reserve(_storage.size());
    auto it = std::back_insert_iterator(items);
    for (const auto& item : _storage) {
        it = item;
    }
    return items;
}

void MemoryStorage::store(const std::string& key, const StorageValue& data)
{
    {
        std::lock_guard<std::shared_mutex> lock(_mutex);
        _storage[key] = data;
    }
    emitUpdateNotification(*this);
}

void MemoryStorage::store(std::initializer_list<StorageValueItem> items)
{
    {
        std::lock_guard<std::shared_mutex> lock(_mutex);
        for (const auto& item : items) {
            _storage.insert_or_assign(item.first, item.second);
        }
    }
    emitUpdateNotification(*this);
}

} // namespace data
