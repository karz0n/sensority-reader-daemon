/*!
 * \file MqttCommon.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jun 17, 2018
 */

#ifndef MQTTCOMMON_H
#define MQTTCOMMON_H

#include <string_view>
#include <string>
#include <vector>
#include <ostream>
#include <functional>

#include <Poco/Notification.h>

#include "MqttSource.hpp"

/*!
 * Forward declaration of mosquitto context
 */
struct mosquitto;

/*!
 * Forward declaration of mosquitto message
 */
struct mosquitto_message;

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

//------------------------------------------------------------------------------

/*!
 * \brief The mqtt library version struct.
 */
class MqttLibraryVersion {
public:

    MqttLibraryVersion() = default; //!< Default ctor.

    /*!
     * \brief Configure version class object.
     * \param maj major version value of library.
     * \param min minor version value of library.
     * \param rev revision of library.
     */
    MqttLibraryVersion(int maj, int min, int rev)
        : _major{maj}
        , _minor{min}
        , _revision{rev}
    { }

    /*!
     * \brief Returns major version value of library.
     * \return a number of minor version value.
     */
    int majorVersion() const
    {
        return _major;
    }

    /*!
     * \brief Returns minor version value of library.
     * \return a number of major version value.
     */
    int minorVersion() const
    {
        return _minor;
    }

    /*!
     * \brief Returns revision value of library.
     * \return a number of revision value.
     */
    int revision() const
    {
        return _revision;
    }

private:
    int _major{0};
    int _minor{0};
    int _revision{0};
};

/*!
 * \brief The list of connection status codes.
 */
enum class MqttConnectionStatusCodes {
    success = 0,                     //!< Connection successful.
    unacceptableProtocolVersion = 1, //!< Connection refused (unacceptable protocol version).
    identifierRejected = 2,          //!< Connection refused (identifier rejected).
    brokerUnavailable = 3            //!< Connection refused (broker unavailable).
};

/*!
 * \brief The list of log levels.
 */
enum class MqttLogLevel {
    info,
    notice,
    warning,
    error,
    debug
};

/*!
 * \brief The list of protocol versions.
 */
enum class MqttProtocolVersion {
    v31,
    v311
};

/*!
 * \brief The list of transport layer verification requirements.
 */
enum class MqttVerificationRequirements {
    none,
    peer
};

/*!
 * \brief The list of transport layer versions.
 */
enum class MqttTransportLayerVersions {
    v1,
    v11,
    v12
};

/*!
 * \brief The list of quality of service levels.
 */
enum class MqttQoS {
    v0 = 0,
    v1,
    v2
};

/*!
 * The context type.
 */
using MqttContext = mosquitto;

/*!
 * The message type.
 */
using MqttMessage = mosquitto_message;

/*!
 * An array of integers which indicates the granted QoS
 */
using MqttGrantedQoS = std::vector<int>;

//------------------------------------------------------------------------------

/*!
 * \brief Default value of MQTT insecure endpoint port.
 */
constexpr unsigned short MQTT_DEFAULT_INSECURE_PORT = 1883;

/*!
 * \brief Default value of MQTT secure endpoint port.
 */
constexpr unsigned short MQTT_DEFAULT_SECURE_PORT = 8883;

/*!
 * \brief Default value of MQTT connection keepalive timeout.
 */
constexpr int MQTT_DEFAULT_KEEPALIVE = 60;

/*!
 * \brief Default value of MQTT quality of service to be used for the message.
 */
constexpr int MQTT_DEFAULT_QOS_VALUE = 0;

/*!
 * \brief Default value of MQTT retain to be used for the message.
 */
const bool MQTT_DEFAULT_RETAIN_VALUE = false;

/*!
 * \brief String view for TLS v1 option.
 */
constexpr std::string_view MQTT_TLS_V1{"tlsv1"};

/*!
 * \brief String view for TLS v1.1 option.
 */
constexpr std::string_view MQTT_TLS_V11{"tlsv1.1"};

/*!
 * \brief String view for TLS v1.2 option.
 */
constexpr std::string_view MQTT_TLS_V12{"tlsv1.2"};

//------------------------------------------------------------------------------

/*!
 * \brief Call to get string description of an error number.
 * \param errorCode an error number.
 * \return string describing the error..
 */
static std::string stringifyErrorCode(int errorCode);

/*!
 * \brief Call to get string description of a connection result.
 * \param connackCode connection result code.
 * \return string describing the result.
 */
static std::string stringifyConnackCode(int connackCode);

//------------------------------------------------------------------------------

/*!
 * \brief The MqttNotification class
 */
class MqttNotification : public Poco::Notification {
public:
    /*!
     * \brief MqttNotification
     * \param source
     */
    MqttNotification(MqttSource& source);

    /*!
     * Default dtor.
     */
    virtual ~MqttNotification() = default;

    /*!
     * \brief source
     * \return
     */
    MqttSource& source() const;

private:
    MqttSource& _source;
};

//------------------------------------------------------------------------------

/*!
 * \brief The mqtt connect notification class.
 *
 * This notification is emitted after connection has been established.
 */
class MqttConnectNotification : public MqttNotification {
public:
    using Ptr = Poco::AutoPtr<MqttConnectNotification>; //!< Pointer to the class object.

