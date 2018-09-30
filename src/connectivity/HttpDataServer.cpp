/*!
 * \file HttpDataServer.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Feb 21, 2018
 */

#include "HttpDataServer.hpp"

#include <Poco/Net/HTTPServerParams.h>

#include "data/FormatterFactory.hpp"

#include "HttpDataRequestHandlerFactory.hpp"

using Poco::Net::HTTPServerParams;
using Poco::Net::HTTPServer;

using data::StorageManager;
using data::OutputFormats;
using data::FormatterFactory;

namespace connectivity {

HttpDataServer::HttpDataServer(
        StorageManager::Ptr m,
        OutputFormats f /*= DEFAULT_HTTP_FORMAT*/,
        unsigned short p /*= DEFAULT_HTTP_PORT*/)
    : _runned(false)
{
    _server = std::make_unique<HTTPServer>(
        new HttpDataRequestHandlerFactory(m, FormatterFactory::create(f)),
        p,
        new HTTPServerParams);
}

HttpDataServer::~HttpDataServer()
{
    if (isRunned()) {
        stop();
    }
}

void HttpDataServer::run()
{
    poco_assert_msg(!isRunned(), "Http server has already been run");

    _server->start();

    _runned = true;
}

void HttpDataServer::stop()
{
    poco_assert_msg(isRunned(), "Http server has already been stopped");

    _server->stopAll(true);

    _runned = false;
}

} // namespace connectivity {
