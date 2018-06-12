/*!
 * \file Thread.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date May 27, 2018
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
