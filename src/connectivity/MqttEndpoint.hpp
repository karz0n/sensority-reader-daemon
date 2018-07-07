/*!
 * \file MqttEndpoint.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date May 20, 2018
 */

#ifndef MQTTENDPOINT_HPP
#define MQTTENDPOINT_HPP

#include <memory>
#include <string>
#include <optional>

#include "MqttCommon.hpp"
#include "MqttNotifier.hpp"

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

/*!
 * \brief The MqttEndpoint class.
 */
class MqttEndpoint : public MqttNotifier {
public:
    using Ptr = std::shared_ptr<MqttEndpoint>; //!< Pointer to the class.
    using PasswordProviderCallback = int(*)(char*, int, int, void*); //!< Password provider callback.

    /*!
     * \brief Configures mqtt endpoint object.
     *
     * \param id the string to use as the client id.
     *
     * \param cleanSession set to \c true to instruct the broker
     *        to clean all messages and subscriptions on disconnect,
     *        \c false to instruct it to keep them.
     */
    MqttEndpoint(const std::string& id, bool cleanSession = true);

    /*!
     * Default virtual dtor.
     */
    virtual ~MqttEndpoint();

    /*!
     * \brief Connects to an MQTT broker.
     *
     * \param host the hostname or ip address of the broker to connect to.
     *
     * \param port the network port to connect to.
     *
     * \param keepalive the number of seconds after which the broker should
     *        send a PING message to the clien.
     */
    void connect(const std::string& host,
                 unsigned short port = MQTT_DEFAULT_INSECURE_PORT,
                 int keepalive = MQTT_DEFAULT_KEEPALIVE);

    /*!
     * \brief Disconnects from the broker.
     */
    void disconnect();

    /*!
     * \brief Specifies user credentials.
     * \param username the username of user.
     * \param password the password of user.
     */
    void setCredentials(const std::string& username,
                        const std::string& password);

    /*!
     * \brief Sets the number of messages that can be “in flight” at one time.
     * \param value the number of messages.
     */
    void setMaxInflightMessages(unsigned int value);

    /*!
     * \brief Configures the behaviour of the client when it has unexpectedly
     *        disconnected.
     *
     * \param delay the number of seconds to wait between reconnects.
     *
     * \param delayMax the maximum number of seconds to wait between reconnects.
     *
     * \param exponentialBackoff use exponential backoff between reconnect
     *                           attempts. Set to \c true to enable.
     */
    void setReconnectDelay(unsigned int delay, unsigned int delayMax,
                           bool exponentialBackoff);

    /*!
     * \brief Configures verification of the server hostname
     *        in the server certificate.
     *
     * \param isInsecure if set to \c false, the default, certificate hostname
     *                   checking is performed.  If set to \c true, no hostname
     *                   checking is performed and the connection is insecure.
     */
    void setInsecure(bool isInsecure);

    /*!
     * \brief Sets advanced SSL/TLS options. Must be called before connect().
     *
     * \param requirements defining the verification requirements the client
     *        will impose on the server.
     *
     * \param version the version of the SSL/TLS protocol to use as a string.
     *                The available values depend on the version of openssl that
     *                the library was compiled against.
     *                For openssl >= 1.0.1, the available options are tlsv1.2,
     *                tlsv1.1 and tlsv1, with tlv1.2 as the default.
     *                For openssl < 1.0.1, only tlsv1 is available.
     *
     * \param ciphers a string describing the ciphers available for use.
     */
    void setTransportLayerOptions(
            MqttVerificationRequirements requirements,
            MqttTransportLayerVersions version,
            const std::string& ciphers);

    /*!
     * \brief Configures the client for certificate based SSL/TLS support.
     *
     * \param path the path to a directory containing the PEM encoded trusted
     *        CA certificate files.
     */
    void configureTransportLayerSecurity(const std::string& path);

    /*!
     * \brief Configures the client for pre-shared-key based TLS support.
     *        Must be called before connect().
     *
     * \param psk the pre-shared-key in hex format with no leading “0x”.
     *
     * \param identity the identity of this client.  May be used as the username
     *        depending on the server settings.
     *
     * \param ciphers a string describing the PSK ciphers available for use.
     */
    void configureTransportLayerSecurity(
            const std::string& psk,
            const std::string& identity,
            const std::string& ciphers);

