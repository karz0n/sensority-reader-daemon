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

using sensor::SensorReadableData;

namespace connectivity {

HttpDataServer::HttpDataServer(
        unsigned short p,
        SensorReadableData::Ptr d)
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

formatter::Formatter::Ptr HttpDataServer::getFormatter()
{
    return formatter::Formatter::create<formatter::JsonFormatter>();
}

} // namespace connectivity {
