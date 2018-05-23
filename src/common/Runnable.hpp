/*
 * Runnable.hpp
 *
 *  Created on: May 14, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef RUNNABLE_HPP_
#define RUNNABLE_HPP_

namespace common {

/**
 * @brief The Runnable class
 */
class Runnable
{
public:
    Runnable() = default;
    virtual ~Runnable() = default;

    virtual void run() = 0;
    virtual bool isRunned() const = 0;
    virtual void shutdown() = 0;
};

} // namespace common

#endif // RUNNABLE_HPP_
