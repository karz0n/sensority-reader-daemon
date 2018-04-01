/*
 * SensorReaderApplication.h
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADERAPPLICATION_H_
#define SENSORREADERAPPLICATION_H_

#include <string>
#include <vector>

#include <Poco/Util/OptionSet.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/ServerApplication.h>

#include "SensorCommon.h"
#include "SensorReadingStrategy.h"

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
    unsigned int getDevicePin() const;
    SensorTypes getDeviceType() const;
    SensorReadingStrategy::Ptr getDeviceReadingStrategy(SensorTypes deviceType) const;

private:
	bool _helpRequested;
};

#endif /* SENSORREADERAPPLICATION_H_ */
