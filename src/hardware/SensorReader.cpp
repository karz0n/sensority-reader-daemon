/*!
 * \file SensorReader.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 18, 2018
 */

#include "SensorReader.hpp"

namespace hardware {

SensorReader::SensorReader(data::Storage::Ptr s)
    : _stopOffered{true}
    , _runned{false}
    , _storage{s}
{ }

void SensorReader::start()
{
    _stopOffered = false;
    _thread = std::thread(&SensorReader::run, this);
    _runned = true;
}

void SensorReader::stop()
{
    _stopOffered = true;
    _offer.notify_one();
    if (_thread.joinable()) {
        _thread.join();
    }
    _runned = false;
}

bool SensorReader::isProceed() const
{
    return !_stopOffered;
}

} // namespace hardware
