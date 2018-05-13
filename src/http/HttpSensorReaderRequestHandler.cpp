/*
 * HttpSensorReaderRequestHandler.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "HttpSensorReaderRequestHandler.hpp"

#ifndef NDEBUG
#include <Poco/Util/Application.h>
#endif

using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

HttpSensorReaderRequestHandler::HttpSensorReaderRequestHandler(
        const SensorDataReadable& d,
        const Formatter& f)
    : _data(d), _formatter(f)
{ }

void HttpSensorReaderRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
#ifndef NDEBUG
    using Poco::Util::Application;
    Application::instance()
            .logger()
            .information("Request from " + request.clientAddress().toString());
#endif

    // TODO: Make independent setting of conent type
    //       from type of formatter

    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    auto& os = response.send();
    os << _data.format(_formatter);
}

