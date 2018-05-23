/*
 * System.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
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
        throw Poco::RuntimeException("Error set high priority");
    }
}

void System::setCurrentThreadDefaultPriority()
{
    sched_param sched = {0};
    sched.sched_priority = SCHED_OTHER;

    int rc = sched_setscheduler(0, SCHED_OTHER, &sched);
    if (rc) {
        throw Poco::RuntimeException("Error set default priority");
    }
}

} // namespace common
