/*!
 * \file FormatterFactory.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date May 27, 2018
 */

#ifndef FORMATTERFACTORY_HPP
#define FORMATTERFACTORY_HPP

#include "Formatter.hpp"

namespace formatter {

/*!
 * \addtogroup formatter
 * @{
 */

/*!
 * \brief The FormatterFactory class.
 * \details Formatter factory which create instance of specific formatter class.
 */
class FormatterFactory
{
public:
    /*!
     * \brief Create instance of specific formatter class.
     * \param format formatter type in string notation.
     * \return instance of specific formatter class.
     */
    static Formatter::Ptr create(const std::string& format);
};

/*! @} */

} // namespace formatter

#endif // FORMATTERFACTORY_HPP
