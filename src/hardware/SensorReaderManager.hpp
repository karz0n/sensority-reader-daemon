/*!
 * \file SensorReaderManager.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 18, 2018
 */

#ifndef SENSORREADERMANAGER_HPP
#define SENSORREADERMANAGER_HPP

#include <string>
#include <memory>
#include <unordered_map>

#include "SensorReader.hpp"

namespace hardware {

/*!
 * \addtogroup hardware
 * @{
 */

class SensorReaderManager {
public:
    using Ptr = std::unique_ptr<SensorReaderManager>;

    /*!
     * \brief append
     * \param name
     * \param reader
     */
    void append(const std::string& name, SensorReader::Ptr reader);

    /*!
     * \brief remove
     * \param name
     */
    void remove(const std::string& name);

    /*!
     * \brief has
     * \param name
     * \return
     */
    bool has(const std::string& name) const;

    /*!
     * \brief start
     * \param name
     */
    void start(const std::string& name);

    /*!
     * \brief stop
     * \param name
     */
    void stop(const std::string& name);

    /*!
     * \brief startAll
     */
    void startAll();

    /*!
     * \brief stopAll
     */
    void stopAll();

private:
    /* */
    using Readers = std::unordered_map<std::string, SensorReader::Ptr>;

private:
    SensorReader& get(const std::string& name);

private:
    Readers _readers;
};

/*! @} */

} // namespace hardware

#endif // SENSORREADERMANAGER_HPP
