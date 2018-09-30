/*!
 * \file TemperatureSensorReader.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 18, 2018
 */

#include "TemperatureSensorReader.hpp"

#include <array>
#include <chrono>
#include <exception>

#include <Poco/Exception.h>
#include <Poco/Util/Application.h>

#include "common/System.hpp"

#include "DeviceLibrary.hpp"
#include "DeviceGpio.hpp"

using Poco::Util::Application;

/**
 * \brief
 */
static const int DHT_MAXCOUNT = 32000;

/**
 * \brief
 */
static const int DHT_PULSES = 41;

namespace hardware {

/*!
 * \addtogroup hardware
 * @{
 */

TemperatureSensorReader::TemperatureSensorReader(data::Storage::Ptr storage,
                                                 DevicePinNum pin,
                                                 SensorTypes type)
    : SensorReader{storage}
    , _pin{pin}
    , _type{type}
{ }

void TemperatureSensorReader::run()
{
    DeviceLibrary::instance().initialize();

    auto pauseLength = (_type == SensorTypes::dht11)
        ? std::chrono::milliseconds(1000)
        : std::chrono::milliseconds(2000);

    while(isProceed()) {
        try {
            read();
        }
        catch (const Poco::Exception& e) {
            Application& app = Application::instance();
            app.logger().error(e.displayText());
        }
        catch (const std::exception& e) {
            Application& app = Application::instance();
            app.logger().error(e.what());
        }
        catch (...) {
            Application& app = Application::instance();
            app.logger().error("Unknown error");
        }
        waitFor(pauseLength);
    }

    DeviceLibrary::instance().cleanup();
}

void TemperatureSensorReader::read()
{
    std::array<unsigned long long, DHT_PULSES * 2> pulseCounts;

    bool isRoot = common::System::isRoot();
    if (isRoot) {
        common::System::setCurrentThreadHighPriority();
    }
    try {
        DeviceGpio::Ptr gpio = DeviceLibrary::instance().gpio(_pin);
        gpio->dir(DevicePinDirs::outHigh);
        gpio->delay(500);
        gpio->write(DevicePinLevels::low);
        gpio->delay(_type == SensorTypes::dht11 ? 18 : 15);
        gpio->dir(DevicePinDirs::in);
        gpio->count(DevicePinLevels::high, DHT_MAXCOUNT);

        for (std::size_t i = 0; i < DHT_PULSES * 2; i += 2) {
            pulseCounts[i] = gpio->count(DevicePinLevels::low, DHT_MAXCOUNT);
            pulseCounts[i + 1] = gpio->count(DevicePinLevels::high, DHT_MAXCOUNT);
        }
    } catch (...) {
        if (isRoot) {
            common::System::setCurrentThreadDefaultPriority();
        }
        throw;
    }

    unsigned long long threshold = 0;
    for (std::size_t i = 2; i < DHT_PULSES * 2; i += 2) {
        threshold += pulseCounts[i];
    }
    threshold /= DHT_PULSES - 1;

    std::array<unsigned char, 5> data;
    for (std::size_t i = 3; i < DHT_PULSES * 2; i += 2) {
        std::size_t index = (i - 3) / 16;
        data[index] <<= 1;
        if (pulseCounts[i] >= threshold) {
            data[index] |= 1;
        }
    }

    if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
        if (_type == SensorTypes::dht11) {
            double temperature = data[2];
            double humidity = data[0];
            storage().store({
                {"temperature", temperature},
                {"humidity", humidity}
            });
            return;
        }

        if (_type == SensorTypes::dht22) {
            double humidity = (data[0] * 256 + data[1]) / 10.0;
            double temperature = ((data[2] & 0x7F) * 256 + data[3]) / 10.0;
            if (data[2] & 0x80) {
                temperature *= -1.0;
            }
            storage().store({
                {"temperature", temperature},
                {"humidity", humidity}
            });
            return;
        }

        throw Poco::RuntimeException("Unknown sensor type");
    }

    throw Poco::RuntimeException("Value checksum error");
}

/*! @} */

} // namespace hardware

