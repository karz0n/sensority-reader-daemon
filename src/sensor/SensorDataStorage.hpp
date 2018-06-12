/*!
 * \file SensorDataStorage.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Feb 28, 2018
 */

#ifndef SENSORDATASTORAGE_HPP
#define SENSORDATASTORAGE_HPP

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <utility>

#include "SensorData.hpp"
#include "SensorReadableData.hpp"

#include "Formatter.hpp"

namespace sensor {

/*!
 * \addtogroup sensor
 * @{
 */

/*!
 * \brief The SensorDataStorage class
 */
class SensorDataStorage : public SensorReadableData {
public:
    using Ptr = std::shared_ptr<SensorDataStorage>;     //!< Type of pointer to the class
    using Clock = std::chrono::steady_clock;            //!< Type of clock
    using TimePoint = std::chrono::time_point<Clock>;   //!< Type of time point

    SensorDataStorage();

    std::string format(const formatter::Formatter& formatter) const override;

    /*!
     * \brief Update storage value with specified pointer to the data.
     * \param data pointer to the object.
     */
    void update(SensorData::Ptr data);

    /*!
     * \brief Return flag which indicate that data storage is empty.
     * \return flag of empties state.
     */
    bool empty() const;

    /*!
     * \brief Return time point of last update.
     * \return time point.
     */
    TimePoint lastUpdate() const;

public:
    /*!
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

    /*!
     * \brief Lock reading of storage.
     * \return The read lock monitor.
     */
    ReadLock lockRead() const;

    /*!
     * \brief Lock writing to storage.
     * \return The write lock monitor.
     */
    WriteLock lockWrite() const;

private:
    mutable std::shared_mutex _mutex;
    SensorData::Ptr _data;
    bool _empty;
    TimePoint _lastUpdate;
};

/*! @} */

} // namespace sensor

#endif // SENSORDATASTORAGE_HPP
