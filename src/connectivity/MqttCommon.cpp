/*!
 * \file MqttCommon.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jun 17, 2018
 */

#include "MqttCommon.hpp"

#include <mosquitto.h>

namespace connectivity {

//------------------------------------------------------------------------------

std::string stringifyErrorCode(int errorCode)
{
    const char* s = mosquitto_strerror(errorCode);
    return std::string(s);
}

std::string stringifyConnackCode(int connackCode)
{
    const char* s = mosquitto_connack_string(connackCode);
    return std::string(s);
}

//------------------------------------------------------------------------------

MqttNotification::MqttNotification(MqttObservable& source)
    : _source(source)
{ }

MqttObservable& MqttNotification::source() const
{
    return _source;
}

//------------------------------------------------------------------------------

MqttConnectNotification::MqttConnectNotification(MqttObservable& source,
                                                 MqttConnectionStatusCodes status)
    : MqttNotification{source}
    , _status{status}
{ }

MqttConnectionStatusCodes MqttConnectNotification::status() const
{
    return _status;
}

std::string MqttConnectNotification::statusAsString() const
{
    int c = static_cast<int>(status());
    return stringifyConnackCode(c);
}

bool MqttConnectNotification::isSuccess() const
{
    return (_status == MqttConnectionStatusCodes::success);
}

//------------------------------------------------------------------------------

MqttDisconnectNotification::MqttDisconnectNotification(MqttObservable& source,
                                                       int reason)
    : MqttNotification{source}
    , _reson{reason}
{ }

int MqttDisconnectNotification::reason() const
{
    return _reson;
}

bool MqttDisconnectNotification::isUnexpected() const
{
    return (_reson != 0);
}

//------------------------------------------------------------------------------

MqttPublishNotification::MqttPublishNotification(MqttObservable& source,
                                                 int messageId)
    : MqttNotification{source}
    , _messageId{messageId}
{ }

int MqttPublishNotification::messageId() const
{
    return _messageId;
}

//------------------------------------------------------------------------------

MqttMessageNotification::MqttMessageNotification(MqttObservable& source,
                                                 const MqttMessage& message)
    : MqttNotification{source}
    , _message{message}
{ }

const MqttMessage& MqttMessageNotification::message() const
{
    return _message;
}

//------------------------------------------------------------------------------

MqttSubscribeNotification::MqttSubscribeNotification(MqttObservable& source,
                                                     int messageId,
                                                     const MqttGrantedQoS& qos)
    : MqttNotification{source}
    , _messageId{messageId}
    , _qos{qos}
{ }

int MqttSubscribeNotification::messageId() const
{
    return _messageId;
}

const MqttGrantedQoS& MqttSubscribeNotification::qos() const
{
    return _qos;
}

//------------------------------------------------------------------------------

MqttUnsubscribeNotification::MqttUnsubscribeNotification(MqttObservable& source,
                                                         int messageId)
    : MqttNotification{source}
    , _messageId{messageId}
{ }

int MqttUnsubscribeNotification::messageId() const
{
    return _messageId;
}

//------------------------------------------------------------------------------

MqttLogNotification::MqttLogNotification(MqttObservable& source,
                    MqttLogLevel level,
                    const std::string& message)
    : MqttNotification{source}
    , _level{level}
    , _message{message}
{ }

MqttLogLevel MqttLogNotification::level() const
{
    return _level;
}

const std::string& MqttLogNotification::message() const
{
    return _message;
}

//------------------------------------------------------------------------------

} // namespace connectivity
