/*
 * HttpSensorReaderServer.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "HttpSensorReaderServer.h"
#include "HttpSensorReaderRequestHandlerFactory.h"
#include "JsonFormatter.h"

#include <Poco/Net/HTTPServerParams.h>

using Poco::Net::HTTPServerParams;
using Poco::Net::HTTPServer;

HttpSensorReaderServer::HttpSensorReaderServer(SensorReader::Ptr reader)
    : SensorReaderServer(std::move(reader))
    , _port(8080), _runned(false)
{
    _formatter = std::make_shared<JsonFormatter>();
    _server = std::make_unique<HTTPServer>(
        new HttpSensorReaderRequestHandlerFactory(storage(), *_formatter),
        _port,
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
