/*
 * HttpSensorReaderRequestHandlerFactory.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "HttpSensorReaderRequestHandlerFactory.hpp"
#include "HttpSensorReaderRequestHandler.hpp"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;

HttpSensorReaderRequestHandlerFactory::HttpSensorReaderRequestHandlerFactory(
        const SensorDataStorage& s,
        const Formatter& f)
    : _storage(s), _formatter(f)
{ }

HTTPRequestHandler* HttpSensorReaderRequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request)
{
    if (request.getURI() == "/") {
        return new HttpSensorReaderRequestHandler(_storage, _formatter);
    }
    else {
        return nullptr;
    }
}

