/*
 * HttpDataRequestHandler.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "HttpDataRequestHandler.hpp"

#include "sensor/SensorReadableData.hpp"
#include "formatter/Formatter.hpp"

#ifndef NDEBUG
#include <Poco/Util/Application.h>
#endif

using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

using sensor::SensorReadableData;
using formatter::Formats;
using formatter::Formatter;

namespace connectivity {

HttpDataRequestHandler::HttpDataRequestHandler(
        const SensorReadableData& d,
        const Formatter& f)
    : _data(d), _formatter(f)
{ }

void HttpDataRequestHandler::handleRequest(HTTPServerRequest& request,
                                           HTTPServerResponse& response)
{
#ifndef NDEBUG
    using Poco::Util::Application;
    Application::instance()
            .logger()
            .information("Request from " + request.clientAddress().toString());
#endif

    response.setChunkedTransferEncoding(true);

    switch (_formatter.type()) {
    case Formats::text:
        response.setContentType("text/plain");
        break;
    case Formats::json:
        response.setContentType("application/json");
        break;
    default:
        response.setContentType("text/plain");
    }

    auto& os = response.send();
    os << _data.format(_formatter);
}

} // namespace connectivity
