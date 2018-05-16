/*
 * HttpDataRequestHandlerFactory.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "HttpDataRequestHandlerFactory.hpp"
#include "HttpDataRequestHandler.hpp"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;

HttpDataRequestHandlerFactory::HttpDataRequestHandlerFactory(
        std::shared_ptr<SensorReadableData> d,
        std::shared_ptr<Formatter> f)
    : _data(d), _formatter(f)
{ }

HTTPRequestHandler* HttpDataRequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request)
{
    if (request.getURI() == "/") {
        return new HttpDataRequestHandler(*_data, *_formatter);
    }
    else {
        return nullptr;
    }
}
