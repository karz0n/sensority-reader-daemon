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

namespace connectivity {

HttpDataRequestHandlerFactory::HttpDataRequestHandlerFactory(
        sensor::SensorReadableData::Ptr d,
        formatter::Formatter::Ptr f)
    : _data(d), _formatter(f)
{ }

HTTPRequestHandler* HttpDataRequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request)
{
    if (request.getURI() != "/") {
        return nullptr;
    }

    return new HttpDataRequestHandler(*_data, *_formatter);
}

} // namespace connectivity
