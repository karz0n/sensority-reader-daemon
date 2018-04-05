/*
 * SensorDataStorage.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "SensorDataStorage.h"

SensorDataStorage::SensorDataStorage()
	: _empty(true)
{ }

std::string SensorDataStorage::format(const Formatter& formatter) const
{
    WriteLock lock = lockWrite();
	return _data->format(formatter);
}

void SensorDataStorage::update(std::unique_ptr<SensorData> data)
{
    ReadLock lock = lockRead();
	_empty = false;
	_lastUpdate = Clock::now();
    _data = std::move(data);
}

bool SensorDataStorage::empty() const
{
    WriteLock lock = lockWrite();
	return _empty;
}

SensorDataStorage::TimePoint SensorDataStorage::lastUpdate() const
{
    WriteLock lock = lockWrite();
	return _lastUpdate;
}

SensorDataStorage::ReadLock SensorDataStorage::lockRead() const
{
    return ReadLock(_mutex);
}

SensorDataStorage::WriteLock SensorDataStorage::lockWrite() const
{
    return WriteLock(_mutex);
}

