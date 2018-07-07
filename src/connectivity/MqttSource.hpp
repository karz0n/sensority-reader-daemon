/*!
 * \file MqttSource.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jun 17, 2018
 */

#ifndef MQTTSOURCE_HPP
#define MQTTSOURCE_HPP

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

/*!
 * \brief The source of notification class.
 */
class MqttSource
{
public:
    MqttSource();           //!< Default ctor.
    virtual ~MqttSource();  //!< Default dtor.
};

/*! @} */

} // namespace connectivity

#endif // MQTTSOURCE_HPP
