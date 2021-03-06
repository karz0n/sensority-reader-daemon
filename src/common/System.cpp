/*!
 * \file System.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Feb 21, 2018
 */

#include "System.hpp"

#include <unistd.h>
#include <sched.h>

#include <Poco/Exception.h>

namespace common {

bool System::isRoot()
{
    return (geteuid() == 0);
}

void System::setCurrentThreadHighPriority()
{
    sched_param sched = {0};
    sched.sched_priority = sched_get_priority_max(SCHED_FIFO);

    int rc = sched_setscheduler(0, SCHED_FIFO, &sched);
    if (rc) {
        throw Poco::RuntimeException("Set high priority failed");
    }
}

void System::setCurrentThreadDefaultPriority()
{
    sched_param sched = {0};
    sched.sched_priority = SCHED_OTHER;

    int rc = sched_setscheduler(0, SCHED_OTHER, &sched);
    if (rc) {
        throw Poco::RuntimeException("Set default priority failed");
    }
}

} // namespace common
