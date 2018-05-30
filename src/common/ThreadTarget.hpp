/*
 * ThreadTarget.hpp
 *
 *  Created on: May 27, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef THREADTARGET_HPP_
#define THREADTARGET_HPP_

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include <iostream>

#include "Runnable.hpp"

namespace common {

class ThreadTarget : public Runnable
{
public:
    ThreadTarget();
    ~ThreadTarget() override;

    /**
     * @brief start
     */
    void start();

    /**
     * @brief stop target
     */
    void stop();

public:
    bool isRunned() const override;
    void run() override;

protected:
    /**
     * @brief isProceed
     * @return
     */
    bool isProceed() const;

    /**
     * @brief offerToStop
     */
    void offerToStop();

    /**
     * Sleep for specified time duration with termination checking
     */
    template<typename Rep, typename Period>
    void sleepFor(const std::chrono::duration<Rep, Period>& duration)
    {
        std::unique_lock<std::mutex> lk(_om);
        _offered.wait_for(lk, duration, [&]() {
            return _stopOffered;
        });
    }

    /**
     * Sleep until specified time point with termination checking
     */
    template<typename Clock, typename Duration>
    void sleepUntil(const std::chrono::time_point<Clock,Duration>& timePoint)
    {
        std::unique_lock<std::mutex> lk(_om);
        _offered.wait_until(lk, timePoint, [&]() {
            return _stopOffered;
        });
    }

protected:
    /**
     * @brief doStart
     */
    virtual void doStart() = 0;

    /**
     * @brief doStop
     */
    virtual void doStop() = 0;

private:
    bool _runned;
    bool _stopOffered;
    mutable std::mutex _rm;
    mutable std::mutex _om;
    std::condition_variable _stopped;
    std::condition_variable _offered;
};

} // namespace common

#endif // THREADTARGET_HPP_
