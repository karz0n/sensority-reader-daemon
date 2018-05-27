/*
 * SensorReaderApplication.hpp
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADERAPPLICATION_HPP_
#define SENSORREADERAPPLICATION_HPP_

#include <string>

#include <Poco/Util/ServerApplication.h>

#include "device/DeviceCommon.hpp"
#include "connectivity/HttpDataServer.hpp"
#include "sensor/SensorCommon.hpp"
#include "sensor/SensorReader.hpp"

/**
 * @brief The SensorReaderApplication class
 */
class SensorReaderApplication: public Poco::Util::ServerApplication {
public:
	SensorReaderApplication();
    ~SensorReaderApplication() override;

protected:
	void initialize(Poco::Util::Application& self) override;
	void defineOptions(Poco::Util::OptionSet& options) override;

    int main(const std::vector<std::string>& args) override;

protected:
    void handleHelp(const std::string& name, const std::string& value);

private:
    void displayHelp();

    sensor::SensorReader::Ptr createSensorReader();
    connectivity::HttpDataServer::Ptr createHttpServer(sensor::SensorReadableData::Ptr);

    bool isHttpEnabled() const;
    unsigned short getHttpPort() const;
    std::string getHttpFormat() const;

    device::PinNum getDevicePin() const;
    sensor::SensorTypes getDeviceType() const;

private:
	bool _helpRequested;
};

#endif /* SENSORREADERAPPLICATION_HPP_ */
