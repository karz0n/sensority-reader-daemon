/*
 * HttpSensorReaderRequestHandlerFactory.h
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef HTTPSENSORREADERREQUESTHANDLERFACTORY_H_
#define HTTPSENSORREADERREQUESTHANDLERFACTORY_H_

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include "Formatter.h"
#include "SensorDataStorage.h"

/**
 * @brief The HttpSensorReaderRequestHandlerFactory class
 */
class HttpSensorReaderRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory {
public:
    HttpSensorReaderRequestHandlerFactory(const SensorDataStorage& storage, const Formatter& formatter);

    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

private:
    const SensorDataStorage& _storage;
    const Formatter& _formatter;
};

#endif /* HTTPSENSORREADERREQUESTHANDLERFACTORY_H_ */
