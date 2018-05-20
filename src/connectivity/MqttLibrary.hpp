/*
 * MqttLibrary.hpp
 *
 *  Created on: May 20, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef MQTTLIBRARY_HPP
#define MQTTLIBRARY_HPP

#include <string>
#include <memory>

#include "MqttDataEndpoint.hpp"

namespace connectivity {

/**
 * @brief The MqttLibrary class
 */
class MqttLibrary final
{
public:
    static MqttLibrary& instance();

    void initialize();
    void cleanup();
    inline bool isInitialized() const;

    MqttDataEndpoint::Ptr endpoint(const std::string& id = "", bool cleanSession = true);

public:
    MqttLibrary(const MqttLibrary&) = delete;
    MqttLibrary operator=(const MqttLibrary&) = delete;

private:
    MqttLibrary();
    ~MqttLibrary();

private:
    unsigned long _counter;
};

//
// Inline
//

bool MqttLibrary::isInitialized() const
{
    return _counter > 0;
}

} // namespace connectivity

#endif // MQTTLIBRARY_HPP
