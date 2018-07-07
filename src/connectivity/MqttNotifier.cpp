/*!
 * \file MqttNotifier.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jun 22, 2018
 */

#include "MqttNotifier.hpp"

#include <Poco/NObserver.h>

using Poco::NObserver;

namespace connectivity {

MqttNotifier::MqttNotifier()
{

}

void MqttNotifier::inject(MqttTarget& target)
{
    _nc.addObserver(
        NObserver<MqttTarget, MqttConnectNotification>(target, &MqttTarget::on));
    _nc.addObserver(
        NObserver<MqttTarget, MqttDisconnectNotification>(target, &MqttTarget::on));
    _nc.addObserver(
        NObserver<MqttTarget, MqttPublishNotification>(target, &MqttTarget::on));
}

void MqttNotifier::eject(MqttTarget& target)
{
    _nc.removeObserver(
        NObserver<MqttTarget, MqttConnectNotification>(target, &MqttTarget::on));
    _nc.removeObserver(
        NObserver<MqttTarget, MqttDisconnectNotification>(target, &MqttTarget::on));
    _nc.removeObserver(
        NObserver<MqttTarget, MqttPublishNotification>(target, &MqttTarget::on));
}

void MqttNotifier::emitConnectNotification(MqttConnectionStatusCodes status)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(
                new MqttConnectNotification(*this, status));
}

void MqttNotifier::emitDisconnectNotification(int reason)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(
                new MqttDisconnectNotification(*this, reason));
}

void MqttNotifier::emitPublishNotification(int messageId)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(
                new MqttPublishNotification(*this, messageId));
}

void MqttNotifier::emitMessageNotification(const MqttMessage& message)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(
                new MqttMessageNotification(*this, message));
}

void MqttNotifier::emitSubscribeNotification(int messageId, const MqttGrantedQoS& qos)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(
                new MqttSubscribeNotification(*this, messageId, qos));
}

void MqttNotifier::emitUnsubscribeNotification(int messageId)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(
                new MqttUnsubscribeNotification(*this, messageId));
}

void MqttNotifier::emitLogNotification(MqttLogLevel level,
                                       const std::string& message)
{
    if (!_nc.hasObservers()) {
        return;
    }
    _nc.postNotification(
                new MqttLogNotification(*this, level, message));
}

}


