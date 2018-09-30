/*!
 * \file DataObservable.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Sep 20, 2018
 */

#include "DataObservable.hpp"

#include <Poco/NObserver.h>

#include "DataObserver.hpp"
#include "Storage.hpp"

using Poco::NObserver;

namespace data {

void DataObservable::inject(DataObserver& observer)
{
    _nc.addObserver(
        NObserver<DataObserver, StorageUpdateNotification>(observer, &DataObserver::on));
}

void DataObservable::eject(DataObserver& observer)
{
    _nc.removeObserver(
        NObserver<DataObserver, StorageUpdateNotification>(observer, &DataObserver::on));
}

bool DataObservable::hasObservers() const
{
    return _nc.hasObservers();
}

std::size_t DataObservable::countObservers() const
{
    return _nc.countObservers();
}

void DataObservable::emitUpdateNotification(Storage& storage)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(new StorageUpdateNotification(storage));
}

} // namespace data
