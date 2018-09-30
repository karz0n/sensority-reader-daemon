/*!
 * \file MqttNotifier.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jun 22, 2018
 */

#include "MqttNotifier.hpp"

#include "data/FormatterFactory.hpp"

namespace connectivity {

MqttNotifier::MqttNotifier(MqttEndpoint::Ptr e, data::OutputFormats format /*= DEFAULT_HTTP_FORMAT*/)
    : _connected{false}
    , _endpoint{e}
{
    _formatter = data::FormatterFactory::create(format);

    _endpoint->inject(*this);
}

MqttNotifier::~MqttNotifier()
{
    if (!_storages.empty()) {
        for (auto& storage : _storages) {
            storage->eject(*this);
        }
    }

    _endpoint->eject(*this);
}

void MqttNotifier::on(const MqttConnectNotification::Ptr& event)
{
    _connected = event->isSuccess();
}

void MqttNotifier::on(const MqttDisconnectNotification::Ptr& event)
{
    _connected = false;
}

void MqttNotifier::on(const data::StorageUpdateNotification::Ptr& event)
{
    if (_connected) {
        auto& s = event->storage();
        _endpoint->publish(s.name(), s.format(*_formatter));
    }
}

void MqttNotifier::watch(data::Storage::Ptr storage)
{
    _storages.push_back(storage);

    storage->inject(*this);
}

}
