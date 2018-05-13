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
        const SensorDataStorage& s,
        const Formatter& f)
    : _storage(s), _formatter(f)
{ }

void HttpSensorReaderRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
#ifndef NDEBUG
    using Poco::Util::Application;
    Application& app = Application::instance();
    app.logger()
       .information("Request from " + request.clientAddress().toString());
#endif

    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    std::ostream& os = response.send();
    os << _storage.format(_formatter);
}

