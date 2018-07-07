/*!
 * \file MqttTarget.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jun 17, 2018
 */

#include "MqttTarget.hpp"

#ifndef NDEBUG
#include <Poco/Util/Application.h>
#endif

namespace connectivity {

void MqttTarget::on(const MqttConnectNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Connect");
#endif
}

void MqttTarget::on(const MqttDisconnectNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Disconnect");
#endif
}

void MqttTarget::on(const MqttPublishNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Publish");
#endif
}

void MqttTarget::on(const MqttMessageNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Message");
#endif
}

void MqttTarget::on(const MqttSubscribeNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Subscribe");
#endif
}

void MqttTarget::on(const MqttUnsubscribeNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Unsubscribe");
#endif
}

} // namespace connectivity
