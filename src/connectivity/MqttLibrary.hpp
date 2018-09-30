/*!
 * \file MqttLibrary.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Feb 21, 2018
 */

#ifndef MQTTLIBRARY_HPP
#define MQTTLIBRARY_HPP

#include <string>
#include <memory>

#include "MqttCommon.hpp"
#include "MqttClient.hpp"

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

/*!
 * \brief The MqttLibrary class.
 */
class MqttLibrary final {
public:
    /*!
     * \brief Return single instance of class.
     * \return instance of class.
     */
    static MqttLibrary& instance();

    /*!
     * \brief version
     * \return
     */
    static MqttLibraryVersion version();

    /*!
     * \brief Return init state of library.
     * \return init state value.
     */
    bool isInitialized() const;

    /*!
     * \brief Initialize library.
     */
    void initialize();

    /*!
     * \brief Clear system resources holded by library.
     */
    void cleanup();

    /*!
     * \brief client
     * \param cleanSession
     * \return
     */
    MqttEndpoint::Ptr client(bool cleanSession = true);

    /*!
     * \brief client
     * \param id
     * \param cleanSession
     * \return
     */
    MqttEndpoint::Ptr client(const std::string& id, bool cleanSession = true);

public:
    MqttLibrary(const MqttLibrary&) = delete;
    const MqttLibrary& operator=(const MqttLibrary&) = delete;

private:
    MqttLibrary();  //!< Default ctor.
    ~MqttLibrary(); //!< Default dtor.

private:
    unsigned long _counter;
};

/*! @} */

} // namespace connectivity

#endif // MQTTLIBRARY_HPP
