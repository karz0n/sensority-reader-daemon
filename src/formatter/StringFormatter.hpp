/*
 * StringFormatter.hpp
 *
 *  Created on: Mar 1, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef STRINGFORMATTER_HPP_
#define STRINGFORMATTER_HPP_

#include "Formatter.hpp"

namespace formatter {

/**
 * @brief The StringFormatter class
 */
class StringFormatter : public Formatter {
public:
    inline Formats type() const override;
    std::string format(const Values& values) const override;
};

//
// Inlines
//

Formats StringFormatter::type() const
{
    return Formats::text;
}

} // namespace formatter

#endif /* STRINGFORMATTER_HPP_ */
