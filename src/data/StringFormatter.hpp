/*!
 * \file StringFormatter.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 1, 2018
 */

#ifndef STRINGFORMATTER_HPP
#define STRINGFORMATTER_HPP

#include "Formatter.hpp"

namespace data {

/*!
 * \addtogroup data
 * @{
 */

/*!
 * \brief The StringFormatter class.
 */
class StringFormatter : public Formatter {
public:
    inline OutputFormats type() const override;

    std::string format(const StorageValueItems& items) const override;

    std::string format(const StorageValueItemsGroup& group) const override;
};

//
// Inlines
//

OutputFormats StringFormatter::type() const
{
    return OutputFormats::text;
}

/*! @} */

} // namespace data

#endif // STRINGFORMATTER_HPP
