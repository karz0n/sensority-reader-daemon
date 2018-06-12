/*!
 * \file StringFormatter.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 1, 2018
 */

#ifndef STRINGFORMATTER_HPP
#define STRINGFORMATTER_HPP

#include "Formatter.hpp"

namespace formatter {

/*!
 * \addtogroup formatter
 * @{
 */

/*!
 * \brief The StringFormatter class.
 */
class StringFormatter : public Formatter {
public:
    inline Formats type() const override
    {
        return Formats::text;
    }

    std::string format(const Values& values) const override;
};

/*! @} */

} // namespace formatter

#endif // STRINGFORMATTER_HPP
