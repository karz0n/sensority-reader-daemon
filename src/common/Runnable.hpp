/*!
 * \file Runnable.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date May 14, 2018
 */

#ifndef RUNNABLE_HPP
#define RUNNABLE_HPP

namespace common {

/*!
 * \addtogroup common
 * @{
 */

/*!
 * \brief The Runnable class.
 */
class Runnable {
public:
    Runnable() = default;           //!< Default ctor.
    virtual ~Runnable() = default;  //!< Default dtor.

    /*!
     * \brief Return state of object.
     * \details Must be overridden in derived class.
     * \return state of object
     */
    virtual bool isRunned() const = 0;

    /*!
     * \brief Should do main work.
     * \details Must be overridden in derived class.
     */
    virtual void run() = 0;
};

/*! @} */

} // namespace common

#endif // RUNNABLE_HPP
