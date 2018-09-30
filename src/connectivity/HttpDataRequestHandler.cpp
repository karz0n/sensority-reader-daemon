/*!
 * \file HttpDataRequestHandler.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 22, 2018
 */

#include "HttpDataRequestHandler.hpp"

#ifndef NDEBUG
#include <Poco/Util/Application.h>
#endif

#include "data/StorageManager.hpp"
#include "data/Formatter.hpp"

using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

using data::StorageManager;
using data::Formatter;
using data::OutputFormats;

namespace connectivity {

HttpDataRequestHandler::HttpDataRequestHandler(
        const data::StorageManager& m,
        const Formatter& f)
    : _storageManager{m}
    , _formatter{f}
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
    response.setContentType("text/plain");

    if (_formatter.type() == OutputFormats::json) {
        response.setContentType("application/json");
    }

    auto& os = response.send();
    os << _storageManager.format(_formatter);
}

} // namespace connectivity
