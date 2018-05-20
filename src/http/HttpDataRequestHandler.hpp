/*
 * HttpDataRequestHandler.hpp
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef HTTPDATAREQUESTHANDLER_HPP_
#define HTTPDATAREQUESTHANDLER_HPP_

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandler.h>

#include "formatter/Formatter.hpp"
#include "sensor/SensorReadableData.hpp"

/**
 * @brief The HttpDataRequestHandler class
 */
class HttpDataRequestHandler: public Poco::Net::HTTPRequestHandler {
public:
    HttpDataRequestHandler(
            const SensorReadableData& storage,
            const Formatter& formatter);

    void handleRequest(
            Poco::Net::HTTPServerRequest& request,
            Poco::Net::HTTPServerResponse& response);

private:
    const SensorReadableData& _data;
    const Formatter& _formatter;
};

#endif /* HTTPDATAREQUESTHANDLER_HPP_ */