/*
 * SensorDataStorage.hpp
 *
 *  Created on: Feb 28, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORDATASTORAGE_HPP_
#define SENSORDATASTORAGE_HPP_

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <utility>

#include "SensorData.hpp"
#include "SensorReadableData.hpp"

#include "Formatter.hpp"

namespace sensor {

/**
 * Data storage class
 */
class SensorDataStorage : public SensorReadableData {
public:
    using Ptr = std::shared_ptr<SensorDataStorage>;
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    SensorDataStorage();

    std::string format(const formatter::Formatter& formatter) const override;

    void update(SensorData::Ptr data);
    bool empty() const;
    TimePoint lastUpdate() const;

public:
    /**
     * Sensor data storage factory method
     */
    template<typename ...As>
    static Ptr create(As&&... args)
    {
        return std::make_shared<SensorDataStorage>(std::forward<As>(args)...);
    }

private:
    using ReadLock = std::unique_lock<std::shared_mutex>;
    using WriteLock = std::shared_lock<std::shared_mutex>;

    /**
     * @brief Lock reading of storage.
     * @return The read lock monitor.
     */
    ReadLock lockRead() const;

    /**
     * @brief Lock writing to storage.
     * @return The write lock monitor.
     */
    WriteLock lockWrite() const;

private:
    mutable std::shared_mutex _mutex;
    SensorData::Ptr _data;
    bool _empty;
    TimePoint _lastUpdate;
};

} // namespace sensor

#endif /* SENSORDATASTORAGE_HPP_ */
