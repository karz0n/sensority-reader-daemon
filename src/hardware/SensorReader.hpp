/*!
 * \file SensorReader.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 18, 2018
 */

#ifndef SENSORREADER_HPP
#define SENSORREADER_HPP

#include <memory>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <thread>

#include "data/Storage.hpp"

namespace hardware {

/*!
 * \addtogroup hardware
 * @{
 */

class SensorReader
{
public:
    using Ptr = std::unique_ptr<SensorReader>;

    SensorReader(data::Storage::Ptr storage);

    /*!
     * \brief Start thread target.
     */
    void start();

    /*!
     * \brief Stop thread target.
     */
    void stop();

    /*!
     * \brief
     * \return
     */
    inline data::Storage& storage();

    /*!
     * \brief
     * \return
     */
    inline const data::Storage& storage() const;

    /*!
     * \brief isRunned
     * \return
     */
    inline bool isRunned() const;

protected:
    /*!
     * \brief
     */
    virtual void run() = 0;

    /*!
     * \brief Return proceed condition state of thread target.
     * \return proceed condition state.
     */
    bool isProceed() const;

    /*!
     * \brief Sleep for specified time duration with termination checking.
     */
    template<typename Rep, typename Period>
    void waitFor(const std::chrono::duration<Rep, Period>& duration)
    {
        std::unique_lock<std::mutex> lk(_om);
        _offer.wait_for(lk, duration, [&]() -> bool {
            return _stopOffered;
        });
    }

    /*!
     * \brief Sleep until specified time point with termination checking.
     */
    template<typename Clock, typename Duration>
    void waitUntil(const std::chrono::time_point<Clock,Duration>& timePoint)
    {
        std::unique_lock<std::mutex> lk(_om);
        _offer.wait_until(lk, timePoint, [&]() -> bool {
            return _stopOffered;
        });
    }

private:
    std::atomic<bool> _stopOffered;
    bool _runned;
    data::Storage::Ptr _storage;
    mutable std::mutex _om;
    std::condition_variable _offer;
    std::thread _thread;
};

//
// Inlines
//

data::Storage& SensorReader::storage()
{
    return *_storage;
}

const data::Storage& SensorReader::storage() const
{
    return *_storage;
}

bool SensorReader::isRunned() const
{
    return _runned;
}

/*! @} */

} // namespace hardware

#endif // SENSORREADER_HPP
