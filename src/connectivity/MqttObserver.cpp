/*!
 * \file MqttObserver.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jun 17, 2018
 */

#include "MqttObserver.hpp"

#ifndef NDEBUG
#include <Poco/Util/Application.h>
#endif

namespace connectivity {

void MqttObserver::on(const MqttConnectNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Connect");
#endif
}

void MqttObserver::on(const MqttDisconnectNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Disconnect");
#endif
}

void MqttObserver::on(const MqttPublishNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Publish");
#endif
}

void MqttObserver::on(const MqttMessageNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Message");
#endif
}

void MqttObserver::on(const MqttSubscribeNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Subscribe");
#endif
}

void MqttObserver::on(const MqttUnsubscribeNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Unsubscribe");
#endif
}

void MqttObserver::on(const MqttLogNotification::Ptr&)
{
#ifndef NDEBUG
    Poco::Util::Application::instance()
            .logger().debug("On Log");
#endif
}

} // namespace connectivity
