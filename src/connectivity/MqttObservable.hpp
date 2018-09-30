/*!
 * \file MqttObservable.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jun 17, 2018
 */

#ifndef MQTTOBSERVABLE_HPP
#define MQTTOBSERVABLE_HPP

#include <string>

#include <Poco/NotificationCenter.h>

#include "MqttCommon.hpp"
#include "MqttObserver.hpp"

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

/*!
 * \brief The source of notification class.
 */
class MqttObservable
{
public:
    virtual ~MqttObservable() = default;  ///!< Default dtor.

    /*!
     * \brief inject
     * \param observer
     */
    void inject(MqttObserver& observer);

    /*!
     * \brief eject
     * \param observer
     */
    void eject(MqttObserver& observer);

    /*!
     * \brief hasObservers
     * \return
     */
    bool hasObservers() const;

    /*!
     * \brief countObservers
     * \return
     */
    std::size_t countObservers() const;

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

#endif // MQTTOBSERVABLE_HPP
