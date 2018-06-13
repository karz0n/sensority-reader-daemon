/*!
 * \file Thread.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date May 27, 2018
 */

#ifndef THREAD_HPP
#define THREAD_HPP

#include <thread>

#include "Runnable.hpp"

namespace common {

/*!
 * \addtogroup common
 * @{
 */

/*!
 * \brief The Thread class.
 * \details Basic thread class for thread.
 */
class Thread {
public:
    Thread();                   //!< Default ctor.
    Thread(Runnable& target);   //!< Construct and start thread using given target.

    virtual ~Thread();

    /*!
     * \brief Start thread with given target.
     * \param target runnable target.
     */
    void start(Runnable& target);

    /*!
     * \brief Return flag of thread possibility to be joined in another thread.
     * \return flag of thread possibility to be joined.
     */
    bool isJoinable() const;

    /*!
     * \brief Join this thread in another thread.
     * \details Blocking calling thread until this thread will not stop.
     */
    void join();

private:
    std::thread _thread;
};

/*! @} */

} // namespace common

#endif // THREAD_HPP
