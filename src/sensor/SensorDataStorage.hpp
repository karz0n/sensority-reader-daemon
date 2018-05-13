/*
 * SensorDataStorage.h
 *
 *  Created on: Feb 28, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORDATASTORAGE_H_
#define SENSORDATASTORAGE_H_

#include <memory>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <chrono>

#include "SensorData.hpp"
#include "SensorDataReadable.hpp"

#include "Formatter.hpp"

/**
 * Data storage class
 */
class SensorDataStorage: public SensorDataReadable {
public:
	using Clock = std::chrono::steady_clock;
	using TimePoint = std::chrono::time_point<Clock>;

	SensorDataStorage();

    std::string format(const Formatter& formatter) const override;

    void update(std::unique_ptr<SensorData> data);
	bool empty() const;
	TimePoint lastUpdate() const;

protected:
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
    std::unique_ptr<SensorData> _data;
	bool _empty;
    TimePoint _lastUpdate;
};

#endif /* SENSORDATASTORAGE_H_ */
