/*!
 * \file MemoryStorage.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 16, 2018
 */

#ifndef MEMORYSTORAGE_HPP
#define MEMORYSTORAGE_HPP

#include <unordered_map>
#include <shared_mutex>

#include "StorageCommon.hpp"
#include "Storage.hpp"

namespace data {

/*!
 * \addtogroup data
 * @{
 */

/*!
 * \brief The MemoryStorage class.
 */
class MemoryStorage : public Storage
{
public:
    MemoryStorage(const std::string& name);

    StorageValueItems extract() const override;
    StorageValueItems extract(std::initializer_list<std::string> keys) const override;
    StorageValue extract(const std::string& key) const override;

    void store(std::initializer_list<StorageValueItem> items) override;
    void store(const std::string& key, const StorageValue& data) override;

private:
    mutable std::shared_mutex _mutex;
    std::unordered_map<std::string, StorageValue> _storage;
};

/*! @} */

} // namespace data

#endif // MEMORYSTORAGE_HPP
