/*
 * System.h
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

/**
 * @brief The System class
 */
class System {
public:
    static bool isRoot();

    static void setCurrentThreadHighPriority();
    static void setCurrentThreadDefaultPriority();
};

#endif /* SYSTEM_H_ */
