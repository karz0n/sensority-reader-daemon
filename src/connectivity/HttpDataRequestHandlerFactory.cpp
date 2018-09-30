/*!
 * \file HttpDataRequestHandlerFactory.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 22, 2018
 */

#include "HttpDataRequestHandlerFactory.hpp"
#include "HttpDataRequestHandler.hpp"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;

namespace connectivity {

HttpDataRequestHandlerFactory::HttpDataRequestHandlerFactory(
        data::StorageManager::Ptr m,
        data::Formatter::Ptr f)
    : _storageManager{m}
    , _formatter{f}
{ }

HTTPRequestHandler* HttpDataRequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request)
{
    if (request.getURI() != "/") {
        return nullptr;
    }
    return new HttpDataRequestHandler(*_storageManager, *_formatter);
}

} // namespace connectivity
