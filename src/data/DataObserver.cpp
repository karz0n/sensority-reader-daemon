/*!
 * \file DataObserver.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 16, 2018
 */

#include "DataObserver.hpp"

#ifndef NDEBUG
#include <Poco/Util/Application.h>
#endif

namespace data {

void DataObserver::on(const StorageUpdateNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Data");
#endif
}

} // namespace data
