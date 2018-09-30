/*!
 * \file MqttNotifier.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jun 22, 2018
 */

#ifndef MQTTNOTIFIER_HPP
#define MQTTNOTIFIER_HPP

#include <atomic>
#include <memory>
#include <list>

#include "data/DataObserver.hpp"
#include "data/Formatter.hpp"
#include "data/Storage.hpp"

#include "MqttClient.hpp"

namespace data {
class Storage;
}

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

/*!
 * \brief The MqttNotifier class.
 *
 */
class MqttNotifier : private data::DataObserver,
                     private MqttObserver
{
public:
    using Ptr = std::unique_ptr<MqttNotifier>;

    MqttNotifier(MqttEndpoint::Ptr endpoint, data::OutputFormats format);
    virtual ~MqttNotifier();

    /*!
     * \brief watch
     *
     * \param storage
     */
    void watch(data::Storage::Ptr storage);

private:
    void on(const MqttConnectNotification::Ptr& event) override;
    void on(const MqttDisconnectNotification::Ptr& event) override;

private:
    void on(const data::StorageUpdateNotification::Ptr& event) override;

private:
    std::atomic<bool> _connected;
    MqttEndpoint::Ptr _endpoint;
    data::Formatter::Ptr _formatter;
    std::list<data::Storage::Ptr> _storages;
};

/*! @} */

} // namespace connectivity

#endif // MQTTNOTIFIER_HPP
