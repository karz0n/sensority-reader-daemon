/*!
 * \file SensorReaderManager.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 18, 2018
 */

#include "SensorReaderManager.hpp"

#include <algorithm>

#include <Poco/Exception.h>
#include <Poco/Format.h>

namespace hardware {

void SensorReaderManager::append(const std::string& name, SensorReader::Ptr reader)
{
    if (has(name)) {
        throw Poco::ExistsException(Poco::format("Reader with '%s' name already exists", name));
    }
    _readers.emplace(name, std::move(reader));
}

void SensorReaderManager::remove(const std::string& name)
{
    auto it = _readers.find(name);
    if (it == _readers.end()) {
        throw Poco::NotFoundException(Poco::format("Reader with '%s' name not found", name));
    }

    auto& r = *it->second;
    if (r.isRunned()) {
        r.stop();
    }
    _readers.erase(it);
}

bool SensorReaderManager::has(const std::string& name) const
{
    return (_readers.count(name) != 0);
}

void SensorReaderManager::start(const std::string& name)
{
    auto& r = get(name);
    if (!r.isRunned()) {
        r.start();
    }
}

void SensorReaderManager::stop(const std::string& name)
{
    auto& r = get(name);
    if (r.isRunned()) {
        r.stop();
    }
}

void SensorReaderManager::startAll()
{
    if (_readers.empty()) {
        return;
    }

    std::for_each(_readers.begin(), _readers.end(), [] (Readers::value_type& p) {
        auto& r = *p.second;
        if (!r.isRunned()) {
            r.start();
        }
    });
}

void SensorReaderManager::stopAll()
{
    if (_readers.empty()) {
        return;
    }

    std::for_each(_readers.cbegin(), _readers.cend(), [] (const Readers::value_type& p) {
        auto& r = *p.second;
        if (r.isRunned()) {
            r.stop();
        }
    });
}

SensorReader& SensorReaderManager::get(const std::string& name)
{
    auto it = _readers.find(name);
    if (it == _readers.end()) {
        throw Poco::NotFoundException(Poco::format("Reader with '%s' name not found", name));
    }
    return *it->second;
}

} // namespace hardware
