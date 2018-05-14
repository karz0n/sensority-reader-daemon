/*
 * HttpSensorReaderServer.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "HttpDataServer.hpp"
#include "HttpDataRequestHandlerFactory.hpp"

#include "formatter/JsonFormatter.hpp"

#include <Poco/Net/HTTPServerParams.h>

using Poco::Net::HTTPServerParams;
using Poco::Net::HTTPServer;

HttpDataServer::HttpDataServer(
        unsigned short p,
        std::shared_ptr<SensorDataReadable> d)
    : _runned(false)
{
    _server = std::make_unique<HTTPServer>(
        new HttpDataRequestHandlerFactory(d, getFormatter()),
        p,
        new HTTPServerParams);
}

HttpDataServer::~HttpDataServer()
{
    if (isRunned()) {
        _server->stopAll(true);
    }
}

void HttpDataServer::run()
{
    poco_assert_msg(!isRunned(), "Http server has already been run");

    _runned = true;
    _server->start();
}

void HttpDataServer::shutdown()
{
    poco_assert_msg(isRunned(), "Http server has already been stopped");

    _server->stopAll(true);
    _runned = false;
}

std::shared_ptr<Formatter> HttpDataServer::getFormatter()
{
    return std::make_shared<JsonFormatter>();
}
