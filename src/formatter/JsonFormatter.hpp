/*!
 * \file JsonFormatter.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 20, 2018
 */

#ifndef JSONFORMATTER_HPP
#define JSONFORMATTER_HPP

#include "Formatter.hpp"

namespace formatter {

/*!
 * \addtogroup formatter
 * @{
 */

/*!
 * \brief The JsonFormatter class.
 */
class JsonFormatter : public Formatter {
public:
    inline Formats type() const override
    {
        return Formats::json;
    }

    std::string format(const Values& values) const override;
};

/*! @} */

} // namespace formatter

#endif // JSONFORMATTER_HPP
