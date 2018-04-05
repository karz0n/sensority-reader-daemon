/*
 * SensorReaderServer.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include <Poco/Foundation.h>

#include "SensorReaderServer.h"

SensorReaderServer::SensorReaderServer(std::unique_ptr<SensorReader> r)
    : _reader(std::move(r))
{ }

SensorReaderServer::~SensorReaderServer()
{
    if (_reader->isRunned()) {
        _reader->shutdown();
    }
}

bool SensorReaderServer::isRunned() const
{
    return _reader->isRunned();
}

void SensorReaderServer::run()
{
    poco_assert(!_reader->isRunned());

    _reader->run();
}

void SensorReaderServer::shutdown()
{
    poco_assert(_reader->isRunned());

    _reader->shutdown();
}




