/*
 * SensorDataStorage.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "SensorDataStorage.hpp"

namespace sensor {

SensorDataStorage::SensorDataStorage()
	: _empty(true)
{ }

std::string SensorDataStorage::format(const formatter::Formatter& formatter) const
{
    WriteLock lock = lockWrite();
	return _data->format(formatter);
}

void SensorDataStorage::update(SensorData::Ptr data)
{
    ReadLock lock = lockRead();
    _data = std::move(data);
	_empty = false;
	_lastUpdate = Clock::now();
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

} // namespace sensor

