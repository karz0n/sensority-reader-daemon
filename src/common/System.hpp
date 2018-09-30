/*!
 * \file System.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Feb 21, 2018
 */

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

namespace common {

/*!
 * \addtogroup common
 * @{
 */

/*!
 * \brief The System class.
 */
class System {
public:
    /*!
     * \brief Return true if we are root.
     * \return flag which indicate that we have root access.
     */
    static bool isRoot();

    /*!
     * \brief Set high priority of current thread.
     */
    static void setCurrentThreadHighPriority();

    /*!
     * \brief Set default priority of current thread.
     */
    static void setCurrentThreadDefaultPriority();
};

/*! @} */

} // namespace common

#endif // SYSTEM_HPP
