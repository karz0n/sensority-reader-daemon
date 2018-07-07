/*!
 * \file MqttTarget.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jun 17, 2018
 */

#ifndef MQTTTARGET_HPP
#define MQTTTARGET_HPP

#include "MqttCommon.hpp"

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

/*!
 * \brief The target of notifications class.
 */
class MqttTarget
{
public:
    virtual ~MqttTarget() = default;

    /*!
     * \brief Called on connect notification was emitted.
     *
     * \see MqttConnectNotification
     */
    virtual void on(const MqttConnectNotification::Ptr& event);

    /*!
     * \brief Called on disconnect notification was emitted.
     *
     * \see MqttDisconnectNotification
     */
    virtual void on(const MqttDisconnectNotification::Ptr& event);

    /*!
     * \brief Called on publish notification was emitted.
     *
     * \see MqttPublishNotification
     */
    virtual void on(const MqttPublishNotification::Ptr& event);

    /*!
     * \brief Called on message notification was emitted.
     *
     * \see MqttMessageNotification.
     */
    virtual void on(const MqttMessageNotification::Ptr& event);

    /*!
     * \brief Called on subscribe notification was emitted.
     *
     * \see MqttSubscribeNotification
     */
    virtual void on(const MqttSubscribeNotification::Ptr& event);

    /*!
     * \brief Called on unsubscribe notification was emitted.
     *
     * \see MqttUnsubscribeNotification
     */
    virtual void on(const MqttUnsubscribeNotification::Ptr& event);
};

/*! @} */

} // namespace connectivity

#endif // MQTTTARGET_HPP
