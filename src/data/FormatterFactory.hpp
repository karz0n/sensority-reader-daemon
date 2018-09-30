/*!
 * \file FormatterFactory.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date May 27, 2018
 */

#ifndef FORMATTERFACTORY_HPP
#define FORMATTERFACTORY_HPP

#include "StorageCommon.hpp"
#include "Formatter.hpp"

namespace data {

/*!
 * \addtogroup data
 * @{
 */

/*!
 * \brief The StorageFormatterFactory class.
 *
 * \details Formatter factory which create instance of specific formatter class.
 */
class FormatterFactory {
public:
    /*!
     * \brief Create instance of specific formatter class.
     *
     * \param format formatter type in string notation.
     *
     * \return instance of specific formatter class.
     */
    static Formatter::Ptr create(OutputFormats format);
};

/*! @} */

} // namespace data

#endif // FORMATTERFACTORY_HPP
