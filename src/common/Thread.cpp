/*
 * Thread.cpp
 *
 *  Created on: May 27, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "Thread.hpp"

namespace common {

Thread::Thread()
{ }

Thread::Thread(Runnable& t)
{
    start(t);
}

Thread::~Thread()
{
    if (isJoinable()) {
        join();
    }
}

void Thread::start(Runnable& target)
{
    _thread = std::thread(&Runnable::run, &target);
}

bool Thread::isJoinable() const
{
    return _thread.joinable();
}

void Thread::join()
{
    _thread.join();
}

} // namespace common
