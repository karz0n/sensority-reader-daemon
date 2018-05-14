/*
 * StringFormatter.hpp
 *
 *  Created on: Mar 1, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef STRINGFORMATTER_HPP_
#define STRINGFORMATTER_HPP_

#include "Formatter.hpp"

/**
 * @brief The StringFormatter class
 */
class StringFormatter : public Formatter {
public:
    std::string format(const Values& values) const override;
    inline Formats type() const override;
};

//
// Inlines
//

Formats StringFormatter::type() const
{
    return Formats::text;
}

#endif /* STRINGFORMATTER_HPP_ */
