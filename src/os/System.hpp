/*
 * System.hpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

/**
 * @brief The System class
 */
class System {
public:
    static bool isRoot();

    static void setCurrentThreadHighPriority();
    static void setCurrentThreadDefaultPriority();
};

#endif /* SYSTEM_HPP_ */
