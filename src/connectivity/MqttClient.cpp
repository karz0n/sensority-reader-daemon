/*!
 * \file MqttClient.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date May 20, 2018
 */

#include "MqttClient.hpp"

#include <utility>

#include <mosquitto.h>

#include <Poco/Format.h>
#include <Poco/Exception.h>

namespace
{
    template<typename T, typename M = std::string>
    inline T createException(M&& message, int errorCode)
    {
        std::string s = connectivity::stringifyErrorCode(errorCode);
        T nested{s, errorCode};
        return T{std::forward<M>(message), nested};
    }
}

namespace connectivity {

MqttEndpoint::MqttEndpoint(const std::string& id, bool cleanSession /*= true*/)
    : _context{nullptr}
{
    _context = mosquitto_new(id.c_str(), cleanSession, this);
    if (_context == nullptr) {      
        throw Poco::RuntimeException(
            Poco::format("Create mosquitto internal object with '%s' id", id));
    }

    mosquitto_connect_callback_set(_context, &onConnect);
    mosquitto_disconnect_callback_set(_context, &MqttEndpoint::onDisconnect);
    mosquitto_publish_callback_set(_context, &MqttEndpoint::onPublish);
    mosquitto_message_callback_set(_context, &MqttEndpoint::onMessage);
    mosquitto_subscribe_callback_set(_context, &MqttEndpoint::onSubscribe);
    mosquitto_unsubscribe_callback_set(_context, &MqttEndpoint::onUnsubscribe);
    mosquitto_log_callback_set(_context, &MqttEndpoint::onLog);

}

MqttEndpoint::~MqttEndpoint()
{
    mosquitto_destroy(_context);
}

void MqttEndpoint::connect(const std::string& host,
                           unsigned short port /*= MQTT_DEFAULT_INSECURE_PORT*/,
                           int keepalive /*= MQTT_DEFAULT_KEEPALIVE*/)
{
    int rc = mosquitto_connect_bind_async(_context, host.c_str(), port, keepalive, nullptr);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            Poco::format("Attempt connect to '%s:%d' host", host, port), rc);
    }

    rc = mosquitto_loop_start(_context);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Start exchange thread loop", rc);
    }
}

void MqttEndpoint::disconnect()
{
    int rc = mosquitto_disconnect(_context);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Disconnect from host", rc);
    }

    rc = mosquitto_loop_stop(_context, false);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Stop exchange thread loop", rc);
    }
}

void MqttEndpoint::setCredentials(const std::string& username,
                                  const std::string& password)
{
    int rc = mosquitto_username_pw_set(_context,
                                       username.c_str(), password.c_str());
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Set credential", rc);
    }
}

void MqttEndpoint::setReconnectDelay(unsigned int delay,
                                     unsigned int delayMax,
                                     bool exponentialBackoff)
{
    int rc = mosquitto_reconnect_delay_set(_context, delay, delayMax,
                                           exponentialBackoff);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Set reconnect delay", rc);
    }
}

void MqttEndpoint::setInsecure(bool isInsecure)
{
    int rc = mosquitto_tls_insecure_set(_context, isInsecure);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Set insecure mode", rc);
    }
}

void MqttEndpoint::setTransportLayerOptions(
        MqttVerificationRequirements requirements,
        MqttTransportLayerVersions version)
{
    int r = (requirements == MqttVerificationRequirements::peer)
            ? 0     // SSL_VERIFY_NONE
            : 1;    // SSL_VERIFY_PEER

    std::string v;
    switch (version) {
    case MqttTransportLayerVersions::v1:
        v = MQTT_TLS_V1;
        break;
    case MqttTransportLayerVersions::v11:
        v = MQTT_TLS_V11;
        break;
    case MqttTransportLayerVersions::v12:
        v = MQTT_TLS_V11;
        break;
    default:
#ifndef NDEBUG
        poco_unexpected();
#endif
    }

    int rc = mosquitto_tls_opts_set(_context, r, v.c_str(), nullptr);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Set transport layer options", rc);
    }
}

void MqttEndpoint::configureTransportLayerSecurity(const std::string& path)
{
    int rc = mosquitto_tls_set(_context, nullptr, path.c_str(),
                               nullptr, nullptr, nullptr);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Configure transport layer security", rc);
    }
}

void MqttEndpoint::configureTransportLayerSecurity(
        const std::string& psk,
        const std::string& identity,
        const std::string& ciphers)
{
    int rc = mosquitto_tls_psk_set(_context, psk.c_str(), identity.c_str(),
                                   ciphers.c_str());
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Configure transport layer security", rc);
    }
}

void MqttEndpoint::configureTransportLayerSecurity(const std::string& caFile,
                                        const std::string& certFile,
                                        const std::string& keyFile,
                                        std::optional<PasswordProviderCallback> passwordProvider)
{
    int rc = mosquitto_tls_set(_context, caFile.c_str(), nullptr, certFile.c_str(),
                               keyFile.c_str(),
                               passwordProvider.value_or(nullptr));
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Configure transport layer security", rc);
    }
}

void MqttEndpoint::setMaxInflightMessages(unsigned int value)
{
    int rc = mosquitto_max_inflight_messages_set(_context, value);
    if (rc != MOSQ_ERR_SUCCESS) {
        if (rc != MOSQ_ERR_SUCCESS) {
            throw createException<Poco::RuntimeException>(
                "Set max number of inflight messages", rc);
        }
    }
}