    /*!
     * \brief Configures the client for certificate based SSL/TLS support.
     *
     * \param caFile path to a file containing the PEM encoded trusted
     *               CA certificate files.
     *
     * \param certFile path to a file containing the PEM encoded
     *                 certificate file for this client.
     *
     * \param keyFile path to a file containing the PEM encoded private
     *                key for this client.
     *
     * \param passwordProvider if keyfile is encrypted provided callback
     *                         function called to allow client to pass
     *                         the correct password for decryption.
     *                         Your callback must write the password into (1),
     *                         which is (2) bytes long.  The return value must
     *                         be the length of the password.
     */
    void configureTransportLayerSecurity(
            const std::string& caFile,
            const std::string& certFile,
            const std::string& keyFile,
            std::optional<PasswordProviderCallback> passwordProvider);

    /*!
     * \brief Sets version for the client. Must be called before connect().
     * \param version the client version.
     */
    void setProtocolVersion(MqttProtocolVersion version);

    /*!
     * \brief Configures will information. Must be called before connect().
     *
     * \param topic the topic on which to publish the will.
     *
     * \param payload pointer to the data to send.
     *
     * \param size the size of the payload (bytes).
     *
     * \param qos the value indicating the Quality of Service to be used
     *            for the payload.
     *
     * \param retain set to \c true to make the will a retained message.
     */
    void willSet(const std::string& topic,
                 const void* payload,
                 std::size_t size,
                 MqttQoS qos = MqttQoS::v0,
                 bool retain = MQTT_DEFAULT_RETAIN_VALUE);


    /*!
     * \brief Configures will information. Must be called before connect().
     *
     * \param topic the topic on which to publish the will.
     *
     * \param message the will message to send.
     *
     * \param qos the value indicating the Quality of Service to be used
     *            for the message.
     *
     * \param retain set to \c true to make the will a retained message.
     */
    void willSet(const std::string& topic,
                 const std::string& message,
                 MqttQoS qos = MqttQoS::v0,
                 bool retain = MQTT_DEFAULT_RETAIN_VALUE);

    /*!
     * \brief Removes a previously configured will.
     */
    void willClear();

    /*!
     * \brief Publishes a message on a given topic.
     *
     * \param topic the name of the topic.
     *
     * \param payload pointer to the data to send.
     *
     * \param size the size of the payload in bytes.
     *
     * \param qos the value indicating the Quality of Service to be used
     *            for the payload.
     *
     * \param retain set to true to make the message retained.
     */
    void publish(const std::string& topic,
                 const void* payload,
                 std::size_t size,
                 MqttQoS qos = MqttQoS::v0,
                 bool retain = MQTT_DEFAULT_RETAIN_VALUE);

    /*!
     * \brief Publishes a message on a given topic.
     *
     * \param topic the name of the topic.
     *
     * \param message the message to send.
     *
     * \param qos the value indicating the Quality of Service to be used
     *            for the message.
     *
     * \param retain set to true to make the message retained.
     */
    void publish(const std::string& topic,
                 const std::string& message,
                 MqttQoS qos = MqttQoS::v0,
                 bool retain = MQTT_DEFAULT_RETAIN_VALUE);

    /*!
     * \brief Subscribes to a topic.
     *
     * \param pattern the subscription pattern.
     *
     * \param qos the requested Quality of Service for this subscription.
     */
    void subscribe(const std::string& pattern, MqttQoS qos = MqttQoS::v0);

    /*!
     * \brief Unsubscribes from a topic.
     *
     * \param pattern the unsubscription pattern.
     */
    void unsubscribe(const std::string& pattern);

public:
    MqttEndpoint(const MqttEndpoint&) = delete;
    MqttEndpoint operator=(const MqttEndpoint&) = delete;

public:
    /*!
     * Mqtt data endpoint factory method
     */
    template<typename ...As>
    static Ptr create(As&&... args)
    {
        return std::make_shared<MqttEndpoint>(std::forward<As>(args)...);
    }

private:
    /*! @see MqttConnectNotification */
    static void onConnect(MqttContext* context, void* object,
                          int status);

    /*! @see MqttDisconnectNotification */
    static void onDisconnect(MqttContext* context, void* object,
                             int status);

    /*! @see MqttPublishNotification */
    static void onPublish(MqttContext* context, void* object,
                          int messageId);

    /*! @see MqttMessageNotification */
    static void onMessage(MqttContext* context, void* object,
                          const MqttMessage*);

    /*! @see MqttSubscribeNotification  */
    static void onSubscribe(MqttContext* context, void* object,
                            int messageId, int qosCount, const int* grantedQos);

    /*! @see MqttUnsubscribeNotification */
    static void onUnsubscribe(MqttContext* context, void* object,
                              int messageId);

    /*! @see MqttLogNotification */
    static void onLog(MqttContext* context, void* object,
                      int level, const char *message);

private:
    MqttContext* _context;
};

/*! @} */

} // namespace connectivity

#endif  // MQTTENDPOINT_HPP
