/*!
 * \file Formattable.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Sep 13, 2018
 */

#include <string>

#include "Formatter.hpp"

#ifndef FORMATTABLE_HPP
#define FORMATTABLE_HPP

namespace data {

/*!
 * \addtogroup data
 * @{
 */

class Formattable {
public:
    /*!
     * \brief format
     * \param formatter
     * \return
     */
    virtual std::string format(const Formatter& formatter) const = 0;
};

/*! @} */

} // namespace data

#endif // FORMATTABLE_HPP
