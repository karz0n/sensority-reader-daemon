/*!
 * \file JsonFormatter.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 20, 2018
 */

#ifndef JSONFORMATTER_HPP
#define JSONFORMATTER_HPP

#include "Formatter.hpp"

namespace data {

/*!
 * \addtogroup data
 * @{
 */

/*!
 * \brief The JsonFormatter class.
 */
class JsonFormatter : public Formatter {
public:
    inline OutputFormats type() const override;

    std::string format(const StorageValueItems& items) const override;

    std::string format(const StorageValueItemsGroup& group) const override;
};

//
// Inlines
//

OutputFormats JsonFormatter::type() const
{
    return OutputFormats::json;
}

/*! @} */

} // namespace data

#endif // JSONFORMATTER_HPP
