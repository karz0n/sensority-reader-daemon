/*!
 * \file MqttObservable.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jun 17, 2018
 */

#include "MqttObservable.hpp"

#include <Poco/NObserver.h>

using Poco::NObserver;

namespace connectivity {

void MqttObservable::inject(MqttObserver& target)
{
    _nc.addObserver(
        NObserver<MqttObserver, MqttConnectNotification>(target, &MqttObserver::on));
    _nc.addObserver(
        NObserver<MqttObserver, MqttDisconnectNotification>(target, &MqttObserver::on));
    _nc.addObserver(
        NObserver<MqttObserver, MqttPublishNotification>(target, &MqttObserver::on));
    _nc.addObserver(
        NObserver<MqttObserver, MqttMessageNotification>(target, &MqttObserver::on));
    _nc.addObserver(
        NObserver<MqttObserver, MqttSubscribeNotification>(target, &MqttObserver::on));
    _nc.addObserver(
        NObserver<MqttObserver, MqttUnsubscribeNotification>(target, &MqttObserver::on));
    _nc.addObserver(
        NObserver<MqttObserver, MqttLogNotification>(target, &MqttObserver::on));
}

void MqttObservable::eject(MqttObserver& target)
{
    _nc.removeObserver(
        NObserver<MqttObserver, MqttConnectNotification>(target, &MqttObserver::on));
    _nc.removeObserver(
        NObserver<MqttObserver, MqttDisconnectNotification>(target, &MqttObserver::on));
    _nc.removeObserver(
        NObserver<MqttObserver, MqttPublishNotification>(target, &MqttObserver::on));
    _nc.removeObserver(
        NObserver<MqttObserver, MqttMessageNotification>(target, &MqttObserver::on));
    _nc.removeObserver(
        NObserver<MqttObserver, MqttSubscribeNotification>(target, &MqttObserver::on));
    _nc.removeObserver(
        NObserver<MqttObserver, MqttUnsubscribeNotification>(target, &MqttObserver::on));
    _nc.removeObserver(
                NObserver<MqttObserver, MqttLogNotification>(target, &MqttObserver::on));
}

bool MqttObservable::hasObservers() const
{
    return _nc.hasObservers();
}

std::size_t MqttObservable::countObservers() const
{
    return _nc.countObservers();
}

void MqttObservable::emitConnectNotification(MqttConnectionStatusCodes status)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(new MqttConnectNotification(*this, status));
}

void MqttObservable::emitDisconnectNotification(int reason)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(new MqttDisconnectNotification(*this, reason));
}

void MqttObservable::emitPublishNotification(int messageId)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(new MqttPublishNotification(*this, messageId));
}

void MqttObservable::emitMessageNotification(const MqttMessage& message)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(new MqttMessageNotification(*this, message));
}

void MqttObservable::emitSubscribeNotification(int messageId, const MqttGrantedQoS& qos)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(new MqttSubscribeNotification(*this, messageId, qos));
}

void MqttObservable::emitUnsubscribeNotification(int messageId)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(new MqttUnsubscribeNotification(*this, messageId));
}

void MqttObservable::emitLogNotification(MqttLogLevel level, const std::string& message)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(new MqttLogNotification(*this, level, message));
}

} // namespace connectivity
