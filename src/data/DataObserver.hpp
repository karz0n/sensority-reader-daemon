/*!
 * \file DataObserver.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 16, 2018
 */

#ifndef DATAOBSERVER_HPP
#define DATAOBSERVER_HPP

#include "StorageCommon.hpp"

namespace data {

/*!
 * \addtogroup data
 * @{
 */

class DataObserver
{
public:
    virtual ~DataObserver() = default;

    virtual void on(const StorageUpdateNotification::Ptr& event);
};

/*! @} */

} // namespace data

#endif // DATAOBSERVER_HPP
