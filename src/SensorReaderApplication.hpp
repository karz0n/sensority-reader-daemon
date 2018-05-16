/*
 * SensorReaderApplication.hpp
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADERAPPLICATION_HPP_
#define SENSORREADERAPPLICATION_HPP_

#include <cstdint>

#include <Poco/Util/ServerApplication.h>

#include "sensor/SensorCommon.hpp"

/**
 * @brief The SensorReaderApplication class
 */
class SensorReaderApplication: public Poco::Util::ServerApplication {
public:
	SensorReaderApplication();
    ~SensorReaderApplication() override;

protected:
	void initialize(Poco::Util::Application& self) override;
	void uninitialize() override;
	void reinitialize(Poco::Util::Application& self) override;
	void defineOptions(Poco::Util::OptionSet& options) override;
	void handleOption(const std::string& name, const std::string& value) override;

    int main(const std::vector<std::string>& args) override;

protected:
    void handleHelp(const std::string& name, const std::string& value);

private:
    void displayHelp();
    unsigned short getServerPort() const;
    std::uint8_t getDevicePin() const;
    SensorTypes getDeviceType() const;

private:
	bool _helpRequested;
};

#endif /* SENSORREADERAPPLICATION_HPP_ */
