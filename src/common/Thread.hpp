/*
 * Thread.hpp
 *
 *  Created on: May 27, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <thread>

#include "Runnable.hpp"

namespace common {

class Thread
{
public:
    Thread();
    Thread(Runnable& target);
    virtual ~Thread();

    /**
     * @brief start thread with given target
     */
    void start(Runnable& target);

    /**
     * @brief isJoinable
     * @return
     */
    bool isJoinable() const;

    /**
     * @brief join
     */
    void join();

private:
    std::thread _thread;
};

} // namespace common

#endif // THREAD_HPP_
