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
	WriteLocking lock = lockWrite();
	return _data->format(formatter);
}

void SensorDataStorage::update(SensorData::Ptr data)
{
	ReadLocking lock = lockRead();
	_empty = false;
	_lastUpdate = Clock::now();
    _data = std::move(data);
}

bool SensorDataStorage::empty() const
{
	WriteLocking lock = lockWrite();
	return _empty;
}

SensorDataStorage::TimePoint SensorDataStorage::lastUpdate() const
{
	WriteLocking lock = lockWrite();
	return _lastUpdate;
}

SensorDataStorage::ReadLocking SensorDataStorage::lockRead() const
{
	return ReadLocking(_mutex);
}

SensorDataStorage::WriteLocking SensorDataStorage::lockWrite() const
{
	return WriteLocking(_mutex);
}

