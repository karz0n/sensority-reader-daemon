/*!
 * \file MqttNotifier.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jun 22, 2018
 */

#ifndef MQTTNOTIFIER_HPP
#define MQTTNOTIFIER_HPP

#include <string>

#include <Poco/NotificationCenter.h>

#include "MqttSource.hpp"
#include "MqttCommon.hpp"
#include "MqttTarget.hpp"

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

/*!
 * \brief The MqttNotifier class.
 *
 */
class MqttNotifier : public MqttSource
{
public:
    MqttNotifier();

    /*!
     * \brief inject
     * \param target
     */
    void inject(MqttTarget& target);

    /*!
     * \brief eject
     * \param target
     */
    void eject(MqttTarget& target);

protected:

    /*!
     * \brief emitConnectNotification
     * \param statusCode
     */
    void emitConnectNotification(MqttConnectionStatusCodes statusCode);

    /*!
     * \brief emitDisconnectNotification
     * \param reason
     */
    void emitDisconnectNotification(int reason);

    /*!
     * \brief emitPublishNotification
     * \param messageId
     */
    void emitPublishNotification(int messageId);

    /*!
     * \brief emitMessageNotification
     * \param message
     */
    void emitMessageNotification(const MqttMessage& message);

    /*!
     * \brief emitSubscribeNotification
     * \param messageId
     * \param qos
     */
    void emitSubscribeNotification(int messageId, const MqttGrantedQoS& qos);

    /*!
     * \brief emitUnsubscribeNotification
     * \param messageId
     */
    void emitUnsubscribeNotification(int messageId);

    /*!
     * \brief emitLogNotification
     * \param level
     * \param message
     */
    void emitLogNotification(MqttLogLevel level, const std::string& message);

private:
    Poco::NotificationCenter _nc;
};

/*! @} */

} // namespace connectivity

#endif // MQTTNOTIFIER_HPP
