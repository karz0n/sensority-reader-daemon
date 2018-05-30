/*
 * ThreadTarget.cpp
 *
 *  Created on: May 27, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "ThreadTarget.hpp"

namespace common {

ThreadTarget::ThreadTarget()
    : _runned(false)
    , _stopOffered(false)
{ }

ThreadTarget::~ThreadTarget()
{
    if (isRunned()) {
        stop();
    }
}

void ThreadTarget::start()
{
    {
        std::lock_guard<std::mutex> lk(_om);
        _stopOffered = false;
    }
    {
        std::lock_guard<std::mutex> lk(_rm);
        _runned = true;
    }

    doStart();

    {
        std::lock_guard<std::mutex> lk(_rm);
        _runned = false;
    }

    _stopped.notify_one();
}

void ThreadTarget::stop()
{
    offerToStop();

    std::unique_lock<std::mutex> lk(_rm);
    _stopped.wait(lk, [&]() {
        return !_runned;
    });

    doStop();
}

bool ThreadTarget::isRunned() const
{
    std::lock_guard<std::mutex> lk(_rm);
    return _runned;
}

void ThreadTarget::run()
{
    start();
}

bool ThreadTarget::isProceed() const
{
    std::lock_guard<std::mutex> lk(_om);
    return !_stopOffered;
}

void ThreadTarget::offerToStop()
{
    {
        std::lock_guard<std::mutex> lk(_om);
        _stopOffered = true;
    }

    _offered.notify_one();
}

} // namespace common