void MqttEndpoint::setProtocolVersion(MqttProtocolVersion version)
{
    int v = MQTT_PROTOCOL_V31;
    if (version == MqttProtocolVersion::v311) {
        v = MQTT_PROTOCOL_V311;
    }

    int rc = mosquitto_opts_set(_context, MOSQ_OPT_PROTOCOL_VERSION, &v);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Set client protocol version", rc);
    }
}

void MqttEndpoint::willSet(const std::string& topic,
             const void* payload, std::size_t size,
             MqttQoS qos /*= MqttQoS::v0*/,
             bool retain /*= MQTT_DEFAULT_RETAIN_VALUE*/)
{
    poco_assert_dbg(size > 0 && size < std::numeric_limits<int>::max());

    int rc = mosquitto_will_set(_context, topic.c_str(),
                                int(size), payload,
                                int(qos), retain);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Set will message", rc);
    }
}

void MqttEndpoint::willSet(const std::string& topic,
             const std::string& message,
             MqttQoS qos /*= MqttQoS::v0*/,
             bool retain /*= MQTT_DEFAULT_RETAIN_VALUE*/)
{
    willSet(topic, message.c_str(), message.size(), qos, retain);
}

void MqttEndpoint::willClear()
{
    int rc = mosquitto_will_clear(_context);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Clear will message", rc);
    }
}

void MqttEndpoint::publish(const std::string& topic,
                           const void* payload,
                           std::size_t size,
                           MqttQoS qos /*= MqttQoS::v0*/,
                           bool retain /*= MQTT_DEFAULT_RETAIN_VALUE*/)
{
    poco_assert_dbg(size > 0 && size < std::numeric_limits<int>::max());

    int rc = mosquitto_publish(_context, nullptr, topic.c_str(),
                               int(size), payload,
                               int(qos), retain);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Publish data to the broker", rc);
    }
}

void MqttEndpoint::publish(const std::string& topic,
                           const std::string& message,
                           MqttQoS qos /*= MqttQoS::v0*/,
                           bool retain /*= MQTT_DEFAULT_RETAIN_VALUE*/)
{
    publish(topic, message.c_str(), message.size(), qos, retain);
}

void MqttEndpoint::subscribe(const std::string& topic,
                             MqttQoS qos /*= MqttQoS::v0*/)
{
    int rc = mosquitto_subscribe(_context, nullptr, topic.c_str(), int(qos));
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Subscribe to the topic", rc);
    }
}

void MqttEndpoint::unsubscribe(const std::string& pattern)
{
    int rc = mosquitto_unsubscribe(_context, nullptr, pattern.c_str());
    if (rc != MOSQ_ERR_SUCCESS) {
        throw createException<Poco::RuntimeException>(
            "Unsubscribe from the topic", rc);
    }
}

void MqttEndpoint::onConnect(MqttContext*, void* object, int status)
{
    poco_check_ptr(object);

    MqttConnectionStatusCodes s = static_cast<MqttConnectionStatusCodes>(status);

    MqttEndpoint& e = *static_cast<MqttEndpoint*>(object);
    e.emitConnectNotification(s);
}

void MqttEndpoint::onDisconnect(MqttContext*, void* object, int reason)
{
    poco_check_ptr(object);

    MqttEndpoint& e = *static_cast<MqttEndpoint*>(object);
    e.emitDisconnectNotification(reason);
}

void MqttEndpoint::onPublish(MqttContext*, void* object, int messageId)
{
    poco_check_ptr(object);

    MqttEndpoint& e = *static_cast<MqttEndpoint*>(object);
    e.emitPublishNotification(messageId);
}

void MqttEndpoint::onMessage(MqttContext*, void* object, const MqttMessage* message)
{
    poco_check_ptr(object);
    poco_check_ptr(message);

    MqttEndpoint& e = *static_cast<MqttEndpoint*>(object);
    e.emitMessageNotification(*message);
}

void MqttEndpoint::onSubscribe(MqttContext*, void* object, int messageId,
                               int qosCount, const int* grantedQos)
{
    poco_check_ptr(object);

    std::vector<int> qos;
    if (qosCount > 0) {
        poco_check_ptr(grantedQos);

        std::size_t size = std::size_t(qosCount);
        qos.reserve(size);
        for (std::size_t i = 0; i < size; ++i) {
            qos[i] = grantedQos[i];
        }
    }

    MqttEndpoint& e = *static_cast<MqttEndpoint*>(object);
    e.emitSubscribeNotification(messageId, qos);
}

void MqttEndpoint::onUnsubscribe(MqttContext*, void* object, int messageId)
{
    poco_check_ptr(object);

    MqttEndpoint& e = *static_cast<MqttEndpoint*>(object);
    e.emitUnsubscribeNotification(messageId);
}

void MqttEndpoint::onLog(MqttContext*, void* object, int level, const char* message)
{
    poco_check_ptr(object);
    poco_check_ptr(message);

    MqttLogLevel logLevel = MqttLogLevel::debug;
    switch (level) {
    case MOSQ_LOG_INFO:
        logLevel = MqttLogLevel::info;
        break;
    case MOSQ_LOG_NOTICE:
        logLevel = MqttLogLevel::notice;
        break;
    case MOSQ_LOG_WARNING:
        logLevel = MqttLogLevel::warning;
        break;
    case MOSQ_LOG_ERR:
        logLevel = MqttLogLevel::error;
        break;
    case MOSQ_LOG_DEBUG:
        logLevel = MqttLogLevel::debug;
        break;
    default:
#ifndef NDEBUG
        poco_unexpected();
#endif
    }

    MqttEndpoint& e = *static_cast<MqttEndpoint*>(object);
    e.emitLogNotification(logLevel, std::string(message));
}

} // namespace connectivity
