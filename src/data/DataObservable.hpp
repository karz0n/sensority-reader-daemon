/*!
 * \file DataObservable.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Sep 20, 2018
 */

#ifndef DATAOBSERVABLE_HPP
#define DATAOBSERVABLE_HPP

#include <Poco/NotificationCenter.h>

namespace data {

class DataObserver;
class Storage;

/*!
 * \addtogroup data
 * @{
 */

/*!
 *
 */
class DataObservable
{
public:
    /*!
     * \brief inject
     * \param target
     */
    void inject(DataObserver& observer);

    /*!
     * \brief eject
     * \param target
     */
    void eject(DataObserver& observer);

    /*!
     * \brief hasObservers
     */
    bool hasObservers() const;

    /*!
     * \brief countObservers
     * \return
     */
    std::size_t countObservers() const;

protected:
    /*!
     * \brief emitUpdateNotification
     */
    void emitUpdateNotification(Storage& source);

private:
    Poco::NotificationCenter _nc;
};

/*! @} */

} // namespace data

#endif // DATAOBSERVABLE_HPP