    /*!
     * \brief MqttConnectNotification contructor.
     * \param source the source of notification.
     * \param status the status of connection.
     */
    MqttConnectNotification(MqttSource& source,
                            MqttConnectionStatusCodes status);

    /*!
     * \brief Returns the status of connection.
     * \return the status of connection.
     */
    MqttConnectionStatusCodes status() const;

    /*!
     * \brief Returns the status of connection in string representation.
     * \return the status of connection as string.
     */
    std::string statusAsString() const;

    /*!
     * \brief Returns \c true iif connection was successful.
     * \return \c true for successful connection, \c false otherwase.
     */
    bool isSuccess() const;

private:
    MqttConnectionStatusCodes _status;
};

//------------------------------------------------------------------------------

/*!
 * \brief The MqttDisconnectNotification class
 *
 * This notification is emitted after disconnection.
 */
class MqttDisconnectNotification : public MqttNotification {
public:
    using Ptr = Poco::AutoPtr<MqttDisconnectNotification>; ///< Pointer to the class object.

    /*!
     * \brief MqttDisconnectNotification contructor.
     * \param source the source of notification.
     * \param reason the integer value indicating the reason for the disconnect.
     *               A value of 0 means the client has called disconnect.
     */
    MqttDisconnectNotification(MqttSource& source, int reason);

    /*!
     * \brief reason
     * \return
     */
    int reason() const;

    /*!
     * \brief isUnexpected
     * \return
     */
    bool isUnexpected() const;

private:
    int _reson;
};

//------------------------------------------------------------------------------

/*!
 * \brief The MqttPublishNotification class
 *
 * This notification is emitted after successful publishing.
 */
class MqttPublishNotification : public MqttNotification {
public:
    using Ptr = Poco::AutoPtr<MqttPublishNotification>; ///< Pointer to the class object.

    /*!
     * \brief MqttPublishNotification
     * \param source the source of notification.
     * \param messageId the message id of the sent message.
     */
    MqttPublishNotification(MqttSource& source, int messageId);

    /*!
     * \brief messageId
     * \return
     */
    int messageId() const;

private:
    int _messageId;
};

//------------------------------------------------------------------------------

/*!
 * \brief The MqttMessageNotification class
 *
 * This notification which will be called after message was received.
 */
class MqttMessageNotification : public MqttNotification {
public:
    using Ptr = Poco::AutoPtr<MqttMessageNotification>; ///< Pointer to the class object.

    /*!
     * \brief MqttMessageNotification
     * \param source the source of notification.
     * \param message the message data.
     */
    MqttMessageNotification(MqttSource& source,
                            const MqttMessage& message);

    /*!
     * \brief message
     * \return
     */
    const MqttMessage& message() const;

private:
    const MqttMessage& _message;
};

//------------------------------------------------------------------------------

/*!
 * \brief The MqttSubscribeNotification class
 *
 * This notification is emitted after successful subscribing.
 */
class MqttSubscribeNotification : public MqttNotification {
public:
    using Ptr = Poco::AutoPtr<MqttSubscribeNotification>; ///< Pointer to the class object.

    /*!
     * \brief MqttSubscribeNotification
     * \param source the source of notification.
     * \param messageId the message id of the subscribe message.
     * \param qos an array of integers indicating the granted QoS
     *            for each of the subscriptions.
     */
    MqttSubscribeNotification(MqttSource& source,
                              int messageId,
                              const MqttGrantedQoS& qos);

    /*!
     * \brief messageId
     * \return
     */
    int messageId() const;

    /*!
     * \brief qos
     * \return
     */
    const MqttGrantedQoS& qos() const;

private:
    int _messageId;
    MqttGrantedQoS _qos;
};

//------------------------------------------------------------------------------

/*!
 * \brief The MqttUnsubscribeNotification class
 */
class MqttUnsubscribeNotification : public MqttNotification {
public:
    using Ptr = Poco::AutoPtr<MqttUnsubscribeNotification>; ///< Pointer to the class object.

    /*!
     * \brief MqttUnsubscribeNotification
     * \param source the source of notification.
     * \param messageId the message id of the subscribe message.
     */
    MqttUnsubscribeNotification(MqttSource& source,
                                int messageId);

    /*!
     * \brief messageId
     * \return
     */
    int messageId() const;

private:
    int _messageId;
};

//------------------------------------------------------------------------------

/*!
 * \brief The MqttLogNotification class
 */
class MqttLogNotification : public MqttNotification {
public:
    using Ptr = Poco::AutoPtr<MqttLogNotification>; ///< Pointer to the class object.

    /*!
     * \brief MqttLogNotification
     * \param source
     * \param level
     * \param message
     */
    MqttLogNotification(MqttSource& source,
                        MqttLogLevel level,
                        const std::string& message);

    /*!
     * \brief level
     * \return
     */
    MqttLogLevel level() const;

    /*!
     * \brief message
     * \return
     */
    const std::string& message() const;

private:
    MqttLogLevel _level;
    std::string _message;
};

//------------------------------------------------------------------------------

/*! @} */

} // namespace connectivity

#endif // MQTTCOMMON_H
