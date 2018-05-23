/*
 * System.hpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

namespace common {

/**
 * @brief The System class
 */
class System {
public:
    /**
     * @brief Return true if we are root
     * @return flag that indicate root access
     */
    static bool isRoot();

    /**
     * @brief set high priority of current thread
     */
    static void setCurrentThreadHighPriority();

    /**
     * @brief set default priority of current thread
     */
    static void setCurrentThreadDefaultPriority();
};

} // namespace common

#endif /* SYSTEM_HPP_ */
