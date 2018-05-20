/*
 * MqttDataEndpoint.hpp
 *
 *  Created on: May 20, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef MQTTDATAENDPOINT_HPP
#define MQTTDATAENDPOINT_HPP

#include <memory>
#include <string>

/**
 *
 */
struct mosquitto;

namespace connectivity {

/**
 * @brief Default value of MQTT insecure endpoint port
 */
const unsigned short MQTT_DEFAULT_INSECURE_PORT = 1883;

/**
 * @brief Default value of MQTT secure endpoint port
 */
const unsigned short MQTT_DEFAULT_SECURE_PORT = 8883;

/**
 * @brief Default value of MQTT connection keepalive timeout
 */
const int MQTT_DEFAULT_KEEPALIVE = 60;

/**
 * @brief Default value of MQTT quality of service to be used for the message
 */
const int MQTT_DEFAULT_QOS_VALUE = 0;

/**
 * @brief Default value of MQTT retain to be used for the message
 */
const bool MQTT_DEFAULT_RETAIN_VALUE = false;

/**
 * @brief The MqttDataEndpoint class
 */
class MqttDataEndpoint
{
public:
    using Ptr = std::shared_ptr<MqttDataEndpoint>;

    MqttDataEndpoint(const std::string& id = "", bool cleanSession = true);
    virtual ~MqttDataEndpoint();

    /**
     * @brief connect to an MQTT broker
     * @param host the hostname or ip address of the broker to connect to
     * @param port the network port to connect to
     * @param keepalive the number of seconds after which the broker should send a PING message to the clien
     */
    void connect(const std::string& host,
                 unsigned short port = MQTT_DEFAULT_INSECURE_PORT,
                 int keepalive = MQTT_DEFAULT_KEEPALIVE);

    /**
     * @brief disconnect from the broker
     */
    void disconnect();

    /**
     * @brief obtain status of connection
     * @return the status of connection
     */
    inline bool isConnected() const;

    /**
     * @brief specify path to certificate files
     * @param path the path to a directory containing the PEM encoded trusted CA certificate files
     */
    void setCertificatesPath(const std::string& path);

    /**
     * @brief specify user credentials
     * @param username the username of user
     * @param password the password of user
     */
    void setCredentials(const std::string& username,
                        const std::string& password);


    /**
     * @brief publish
     * @param topic name of the topic
     * @param payload pointer to the data to send
     * @param size the size of the payload (bytes)
     * @param qos integer value 0, 1 or 2 indicating the Quality of Service to be used for the message
     * @param retain set to true to make the message retained
     */
    void publish(const std::string& topic,
                 const void* payload,
                 std::size_t size,
                 int qos = MQTT_DEFAULT_QOS_VALUE,
                 bool retain = MQTT_DEFAULT_RETAIN_VALUE);
public:
    MqttDataEndpoint(const MqttDataEndpoint&) = delete;
    MqttDataEndpoint operator=(const MqttDataEndpoint&) = delete;

public:

    template<typename ...Ts>
    static Ptr create(Ts&&... args)
    {
        return std::make_shared<MqttDataEndpoint>(std::forward<Ts>(args)...);
    }

private:
    mosquitto* _mosq;
    bool _connected;
};

//
// Inlines
//

bool MqttDataEndpoint::isConnected() const
{
    return _connected;
}

} // namespace connectivity

#endif  // MQTTDATAENDPOINT_HPP
