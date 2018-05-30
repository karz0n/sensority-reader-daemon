/*
 * HttpDataServer.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "HttpDataServer.hpp"

#include <Poco/Net/HTTPServerParams.h>

#include "formatter/FormatterFactory.hpp"

#include "HttpDataRequestHandlerFactory.hpp"

using Poco::Net::HTTPServerParams;
using Poco::Net::HTTPServer;

using sensor::SensorReadableData;

namespace connectivity {

HttpDataServer::HttpDataServer(
        unsigned short p,
        const std::string& f,
        SensorReadableData::Ptr d)
    : _runned(false)
{
    _server = std::make_unique<HTTPServer>(
        new HttpDataRequestHandlerFactory(d, getFormatter(f)),
        p,
        new HTTPServerParams);
}

HttpDataServer::~HttpDataServer()
{
    if (isRunned()) {
        shutdown();
    }
}

void HttpDataServer::run()
{
    poco_assert_msg(!isRunned(), "Http server has already been run");

    _server->start();

    _runned = true;
}

void HttpDataServer::shutdown()
{
    poco_assert_msg(isRunned(), "Http server has already been stopped");

    _server->stopAll(true);

    _runned = false;
}

formatter::Formatter::Ptr HttpDataServer::getFormatter(const std::string& format)
{
    return formatter::FormatterFactory::create(format);
}

} // namespace connectivity {
