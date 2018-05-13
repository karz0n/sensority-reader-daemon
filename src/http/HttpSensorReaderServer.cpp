/*
 * HttpSensorReaderServer.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "HttpSensorReaderServer.hpp"
#include "HttpSensorReaderRequestHandlerFactory.hpp"

#include "formatter/JsonFormatter.hpp"

#include <Poco/Net/HTTPServerParams.h>

using Poco::Net::HTTPServerParams;
using Poco::Net::HTTPServer;

HttpSensorReaderServer::HttpSensorReaderServer(
        unsigned short p,
        std::shared_ptr<SensorDataReadable> d)
    : _runned(false)
{
    _server = std::make_unique<HTTPServer>(
        new HttpSensorReaderRequestHandlerFactory(d, createFormatter()),
        p,
        new HTTPServerParams);
}

HttpSensorReaderServer::~HttpSensorReaderServer()
{
    if (_runned) {
        _server->stopAll(true);
    }
}

bool HttpSensorReaderServer::isRunned() const
{
    return _runned;
}

void HttpSensorReaderServer::run()
{
    poco_assert(!_runned);

    _runned = true;
    _server->start();
}

void HttpSensorReaderServer::shutdown()
{
    poco_assert(_runned);

    _server->stopAll(true);
    _runned = false;
}

std::shared_ptr<Formatter> HttpSensorReaderServer::createFormatter()
{
    return std::make_shared<JsonFormatter>();
}
