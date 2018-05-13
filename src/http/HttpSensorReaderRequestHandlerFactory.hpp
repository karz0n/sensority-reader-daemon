/*
 * HttpSensorReaderRequestHandlerFactory.h
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef HTTPSENSORREADERREQUESTHANDLERFACTORY_H_
#define HTTPSENSORREADERREQUESTHANDLERFACTORY_H_

#include <memory>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include "formatter/Formatter.hpp"
#include "sensor/SensorDataReadable.hpp"

/**
 * @brief The HttpSensorReaderRequestHandlerFactory class
 */
class HttpSensorReaderRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory {
public:
    HttpSensorReaderRequestHandlerFactory(
            std::shared_ptr<SensorDataReadable> data,
            std::shared_ptr<Formatter> formatter);

    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

private:
    std::shared_ptr<SensorDataReadable> _data;
    std::shared_ptr<Formatter> _formatter;
};

#endif /* HTTPSENSORREADERREQUESTHANDLERFACTORY_H_ */
