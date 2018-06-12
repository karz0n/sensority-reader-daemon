/*!
 * \file ThreadTarget.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date May 27, 2018
 */

#ifndef THREADTARGET_HPP
#define THREADTARGET_HPP

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include "Runnable.hpp"

namespace common {

/*!
 * \addtogroup common
 * @{
 */

/*!
 * \brief The ThreadTarget class.
 */
class ThreadTarget : public Runnable
{
public:
    ThreadTarget();
    ~ThreadTarget() override;

    /*!
     * \brief Start thread target.
     */
    void start();

    /*!
     * \brief Stop thread target.
     */
    void stop();

public:
    bool isRunned() const override final;
    void run() override final;

protected:
    /*!
     * \brief Return proceed condition state of thread target.
     * \return proceed condition state.
     */
    bool isProceed() const;

    /*!
     * \brief Offer thread target to stop.
     * \details Main cycle of thread target should check ThreadTarget::isProceed method.
     */
    void offerToStop();

    /*!
     * Sleep for specified time duration with termination checking.
     */
    template<typename Rep, typename Period>
    void sleepFor(const std::chrono::duration<Rep, Period>& duration)
    {
        std::unique_lock<std::mutex> lk(_om);
        _offered.wait_for(lk, duration, [&]() {
            return _stopOffered;
        });
    }

    /*!
     * Sleep until specified time point with termination checking.
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
    /*!
     * \brief Start method of thread target.
     * \details Must be overridden in derived class.
     */
    virtual void doStart() = 0;

    /*!
     * \brief Stop method of thread target.
     * \details Must be overridden in derived class.
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

/*! @} */

} // namespace common

#endif // THREADTARGET_HPP
