/*!
 * \file StorageCommon.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 16, 2018
 */

#include "StorageCommon.hpp"

namespace data {

//------------------------------------------------------------------------------

StorageNotification::StorageNotification(Storage& storage)
    : _storage{storage}
{ }

Storage& StorageNotification::storage() const
{
    return _storage;
}

//------------------------------------------------------------------------------

StorageUpdateNotification::StorageUpdateNotification(Storage& storage)
    : StorageNotification{storage}
{ }

//------------------------------------------------------------------------------

} // namespace data
