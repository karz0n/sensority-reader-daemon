/*
 * HttpSensorReaderRequestHandler.h
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef HTTPSENSORREADERREQUESTHANDLER_H_
#define HTTPSENSORREADERREQUESTHANDLER_H_

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandler.h>

#include "formatter/Formatter.hpp"
#include "sensor/SensorDataReadable.hpp"

/**
 * @brief The HttpSensorReaderRequestHandler class
 */
class HttpSensorReaderRequestHandler: public Poco::Net::HTTPRequestHandler {
public:
    HttpSensorReaderRequestHandler(
            const SensorDataReadable& storage,
            const Formatter& formatter);

    void handleRequest(
            Poco::Net::HTTPServerRequest& request,
            Poco::Net::HTTPServerResponse& response);

private:
    const SensorDataReadable& _data;
    const Formatter& _formatter;
};

#endif /* HTTPSENSORREADERREQUESTHANDLER_H_ */
