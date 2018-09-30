/*!
 * \file StorageCommon.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 16, 2018
 */

#ifndef STORAGECOMMON_HPP
#define STORAGECOMMON_HPP

#include <string>
#include <vector>
#include <utility>
#include <variant>
#include <map>

#include <Poco/Notification.h>

namespace data {

class Storage;

/*!
 * \addtogroup data
 * @{
 */

//------------------------------------------------------------------------------

/*!
 *
 */
using StorageValue = std::variant<int, double>;

/*!
 *
 */
using StorageValueItem = std::pair<std::string, StorageValue>;

/*!
 *
 */
using StorageValueItems = std::vector<StorageValueItem>;

/*!
 *
 */
using StorageValueItemsGroup = std::map<std::string, StorageValueItems>;

//------------------------------------------------------------------------------

/*!
 * \brief The StorageNotification class
 */
class StorageNotification : public Poco::Notification {
public:
    /*!
     * Default dtor.
     */
    virtual ~StorageNotification() = default;

    /*!
     * \brief source
     * \return
     */
    Storage& storage() const;

protected:
    StorageNotification(Storage& storage);

private:
    Storage& _storage;
};

//------------------------------------------------------------------------------

/*!
 * \brief The StorageUpdateNotification class
 */
class StorageUpdateNotification : public StorageNotification {
public:
    using Ptr = Poco::AutoPtr<StorageUpdateNotification>;

    StorageUpdateNotification(Storage& storage);
};

/*! @} */

} // namespace data

#endif // STORAGECOMMON_HPP
