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

HttpSensorReaderServer::HttpSensorReaderServer(std::unique_ptr<SensorReader> r, unsigned short p)
    : SensorReaderServer(std::move(r))
    , _runned(false)
{
    _formatter = std::make_unique<JsonFormatter>();
    _server = std::make_unique<HTTPServer>(
        new HttpSensorReaderRequestHandlerFactory(storage(), *_formatter),
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
    SensorReaderServer::run();
    _server->start();
}

void HttpSensorReaderServer::shutdown()
{
    poco_assert(_runned);

    _server->stopAll(true);
    SensorReaderServer::shutdown();
    _runned = false;
}
