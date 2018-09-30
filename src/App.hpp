/*!
* \file App.hpp
* \author Denys Asauliak <d.asauliak@gmail.com>
* \date Mar 22, 2018
*/

#ifndef APP_HPP
#define APP_HPP

#include <string>

#include <Poco/Util/ServerApplication.h>

#include "hardware/SensorReaderManager.hpp"

/*!
 * \brief The App class
 */
class App: public Poco::Util::ServerApplication {
public:
    App();
    ~App() override;

protected:
    /*!
     * \brief Initialize application.
     * \param self reference to the application object.
     */
	void initialize(Poco::Util::Application& self) override;

    /*!
     * \brief Define option set.
     * \param options reference to the options collection.
     */
	void defineOptions(Poco::Util::OptionSet& options) override;

    /*!
     * \brief Main method of application.
     * \param args arguments of the application.
     * \return exit code.
     */
    int main(const std::vector<std::string>& args) override;

protected:
    /*!
     * \brief Handle application help
     * \param name option name.
     * \param value option value.
     */
    void handleHelp(const std::string& name, const std::string& value);

private:
    void displayHelp();

    hardware::SensorReaderManager::Ptr initSensorReaderManager();
    void initHttpDataServer();
    void initMqttEndpoint();

//    bool isHttpEnabled() const;
//    unsigned short getHttpPort() const;
//    std::string getHttpFormat() const;

//    device::PinNum getDevicePin() const;
//    sensor::SensorTypes getDeviceType() const;

private:
	bool _helpRequested;
    hardware::SensorReaderManager _manager;
};

#endif // APP_HPP
