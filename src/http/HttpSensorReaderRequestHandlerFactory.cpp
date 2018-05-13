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
        std::shared_ptr<SensorDataReadable> d,
        std::shared_ptr<Formatter> f)
    : _data(d), _formatter(f)
{ }

HTTPRequestHandler* HttpSensorReaderRequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request)
{
    if (request.getURI() == "/") {
        return new HttpSensorReaderRequestHandler(*_data, *_formatter);
    }
    else {
        return nullptr;
    }
}
